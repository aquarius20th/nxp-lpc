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
#pragma  once


MBException MBFuncReportSlaveID( UCHAR * pucFrame, USHORT * usLen );

MBException    MBFuncReadInputRegister( UCHAR * pucFrame, USHORT * usLen );

MBException    MBFuncReadHoldingRegister( UCHAR * pucFrame, USHORT * usLen );

MBException    MBFuncWriteHoldingRegister( UCHAR * pucFrame, USHORT * usLen );

MBException    MBFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );

MBException    MBFuncReadCoils( UCHAR * pucFrame, USHORT * usLen );
 
MBException    MBFuncWriteCoil( UCHAR * pucFrame, USHORT * usLen );
 
MBException    MBFuncWriteMultipleCoils( UCHAR * pucFrame, USHORT * usLen );
 
MBException    MBFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen );
 
MBException    MBFuncReadWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
  