#include <rtthread.h>
#include "dm9161.h"

#include <netif/ethernetif.h>
#include "lwipopts.h"
#include "emac_def.h"
#include "applib.h"
#include "iolpc23xx.h" 

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


//�˴���Ҫ��ȷ����Ҫ��Ҫ??????
#define RB_BUFFER_SIZE		8			/* max number of receive buffers */
#define ETH_RX_BUF_SIZE		128

#define TB_BUFFER_SIZE		4
#define ETH_TX_BUF_SIZE		(PBUF_POOL_BUFSIZE)

typedef struct {                        /* RX Descriptor struct              */
	rt_uint32_t Packet;
	rt_uint32_t Ctrl;
} RX_Desc;

typedef struct {                        /* RX Status struct                  */
	rt_uint32_t Info;
	rt_uint32_t HashCRC;
} RX_Stat;

typedef struct {                        /* TX Descriptor struct              */
	rt_uint32_t Packet;
	rt_uint32_t Ctrl;
} TX_Desc;

typedef struct {                        /* TX Status struct                  */
	rt_uint32_t Info;
} TX_Stat;

static            RX_Desc *rb_descriptors ;
static            TX_Desc *tb_descriptors ;

// static  RX_Stat Rx_Stat[NUM_RX_FRAG]; /* Must be 8-Byte alligned   */
// static  TX_Stat Tx_Stat[NUM_TX_FRAG];
static  RX_Stat *Rx_Stat ; /* Must be 8-Byte alligned   */
static  TX_Stat *Tx_Stat ;
static  rt_uint8_t       *RxBufBaseAddr;
static  rt_uint8_t       *TxBufBaseAddr;

#define  EMAC_RX_DESC_BASE_ADDR                (EMAC_RAM_BASE_ADDR)
#define  EMAC_RX_STATUS_BASE_ADDR              (EMAC_RX_DESC_BASE_ADDR   + (NUM_RX_FRAG * sizeof(RX_Desc)))
#define  EMAC_TX_DESC_BASE_ADDR                (EMAC_RX_STATUS_BASE_ADDR + (NUM_RX_FRAG * sizeof(RX_Stat)))
#define  EMAC_TX_STATUS_BASE_ADDR              (EMAC_TX_DESC_BASE_ADDR   + (NUM_TX_FRAG * sizeof(TX_Desc)))
#define  EMAC_RX_BUFF_BASE_ADDR                (EMAC_TX_STATUS_BASE_ADDR + (NUM_TX_FRAG * sizeof(TX_Stat)))
#define  EMAC_TX_BUFF_BASE_ADDR                (EMAC_RX_BUFF_BASE_ADDR   + (NUM_RX_FRAG * ETH_FRAG_SIZE))

/* EMAC local DMA buffers. */
//static rt_uint32_t rx_buf[NUM_RX_FRAG][ETH_FRAG_SIZE>>2];
//static rt_uint32_t tx_buf[NUM_TX_FRAG][ETH_FRAG_SIZE>>2];


static struct rt_lpc24xx_eth lpc24xx_device;

static struct rt_semaphore tx_sem;


//  function added to initialize Rx Descriptors
void RxDescrInit (void)
{
	/* Initialize Receive Descriptor and Status array. */
	unsigned int i = 0;

	rb_descriptors      =  (RX_Desc *)(EMAC_RX_DESC_BASE_ADDR);
 	Rx_Stat            =  (RX_Stat  *)(EMAC_RX_STATUS_BASE_ADDR);
 	RxBufBaseAddr       =  (rt_uint8_t *)(EMAC_RX_BUFF_BASE_ADDR);
 
	for (i = 0; i < NUM_RX_FRAG; i++) 
	{ 
		rb_descriptors[i].Packet  = (rt_uint32_t)(RxBufBaseAddr + (i * ETH_FRAG_SIZE));
		rb_descriptors[i].Ctrl    = RCTRL_INT | (ETH_FRAG_SIZE-1);
		Rx_Stat[i].Info    = 0;
		Rx_Stat[i].HashCRC = 0;
	}

	/* Set EMAC Receive Descriptor Registers. */
	MAC_RXDESCRIPTOR    = (rt_uint32_t)&rb_descriptors[0];
	MAC_RXSTATUS        = (rt_uint32_t)&Rx_Stat[0];
 
	MAC_RXDESCRIPTORNUM = NUM_RX_FRAG-1;

	/* Rx Descriptors Point to 0 */
	MAC_RXCONSUMEINDEX  = 0;
}


//  function added to initialize Tx Descriptors
void TxDescrInit (void) 
{
	unsigned int i;

	tb_descriptors      =  (TX_Desc *)(EMAC_TX_DESC_BASE_ADDR);
	Tx_Stat            =  (TX_Stat  *)(EMAC_TX_STATUS_BASE_ADDR);
	TxBufBaseAddr       =  (rt_uint8_t *)(EMAC_TX_BUFF_BASE_ADDR);

	for (i = 0; i < NUM_TX_FRAG; i++) 
	{
		tb_descriptors[i].Packet =  (rt_uint32_t)(TxBufBaseAddr + (i * ETH_FRAG_SIZE));
		tb_descriptors[i].Ctrl   = 0;
		Tx_Stat[i].Info   = 0;
	}

	/* Set EMAC Transmit Descriptor Registers. */
	MAC_TXDESCRIPTOR    = (rt_uint32_t)&tb_descriptors[0];
	MAC_TXSTATUS        = (rt_uint32_t)&Tx_Stat[0];
	MAC_TXDESCRIPTORNUM = NUM_TX_FRAG-1;

	/* Tx Descriptors Point to 0 */
	MAC_TXPRODUCEINDEX  = 0;
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
	MAC_COMMAND |= CR_RX_EN;
	MAC_MAC1 |= MAC1_REC_EN;
	return;    
}

void EMAC_RxDisable( void )
{
	MAC_COMMAND &= ~CR_RX_EN;
	MAC_MAC1 &= ~MAC1_REC_EN;
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
void nic_isr_handler( void )
{
    rt_uint32_t status   =  (MAC_INTSTATUS & MAC_INTENABLE);

    if (status & INT_RX_DONE) // if receive packet
    {
//        rt_err_t result;

        /* a frame has been received */
        result = eth_device_ready(&(lpc24xx_device.parent));
        RT_ASSERT(result == RT_EOK);
	    MAC_INTCLEAR            = (INT_RX_DONE);                            /* Clear the interrupt flags        */
    }

	if ((status & (INT_RX_OVERRUN)) > 0) 
	{                           /* If a fator Overrun error has occured                     */
		MAC_INTCLEAR            = (INT_RX_OVERRUN);                         /* Clear the overrun interrupt flag                         */
		MAC_COMMAND            |=  COMMAND_RESET_RX;                        /* Soft reset the Rx datapath, this disables the receiver   */
		MAC_COMMAND            |=  COMMAND_RX_EN;                           /* Re-enable the reciever                                   */
		MAC_MAC1               |=  MAC1_REC_EN;                             /* Re-enable the reciever                                   */
	}
}

#define  NET_IF_ADDR_SIZE                                  6    /* 48-bit MAC/net addr size.                            */
#define  NET_IF_ADDR_SIZE_MAC                            NET_IF_ADDR_SIZE

#define  NET_IF_ADDR_BROADCAST                0xFFFFFFFFFFFF
#define  NET_IF_ADDR_BROADCAST_xx                       0xFF    /* ALL broadcast addr octet vals identical.             */
#define  NET_IF_ADDR_BROADCAST_00                       0xFF
#define  NET_IF_ADDR_BROADCAST_01                       0xFF
#define  NET_IF_ADDR_BROADCAST_02                       0xFF
#define  NET_IF_ADDR_BROADCAST_03                       0xFF
#define  NET_IF_ADDR_BROADCAST_04                       0xFF
#define  NET_IF_ADDR_BROADCAST_05                       0xFF
rt_uint8_t   NetIF_MAC_Addr[NET_IF_ADDR_SIZE];      /* NIC's MAC addr.                                      */
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
void SetMacID( )   
{
	MAC_SA0   =  (NetIF_MAC_Addr[5] << 8) |(NetIF_MAC_Addr[4]);                   /* Write the MAC Address, octect 2 and 1 to the EMAC        */
	MAC_SA1   =  (NetIF_MAC_Addr[3] << 8) |(NetIF_MAC_Addr[2]);                   /* Write the MAC Address, octect 4 and 3 to the EMAC        */
	MAC_SA2  =  (NetIF_MAC_Addr[1] << 8) | (NetIF_MAC_Addr[0]);                  /* Write the MAC Address, octect 6 and 5 to the EMAC        */

//	MAC_SA0 = mac_ptr[0]*256+mac_ptr[1];
//	MAC_SA1 = mac_ptr[2]*256+mac_ptr[3];
//	MAC_SA2 = mac_ptr[4]*256+mac_ptr[5];
	//��MAC��ַд��MY����MAC����ID��
}

static  void  AppInitTCPIP (void)
{  
	NetIF_MAC_Addr[0] = 0x3e;
	NetIF_MAC_Addr[1] = 0x50;
	NetIF_MAC_Addr[2] = 0xC2;
	NetIF_MAC_Addr[3] = 0x25;
	NetIF_MAC_Addr[4] = 0x61;
	NetIF_MAC_Addr[5] = 0x39;

// 	err             = Net_Init();                               /* Initialize uC/TCP-IP                                     */
// 
// 	AppNetIP        = NetASCII_Str_to_IP("10.10.1.129",  &err);
// 	AppNetMsk       = NetASCII_Str_to_IP("255.255.255.0", &err);
// 	AppNetGateway   = NetASCII_Str_to_IP("10.10.1.1",   &err);

//	err             = NetIP_CfgAddrThisHost(AppNetIP, AppNetMsk);
//	err             = NetIP_CfgAddrDfltGateway(AppNetGateway);
}
/*********************************************************************************************************
** ��������: phy_hw_init
** ��������: phy_hw_init
**
** ����������  
**
** �䡡��:  void
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��8��8��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void  phy_hw_init (void)
{ /* Configure I/O and the RMII / MII interface pins          */
	PINSEL2             =   0x50150105;	                                /* Selects P1[0,1,4,8,9,10,14,15]                           */
	PINSEL3             =   0x00000005;	                                /* Selects P1[17:16]                                        */
}
/*********************************************************************************************************
** ��������: nic_linkup
** ��������: nic_linkup
**
** ����������  Message from NIC that the ethernet link is up.
**
** �䡡��:  void
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��8��10��
** ��  ע:  WARNING: Called in interruption context most of the time.
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void  nic_linkup (void)
{
	rt_uint32_t  link_speed;
	rt_uint32_t  link_duplex;

	link_speed              =   get_phy_link_speed();                  /* Read the PHY's current link speed                    */
	link_duplex             =   get_phy_link_duplex();                 /* Read the PHY's current link duplex mode              */

	if (link_speed == NET_PHY_SPD_0 || link_duplex == NET_PHY_DUPLEX_UNKNOWN) 
	{   /* Inform the EMAC about the current PHY settings       */
		nic_link_change(NET_PHY_SPD_0, NET_PHY_DUPLEX_UNKNOWN);    
	}
	else
	{                /* Inform the EMAC about the current PHY settings       */
		nic_link_change(link_speed,    link_duplex);  
	}
}
/*********************************************************************************************************
** ��������: nic_linkdown
** ��������: nic_linkdown
**
** ����������  Message from NIC that the ethernet link is down.
**
** �䡡��:  void
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��8��10��
** ��  ע:  WARNING: Called in interruption context most of the time.
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void  nic_linkdown (void)
{
	rt_uint32_t  link_speed;
	rt_uint32_t  link_duplex;

	link_speed              =   get_phy_link_speed();                  /* Read the PHY's current link speed                    */
	link_duplex             =   get_phy_link_duplex();                 /* Read the PHY's current link duplex mode              */

	if (link_speed == NET_PHY_SPD_0 || link_duplex == NET_PHY_DUPLEX_UNKNOWN)
	{    /* Inform the EMAC about the current PHY settings       */
		nic_link_change(NET_PHY_SPD_0, NET_PHY_DUPLEX_UNKNOWN);   
	} 
	else
	{  /* Inform the EMAC about the current PHY settings       */
		nic_link_change(link_speed,    link_duplex);                
	}
}

/* RT-Thread Device Interface */

rt_uint16_t PHYREG[80];
/* ----------------- MCFG bits ---------------- */
#define  MCFG_CLKSEL_DIV4                             0x0000
#define  MCFG_CLKSEL_DIV6                             0x0008
#define  MCFG_CLKSEL_DIV8                             0x000C
#define  MCFG_CLKSEL_DIV10                            0x0010
#define  MCFG_CLKSEL_DIV14                            0x0014
#define  MCFG_CLKSEL_DIV20                            0x0018
#define  MCFG_CLKSEL_DIV28                            0x001C

static  rt_uint8_t        MII_Dividers [7][2] =  {{4,  MCFG_CLKSEL_DIV4},
{6,  MCFG_CLKSEL_DIV6},
{8,  MCFG_CLKSEL_DIV8},
{10, MCFG_CLKSEL_DIV10},
{14, MCFG_CLKSEL_DIV14},
{20, MCFG_CLKSEL_DIV20},
{28, MCFG_CLKSEL_DIV28}};


#define  MAIN_OSC_FRQ              11059200L
#define  IRC_OSC_FRQ               11059200L
#define  RTC_OSC_FRQ                  32768L


rt_uint32_t  BSP_CPU_ClkFreq (void)
{
	rt_uint32_t  msel;
	rt_uint32_t  nsel;
	rt_uint32_t  fin;
	rt_uint32_t  pll_clk_feq;                                    /* When the PLL is enabled, this is Fcco                    */
	rt_uint32_t  clk_div;
	rt_uint32_t  clk_freq;

	switch (CLKSRCSEL & 0x03)
	{                                 /* Determine the current clock source                       */
		case 0:
			fin        =  IRC_OSC_FRQ;
			break;
		case 1:
			fin        =  MAIN_OSC_FRQ;
			break;
		case 2:
			fin        =  RTC_OSC_FRQ;
			break;
		default:
			fin        =  IRC_OSC_FRQ;
			break;
	}

	if ((PLLSTAT & (1 << 25)) > 0) 
	{                                                              /* If the PLL is currently enabled and connected        */
		msel        = (rt_uint32_t)(PLLSTAT & 0x3FFF) + 1;           /* Obtain the PLL multiplier                            */
		nsel        = (rt_uint32_t)((PLLSTAT >>   16) & 0x0F) + 1;   /* Obtain the PLL divider                               */
		pll_clk_feq = (2 * msel * fin / nsel);                      /* Compute the PLL output frequency                     */
	} 
	else
	{
		pll_clk_feq = (fin);                                        /* The PLL is bypassed                                  */
	}

	clk_div         = (rt_uint8_t)(CCLKCFG & 0x0F) + 1;             /* Obtain the CPU core clock divider                    */
	clk_freq        = (rt_uint32_t)(pll_clk_feq / clk_div);          /* Compute the ARM Core clock frequency                 */

	return (clk_freq);
}
 
static void hd_DelayMS(rt_uint32_t ms)
{
	//ִ��11059200����䣬��ʱ3.570S�����ÿms����3097�����
	rt_uint32_t count=3339*ms;
	rt_uint32_t i;
	for (i=0;i<count;i++)
	{
		__asm{ NOP };
	}
}


void  nic_int_init  (void)
{
 	rt_hw_interrupt_install(VIC_ETHERNET, nic_isr_handler, RT_NULL);
	rt_hw_interrupt_umask(VIC_ETHERNET);
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


/* See the header file for descriptions of public functions. */
void lpc24xxether_write_frame(rt_uint8_t *ptr, rt_uint32_t length, rt_bool_t eof)
{
	rt_uint8_t *buf_ptr;
	static rt_uint32_t current_tb_index = 0;
	rt_uint32_t is_last, tx_offset = 0, remain, pdu_length;

	rt_uint32_t TxProduceIndex = MAC_TXPRODUCEINDEX;
	rt_uint32_t TxConsumeIndex = MAC_TXCONSUMEINDEX;	 

	while(tx_offset < length)
	{
		/* check whether buffer is available */
		while( TxConsumeIndex == (TxProduceIndex+1)%NUM_TX_FRAG)
		{	/* no buffer */
			rt_thread_delay(5);
			TxProduceIndex = MAC_TXPRODUCEINDEX;
			TxConsumeIndex = MAC_TXCONSUMEINDEX;
		}

		/* Get the address of the buffer from the descriptor, then copy
		the data into the buffer. */
		current_tb_index = MAC_TXPRODUCEINDEX;
		buf_ptr = (rt_uint8_t *)tb_descriptors[current_tb_index].Packet;

		/* How much can we write to the buffer? */
		remain = length - tx_offset;
		pdu_length = (remain <= ETH_TX_BUF_SIZE)? remain : ETH_TX_BUF_SIZE;

		/* Copy the data into the buffer. */
		rt_memcpy(buf_ptr, &ptr[tx_offset], pdu_length );
		tx_offset += pdu_length;

		/* Is this the last data for the frame? */
		if((eof == RT_TRUE) && ( tx_offset >= length ))
			is_last = RT_TRUE;
		else 
			is_last = RT_FALSE;

		/* Fill out the necessary in the descriptor to get the data sent,
		then move to the next descriptor, wrapping if necessary. */

		if(is_last)
		tb_descriptors[current_tb_index].Ctrl =  (EMAC_TX_DESC_OVERRIDE   |        /* Override the defaults from the MAC internal registers    */
			EMAC_TX_DESC_PAD        |        /* Add padding for frames < 64 bytes                        */
			EMAC_TX_DESC_LAST       |        /* No additional descriptors to follow, this is the last    */
			EMAC_TX_DESC_CRC)       |        /* Append the CRC automatically                             */
			(pdu_length - 1);                       /* Write the size of the frame, starting from 0             */
		else
			tb_descriptors[current_tb_index].Ctrl =  (EMAC_TX_DESC_OVERRIDE   |        /* Override the defaults from the MAC internal registers    */
			EMAC_TX_DESC_PAD        |        /* Add padding for frames < 64 bytes                        */
			EMAC_TX_DESC_CRC)       |        /* Append the CRC automatically                             */
			(pdu_length - 1);               /* Write the size of the frame, starting from 0             */

		MAC_TXPRODUCEINDEX      =   (MAC_TXPRODUCEINDEX + 1) % NUM_TX_FRAG;    /* Increment the produce Ix register, initiate Tx of frame  */
	}
}
/* ethernet device interface */
/*
* Transmit packet.
*/
rt_err_t lpc24xxether_tx( rt_device_t dev, struct pbuf* p)
{
	struct pbuf* q;

	/* lock tx operation */
	rt_sem_take(&tx_sem, RT_WAITING_FOREVER);

	for (q = p; q != NULL; q = q->next)
	{
		if (q->next == RT_NULL)
			lpc24xxether_write_frame(q->payload, q->len, RT_TRUE);
		else
			lpc24xxether_write_frame(q->payload, q->len, RT_FALSE);
	}

	rt_sem_release(&tx_sem);

	return 0;
}

rt_uint16_t get_nic_rx_pkt_size (void)
{
	rt_int16_t   size;
	rt_uint32_t   rxstatus;


	rxstatus        =  Rx_Stat[MAC_RXCONSUMEINDEX].Info;             /* Accquire the status word for this desciptor              */

	rxstatus       &= (RINFO_NO_DESCR    |                       /* Obtain the descriptor error bits                         */
		RINFO_OVERRUN   |
		RINFO_ALIGN_ERR   |
		RINFO_LEN_ERR    |
		RINFO_SYM_ERR    |
		RINFO_CRC_ERR    |
		RINFO_FAIL_FILT);

	if (rxstatus > 0)
	{                                                 /* If any receive errors (except range error) occured       */
		size        =  0;                                               /* then return 0 so upper layer call NetNIC_RxPktDiscard()  */
	}
	else
	{
		size        =  Rx_Stat[MAC_RXCONSUMEINDEX].Info & 0x7FF;     /* Obtain the fragment size from the status struct pointer  */
		size       -=  3;                                               /* +1 since the size is 0 based, -4 to ignore FCS           */
	}

	if (size < 0) 
	{    /* Ensure that the subtraction didnt cause an underflow     */
		size = 0;
	}

	return (size);  /* Return the size of the current frame  */
}

void lpc24xxether_read_frame(rt_uint8_t* ptr, rt_uint32_t section_length, rt_uint32_t total)
{
	static rt_uint8_t* src_ptr;
	register rt_uint32_t buf_remain, section_remain;
	static rt_uint32_t section_read = 0, buf_offset = 0, frame_read = 0;
 
//	rt_uint32_t RxProduceIndex = MAC_RXPRODUCEINDEX;
	rt_uint32_t RxConsumeIndex = MAC_RXCONSUMEINDEX;	 

	if(ptr == RT_NULL)
	{
		/* Reset our state variables ready for the next read from this buffer. */
		src_ptr = (rt_uint8_t *)(rb_descriptors[RxConsumeIndex].Packet );
		frame_read = (rt_uint32_t)0;
		buf_offset = (rt_uint32_t)0;
	}
	else
	{
		/* Loop until we have obtained the required amount of data. */
		section_read = 0;
		while( section_read < section_length )
		{
			buf_remain = (ETH_RX_BUF_SIZE - buf_offset);
			section_remain = section_length - section_read;

			if( section_remain > buf_remain )
			{
				/* more data on section than buffer size */
				rt_memcpy(&ptr[ section_read ], &src_ptr[buf_offset], buf_remain);
				section_read += buf_remain;
				frame_read += buf_remain;

				/* free buffer */
				//rb_descriptors[current_rb_index].Packet &= ~RxDESC_FLAG_OWNSHIP;
				Rx_Stat[MAC_RXCONSUMEINDEX].Info     = 0;                       //Clear status for debugging purposes                      */

				/* move to the next frame. */
				MAC_RXCONSUMEINDEX      = (MAC_RXCONSUMEINDEX + 1) % NUM_RX_FRAG;     

				/* Reset the variables for the new buffer. */
				src_ptr = (rt_uint8_t *)(rb_descriptors[MAC_RXCONSUMEINDEX].Packet );
				buf_offset = 0;
			}
			else
			{
				/* more data on buffer than section size */
				rt_memcpy(&ptr[section_read], &src_ptr[buf_offset], section_remain);
				buf_offset += section_remain;
				section_read += section_remain;
				frame_read += section_remain;

				/* finish this read */
				if((buf_offset >= ETH_RX_BUF_SIZE) || (frame_read >= total))
				{
					/* free buffer */
					Rx_Stat[MAC_RXCONSUMEINDEX].Info     = 0;                       //Clear status for debugging purposes                      */

					/* move to the next frame. */
					MAC_RXCONSUMEINDEX      = (MAC_RXCONSUMEINDEX + 1) % NUM_RX_FRAG;     

					src_ptr = (rt_uint8_t*)(rb_descriptors[MAC_RXCONSUMEINDEX].Packet );
					buf_offset = 0;
				}
			}
		}
	} 
}

struct pbuf *lpc24xxether_rx(rt_device_t dev)
{
	struct pbuf *p = RT_NULL;
 
	rt_uint32_t RxProduceIndex = MAC_RXPRODUCEINDEX;
	rt_uint32_t RxConsumeIndex = MAC_RXCONSUMEINDEX;	 

	struct pbuf* q;
	rt_uint32_t index, pkt_len = 0;

	while(RxProduceIndex == RxConsumeIndex  )
	{ //������Ϊ��
		rt_thread_delay(5);
		RxProduceIndex = MAC_RXPRODUCEINDEX;
		RxConsumeIndex = MAC_RXCONSUMEINDEX;	 
	}
	
 	
	pkt_len = get_nic_rx_pkt_size();
	//�ж�һ�� pkt_len �Ƿ���Ч�������Ч������

		/* first of all, find the frame length */
// 	index = current_rb_index;
// 	while (rb_descriptors[index].Packet & RxDESC_FLAG_OWNSHIP)
// 	{
// 		pkt_len = rb_descriptors[index].Ctrl & RxDESC_STATUS_BUF_SIZE;
// 		if (pkt_len > 0) 
// 			break;
// 
// 		index ++;
// 		if (index > RB_BUFFER_SIZE) index = 0;
// 	}

	if (pkt_len)
	{
		p = pbuf_alloc(PBUF_LINK, pkt_len, PBUF_RAM);
		if(p != RT_NULL)
		{
			lpc24xxether_read_frame(RT_NULL, 0, pkt_len);
			for(q = p; q != RT_NULL; q= q->next)
				lpc24xxether_read_frame(q->payload, q->len, pkt_len);
		}
		else
		{
			rt_kprintf("no memory in pbuf\n");
		}
	}
	return p;
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
  	lpc24xx_device.parent.parent.init		= rt_emac_init;
  	lpc24xx_device.parent.parent.open		= rt_dm9000_open;
  	lpc24xx_device.parent.parent.close		= rt_dm9000_close;
  	lpc24xx_device.parent.parent.read		= rt_dm9000_read;
	lpc24xx_device.parent.parent.write		= rt_dm9000_write;
	lpc24xx_device.parent.parent.control	= rt_dm9000_control;
	lpc24xx_device.parent.parent.private    = RT_NULL;

  	lpc24xx_device.parent.eth_rx			= lpc24xxether_rx;
  	lpc24xx_device.parent.eth_tx			= lpc24xxether_tx;

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
	AppInitTCPIP();
	lpc24xxether_register("E0");	 
}

