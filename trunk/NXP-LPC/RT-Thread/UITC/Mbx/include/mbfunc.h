/****************************************Copyright (c)**************************************************
**                                         
**                                      
**                                      
**
**                           
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名:  
**创   建   人:  
**最后修改日期: 
**描        述:   
**   File: $Id: ,v 1.0 2009/11/15 15:27:16   $
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人:  
** 版  本:  
** 日　期:  
** 描　述: 
**
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 描　述:  
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
  