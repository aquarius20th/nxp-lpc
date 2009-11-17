/****************************************Copyright (c)**************************************************

**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/

#ifndef __MODBUS_H
#define __MODBUS_H

#define  MAX_MB_ADDR   247 
#define	MAX_PDU_DATA_LENGTH		 253
#define	MAX_PDU_LENGTH		 	(MAX_PDU_DATA_LENGTH+1)
#define MAX_ADU_LENGTH  		(MAX_PDU_LENGTH+2)


//֧�ֵ�Modbus������
typedef enum MBX_FUNC
{
	MB_FUNC_NONE                           = 0,
	MB_FUNC_READ_COILS		               = 1,		//01�ţ�������
	MB_FUNC_READ_DISCRETE_INPUTS		   = 2,		//02�ţ�������
	MB_FUNC_READ_HOLDING_REGISTER          = 3,		//03�ţ����Ĵ���
	MB_FUNC_READ_INPUT_REGISTER            = 4,     // ������Ĵ���
	MB_FUNC_WRITE_SINGLE_COIL              = 5,     // д������Ȧ
	MB_FUNC_WRITE_REGISTER                 = 6,     // д�����Ĵ���
	MB_FUNC_DIAG_READ_EXCEPTION         	= 7,	//07�ţ����Լ��쳣
	MB_FUNC_DIAG_DIAGNOSTIC                 = 8,
 	MB_FUNC_DIAG_GET_COM_EVENT_CNT        = 11 ,
	MB_FUNC_DIAG_GET_COM_EVENT_LOG        = 12 ,
    MB_FUNC_WRITE_MULTIPLE_COILS           =15,     // д�����Ȧ
    MB_FUNC_WRITE_MULTIPLE_REGISTERS       =16 ,    // д����Ĵ���
	MB_FUNC_OTHER_REPORT_SLAVEID          =  17 ,
    MB_FUNC_READWRITE_MULTIPLE_REGISTERS   = 23 ,   //��/д����Ĵ���

	MB_FUNC_READ_FILE_RECORD               = 20,    //���ļ���¼
	MB_FUNC_WRITE_FILE_RECORD              = 21,    //д�ļ���¼


	MB_FUNC_MEI                            = 43,    //MEI�ӿ�

	MBX_FUNC_DEVICE_CTRL                     = 66,    //MBX��չ���ܣ��豸����

	MBX_FUNC_READ_FORCEMARK                = 101,  //��ǿ�Ʊ�־
	MBX_FUNC_WRITE_FORCEMARK               = 102,  //дǿ�Ʊ�־


    MB_FUNC_ERROR                         = 128 
}MBX_FUNC;

typedef enum MBX_DEV_CTRL
{
	MBX_CTRL_SET_TIME  = 1,          //��ʱ
	MBX_CTRL_RESET     = 2,          //����
	MBX_CTRL_CLEAR_FLASH = 3,        //�������
	MBX_CTRL_CLEAR_FRAM  = 4         //���FRAM
}MBX_DEV_CTRL;

typedef enum MB_MEI_OBJ_ID
{
	MB_MEI_READ_DEV_VER = 0X80,
	MB_MEI_READ_DN_TM = 0X81,
	MB_MEI_READ_VER_TM = 0X82,
	MB_MEI_READ_CFG_VER = 0X83,
	MB_MEI_READ_FLASH_FCB = 0X84,
	MB_MEI_READ_RAM_FCB = 0X85,
	MB_MEI_READ_FLASHRAM_FCB = 0X86
}MB_MEI_OBJ_ID;

typedef enum MBException
{
	MB_EX_NONE = 0x00,
	MB_EX_ILLEGAL_FUNCTION = 0x01,
	MB_EX_ILLEGAL_DATA_ADDRESS = 0x02,
	MB_EX_ILLEGAL_DATA_VALUE = 0x03,
	MB_EX_SLAVE_DEVICE_FAILURE = 0x04,
	MB_EX_ACKNOWLEDGE = 0x05,
	MB_EX_SLAVE_BUSY = 0x06,
	MB_EX_MEMORY_PARITY_ERROR = 0x08,
	MB_EX_GATEWAY_PATH_FAILED = 0x0A,
	MB_EX_GATEWAY_TGT_FAILED = 0x0B
} MBException;

/*! \ingroup modbus
* \brief Errorcodes used by all function in the protocol stack.
*/
typedef enum MBErrorCode
{
	MB_ENOERR,                  /*!< no error. */
	MB_ENOREG,                  /*!< illegal register address. */
	MB_EINVAL,                  /*!< illegal argument. */
	MB_EPORTERR,                /*!< porting layer error. */
	MB_ENORES,                  /*!< insufficient resources. */
	MB_EIO,                     /*!< I/O error. */
	MB_EILLSTATE,               /*!< protocol stack in illegal state. */
	MB_ETIMEDOUT                /*!< timeout error occurred. */
} MBErrorCode;

/*! \ingroup modbus
* \brief If register should be written or read.
*
* This value is passed to the callback functions which support either
* reading or writing register values. Writing means that the application
* registers should be updated and reading means that the modbus protocol
* stack needs to know the current register values.
*
* \see eMBRegHoldingCB( ), eMBRegCoilsCB( ), eMBRegDiscreteCB( ) and 
*   eMBRegInputCB( ).
*/
typedef enum MbxRWMode
{
	MBX_READ,                /*!< Read register values and pass to protocol stack. */
	MBX_WRITE                /*!< Update register values. */
} MbxRWMode;

 
#define RX_OVERTIME	10000			//1000		����1S��ʱ
#define TX_OVERTIME 10000			//1000      ����1S��ʱ
//ͨѶ��ʱʱ��
#define COMM_OVER_TIME			200
#define COMM_OVER_LTIME			600
 

#define	BROADCAST_ADDRESS	0

 
//�������ж�
//typedef void (*RxEnableFunc)(void);

//��������ж�
//typedef void (*TxEnableFunc)(void);

//��ǰ�Ƿ��ͻ��ǽ����ж� ����TRUE - ����̬
//typedef INT8U (*IsTxEnableFunc)(void);

//�������ݵĺ���
// INT8U * pData Ҫ���͵����� 
// INT16U nLen Ҫ�������ݵĳ���
// ���أ�ʵ�ʷ��ͳ�ȥ�����ݳ���
//typedef INT16U (*CommSend)(INT8U * pData, INT16U nLen);


typedef struct MBX
{
	INT8U  Address;
	INT8U  FuncCode;			//����������	

	INT8U  SubFuncCode;        //�ӹ�����
	INT8U  UartId;              //���ں�

	INT8U Broadcast;           //�㲥����  
	INT8U Pad;


	//����
	INT16U ModbusRxCRC;			//ModbusCRCУ��

	INT8U  TempBuf[MAX_ADU_LENGTH];
	
	/**����**/
	INT8U RxBuff[MAX_ADU_LENGTH];	//���ܻ�����
	INT16U RxLen;					//���ܳ���(PDU+��ַ�ĳ���)������CRC��
	INT16U RxCount;					//���ܼ���

	/**����**/
	INT8U TxBuff[MAX_ADU_LENGTH];	//���ͻ�����
	INT16U TxLen;					//���ͳ���(PDU+��ַ�ĳ���)������CRC��
	INT16U TxCount;					//���ͼ���

	INT32U RxTotalLen;             //���յ��ı��ĵ��ܳ���
	INT32U RxTotoalCnt;            //���յ����ĵ�֡����

	INT32U TxTotalLen;
	INT32U TxTotoalCnt;

	INT32U RxCrcErr;      //CRC�����֡����

	OS_EVENT *pUartRecvSem;   //�б���

	volatile INT32U RxTimer;					//����ʱ�������
	volatile INT32U TxTimer;					//���ͳ�ʱ������
  
	/** ͨѶӲ���ӿں��� **/
//	RxEnableFunc pfnRxEnable;
//	TxEnableFunc pfnTxEnable;
//	IsTxEnableFunc pfnIsTxEnable;
//	CommSend pfnCommSend;
}MBX;

extern INT8U InitMBXTsk( void );
  
//�ں����ж�������ã���Ҫ�����жϳ�ʱ
extern void CommTimerHandle( void  );

//����װ�õ�ַ
void SetDeviceAddr( INT8U Addr );

//�ж��������
// void RcvOneByteInDbg(INT8U c);
// void RcvOneByteInComm(INT8U c);

#endif

