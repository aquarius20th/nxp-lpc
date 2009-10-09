#include <rtthread.h> 

#include <netif/ethernetif.h>
#include "lwipopts.h" 
#include "applib.h"
#include "LPC24xx.h" 
#include "bsp.h"
 

#include "emac.h"
#include "emac_def.h"
#include "dm9161.h"	
#include "dm9161_def.h"

#define  DM9161AE_INIT_AUTO_NEG_RETRIES        3

#define  DM9161AE_OUI                   0x00606E
#define  DM9161AE_VNDR_MDL                  0x08

 
#define MAX_ADDR_LEN 6
struct rt_lpc24xx_eth
{
	/* inherit from ethernet device */
	struct eth_device parent;

	/* interface address info. */
	rt_uint8_t  dev_addr[MAX_ADDR_LEN];			/* hw address	*/
};

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

static  RX_Stat *Rx_Stat ; /* Must be 8-Byte alligned   */
static  TX_Stat *Tx_Stat ;
static  rt_uint8_t       *RxBufBaseAddr;
static  rt_uint8_t       *TxBufBaseAddr;
 
static struct rt_lpc24xx_eth lpc24xx_device;

static struct rt_semaphore tx_sem;


#define  EMAC_RX_DESC_BASE_ADDR                (EMAC_RAM_BASE_ADDR)
#define  EMAC_RX_STATUS_BASE_ADDR              (EMAC_RX_DESC_BASE_ADDR   + (NUM_RX_FRAG * sizeof(RX_Desc)))
#define  EMAC_TX_DESC_BASE_ADDR                (EMAC_RX_STATUS_BASE_ADDR + (NUM_RX_FRAG * sizeof(RX_Stat)))
#define  EMAC_TX_STATUS_BASE_ADDR              (EMAC_TX_DESC_BASE_ADDR   + (NUM_TX_FRAG * sizeof(TX_Desc)))
#define  EMAC_RX_BUFF_BASE_ADDR                (EMAC_TX_STATUS_BASE_ADDR + (NUM_TX_FRAG * sizeof(TX_Stat)))
#define  EMAC_TX_BUFF_BASE_ADDR                (EMAC_RX_BUFF_BASE_ADDR   + (NUM_RX_FRAG * ETH_FRAG_SIZE))

//  function added to initialize Rx Descriptors
void rx_descr_init (void)
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
void tx_descr_init (void) 
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

static  void  rxpkt_discard ( )
{
	MAC_RXCONSUMEINDEX      = (MAC_RXCONSUMEINDEX + 1) % NUM_RX_FRAG;
}
/* interrupt service routine */
void nic_isr_handler(int irqno)
{
	rt_uint32_t status               =  MAC_INTSTATUS;    
 	rt_uint32_t  nRsv =  MAC_RSV;
	rt_uint32_t  nSta =  MAC_STATUS;

	if (status & INT_RX_DONE) // if receive packet
	{
		rt_uint8_t result;
		MAC_INTCLEAR = status;
		/* a frame has been received */
		result = eth_device_ready(&(lpc24xx_device.parent));
		RT_ASSERT(result == RT_EOK);
		if (result != RT_EOK)
		{//�������ʧ��,��ô˵����������,��������,��ô�Ͱ�������ӵ�
			rxpkt_discard();
		}
		MAC_INTCLEAR            = (INT_RX_DONE);                            /* Clear the interrupt flags        */
	}

	/* check for receive overrun */
	if (status & INT_RX_OVERRUN)
	{
		MAC_INTCLEAR = INT_RX_OVERRUN;
		//	eth->rx_overrun++;
		MAC_COMMAND |= CR_RX_RES;
		/* usleep(?); */
		MAC_COMMAND |= CR_RX_EN;
		MAC_MAC1 |= MAC1_REC_EN;
	}
	/* check for transmit underrun */
	if (status & INT_TX_UNDERRUN)
	{
		MAC_INTCLEAR = INT_TX_UNDERRUN;
		//	eth->tx_underrun++;
		MAC_COMMAND |= CR_TX_RES;;
		/* usleep(?); */
		MAC_COMMAND |= CR_TX_EN;
	}

	//???????????
	VICVectAddr = 0;            //interrupt close ֪ͨ�жϿ������жϽ���
}

static  void  updata_mac_addr (void)
{  
	/* Update MAC address */
	lpc24xx_device.dev_addr[0] = 0x00;
	lpc24xx_device.dev_addr[1] = 0x38;
	lpc24xx_device.dev_addr[2] = 0x6c;
	lpc24xx_device.dev_addr[3] = 0xa2;
	lpc24xx_device.dev_addr[4] = 0x45;
	lpc24xx_device.dev_addr[5] = 0x3e; 
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
void  phy_hw_init (void)
{ /* Configure I/O and the RMII / MII interface pins          */
  //	PINSEL2             =   0x50150105;	                                /* Selects P1[0,1,4,8,9,10,14,15]                           */
  //	PINSEL3             =   0x00000005;	                                /* Selects P1[17:16]                                        */
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

#define  MAIN_OSC_FRQ              11059200L
#define  IRC_OSC_FRQ               11059200L
#define  RTC_OSC_FRQ                  32768L
 
rt_uint32_t  bsp_cpu_clk_freq (void)
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
 
void rt_delayms(rt_uint32_t ms)
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

/* RT-Thread Device Interface */

rt_uint32_t  get_cpu_clkfreq (void)
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
  
static rt_err_t rt_lpc24xxether_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t rt_lpc24xxether_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_size_t rt_lpc24xxether_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}

static rt_size_t rt_lpc24xxether_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	rt_set_errno(-RT_ENOSYS);
	return 0;
}
 
static rt_err_t rt_lpc24xxether_control(rt_device_t dev, rt_uint8_t cmd, void *args)
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
 

#define   MIN(x, y)   ((x)   >   (y)   ?   (y)   :   (x)) 
void lpc24xxether_write_frame( struct pbuf* p )
{
	struct pbuf* q;
	rt_uint8_t *pDescBuf = NULL;
	rt_uint8_t *pSrcBuf = NULL;
	rt_uint16_t nTxBufOffset = 0,nDescOffset = 0,nPduLen = 0,nSendLen = 0;

	rt_uint32_t TxProduceIndex = MAC_TXPRODUCEINDEX;
	rt_uint32_t TxConsumeIndex = MAC_TXCONSUMEINDEX;	 

	if (p == NULL)
		return ;
 
	pDescBuf = (rt_uint8_t *)tb_descriptors[TxProduceIndex].Packet;

	for (q = p; q != NULL; q = q->next)
	{
		nTxBufOffset = 0;
		if (q && q->len)
		{
			pSrcBuf = (rt_uint8_t*) q->payload;

			while( nTxBufOffset < q->len )
			{
				nPduLen = MIN(ETH_FRAG_SIZE-nDescOffset,q->len-nTxBufOffset);
				if (nPduLen)
				{
					memcpy(&pDescBuf[nDescOffset], &pSrcBuf[nTxBufOffset], nPduLen );
					nSendLen += nPduLen;

					if (nSendLen >= p->tot_len)
					{
						tb_descriptors[TxProduceIndex].Ctrl =  (EMAC_TX_DESC_OVERRIDE   |        /* Override the defaults from the MAC internal registers    */
							EMAC_TX_DESC_PAD        |        /* Add padding for frames < 64 bytes                        */
							EMAC_TX_DESC_LAST       |        /* No additional descriptors to follow, this is the last    */
							EMAC_TX_DESC_CRC)       |        /* Append the CRC automatically                             */
							(nPduLen + nDescOffset- 1);                       /* Write the size of the frame, starting from 0             */
					}
					else
					{
						tb_descriptors[TxProduceIndex].Ctrl =  (EMAC_TX_DESC_OVERRIDE   |        /* Override the defaults from the MAC internal registers    */
							EMAC_TX_DESC_PAD        |        /* Add padding for frames < 64 bytes                        */
							EMAC_TX_DESC_CRC)       |        /* Append the CRC automatically                             */
							(nPduLen + nDescOffset- 1);                       /* Write the size of the frame, starting from 0             */
					}

					nTxBufOffset += nPduLen;
					nDescOffset += nPduLen;
				
					//����
					if (nDescOffset >= ETH_FRAG_SIZE )
					{
						TxProduceIndex ++;
						if (TxProduceIndex >= NUM_TX_FRAG)
						{
							TxProduceIndex -= NUM_TX_FRAG;
						}
						pDescBuf = (rt_uint8_t *)tb_descriptors[TxProduceIndex].Packet;
					}
					else if (nSendLen >= p->tot_len)
					{
						TxProduceIndex ++;
						if (TxProduceIndex >= NUM_TX_FRAG)
						{
							TxProduceIndex -= NUM_TX_FRAG;
						}
						break;
					}
				}
			}
		}							   
	}
	MAC_TXPRODUCEINDEX = TxProduceIndex;
}
/*
* Transmit packet.
*/ 
 
rt_err_t lpc24xxether_tx( rt_device_t dev, struct pbuf* p)
{
	/* lock tx operation */ 
	rt_sem_take(&tx_sem, RT_WAITING_FOREVER); 
	lpc24xxether_write_frame (p); 
	rt_sem_release(&tx_sem);
	return 0;
}
#if 0
void lpc24xxether_read_frame(rt_uint8_t* ptr, rt_uint32_t section_length, rt_uint32_t total)
{
	rt_uint32_t RxProduceIndex = MAC_RXPRODUCEINDEX;
	rt_uint32_t RxConsumeIndex = MAC_RXCONSUMEINDEX;	 
	 rt_uint8_t* src_ptr   = (rt_uint8_t *)(rb_descriptors[RxConsumeIndex].Packet );
	memcpy(&ptr[ 0 ], &src_ptr[0], section_length);
	
	Rx_Stat[MAC_RXCONSUMEINDEX].Info     = 0;                       //Clear status for debugging purposes                      */

	/* move to the next frame. */
	MAC_RXCONSUMEINDEX      = (MAC_RXCONSUMEINDEX + 1) % NUM_RX_FRAG;     
}
#endif

void lpc24xxether_read_frame(rt_uint8_t* ptr, rt_uint32_t section_length, rt_uint32_t total)
{
	register rt_uint32_t buf_remain, section_remain;
	static rt_uint32_t  buf_offset = 0, frame_read = 0;
	static rt_uint8_t* src_ptr = RT_NULL;
	rt_uint32_t section_read = 0;

	rt_uint32_t RxProduceIndex = MAC_RXPRODUCEINDEX;
	rt_uint32_t RxConsumeIndex = MAC_RXCONSUMEINDEX;	 

	src_ptr = (rt_uint8_t *)(rb_descriptors[RxConsumeIndex].Packet );
	/* Loop until we have obtained the required amount of data. */
	
	while( section_read < section_length )
	{
		buf_remain = (total - buf_offset);
		section_remain = section_length - section_read;

		if( section_remain > buf_remain )
		{//Ŀ��ռ乻��
			/* more data on section than buffer size */
			memcpy(&ptr[ section_read ], &src_ptr[buf_offset], buf_remain);
			section_read += buf_remain;
			frame_read += buf_remain;

			/* free buffer */
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
			memcpy(&ptr[section_read], &src_ptr[buf_offset], section_remain);
			buf_offset += section_remain;
			section_read += section_remain;
			frame_read += section_remain;

			/* finish this read */
			if((frame_read >= total) || (buf_offset >= ETH_FRAG_SIZE))
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


rt_uint16_t get_nic_rx_frame_size (void)
{
	rt_uint16_t     rxconsumeix;
	rt_uint16_t     rxproduceix;
	rt_uint16_t     desc_cnt=0 , i =0;
	rt_uint16_t     rx_frame_size = 0;
	rt_uint32_t   rxstatus;
	rt_uint8_t   flag = RT_FALSE;

	rt_uint32_t  nRsv =  MAC_RSV;
	rt_uint32_t  nSta =  MAC_STATUS;


	rxconsumeix =   MAC_RXCONSUMEINDEX;
	rxproduceix =   MAC_RXPRODUCEINDEX;
	if (rxconsumeix == rxproduceix )
	{
		return rx_frame_size;
	}

	if (rxproduceix < rxconsumeix) 
	{ /* If the produce index has wrapped around                  */
		desc_cnt   =   NUM_RX_FRAG - rxconsumeix + rxproduceix;
	}
	else
	{ /* If consumeix is < produceix, then no wrap around occured */
		desc_cnt   =   rxproduceix - rxconsumeix;	
	}

	for (i = rxconsumeix;  ; i++)
	{
		rxstatus   =  Rx_Stat[i].Info;   
		rxstatus       &= (RINFO_NO_DESCR    |                       /* Obtain the descriptor error bits                         */
			RINFO_OVERRUN    |
			RINFO_ALIGN_ERR  |
			RINFO_LEN_ERR    |
			RINFO_SYM_ERR    |
			RINFO_CRC_ERR    |
			RINFO_FAIL_FILT);

		if (rxstatus > 0)
			break;			 
		else
		{
			rx_frame_size  =  Rx_Stat[i].Info & RINFO_SIZE;
			rx_frame_size  -= 3;

			if (rxstatus | RINFO_LAST_FLAG)
			{//���һ��
				break;
			}				 
		}
		if (rxproduceix > rxconsumeix)
		{
			if (i >= rxproduceix) //��ͷ��
				break;
		}
		else
		{
			if (i >= NUM_RX_FRAG-1)
			{
				i = 0;
				flag = RT_TRUE;
			}
			if (flag && i >= rxproduceix)
				break;		
		}					
	}
	return rx_frame_size;
}

rt_uint8_t  is_pkt_size_valid (rt_uint16_t  size)
{
	rt_uint8_t  valid;

	valid = RT_TRUE;

	if (size  < 60)
	{
		valid = RT_FALSE;
	}

	if (size  > 1514+4) 
	{
		valid = RT_FALSE;
	}

	return (valid);
}

struct pbuf *lpc24xxether_rx(rt_device_t dev)
{	
	struct pbuf *p = RT_NULL;

	rt_uint32_t RxProduceIndex = MAC_RXPRODUCEINDEX;
	rt_uint32_t RxConsumeIndex = MAC_RXCONSUMEINDEX;	 

	struct pbuf* q;
	rt_uint16_t  pkt_len = 0;
	rt_uint16_t  pkt_cnt = 0;
	rt_uint8_t   ret = RT_FALSE;

	if (RxProduceIndex == RxConsumeIndex)
		return RT_NULL;

	pkt_len = get_nic_rx_frame_size();
	//�ж�һ�� pkt_len �Ƿ���Ч�������Ч������
	ret = is_pkt_size_valid(pkt_len);
	if (ret == RT_FALSE)
	{
		rxpkt_discard();
		return NULL;
	}

	//
	if (pkt_len)
	{
		p = pbuf_alloc(PBUF_LINK, pkt_len, PBUF_RAM);
		if(p != RT_NULL && pkt_len == p->len)
		{
			SetLed(1,TRUE);
//			lpc24xxether_read_frame(p->payload, p->len, pkt_len);
 			for(q = p; q != RT_NULL; q= q->next)
 				lpc24xxether_read_frame(q->payload, q->len, pkt_len);
			SetLed(1,FALSE);
		}
		else
		{//����ڴ����벻������ô��Ҫ�����������д����ӵ��������ݰ�
			//rt_kprintf("no memory in pbuf\n");
			rxpkt_discard();		 
		}
	}

	return p;
}
 /*********************************************************************************************************
** ��������: set_mac_id
** ��������: set_mac_id
**
** ����������  ����оƬ�����ַ,�����ַ�Ѿ��洢�ڳ���ռ��� 
**
** �䡡��:  
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
 void set_mac_id( )   
{
	MAC_SA0   =  (lpc24xx_device.dev_addr[5] << 8) |(lpc24xx_device.dev_addr[4]);    /* Write the MAC Address, octect 2 and 1 to the EMAC        */
	MAC_SA1   =  (lpc24xx_device.dev_addr[3] << 8) |(lpc24xx_device.dev_addr[2]);    /* Write the MAC Address, octect 4 and 3 to the EMAC        */
	MAC_SA2  =  (lpc24xx_device.dev_addr[1] << 8) | (lpc24xx_device.dev_addr[0]);    /* Write the MAC Address, octect 6 and 5 to the EMAC        */
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
	lpc24xx_device.parent.parent.init		= rt_lpc24xxether_init;
	lpc24xx_device.parent.parent.open		= rt_lpc24xxether_open;
	lpc24xx_device.parent.parent.close		= rt_lpc24xxether_close;
	lpc24xx_device.parent.parent.read		= rt_lpc24xxether_read;
	lpc24xx_device.parent.parent.write		= rt_lpc24xxether_write;
	lpc24xx_device.parent.parent.control	= rt_lpc24xxether_control;
	lpc24xx_device.parent.parent.private    = RT_NULL;

	lpc24xx_device.parent.eth_rx			= lpc24xxether_rx;
	lpc24xx_device.parent.eth_tx			= lpc24xxether_tx;

	/* Update MAC address */
 	updata_mac_addr();
// 	/* update mac address */
// 	update_mac_address(lpc24xx_device);
 
	rt_sem_init(&tx_sem, "emac", 1, RT_IPC_FLAG_FIFO);
	result = eth_device_init(&(lpc24xx_device.parent), (char*)name);
	RT_ASSERT(result == RT_EOK);
	return RT_EOK;
}


void rt_hw_eth_init(void)
{
	lpc24xxether_register("E0");	 
}

