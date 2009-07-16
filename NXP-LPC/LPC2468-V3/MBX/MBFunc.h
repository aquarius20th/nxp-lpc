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
**
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

#ifndef MB_FUNC_H
#define MB_FUNC_H 

//MBX
#define  MBX_PDU_FUNC_DEVICE_CTRL_LEN    (12)           //��ʱ����PDU�ĳ���

#define  MB_PDU_FUNC_MEI_LEN      (4)  //MEI��PDU���ȹ̶�Ϊ4


/* ----------------------- Defines ------------------------------------------*/
#define MB_SER_PDU_SIZE_MIN     4       /*!< Minimum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_MAX     256     /*!< Maximum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_CRC     2       /*!< Size of CRC field in PDU. */
#define MB_SER_PDU_ADDR_OFF     0       /*!< Offset of slave address in Ser-PDU. */
#define MB_SER_PDU_PDU_OFF      1       /*!< Offset of Modbus-PDU in Ser-PDU. */


//�������Լ�MB�Ĵ���
extern MBException MBFuncReadCoils( INT8U * pucFrame, INT16U * usLen );
//д������Ȧ
extern MBException MBFuncWriteCoil( INT8U * pAduBuf, INT16U * usLen );
//д�����Ȧ
extern MBException MBFuncWriteMultipleCoils( INT8U * pucFrame, INT16U * usLen );
//������
extern MBException MBFuncReadDiscreteInputs( INT8U * pucFrame, INT16U * usLen );
//�������ͼĴ��� AQ MW
extern MBException MBFuncReadHoldingRegister( INT8U * pucFrame, INT16U * usLen );
//��AI
extern MBException MBFuncReadInputRegister( INT8U * pucFrame, INT16U * usLen );

//д�����Ĵ���
extern MBException MBFuncWriteHoldingRegister( INT8U * pAduBuf, INT16U * usLen );
//д����Ĵ���
extern MBException MBFuncWriteMultipleHoldingRegister( INT8U * pucFrame, INT16U * usLen );
//����д����Ĵ���
extern MBException MBFuncReadWriteMultipleHoldingRegister( INT8U * pAduBuf, INT16U * usLen );
//������ǿ�Ʊ�־
extern MBException MBXFuncReadForceMark( INT8U * pAduBuf, INT16U * usLen );
//д�����Ĵ�����ǿ�Ʊ�־
extern MBException MBXFuncWriteForceMark( INT8U * pAduBuf, INT16U * usLen );


extern INT8U IsValidFuncCode( INT8U Code  );

//////////////////////////////////////////////////////////////////////////

extern MBException MBXFuncSetTime( INT8U * pAduBuf, INT16U * usAduLen );

extern MBException MBFuncMEI( INT8U * pAduBuf, INT16U * usAduLen );
//д�ļ�
extern MBException MBXWriteFileRecord( INT8U * pAduBuf, INT16U * usAduLen );
//���ļ�
extern MBException MBXReadFileRecord( INT8U * pAduBuf, INT16U * usAduLen );
//�������ݵ�FLASH
extern MBException MBXWriteFileToFlash( INT8U * pAduBuf, INT16U * usAduLen );

#endif
