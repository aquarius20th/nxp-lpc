#include <rtthread.h>
#include "dm9161.h"

#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "emac.h"
#include "applib.h"
#include "LPC24xx.h"


#define  DM9161AE_INIT_AUTO_NEG_RETRIES        3

#define  DM9161AE_OUI                   0x00606E
#define  DM9161AE_VNDR_MDL                  0x08

INT16U PHYID;
 
#define MAX_ADDR_LEN 6
struct rt_lpc24xx_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};

static struct rt_lpc24xx_eth lpc24xx_device;

static struct rt_semaphore tx_sem;

//  function added to initialize Rx Descriptors
void RxDescrInit (void)
{
	unsigned int i;

	for (i = 0; i < NUM_RX_FRAG; i++)
	{
		RX_DESC_PACKET(i)  = RX_BUF(i);
		RX_DESC_CTRL(i)    = RCTRL_INT | (ETH_FRAG_SIZE-1);
		RX_STAT_INFO(i)    = 0;
		RX_STAT_HASHCRC(i) = 0;
	}

	/* Set EMAC Receive Descriptor Registers. */
	MAC_RXDESCRIPTOR    = RX_DESC_BASE;
	MAC_RXSTATUS        = RX_STAT_BASE;
	MAC_RXDESCRIPTORNUM = NUM_RX_FRAG-1;

	/* Rx Descriptors Point to 0 */
	MAC_RXCONSUMEINDEX  = 0;
}


//  function added to initialize Tx Descriptors
void TxDescrInit (void) 
{
	unsigned int i;

	for (i = 0; i < NUM_TX_FRAG; i++) 
	{
		TX_DESC_PACKET(i) = TX_BUF(i);
		TX_DESC_CTRL(i)   = 0;
		TX_STAT_INFO(i)   = 0;
	}

	/* Set EMAC Transmit Descriptor Registers. */
	MAC_TXDESCRIPTOR    = TX_DESC_BASE;
	MAC_TXSTATUS        = TX_STAT_BASE;
	MAC_TXDESCRIPTORNUM = NUM_TX_FRAG-1;

	/* Tx Descriptors Point to 0 */
	MAC_TXPRODUCEINDEX  = 0;
}

void  NetBSP_DlyMs (INT32U ms)
{
	rt_thread_delay(ms/10);
//	OSTimeDlyHMSM(0, 0, ms / 1000, ms % 1000);
}
/*********************************************************************************************************
** ��������: WritePHY
** ��������: WritePHY
**
** ����������  дPHY�˿�
**
** �䡡��:  INT32U PHYReg     
** �䡡��:  INT32U PHYData
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: EMAC_Init().
**
** ������:  LiJin
** �ա���:  2009��7��28��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
/*********************************************************************************************************
** ��������: Write_PHY
** ��������: Write_PHY
**
** ����������  
**
** �䡡��:  INT32U phyadd   PHY address, normally 0.  
** �䡡��:  INT32S PhyReg   PHY register.
** �䡡��:  INT32S Value    Data to write to PHY register.
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��31��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U Write_PHY (INT32U phyadd,INT32S PhyReg, INT32S Value)
{
	unsigned int tout;

	MAC_MCMD = 0x0000;			        // Issue a Write COMMAND     
	MAC_MADR = (phyadd<<8) | PhyReg;    //[12:8] == PHY addr, [4:0]=0x00(BMCR) register addr
	MAC_MWTD = Value;                   //Write the data to the Management Write Data register

	/* Wait utill operation completed */
	tout = 0;
	for (tout = 0; tout < MII_WR_TOUT; tout++)
	{
		if ((MAC_MIND & 1) == 0)
		{
			return TRUE;
		}
	}
	//��ʱ
	return FALSE;
}
/*********************************************************************************************************
** ��������: ReadPHY
** ��������: ReadPHY
**
** ����������  ��PHY�˿ڶ�ȡ����
**
** �䡡��:  INT16U phyadd      PHY address, normally 0.
** �䡡��:  INT32U PHYReg      PHY register.
**          
** �䡡��:   INT32U  PHY data  MRDD        PHY register data.
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��28��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/ 
INT16U Read_PHY ( INT16U phyadd ,INT8U  PhyReg) 
{
	INT32U tout = 0;

	MAC_MCMD = 0;                     // Clear the Read COMMAND    
	MAC_MADR = (phyadd<<8) | PhyReg;  //[12:8] == PHY addr, [4:0]=0x00(BMCR) register addr 
	MAC_MCMD =  MCMD_READ;            // Issue a Read COMMAND 

	/* Wait until operation completed */
	for (tout = 0; tout < MII_RD_TOUT; tout++) 
	{
		if ((MAC_MIND & MIND_BUSY) == 0) 
		{
			break;
		}
	}
	MAC_MCMD = 0;
	return (MAC_MRDD);
}
/******************************************************************************
** Function name:		EMAC_RxEnable/EMAC_RxDisable
**
** Descriptions:		EMAC RX API modules
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void EMAC_RxEnable( void )
{
	MAC_COMMAND |= 0x01;
	MAC_MAC1 |= 0x01;
	return;    
}

void EMAC_RxDisable( void )
{
	MAC_COMMAND &= ~0x01;
	MAC_MAC1 &= ~0x01;
	return;
}
/******************************************************************************
** Function name:		EMAC_TxEnable/EMAC_TxDisable
**
** Descriptions:		EMAC TX API modules
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void EMAC_TxEnable( void )
{
	MAC_COMMAND |= 0x02;
	return;
}

void EMAC_TxDisable( void )
{
	MAC_COMMAND &= ~0x02;
	return;
}
/* interrupt service routine */
void rt_dm9000_isr(int irqno)
{
    rt_uint32_t status;

    if (status) // if receive packet
    {
        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready(&(lpc24xx_device.parent));
        RT_ASSERT(result == RT_EOK);
    }

    if (status) // if finished packet transmission
    {
    }
}
/*********************************************************************************************************
** ��������: SetMacID
** ��������: SetMacID
**
** ����������  ����оƬ�����ַ,�����ַ�Ѿ��洢�ڳ���ռ��� 
**
** �䡡��:  INT8U * mac_ptr
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetMacID(INT8U * mac_ptr)   
{
	MAC_SA0 = mac_ptr[0]*256+mac_ptr[1];
	MAC_SA1 = mac_ptr[2]*256+mac_ptr[3];
	MAC_SA2 = mac_ptr[4]*256+mac_ptr[5];
	//��MAC��ַд��MY����MAC����ID��
}
/* RT-Thread Device Interface */
/*********************************************************************************************************
** ��������: rt_dm9161_init
** ��������: rt_dm9161_init
**
** ����������  ��оƬ�Ĺ����Ĵ�����������,�����Ĵ������÷��ɲο��ĵ�����оƬ�������ֲ�
**
** �䡡��:  rt_device_t dev
**          
** �䡡��:   rt_err_t
**         
** ȫ�ֱ���:            
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��29��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static rt_err_t rt_dm9161_init(rt_device_t dev)
{
	unsigned int regv,tout,id1,id2 ,i = 0;
	INT32U  tempreg = 0;

	/* Power Up the EMAC controller. */
	PCONP |= 0x40000000;
 	/* Set the PIN to RMII */
	// PINSEL2 &= 0x0fc0ccf0;
	//PINSEL2 |= 0X50151105; //PINSEL2 = 0x50151105;	/* selects P1[0,1,4,8,9,10,14,15] */
	//PINSEL3 &= 0xfffffff0;
	//PINSEL3 |= 0X00000005; //PINSEL3 = 0x00000005;	/* selects P1[17:16] */

// 	i = rMAC_MODULEID;
// 	if(i == OLD_EMAC_MODULE_ID)
// 		PINSEL2 = 0x50151105;	/* selects P1[0,1,4,8,9,10,14,15] */
// 	else

	//�Ƿ���Ҫ����?��ҪӲ������ȷ��?
//	PINSEL2 = 0x50150105;
// 	PINSEL3 = 0x00000005;	/* selects P1[17:16] */

	/* Reset all EMAC internal modules. */
	MAC_MAC1 = MAC1_RES_TX | MAC1_RES_MCS_TX | MAC1_RES_RX | MAC1_RES_MCS_RX | MAC1_SIM_RES | MAC1_SOFT_RES;
	MAC_COMMAND = CR_REG_RES | CR_TX_RES | CR_RX_RES;
	/* A short delay after reset. */
	for (tout = 500; tout; tout--);

	/* Initialize MAC control registers. */
	MAC_MAC1 = MAC1_PASS_ALL;
	MAC_MAC2 = MAC2_CRC_EN | MAC2_PAD_EN;
	MAC_MAXF = ETH_MAX_FLEN;
	MAC_CLRT = CLRT_DEF;
	MAC_IPGR = IPGR_DEF;

	//????
	/* Enable Reduced MII interface. */
	MAC_MCFG = MCFG_CLK_DIV20 | MCFG_RES_MII;
	for (tout = 100; tout; tout--);
	MAC_MCFG = MCFG_CLK_DIV20;

	MAC_COMMAND = CR_RMII | CR_PASS_RUNT_FRM;

	/* Enable Reduced MII interface. */
	MAC_COMMAND = CR_RMII | CR_PASS_RUNT_FRM;

	/* Reset Reduced MII Logic. */
	MAC_SUPP = SUPP_RES_RMII| SUPP_SPEED;
	for (tout = 100; tout; tout--);
	MAC_SUPP = SUPP_SPEED;

	//���濪ʼPHY����
	//  ��λPHYоƬ
	#define EMAC_CFG_PHY_ADDR 0 
	Write_PHY(EMAC_CFG_PHY_ADDR, MII_BMCR, 0x9200 );

	// probe phy address
	for(i=0;i<32;i++)
	{
		PHYID = Read_PHY(i , 2 );
		if(PHYID == 0X0181)
			break;
	}
//	if(i >= 32)
//		while(1);
	//  �ȴ�һ��ָ����ʱ�䣬ʹPHY����




	tempreg = Read_PHY(PHYID, 17 );

	//�жϹ�����10/100 ��˫��/ȫ˫��
	if(tempreg & 0x8000)//100fdx
	{

	}
	else if(tempreg & 0x4000)//100hdx
	{

	}
	else if(tempreg & 0x2000)//10fdx
	{

	}
	else if(tempreg & 0x1000)//10hdx
	{
	}
	else
	{//������

	}



	//����MAC��ַ

	 // Initialize Tx and Rx DMA Descriptors 
	TxDescrInit();
	RxDescrInit();
	/* Receive Broadcast, Unicast ,Multicast and Perfect Match Packets */
	MAC_RXFILTERCTRL = RFC_UCAST_EN |RFC_MCAST_EN | RFC_BCAST_EN | RFC_PERFECT_EN;

	/* Enable EMAC interrupts. */
	MAC_INTENABLE = INT_RX_DONE | INT_TX_DONE;

	/* Reset all interrupts */
	MAC_INTCLEAR  = 0xFFFF;

	/* Enable receive and transmit mode of MAC Ethernet core */
	MAC_COMMAND  |= (CR_RX_EN | CR_TX_EN);
	MAC_MAC1     |= MAC1_REC_EN;


    return RT_EOK;
}

static rt_err_t rt_dm9000_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_dm9000_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_dm9000_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_dm9000_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_err_t rt_dm9000_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	switch(cmd)
	{
	case NIOCTL_GADDR:
		/* get mac address */
		if(args) rt_memcpy(args, lpc24xx_device.dev_addr, 6);
		else return -RT_ERROR;
		break;

	default :
		break;
	}

	return RT_EOK;
}

/* ethernet device interface */
/* transmit packet. */
rt_err_t rt_dm9000_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf* q;
	rt_uint32_t len;
	rt_uint8_t* ptr;

	for (q = p; q != NULL; q = q->next)
	{
		len = q->len;
		ptr = q->payload;

		/* write data to device */
	}

	return RT_EOK;
}

/* reception packet. */
struct pbuf *rt_dm9000_rx(rt_device_t dev)
{
    struct pbuf* p;
	rt_uint32_t len;

    /* init p pointer */
    p = RT_NULL;

    if (1) // if there is packet in device
    {
        /* get one packet length */
        len = 0; // packet length

        /* allocate buffer */
        p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);

        if (p != RT_NULL)
        {
            rt_uint8_t* data;
            struct pbuf* q;

            for (q = p; q != RT_NULL; q= q->next)
            {
                data = q->payload;
                len = q->len;

                /* read data from device */
            }
        }
    }
    else
    {
        /* restore interrupt */
    }

    return p;
}

/*********************************************************************************************************
** ��������: lpc24xxether_register
** ��������: lpc24xxether_register
**
** ����������  ע��MAC�豸
**
** �䡡��:  char * name
**          
** �䡡��:   int
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
int lpc24xxether_register(char *name)
{
	rt_err_t result;

	/* init rt-thread device interface */
	lpc24xx_device.parent.parent.init		= rt_dm9161_init;
	lpc24xx_device.parent.parent.open		= rt_dm9000_open;
	lpc24xx_device.parent.parent.close		= rt_dm9000_close;
	lpc24xx_device.parent.parent.read		= rt_dm9000_read;
	lpc24xx_device.parent.parent.write		= rt_dm9000_write;
	lpc24xx_device.parent.parent.control	= rt_dm9000_control;
	lpc24xx_device.parent.parent.private    = RT_NULL;

	lpc24xx_device.parent.eth_rx			= rt_dm9000_rx;
	lpc24xx_device.parent.eth_tx			= rt_dm9000_tx;

	/* Update MAC address */
// 	lpc24xx_device.dev_addr[0] = 0x1e;
// 	lpc24xx_device.dev_addr[1] = 0x30;
// 	lpc24xx_device.dev_addr[2] = 0x6c;
// 	lpc24xx_device.dev_addr[3] = 0xa2;
// 	lpc24xx_device.dev_addr[4] = 0x45;
// 	lpc24xx_device.dev_addr[5] = 0x5e;
// 	/* update mac address */
// 	update_mac_address(lpc24xx_device);

	rt_sem_init(&tx_sem, "emac", 1, RT_IPC_FLAG_FIFO);
	result = eth_device_init(&(lpc24xx_device.parent), (char*)name);
	RT_ASSERT(result == RT_EOK);
	return RT_EOK;
}


void rt_hw_eth_init()
{
	lpc24xxether_register("E0");	 
}

