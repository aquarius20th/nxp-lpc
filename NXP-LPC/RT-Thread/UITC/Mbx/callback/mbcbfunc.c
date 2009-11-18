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
#include <stdlib.h>
#include <string.h>
#include "mb.h"
#include "MemCNST.h"
#include "MemData.h"
 

#pragma diag_suppress   186
/*********************************************************************************************************
** ��������: MBRegCoilsCB
** ��������: MBRegCoilsCB
**
** ���������� ��ȡDO��MB�����͵ļĴ���
**
** �䡡��:  INT8U * pucRegBuffer
** �䡡��:  INT16U usAddress
** �䡡��:  INT16U usNCoils
** �䡡��:  MBRegisterMode eMode
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBErrorCode MBRegCoilsCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNCoils, MBRegisterMode eMode )
{
	MBErrorCode  Status = MB_ENOERR;
	INT8U offset;
	INT16U i=0 ;
	INT8U  *pByte = pucRegBuffer;
	INT16U         RegIndex = 0;

	if ( (usAddress >= Q_START_ADDR) && (usAddress + usNCoils <= Q_START_ADDR+MAX_Q_CNT ) )
	{
		if (eMode == MB_REG_READ)
		{
			while(i<usNCoils)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// ��Qֵд��һ���ֽ�
				{
					if(i<usNCoils)
					{
						RegIndex = usAddress - Q_START_ADDR + i;
						*pByte |= GetQVal(RegIndex+i+1)<<offset;
					}
				}
				pByte++;
			}
		}
		else if ( eMode == MB_REG_WRITE )
		{//д��ʵҲֻ�ǵ�����Ȧ��
			while(i<usNCoils)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// ��Qֵд��һ���ֽ�
				{
					if(i<usNCoils)
					{
						RegIndex = usAddress - Q_START_ADDR + i;
						*pByte |= GetQVal(RegIndex+i+1)<<offset;
					}
				}
				pByte++;
			}
		}
	}
	else
	{
		Status = MB_ENOREG;
	}
	return Status;
}
/*********************************************************************************************************
** ��������: MBRegDiscreteCB
** ��������: MBRegDiscreteCB
**
** ���������� ��ȡDi
**
** �䡡��:  INT8U * pucRegBuffer
** �䡡��:  INT16U usAddress
** �䡡��:  INT16U usNDiscrete
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBErrorCode MBRegDiscreteCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNDiscrete )
{
	MBErrorCode  Status = MB_ENOERR;
	INT8U offset;
	INT16U i=0 ;
	INT8U  *pByte = pucRegBuffer;
	INT16U  RegIndex = 0;
 
	if ( (usAddress >= I_START_ADDR) && (usAddress + usNDiscrete <= I_START_ADDR+MAX_I_CNT ) )
	{
		while(i<usNDiscrete)
		{
			*pByte = 0;
			for(offset=0;offset<8;offset++,i++)		// ��DIֵд��һ���ֽ�
			{
				if(i<usNDiscrete)
				{
					RegIndex = usAddress - I_START_ADDR + i;
					*pByte |= GetIVal(RegIndex+1)<<offset;
				}
			}
			pByte++;
		}
	}
	return Status;
}
/*********************************************************************************************************
** ��������: MBRegInputCB
** ��������: MBRegInputCB
**
** ���������� ���ڴ��ж�ȡ����Ĵ���AI�Ĳ�ֵ
**
** �䡡��:  INT8U * pucRegBuffer
** �䡡��:  INT16U usAddress
** �䡡��:  INT16U usNRegs
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��16��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBErrorCode MBRegInputCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNRegs )
{
	MBErrorCode    eStatus = MB_ENOERR;
	INT16U         RegIndex = 0;
	INT16U         Value = 0 ;

	if ( (usAddress >= AI_START_ADDR) && (usAddress + usNRegs <= AI_START_ADDR+MAX_AI_CNT ) )
	{
		//iRegIndex��0��ʼ
		RegIndex = ( INT16U )( usAddress - AI_START_ADDR );
		while( usNRegs > 0 )
		{
			Value = GetAIVal(RegIndex+1);

			*pucRegBuffer++ = ( INT8U )( Value >> 8 );
			*pucRegBuffer++ = ( INT8U )( Value & 0xFF );
			RegIndex++;
			usNRegs--;
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBRegHoldingCB
** ��������: MBRegHoldingCB
**
** ���������� �����ͼĴ���MW AQ�����ݶ�д�����ӿ�
**
** �䡡��:  INT8U * pucRegBuffer
** �䡡��:  INT16U usAddress
** �䡡��:  INT16U usNRegs
** �䡡��:  MBRegisterMode eMode
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBErrorCode MBRegHoldingCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNRegs, MBRegisterMode eMode )
{
	MBErrorCode    eStatus = MB_ENOERR;
	INT32U         iRegIndex = 0;
	INT16U         Value = 0;

	if ( (usAddress >= MW_START_ADDR) && (usAddress + usNRegs <= MW_START_ADDR + MAX_MW_CNT) )
	{
		iRegIndex = ( INT32U )( usAddress - MW_START_ADDR );
		if (eMode == MB_REG_READ)
		{
			while( usNRegs > 0 )
			{
				Value = GetMWVal(iRegIndex+1);
				*pucRegBuffer++ = ( INT8U ) ( Value >> 8 );
				*pucRegBuffer++ = ( INT8U ) ( Value & 0xFF );
				iRegIndex++;
				usNRegs--;
			}
		}
		else if ( eMode == MB_REG_WRITE )
		{
			while( usNRegs > 0 )
			{
				SetMWVal(iRegIndex+1,Value);
				Value = GetMWVal(iRegIndex+1);
				*pucRegBuffer++ = ( INT8U ) ( Value >> 8 );
				*pucRegBuffer++ = ( INT8U ) ( Value & 0xFF );
				iRegIndex++;
				usNRegs--;
			}
		}
	}
	else if ( (usAddress >= AQ_START_ADDR) && (usAddress + usNRegs <= AQ_START_ADDR + MAX_AQ_CNT) )
	{
		iRegIndex = ( INT32U )( usAddress - AQ_START_ADDR );
		if (eMode == MB_REG_READ)
		{
			while( usNRegs > 0 )
			{
				Value = GetAQVal(iRegIndex+1);
				*pucRegBuffer++ = ( INT8U ) ( Value >> 8 );
				*pucRegBuffer++ = ( INT8U ) ( Value & 0xFF );
				iRegIndex++;
				usNRegs--;
			}
		}
		else if ( eMode == MB_REG_WRITE )
		{
			while( usNRegs > 0 )
			{
				SetAQVal(iRegIndex+1,Value);
				Value = GetAQVal(iRegIndex+1);
				*pucRegBuffer++ = ( INT8U ) ( Value >> 8 );
				*pucRegBuffer++ = ( INT8U ) ( Value & 0xFF );
				iRegIndex++;
				usNRegs--;
			}
		}
	}
	else
	{
		eStatus = MB_ENOREG;
	}
	return eStatus;
}
