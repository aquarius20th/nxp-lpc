/****************************************Copyright (c)**************************************************
**                                         
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:  
**��   ��   ��:  
**����޸�����: 
**��        ��:   
**   File: $Id: ,v 1.0 2009/11/15 15:27:16   $
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:  
** ��  ��:  
** �ա���:  
** �衡��: 
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:
** �ա���:
** �衡��:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#pragma once


#define	MAX_PDU_DATA_LENGTH		 253
#define	MAX_PDU_LENGTH		 	(MAX_PDU_DATA_LENGTH+1)
#define MAX_ADU_LENGTH  		(MAX_PDU_LENGTH+2)

struct MBX_RTU
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

	
	INT32U RxTimer;					//����ʱ�������
	INT32U TxTimer;					//���ͳ�ʱ������
  
	/** ͨѶӲ���ӿں��� **/
//	RxEnableFunc pfnRxEnable;
//	TxEnableFunc pfnTxEnable;
//	IsTxEnableFunc pfnIsTxEnable;
//	CommSend pfnCommSend;
} ;

typedef struct MBX_RTU CMBExt;

void ModbusMainCycle(CMBExt * pMBX);

void InitMbxRtu( CMBExt *pMBX );
