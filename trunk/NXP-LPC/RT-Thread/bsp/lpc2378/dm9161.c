 


#include <rtthread.h>

#include "applib.h"
#include "dm9161.h"
 

/*********************************************************************************************************
** ��������: get_phy_autoneg_state
** ��������: get_phy_autoneg_state
**
** ����������  Returns state of auto-negotiation
**
** �䡡��:  void
**          
** �䡡��:   rt_uint8_t  State of auto-negociation (FALSE = not completed, TRUE = completed).
**         
** ȫ�ֱ���:  
** ����ģ��:  init
**
** ������:  LiJin
** �ա���:  2009��8��3��
** ��  ע:  If any error is encountered while reading the PHY, this function 
will return Auto Negotiation State = FALSE (incomplete).
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
rt_uint8_t  get_phy_autoneg_state(void)
{
	rt_uint16_t     err = 0;
	rt_uint32_t  reg_val;

	reg_val     = read_phy_ex(PHYID, PHY_REG_BMSR, &err);
	reg_val     = read_phy_ex(PHYID, PHY_REG_BMSR, &err);

	if (err   != NET_PHY_ERR_NONE) 
	{
		reg_val = 0;
	}
	/* DM9161AE register 0x01: Basic Status Register #1      */
	/* BIT 5 Signal the result of the auto negotiation   */  
	if ((reg_val & BMSR_ANEGCOMPLETE) == BMSR_ANEGCOMPLETE)
	{  
		return (RT_TRUE);                                     
	} 
	else 
	{   /* 1 = complete, 0 = incomplete                          */
		return (RT_FALSE);
	}
}
/*********************************************************************************************************
** ��������: get_phy_link_state
** ��������: get_phy_link_state
**
** ����������   Returns state of ethernet link
**
** �䡡��:  void
**          
** �䡡��:   rt_uint8_t  State of ethernet link (FALSE = link down, TRUE = link up).
**         
** ȫ�ֱ���:  
** ����ģ��:  isr
**
** ������:  LiJin
** �ա���:  2009��8��3��
** ��  ע:   If any error is encountered while reading the PHY, this function
will return link state = FALSE.
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
rt_uint8_t  get_phy_link_state (void)
{
	rt_uint16_t     err = 0;
	rt_uint32_t  reg_val;

	/* DM9161AE register 0x01: Basic Status Register #1      */
	/* BIT 2 , Link Status, 1 = linked, 0 = not linked.      */
	reg_val      = read_phy_ex(PHYID, PHY_REG_BMSR, &err);
	reg_val      = read_phy_ex(PHYID, PHY_REG_BMSR, &err);

	if (err   != NET_PHY_ERR_NONE)
	{
		reg_val  = 0;
	}

	reg_val     &= BMSR_LSTATUS;

	if (reg_val == BMSR_LSTATUS)
	{
		return (RT_TRUE);
	} 
	else 
	{
		return (RT_FALSE);
	}
}

/*********************************************************************************************************
** ��������: get_phy_link_speed
** ��������: get_phy_link_speed
**
** ���������� Returns the speed of the current Ethernet link 
**
** �䡡��:  void
**          
** �䡡��:   rt_uint32_t  0 = No Link, 10 = 10mbps, 100 = 100mbps
**         
** ȫ�ֱ���:  
** ����ģ��: init
**
** ������:  LiJin
** �ա���:  2009��8��3��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
rt_uint32_t  get_phy_link_speed (void)
{
	rt_uint32_t  bmsr;
	rt_uint32_t  bmcr;
	rt_uint32_t  lpa;
	rt_uint16_t   err;

	bmsr    = read_phy_ex(PHYID, PHY_REG_BMSR, &err);       /* Get Link Status from PHY status reg. Requires 2 reads    */
	bmsr    = read_phy_ex(PHYID, PHY_REG_BMSR, &err);       /* Get Link Status from PHY status reg. Requires 2 reads    */

	if ((bmsr & BMSR_LSTATUS) == 0)
	{
		return (NET_PHY_SPD_0);                                         /* No link                                                  */
	}

	bmcr    = read_phy_ex(PHYID, PHY_REG_BMCR, &err);       /* Read the PHY Control Register                            */

	if ((bmcr & BMCR_ANENABLE) == BMCR_ANENABLE)
	{	/* If AutoNegotiation is enabled                            */
		if ((bmsr & BMSR_ANEGCOMPLETE) == 0)
		{                          /* If AutoNegotiation is not complete                       */
			return (NET_PHY_SPD_0);       					            /* AutoNegotitation in progress                             */
		}

		lpa = read_phy_ex(PHYID, PHY_REG_ANLPAR, &err);     /* Read the Link Partner Ability Register                   */

		if (((lpa & ANLPAR_100FULL) == ANLPAR_100FULL) || ((lpa & ANLPAR_100HALF) == ANLPAR_100HALF))
		{
			return (NET_PHY_SPD_100);
		} 
		else 
		{
			return (NET_PHY_SPD_10);
		}
	} 
	else
	{  /* Auto-negotiation not enabled, get speed from BMCR        */
		if ((bmcr & BMCR_SPEED100) == BMCR_SPEED100) 
		{
			return (NET_PHY_SPD_100);
		}
		else 
		{
			return (NET_PHY_SPD_10);
		}
	}
}

/*********************************************************************************************************
** ��������: get_phy_link_duplex
** ��������: get_phy_link_duplex
**
** ����������  Returns the duplex mode of the current Ethernet link
**            his probes the Davicom DM9161AE '3.3V Dual-Speed Fast Ethernet Transceiver'
** �䡡��:  void
**          
** �䡡��:   rt_uint32_t  0 = Unknown (Auto-Neg in progress), 1 = Half Duplex, 2 = Full Duplex
**         
** ȫ�ֱ���:  
** ����ģ��: EMAC_Init()
**
** ������:  LiJin
** �ա���:  2009��8��10��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
rt_uint32_t  get_phy_link_duplex (void)
{
	rt_uint32_t  bmcr;
	rt_uint32_t  bmsr;
	rt_uint32_t  lpa;
	rt_uint16_t     err;

	bmsr    = read_phy_ex(PHYID, PHY_REG_BMSR, &err);       /* Get Link Status from PHY status reg. Requires 2 reads    */
	bmsr    = read_phy_ex(PHYID, PHY_REG_BMSR, &err);       /* Get Link Status from PHY status reg. Requires 2 reads    */

	if ((bmsr & BMSR_LSTATUS) == 0)
	{
		return (NET_PHY_DUPLEX_UNKNOWN);   /* No link, return 'Duplex Uknown'                          */
	}

	bmcr    = read_phy_ex(PHYID, PHY_REG_BMCR, &err);       /* Read the PHY Control Register      */

	if ((bmcr & BMCR_ANENABLE) == BMCR_ANENABLE)
	{	/* If AutoNegotiation is enabled   */
		if ((bmsr & BMSR_ANEGCOMPLETE) == 0) 
		{     /* If AutoNegotiation is not complete                       */
			return (NET_PHY_DUPLEX_UNKNOWN);   /* AutoNegotitation in progress       */
		}

		lpa = read_phy_ex(PHYID, PHY_REG_ANLPAR, &err);     /* Read the Link Partner Ability Register                   */

		if (((lpa & ANLPAR_100FULL) == ANLPAR_100FULL) || ((lpa & ANLPAR_10FULL) == ANLPAR_10FULL)) 
		{
			return (NET_PHY_DUPLEX_FULL);
		}
		else 
		{
			return (NET_PHY_DUPLEX_HALF);
		}
	} 
	else
	{  /* Auto-negotiation not enabled, get duplex from BMCR       */
		if ((bmcr & BMCR_FULLDPLX) == BMCR_FULLDPLX)
		{
			return (NET_PHY_DUPLEX_FULL);
		} 
		else
		{
			return (NET_PHY_DUPLEX_HALF);
		}
	}
}

static void  phy_auto_nego  (void)
{
	rt_uint16_t   i;
	rt_uint16_t   reg_val;
	rt_uint8_t  link;
	rt_uint16_t      err;
	rt_uint32_t  tout = 0;

	i               = DM9161AE_INIT_AUTO_NEG_RETRIES;                   /* Set the # of retries before declaring a timeout  */
	link            = get_phy_link_state();                            /* Get the current link state. 1=linked, 0=no link  */

	if (link == RT_FALSE) 
	{
		// #if (!defined(EMAC_CFG_RMII)) || (EMAC_CFG_RMII <= 0)
		// 		reg_val     = NetNIC_PhyRegRd(EMAC_CFG_PHY_ADDR, MII_BMCR, &err);   /* Get current control register value           */
		// 		reg_val    |= DEF_BIT_09;                                       /* Set the auto-negotiation start bit               */
		// 
		// 		NetNIC_PhyRegWr(AT91C_PHY_ADDR, MII_BMCR, reg_val, &err);       /* Initiate auto-negotiation                        */
		// #endif

		do {                                                            /* Do while auto-neg incomplete, or retries expired */
			for (tout = 5000; tout; tout--);
			/* Wait for a while auto-neg to proceed (net_bsp.c) */
			reg_val = read_phy_ex(PHYID, PHY_REG_BMSR, &err);   /* Read the Basic Mode Status Register          */
			reg_val = read_phy_ex(PHYID, PHY_REG_BMSR, &err);   /* Read the Basic Mode Status Register          */
			i--;
		} while (((reg_val & BMSR_LSTATUS) == 0) && (i > 0));           /* While link not established and retries remain    */
	}
} 