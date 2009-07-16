//*------------------------------------------------------------------------------------------------
//* �ļ���				: lib_emac.h
//* ��������			: EMAC����ĺ�����ͷ�ļ�
//* ����    			: ������
//* �汾				: 0.1
//* �������ڡ�ʱ��		: 2006/06/07 10:40
//* ����޸����ڡ�ʱ��	: 
//* �޸�ԭ��			: 
//*------------------------------------------------------------------------------------------------

#ifndef	__lib_emac_h
#define	__lib_emac_h

//*---------------------------------------- �ṹ�弰�궨�� -----------------------------------------

#define	EMAC_MII_PINS		(AT91C_PB8_EMDC         | \
							AT91C_PB9_EMDIO         | \
							AT91C_PB2_ETX0          | \
							AT91C_PB3_ETX1          | \
							AT91C_PB10_ETX2         | \
							AT91C_PB11_ETX3         | \
							AT91C_PB1_ETXEN         | \
							AT91C_PB0_ETXCK_EREFCK  | \
							AT91C_PB15_ERXDV_ECRSDV | \
							AT91C_PB5_ERX0			| \
							AT91C_PB6_ERX1			| \
							AT91C_PB13_ERX2			| \
							AT91C_PB14_ERX3			| \
							AT91C_PB17_ERXCK		| \
							AT91C_PB16_ECOL			| \
							AT91C_PB4_ECRS			| \
							AT91C_PB7_ERXER)
							
//* PHYоƬ��ַ
#define	PHY_ADDR			0x01

//* PHYоƬRTL8201��ID��
#define	PHY_ID_RTL8201		0x82010000
										
#define	PHY_REG_ID1			0x02		//* PHY��ʶ�Ĵ���1
#define	PHY_REG_ID2			0x03		//* PHY��ʶ�Ĵ���2

#define	PHY_REG_BMSR		0x01		//* ����ģʽ״̬�Ĵ���
#define	PHY_REG_ANLPAR		0x05		//* �Զ�Э�����ӷ������Ĵ���

//* PHY�Ĵ���λ����
#define	PHY_BMSR_LINKESTABLISHED	((INT16U)(1 << 2))	//* �Ѿ���������Ч���ӣ�����ģʽ״̬�Ĵ�����
#define	PHY_BMSR_AUTONEGEND			((INT16U)(1 << 5))	//* �Զ�Э���Ѿ�����������ģʽ״̬�Ĵ�����
#define	PHY_ANLPAR_100TXFD			((INT16U)(1 << 8))	//* ���ӷ�֧��100Base-TXȫ˫��
#define	PHY_ANLPAR_100TX			((INT16U)(1 << 7))	//* ���ӷ�֧��100Base-TX
#define	PHY_ANLPAR_10TFD			((INT16U)(1 << 6))	//* ���ӷ�֧��10Base-Tȫ˫��

#define	EMAC_NCFGR_SPD_FD_MASK		0xFFFFFFFC			//* �������üĴ������ٶȺ�˫��λ������

#define	NB_RX_BUFS					32					//* ���ջ���������
#define	ETH_RX_BUF_SIZE				128					//* EMAC�����ֲ�涨���ջ�������ռ128�ֽڴ�С��128 * 32���ջ�������4096�ֽ�

#define	NB_TX_BUFS					16					//* ���ͻ���������
#define	ETH_TX_BUF_SIZE				256					//* ���ͻ�������С

/* ���ջ�������������־λ��״̬λ�궨�� */
#define	RxDESC_FLAG_WARP			0x00000002			//* ��ǽ��ջ������������б��е����һ��������
#define	RxDESC_FLAG_OWNSHIP			0x00000001			//* ��ǽ��ջ�����Ϊ��������

/* ���ͻ�����������״̬��Ϣ�궨�� */
#define	TxDESC_STATUS_LAST_BUF		((INT32U)(1 << 15))	//* ֡�����һ��������
#define	TxDESC_STATUS_BUF_SIZE		((INT32U)0x000007FF)//* ��������������
#define	TxDESC_STATUS_WRAP			((INT32U)(1 << 30))	//* ���һ��������

//* ���ջ�����������
#define	EMAC_RxB_ADDR_MASK			0xFFFFFFFC			//* ���ջ�������������ַ����
typedef struct{
	INT32U u32RxBAddrAndFlag;
	union
	{
		INT32U u32Status;
		struct {
			INT32U bitLen					:12;
			INT32U bitRxBOffset				:2;
			INT32U bitStartOfFrm			:1;
			INT32U bitEndOfFrm				:1;
			INT32U bitCFI					:1;
			INT32U bitVLANPrio				:3;
			INT32U bitPrioTag				:1;
			INT32U bitVLANTag				:1;
			INT32U bitTypeID				:1;
			INT32U bitSA4Match				:1;
			INT32U bitSA3Match				:1;
			INT32U bitSA2Match				:1;
			INT32U bitSA1Match				:1;
			INT32U bitRsrved0				:1;
			INT32U bitExtAddrMatch			:1;
			INT32U bitUniCastHashMatch		:1;
			INT32U bitMultiCastHashMatch	:1;
			INT32U bitIsBroadCastAddr		:1;
		}bstStatus;		
	}uStatus;
}AT91S_RxBDescriptor, *AT91PS_RxBDescriptor;

//* ���ͻ����������� 
typedef struct{
	INT32U u32TxBAddr;
	union
	{
		INT32U u32Status;
		struct {
			INT32U bitLen			:11;
			INT32U bitRsrved0		:4;
			INT32U bitIsLastBuf		:1;
			INT32U bitIsNoCRC		:1;
			INT32U bitRsrved1		:10;
			INT32U bitIsBExhausted	:1;
			INT32U bitIsTxUnderrun	:1;
			INT32U bitTxError		:1;
			INT32U bitIsWrap		:1;
			INT32U bitIsUsed		:1;
		}bstStatus;		
	}uStatus;
}AT91S_TxBDescriptor, *AT91PS_TxBDescriptor;
										
//* ʹ��EMAC�������ݽӿ�
#define	macEnableMDI()								\
{													\
	AT91C_BASE_EMAC->EMAC_NCR |= AT91C_EMAC_MPE;	\
}

//* ��ֹEMAC�������ݽӿ�
#define	macDisableMDI()								\
{													\
	AT91C_BASE_EMAC->EMAC_NCR &= ~AT91C_EMAC_MPE;	\
}
//*-------------------------------------------- ԭ������ -----------------------------------------
extern void EMACInit(void);
extern INT16U GetInputPacketLen(void);
extern void EMACReadPacket(INT8S *pbTo, INT16U u16SegmentLen, BOOLEAN blIsLastPbuf);
extern BOOLEAN EMACSendPacket(INT8S *pbFrom, INT32U u32Length, BOOLEAN blIsEndOfFrame);
#endif