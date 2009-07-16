//*------------------------------------------------------------------------------------------------
//* �ļ���				: lib_emac.c
//* ��������			: EMAC����ĺ�����
//* ����    			: ������
//* �汾				: 0.1
//* �������ڡ�ʱ��		: 2006/10/08 10:25
//* ����޸����ڡ�ʱ��	: 
//* �޸�ԭ��			: 
//*------------------------------------------------------------------------------------------------
//*------------------------------------------ ͷ�ļ� ----------------------------------------------
#include "includes.h"
 
#include	"../include/lwip/opt.h"
#include	"emac.h"
//*------------------------------------- �������������� -------------------------------------------
__align(8) static volatile AT91S_RxBDescriptor __staRxBDescriptors[NB_RX_BUFS];	//* ���ջ���������������
__align(4) static volatile INT8S baRxBufs[NB_RX_BUFS][ETH_RX_BUF_SIZE];			//* ���ջ�����

__align(8) static volatile AT91S_TxBDescriptor __staTxBDescriptors[NB_TX_BUFS];	//* ���ͻ���������������
static INT8S baTxBufs[NB_TX_BUFS][ETH_TX_BUF_SIZE];								//* ���ͻ�����

static INT32S	__s32IdxToReset;												//* EMAC���ͻ��������з���λ������

//* ����Ҫ��ȡ�Ľ��ջ�����������λ��
static INT16U	__u16CurRxBIdx;
static INT8S	*__pbFrom;

static INT16U	__u16TotalLenInRxBToRead;										//* EMAC���ջ��������Ѿ����˶����ֽڵ�����
static INT16U 	__u16TxBIndex;		                                            //* ����ʹ�õķ��ͻ�����������������
//*-------------------------------------- ����ԭ������ --------------------------------------------
//*================================================================================================
//*����������������������������������������������������
//*================================================================================================
//*------------------------------------------------------------------------------------------------
//* �������� : __ResetPHY
//* �������� : ��λPHYоƬ��ʹPHYоƬ����UTPģʽ
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
static void __ResetPHY(void)
{
	//* PHY���ϵ��λ�ڼ���Ҫ����RXER/FXEN���ţ�24�ţ�����������״̬��ѡ����UTPģʽ���ǹ���ģʽ��ÿ��PIO
	//*	���߶���������һ���������裬���������ϵ������ŵ��߼���ƽΪ�ߣ������ͻ�ʹ��PHY�����˹���ģʽ������
	//* ��ҪUTPģʽ��Ҳ����PHY�ϵ��λ�ڼ����������״̬Ϊ�ͣ���������������ֹ�ÿ��ߵ��ڲ��������裬Ȼ��
	//* �ٸ�λPHYоƬ��ʹ�����UTPģʽ
//	AT91C_BASE_PIOB->PIO_PPUDR = AT91C_PB7_ERXER;
		
	//* ��λPHYоƬ��RTL8201BL�������ֲ�Ҫ�����ά������10ms�ĵ͵�ƽ����������Ϊ2��(8 + 1)�η���SCK���ڣ�
	//* ʱ��Ϊ15.621ms
//	AT91C_BASE_RSTC->RSTC_RMR = 0xA5000000 | (0x08 << 8);
//	AT91C_BASE_RSTC->RSTC_RCR = 0xA5000000 | AT91C_RSTC_EXTRST;

	//* �ȴ�NRST���Żָ�Ϊ�ߵ�ƽ
//	while(!(AT91C_BASE_RSTC->RSTC_RSR & AT91C_RSTC_NRSTL));
}
//*------------------------------------------------------------------------------------------------
//* �������� : __HandlePHY
//* �������� : ��PHY���ж�д����
//* ��ڲ��� : <u8RegAddr>[in]     ָ����PHY���ĸ��Ĵ������ж�д
//*			 :  <pu16Data>[in/out] ָ��������ݵ�ָ�롣���ڶ��������ַ�����ȡ�����ݣ�����д����Ҫд��
//*			 :                     �Ĵ���������
//*			 :  <blIsRead>[in]     �Ƿ��Ƕ������������������д����
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
static void __HandlePHY(INT8U u8RegAddr, INT16U *pu16Data, BOOLEAN blIsRead)
{
	INT32U	__u32HandleVal;	
#if 0
	
	if(blIsRead)
	{
		__u32HandleVal = (0x01 << 30) 
						| (0x02 << 28) 
						| (PHY_ADDR << 23) 
						| (u8RegAddr << 18) 
						| (0x02 << 16);
	}
	else
	{
		__u32HandleVal = (0x01 << 30) 
						| (0x01 << 28) 
						| (PHY_ADDR << 23) 
						| (u8RegAddr << 18) 
						| (0x02 << 16) 
						| (*pu16Data & 0xFFFF);
	}
		
	AT91C_BASE_EMAC->EMAC_MAN = __u32HandleVal;
	while(!(AT91C_BASE_EMAC->EMAC_NSR & AT91C_EMAC_IDLE));		
	if(blIsRead)
		*pu16Data = AT91C_BASE_EMAC->EMAC_MAN & 0x0000FFFF;

#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __CheckPHYID
//* �������� : ���PHY ID�Ƿ�Ϊ0x82010000��������������PHY��û�о������߳��ֹ��ϣ�������һֱ��ѯֱ����ȷ
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
static void __CheckPHYID(void)
{
	INT32U		__u32PHYID;
	INT8U		__u8DelaySeconds = 0;
 #if 0
	macEnableMDI()
	{
		while(OS_TRUE)	
		{
			__HandlePHY(PHY_REG_ID1, (INT16U*)&__u32PHYID, OS_TRUE);
			__HandlePHY(PHY_REG_ID2, ((INT16U*)&__u32PHYID)+1, OS_TRUE);
			if(__u32PHYID == PHY_ID_RTL8201)
				break;
			else
			{
				__ResetPHY();
				if(__u8DelaySeconds < 15)
					__u8DelaySeconds++;
				OSTimeDlyHMSM(0, 0, __u8DelaySeconds, 0);
			}
		}
	}	
	macDisableMDI()
  #endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __ilWaitLinkEstablished
//* �������� : �ȴ�PHY����ʵ�ʵ�������·
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
__inline void __ilWaitLinkEstablished(void)
{
	INT16U		__u16HandleData;
	INT8U		__u8DelaySeconds = 0;
#if 0	
	while(OS_TRUE)
	{
		__HandlePHY(PHY_REG_BMSR, &__u16HandleData, OS_TRUE);
		if(__u16HandleData & PHY_BMSR_LINKESTABLISHED)
			break;
		else
		{
			__ResetPHY();
			if(__u8DelaySeconds < 15)
				__u8DelaySeconds++;
			OSTimeDlyHMSM(0, 0, __u8DelaySeconds, 0);
		}
	}
#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __ilWaitAutoNegEnd
//* �������� : �ȴ�PHY�Զ�Э�̽���
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
__inline void __ilWaitAutoNegEnd(void)
{
	INT16U		__u16HandleData = 0;
#if 0
	do{
		if(__u16HandleData & PHY_BMSR_AUTONEGEND)
			break;
		else
		{
			__HandlePHY(PHY_REG_BMSR, &__u16HandleData, OS_TRUE);
			OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}while(OS_TRUE);
#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __SetupLinkSpeedAndDuplex
//* �������� : ��PHY��ȡ�Զ�Э�̵Ľ��������EMAC�������·�ٶȺ͵�˫����ʽ��ע�⣬�ú��������������������
//*          : ��ִ��ֱ�����óɹ�
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
static void __SetupLinkSpeedAndDuplex(void)
{
	INT16U		__u16HandleData;
	INT32U		__u32SpdAndFD = 0x00000000;
#if 0
	macEnableMDI()
	{
		__ilWaitLinkEstablished();
		
		__ilWaitAutoNegEnd();
		
		//* ���Э�̵Ľ��
		__HandlePHY(PHY_REG_ANLPAR, &__u16HandleData, OS_TRUE);
		//* ��������
		if((__u16HandleData & PHY_ANLPAR_100TX) || (__u16HandleData & PHY_ANLPAR_100TXFD))
			__u32SpdAndFD = AT91C_EMAC_SPD;
		//* ������˫����ʽ
		if((__u16HandleData & PHY_ANLPAR_100TXFD) || (__u16HandleData & PHY_ANLPAR_10TFD))
			__u32SpdAndFD |= AT91C_EMAC_FD;
		
		//* ����·�ٶȺ͵�˫����ʽ���ý�EMAC���������üĴ���
		AT91C_BASE_EMAC->EMAC_NCFGR = (AT91C_BASE_EMAC->EMAC_NCFGR & EMAC_NCFGR_SPD_FD_MASK) | __u32SpdAndFD;
	}
	macDisableMDI()
#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __InitDescriptorsForRxBAndTxB
//* �������� : ��ʼ�����պͷ��ͻ�������������ʹÿ��������ָ����ȷ�Ļ�������ַ��Ȼ���������׵�ַд�����ָ
//*			 : ��Ĵ���
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
static void __InitDescriptorsForRxBAndTxB(void)
{
	INT32S		i;
#if 0	
	//* �����ջ�������ַ��䵽������������
	for(i=0; i<NB_RX_BUFS; i++)
		__staRxBDescriptors[i].u32RxBAddrAndFlag = (int)baRxBufs[i];
	//* ��λ���һ����������������Wrapλ
	__staRxBDescriptors[NB_RX_BUFS - 1].u32RxBAddrAndFlag |= RxDESC_FLAG_WARP;
	
	
	//* �����ͻ�������ַ��䵽������������
	for(i=0; i<NB_TX_BUFS; i++)
	{
		__staTxBDescriptors[i].u32TxBAddr = (int)baTxBufs[i];
		//* ������������Ϊ�������У����������ֲᣬ��λΪ0��ʾ���������ΪEMAC����
		__staTxBDescriptors[i].uStatus.bstStatus.bitIsUsed = 1;
	}
	//* ��λ���ͻ������Ľ���λ��Wrap��
	__staTxBDescriptors[NB_TX_BUFS - 1].uStatus.bstStatus.bitIsWrap = 1;
	
	//* �������������׵�ַд����պͷ��Ͷ���ָ��Ĵ���
	AT91C_BASE_EMAC->EMAC_RBQP = (INT32U)__staRxBDescriptors;
	AT91C_BASE_EMAC->EMAC_TBQP = (INT32U)__staTxBDescriptors;
	
	//* ��ʼ���뻺����������ص�˽�о�̬����
	__s32IdxToReset = 0;
	__u16CurRxBIdx = 0;
	__u16TotalLenInRxBToRead = 0;
	__u16TxBIndex = 0;
#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : __ilResetTxBDescriptors
//* �������� : ��λ���ͻ�������������Usedλ��ʹ���ܹ�������ʹ��
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
__inline void __ilResetTxBDescriptors(void)
{	
	//* ����EMAC�����ֲᣬEMAC�ڷ�����Ϻ����λ֡�ĵ�һ����������������Usedλ������������ֻ����λ������
	//* ��������
#if 0
	if(__staTxBDescriptors[__s32IdxToReset].uStatus.bstStatus.bitIsUsed)
	{
		while(!__staTxBDescriptors[__s32IdxToReset].uStatus.bstStatus.bitIsLastBuf)
		{
			__s32IdxToReset++;
			if(__s32IdxToReset >= NB_TX_BUFS)
				__s32IdxToReset = 0;
				
			__staTxBDescriptors[__s32IdxToReset].uStatus.bstStatus.bitIsUsed = 1;
		}
		
		__s32IdxToReset++;
		
		if(__s32IdxToReset >= NB_TX_BUFS)
			__s32IdxToReset = 0;
	}
	else;
 #endif 
}
//*------------------------------------------------------------------------------------------------
//* �������� : irqEMACISR
//* �������� : EMAC���ͺͽ��ս����жϴ�����
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void irqEMACISR(void)
{
#if 0
	extern HANDLER hEthernetInput;
	INT32U	__u32IntStatus, __u32ReceiveStatus;

	//* �ڶ�ȡʱ�ж�״̬�Ĵ���λ�ᱻ���
	__u32IntStatus = AT91C_BASE_EMAC->EMAC_ISR;
	
	//* ��������׺��Եĵط���ֻ�ж�ȡRSR�Ĵ�����EMAC�жϴ��������дEOICR�Ĵ���֮����������
	__u32ReceiveStatus = AT91C_BASE_EMAC->EMAC_RSR;
		
	if((__u32IntStatus & AT91C_EMAC_RCOMP) || (__u32ReceiveStatus & AT91C_EMAC_REC))
	{
		//* ��EMAC�����̷߳����ź�
		OSSemPost(hEthernetInput);
			
		//* ���REC��Frame Received��λ
		AT91C_BASE_EMAC->EMAC_RSR = AT91C_EMAC_REC;
	}

	if(__u32IntStatus & AT91C_EMAC_TCOMP)
	{
		//* ��λ���ͻ�������������Usedλʹ��Ϊ��������
		__ilResetTxBDescriptors();
		AT91C_BASE_EMAC->EMAC_TSR = AT91C_EMAC_COMP;
	}
#endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : EMACInit
//* �������� : ��ʼ��EMAC����PHY��MII���ߡ�EMAC����ģʽ�������ã����ý��պͷ��ͻ�����������������
//*			 : EMAC���պͷ����ж�
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void EMACInit(void)
{
	extern HANDLER hEthernetInput;
	
#if OS_CRITICAL_METHOD == 3                     
    OS_CPU_SR  		cpu_sr = 0;
#endif	

	//* ��λPHYоƬ��ʹ�����UTPģʽ
	__ResetPHY();
	
	//* �ȴ�һ��ָ����ʱ�䣬ʹPHY����
	OSTimeDlyHMSM(0, 0, 3, 0);
#if 0
	//* ����PIOB����Ϊ����A���ţ���EMAC���ţ�����ֹPIOB���ƣ���Ϊ�������
	AT91C_BASE_PIOB->PIO_ASR = EMAC_MII_PINS;
	AT91C_BASE_PIOB->PIO_PDR = EMAC_MII_PINS;
	
	//* ��Ϊû��ʹ��ETXER���������ｫ������Ϊ��PIO����
	AT91C_BASE_PIOB->PIO_PER = AT91C_PB12_ETXER;
	AT91C_BASE_PIOB->PIO_ODR = AT91C_PB12_ETXER;
	
	//* ����MDCʱ�ӷ�Ƶ��
	AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_CLK_HCLK_32;
	
	//* ���PHY ID�Ƿ�Ϊ0x82010000��������������PHY��û�о������߳��ֹ��ϣ�������һֱ��ѯֱ����ȷ
	__CheckPHYID();
	
	//* ��PHY��ȡ�Զ�Э�̵Ľ��������EMAC�������·�ٶȺ͵�˫����ʽ��ע�⣬�ú����������������������ִ��
	//* ֱ�����óɹ�
	__SetupLinkSpeedAndDuplex();
	
	//* ������������ʹ�õ��ź�������uCOS�����ñ�֤�ź���������߼����ܹ��ٷְٽ����ɹ�
	hEthernetInput = OSSemCreate(0);
	
	//* ��ʼ�����պͷ��ͻ�������������ʹÿ��������ָ����ȷ�Ļ�������ַ
	__InitDescriptorsForRxBAndTxB();
	
	//* ����EMACΪMIIģʽ��ʹ��EMACʱ��
	AT91C_BASE_EMAC->EMAC_USRIO = AT91C_EMAC_CLKEN;
	
	//* �������״̬�Ĵ���
	AT91C_BASE_EMAC->EMAC_RSR = AT91C_EMAC_OVR | AT91C_EMAC_REC | AT91C_EMAC_BNA;
	
	//* ����������Ч֡�����ջ������������չ㲥֡��������FCS�ֶ�
	AT91C_BASE_EMAC->EMAC_NCFGR |= AT91C_EMAC_CAF | AT91C_EMAC_NBC | AT91C_EMAC_DRFCS;
	
	//* ����EMAC��ַ
	AT91C_BASE_EMAC->EMAC_SA1L = 0xBC | ((INT32U)(0x20 << 8)) | ((INT32U)(0x06 << 16)) | ((INT32U)(0x09 << 24));
	AT91C_BASE_EMAC->EMAC_SA1H = 0x30 | ((INT32U)(0x11 << 8));
	
	//* ����EMAC�ж�
	OS_ENTER_CRITICAL()
	{
		//* ���ͺͽ��ս����ж�ʹ��
		AT91C_BASE_EMAC->EMAC_IER = AT91C_EMAC_RCOMP | AT91C_EMAC_TCOMP;
		
		AT91F_AIC_ConfigureIt(AT91C_BASE_AIC, AT91C_ID_EMAC, AT91C_AIC_PRIOR_HIGHEST, AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL, irqEMACISR);
	    AT91C_BASE_AIC->AIC_IECR = 0x01 << AT91C_ID_EMAC;
	}
	OS_EXIT_CRITICAL()
	
	//* ��󣬽��ա�����ʹ��
	AT91C_BASE_EMAC->EMAC_NCR |= AT91C_EMAC_TE | AT91C_EMAC_RE;
 #endif
}
//*------------------------------------------------------------------------------------------------
//* �������� : GetInputPacketLen
//* �������� : ��ȡ�������Ϣ���ĳ���
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
INT16U GetInputPacketLen(void)
{
	INT16U		__u16Idx, __u16Len = 0;
#if 0	
	//* ������Ƭ֡���ж�������֡ͷλδ����λ
	while((__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag & RxDESC_FLAG_OWNSHIP) 
			&& !__staRxBDescriptors[__u16CurRxBIdx].uStatus.bstStatus.bitStartOfFrm)
	{
		//* �ͷ����������
		__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag &= (~RxDESC_FLAG_OWNSHIP);		
		__u16CurRxBIdx++;
		if(__u16CurRxBIdx >= NB_RX_BUFS)
		{
			__u16CurRxBIdx = 0;
		}
	}
	
	__u16Idx = __u16CurRxBIdx;
	
	//* ֻ�����һ���������ű���֡�ĳ��ȣ�������Ϊ0
	while((__staRxBDescriptors[__u16Idx].u32RxBAddrAndFlag & RxDESC_FLAG_OWNSHIP))
	{
		__u16Len = __staRxBDescriptors[__u16Idx].uStatus.bstStatus.bitLen;
		if(__u16Len > 0)
			break;
			
		__u16Idx++;
		if(__u16Idx >= NB_RX_BUFS)
			__u16Idx = 0;
	}
	
	//* ������Ϣ����ȡλ��
	__pbFrom = (INT8S*)(__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag & EMAC_RxB_ADDR_MASK);
#endif 	
	return __u16Len;
}
//*------------------------------------------------------------------------------------------------
//* �������� : EMACReadPacket
//* �������� : ��EMAC��ȡ��Ϣ���������pbuf�����ú���Ҫ��PBUF_POOL_BUFSIZE���ڻ���ڽ��ջ��������������
//*			 : ��������������������򵥡�ע�⣬�ڵ��øú���֮ǰ�����ȵ���GetInputPacketLen()������������
//*			 : �ܻ�ȡ��ȷ�Ķ�ȡλ��
//* ��ڲ��� :          <pbTo>[in] ָ��pbuf��ָ��
//*			 : <u16SegmentLen>[in] pbuf����Ҫ�洢��ʵ�����ݳ��ȣ���Ϊ������pbufʱ��pbuf_alloc()�Ѿ�����
//*			 :                     ʵ�ʵ�֡������ָ���˶��pbuf��ɵ�pbuf���У���pstPbuf->len�򱣴���
//*			 :                     ÿ��pbuf��Ҫ�洢�����ݡ����仰˵pbuf���е����һ��pbuf��len�ֶγ���Ӧ
//*			 :                     ��С�ڻ����PBUF_POOL_BUFSIZE����ǰ���pbuf�����PBUF_POOL_BUFSIZE
//*			 :  <blIsLastPbuf>[in] �Ƿ������һ��Pbuf
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void EMACReadPacket(INT8S *pbTo, INT16U u16SegmentLen, BOOLEAN blIsLastPbuf)
{		
	INT16U			__u16TotalLenToRead = 0, 					//* �Ѿ���ȡ��pbuf�����ֽ���
					__u16RemainLenToRead,						//* ��ʣ�����ֽ�û�ж�ȡ��pbuf��
					__u16RemainLenInRxBToRead;					//* EMAC���ջ������л�ʣ�¶����ֽ�û�ж�ȡ					
	BOOLEAN			__blIsNotRelease;							//* �Ƿ��Ѿ������ͷŸ�EMAC
	
	
	/* ע�⣬���뱣֤PBUF_POOL_BUFSIZE���ڻ���ڽ��ջ����� */
#if 0	
	while(__u16TotalLenToRead < u16SegmentLen)
	{
		__u16RemainLenInRxBToRead = ETH_RX_BUF_SIZE - __u16TotalLenInRxBToRead;
		__u16RemainLenToRead = u16SegmentLen - __u16TotalLenToRead;
		if(__u16RemainLenToRead >= __u16RemainLenInRxBToRead)
		{
			memcpy(pbTo + __u16TotalLenToRead, __pbFrom, __u16RemainLenInRxBToRead);
			__u16TotalLenToRead += __u16RemainLenInRxBToRead;
			__u16TotalLenInRxBToRead = 0;
			
			//* �����ջ������黹��EMAC
			__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag &= (~RxDESC_FLAG_OWNSHIP);
			__blIsNotRelease = OS_FALSE;
			
			//* �����������������ȡָ��
			__u16CurRxBIdx++;
			if(__u16CurRxBIdx >= NB_RX_BUFS)
				__u16CurRxBIdx = 0;
				
			__pbFrom = (INT8S*)(__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag & EMAC_RxB_ADDR_MASK);
		}
		else
		{
			memcpy(pbTo + __u16TotalLenToRead, __pbFrom, __u16RemainLenToRead);
			__u16TotalLenToRead += __u16RemainLenToRead;
			__u16TotalLenInRxBToRead += __u16RemainLenToRead;
			
			__pbFrom = __pbFrom + __u16TotalLenInRxBToRead;						
			__blIsNotRelease = OS_TRUE;
		}					
	}
	
	if(blIsLastPbuf)
	{
		//* �����ջ������黹��EMAC���������ǡ����PBUF_POOL_BUFSIZE�������������ݰ�����û�б�Ҫ��һ���ͷţ���Ϊ���Ѿ���
		//* ���汻�ͷ�
		if(__blIsNotRelease)
		{
			__staRxBDescriptors[__u16CurRxBIdx].u32RxBAddrAndFlag &= (~RxDESC_FLAG_OWNSHIP);
			__u16CurRxBIdx++;
			if(__u16CurRxBIdx >= NB_RX_BUFS)
				__u16CurRxBIdx = 0;
		}
			
		__u16TotalLenInRxBToRead = 0;
	}
#endif			
}
//*------------------------------------------------------------------------------------------------
//* �������� : EMACSendPacket
//* �������� : ��low_level_output()�������ã����ʵ�ʵ����ݷ��͡�
//* ��ڲ��� :         <pbFrom>[in] ָ��pbuf�����ݵ�ָ��
//*			 :      <u32Length>[in] pbuf�е����ݳ���
//*			 : <blIsEndOfFrame>[in] �Ƿ���pbuf���е����һ����Ҳ����֡β
//* ���ڲ��� : ����޷��������ڴ��򷵻�ERR_MEM���ɹ��򷵻�ERR_OK
//*------------------------------------------------------------------------------------------------
BOOLEAN EMACSendPacket(INT8S *pbFrom, INT32U u32Length, BOOLEAN blIsEndOfFrame)
{
	INT32U 			__u32TotalLenToWrite = 0, __u32CurLenToWrite, __u32LenRemainToWrite, __u32IsLastBuf;
	
	INT32S 			i;
	INT8S			*__pbBuf;
	
#if OS_CRITICAL_METHOD == 3                     
    OS_CPU_SR  		cpu_sr = 0;
#endif	

#if 0
	//* ���Ҫ���͵����ݳ��ȴ���һ�����ͻ�����������Ҫ����Щ���ݷָ��������������з���
	while(__u32TotalLenToWrite < u32Length)
	{
		//* �ȴ����������ã���ȴ�3����
		i = 0;
		while(!__staTxBDescriptors[__u16TxBIndex].uStatus.bstStatus.bitIsUsed)
		{
			//* ����Ѿ�����ȴ�ʱ����Ȼû�п��û�����������������
			if(i > 300)
				return OS_FALSE;
			
			OSTimeDly(1);
			i++;
		}
	
		OS_ENTER_CRITICAL()
		{
			//* ���������л�û�������ַ��Ȼ������ݸ��Ƶ�������
			__pbBuf = (INT8S*)__staTxBDescriptors[__u16TxBIndex].u32TxBAddr;
			
			//* �����򻺳���д������ݳ���
			__u32LenRemainToWrite = u32Length - __u32TotalLenToWrite;
			if(__u32LenRemainToWrite > ETH_TX_BUF_SIZE)
				__u32CurLenToWrite = ETH_TX_BUF_SIZE;
			else
				__u32CurLenToWrite = __u32LenRemainToWrite;
			
			//* ��pbuf�е����ݸ��Ƶ����ͻ�����
			memcpy(__pbBuf, &(pbFrom[__u32TotalLenToWrite]), __u32CurLenToWrite);
			__u32TotalLenToWrite += __u32CurLenToWrite;
			
			//* �����Ƿ����Ѿ�����pbuf����ĩβ����������ǵ�ǰʹ�õĻ�����Ϊ���һ��������
			if(blIsEndOfFrame && (__u32TotalLenToWrite >= u32Length))
			{
				__u32IsLastBuf = TxDESC_STATUS_LAST_BUF;
			}
			else
				__u32IsLastBuf = 0;
	
			//* ��䵱ǰ�����������������е�����ʵ�ʳ��ȡ����һ����������ǡ�WRAPλ�����ȷʵ�����һ����������
			if(__u16TxBIndex >= (NB_TX_BUFS-1))
			{				
				__staTxBDescriptors[__u16TxBIndex].uStatus.u32Status = (__u32CurLenToWrite & TxDESC_STATUS_BUF_SIZE)
																		| __u32IsLastBuf
																		| TxDESC_STATUS_WRAP;
				__u16TxBIndex = 0;
			}
			else
			{
				__staTxBDescriptors[__u16TxBIndex].uStatus.u32Status = (__u32CurLenToWrite & TxDESC_STATUS_BUF_SIZE)
																		| __u32IsLastBuf;
				__u16TxBIndex++;
			}
	
			//* ����Ѿ�����pbuf����ĩβ����������
			if(__u32IsLastBuf)
				AT91C_BASE_EMAC->EMAC_NCR |= AT91C_EMAC_TSTART;
		}
		OS_EXIT_CRITICAL()
	}
#endif
	return OS_TRUE;
}