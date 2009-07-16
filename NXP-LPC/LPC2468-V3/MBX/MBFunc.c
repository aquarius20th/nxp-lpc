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
#include <stdlib.h>
#include <string.h>
#include "includes.h"
#include "MemData.h"
#include "MODBUS.h"
#include "MBFunc.h"
#include "FlashApiWrapper.h"
#include "ram.h"
#include "hd_drive.h"
#include "ClockMgr.h"
 

/*!
* Constants which defines the format of a modbus frame. The example is
* shown for a Modbus RTU/ASCII frame. Note that the Modbus PDU is not
* dependent on the underlying transport.
*
* <code>
* <------------------------ MODBUS SERIAL LINE PDU (1) ------------------->
*              <----------- MODBUS PDU (1') ---------------->
*  +-----------+---------------+----------------------------+-------------+
*  | Address   | Function Code | Data                       | CRC/LRC     |
*  +-----------+---------------+----------------------------+-------------+
*  |           |               |                                   |
* (2)        (3/2')           (3')                                (4)
*
* (1)  ... MB_SER_PDU_SIZE_MAX = 256
* (2)  ... MB_SER_PDU_ADDR_OFF = 0
* (3)  ... MB_SER_PDU_PDU_OFF  = 1
* (4)  ... MB_SER_PDU_SIZE_CRC = 2
*
* (1') ... MB_PDU_SIZE_MAX     = 253
* (2') ... MB_PDU_FUNC_OFF     = 0
* (3') ... MB_PDU_DATA_OFF     = 1
* </code>
*/

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_SIZE_MAX     253 /*!< Maximum size of a PDU. */
#define MB_PDU_SIZE_MIN     1   /*!< Function Code */
#define MB_PDU_FUNC_OFF     0   /*!< Offset of function code in PDU. */
#define MB_PDU_DATA_OFF     1   /*!< Offset for response data in PDU. */

//PDU�ı��Ķ���
/* -----------------------Coil Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_COILCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_COILCNT_MAX        ( 0x07D0 )

#define MB_PDU_FUNC_WRITE_ADDR_OFF          ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_WRITE_VALUE_OFF         ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_SIZE              ( 4 )

#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF      ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_WRITE_MUL_COILCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF   ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF    ( MB_PDU_DATA_OFF + 5 )
#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN      ( 5 )
#define MB_PDU_FUNC_WRITE_MUL_COILCNT_MAX   ( 0x07B0 )

//#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF          ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF        ( MB_PDU_DATA_OFF + 5 )
//#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN          ( 5 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x0078 )

/* -----------------------InputReg Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_REGCNT_OFF         ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX         ( 0x007D )

#define MB_PDU_FUNC_READ_RSP_BYTECNT_OFF    ( MB_PDU_DATA_OFF )

/* ----------------------- DiscreteInputs Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_DISCCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_DISCCNT_MAX        ( 0x07D0 )

#define MB_PDU_FUNC_READWRITE_READ_ADDR_OFF     ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF    ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF  ( MB_PDU_DATA_OFF + 6 )
#define MB_PDU_FUNC_READWRITE_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 8 )
#define MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF  ( MB_PDU_DATA_OFF + 9 )
#define MB_PDU_FUNC_READWRITE_SIZE_MIN          ( 9 )


#define MBX_PDU_FUNC_DN_FILE_SIZE_MIN          ( 8 )
#define MBX_PDU_FUNC_UP_FILE_SIZE_MIN          ( 9 )


#define MBX_PDU_FUNC_READ_FM_SIZE              ( 7 )
#define MBX_PDU_WRITE_READ_FM_SIZE              ( 6 )


/*********************************************************************************************************
** ��������: IsValidFuncCode
** ��������: IsValidFuncCode
**
** ���������� �Ƿ�Ϊ��Ч�Ĺ�����
**
** �䡡��:  INT8U Code
**          
** �䡡��:  INT8U
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
INT8U IsValidFuncCode( INT8U Code  )
{
	if (Code == MB_FUNC_NONE || Code >=MB_FUNC_ERROR )
		return FALSE;

	switch ( Code )
	{
	case MB_FUNC_READ_COILS://01�ţ�������
		return TRUE;
	case MB_FUNC_READ_DISCRETE_INPUTS://02�ţ�������
		return TRUE;
	case MB_FUNC_READ_HOLDING_REGISTER://03�ţ����Ĵ���
		return TRUE;
	case MB_FUNC_READ_INPUT_REGISTER: // ������Ĵ���
		return TRUE;
	case MB_FUNC_WRITE_SINGLE_COIL:   // д������Ȧ
		return TRUE;
	case MB_FUNC_WRITE_REGISTER:   // д�����Ĵ���
		return TRUE;
	case MB_FUNC_DIAG_READ_EXCEPTION:   // ���Լ��쳣
		return TRUE;
	case MB_FUNC_DIAG_DIAGNOSTIC:   // 0X8
		return TRUE;
	case MB_FUNC_DIAG_GET_COM_EVENT_CNT:   // 11
		return TRUE;
	case MB_FUNC_DIAG_GET_COM_EVENT_LOG:   // 12
		return TRUE;
	case MB_FUNC_WRITE_MULTIPLE_COILS:   // д�����Ȧ
		return TRUE;
	case MB_FUNC_WRITE_MULTIPLE_REGISTERS:   // д����Ĵ���
		return TRUE;
	case MB_FUNC_OTHER_REPORT_SLAVEID:   // 17
		return TRUE;
	case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:   // 23
		return TRUE;
	default:
		return FALSE; 	 
	}

	return FALSE;
}   
     
static MBException MBError2Exception( MBErrorCode eErrorCode )
{
	MBException    eStatus;

	switch ( eErrorCode )
	{
	case MB_ENOERR:
		eStatus = MB_EX_NONE;
		break;
	case MB_ENOREG:
		eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
		break;
	case MB_ETIMEDOUT:
		eStatus = MB_EX_SLAVE_BUSY;
		break;
	default:
		eStatus = MB_EX_SLAVE_DEVICE_FAILURE;
		break;
	}

	return eStatus;
}

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
static MBErrorCode MBRegCoilsCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNCoils, MbxRWMode eMode )
{
	MBErrorCode  Status = MB_ENOERR;
	INT8U offset;
	INT16U i=0 ;
	INT8U  *pByte = pucRegBuffer;
	INT16U         RegIndex = 0;

	if ( (usAddress >= Q_START_ADDR) && (usAddress + usNCoils <= Q_START_ADDR+MAX_Q_CNT ) )
	{
		if (eMode == MBX_READ)
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
		else if ( eMode == MBX_WRITE )
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
static MBErrorCode MBRegDiscreteCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNDiscrete )
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
static MBErrorCode MBRegInputCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNRegs )
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
static MBErrorCode MBRegHoldingCB( INT8U * pucRegBuffer, INT16U usAddress, INT16U usNRegs, MbxRWMode eMode )
{
	MBErrorCode    eStatus = MB_ENOERR;
	INT32U         iRegIndex = 0;
	INT16U         Value = 0;

	if ( (usAddress >= MW_START_ADDR) && (usAddress + usNRegs <= MW_START_ADDR + MAX_MW_CNT) )
	{
		iRegIndex = ( INT32U )( usAddress - MW_START_ADDR );
		if (eMode == MBX_READ)
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
		else if ( eMode == MBX_WRITE )
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
		if (eMode == MBX_READ)
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
		else if ( eMode == MBX_WRITE )
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
/*********************************************************************************************************
** ��������: MBXReadForceMarkCB
** ��������: MBXReadForceMarkCB
**
** ���������� ��ͨ����ǿ�Ʊ�־
**
** �䡡��:  INT8U * pucRegBuffer
** �䡡��:  INT8U RegType
** �䡡��:  INT16U usStart
** �䡡��:  INT16U usCnt
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��11��24��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static MBErrorCode MBXReadForceMarkCB( INT8U * pucRegBuffer,INT8U RegType, INT16U usStart, INT16U usCnt )
{
	MBErrorCode  Status = MB_ENOERR;
	INT8U offset;
 	INT8U  *pByte = pucRegBuffer;
	INT16U  RegIndex = 0;
	INT16U  i = 0;

	if (RegType == I_TYPE)
	{
		if (usStart + usCnt <= (MAX_I_CNT ))
		{
			i = 0;
			while(i<usCnt)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// �� ֵд��һ���ֽ�
				{
					RegIndex = usStart + i;
					*pByte |= GetIForceMark(RegIndex+1)<<offset;
				}
				pByte++;
			}		
		}
		else
		{
			Status = MB_ENOREG;
		}
		return Status;
	}
	else if (RegType == Q_TYPE )
	{
		if (usStart + usCnt <= (MAX_Q_CNT ))
		{
			i = 0;
			while(i<usCnt)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// �� ֵд��һ���ֽ�
				{				 
					RegIndex = usStart + i;
					*pByte |= GetQForceMark(RegIndex+1)<<offset;
				}
				pByte++;
			}		
		}
		else
		{
			Status = MB_ENOREG;
		}
		return Status;
	}
	else if (RegType == AQ_TYPE )
	{
		if (usStart + usCnt <= (MAX_AQ_CNT ))
		{
			i = 0;
			while(i<usCnt)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// �� ֵд��һ���ֽ�
				{ 
					RegIndex = usStart + i;
					*pByte |= GetAQForceMark(RegIndex+1)<<offset;					 
				}
				pByte++;
			}		
		}
		else
		{
			Status = MB_ENOREG;
		}
		return Status;
	}
	else if (RegType == AI_TYPE )
	{
		if (usStart + usCnt <= (MAX_AI_CNT ))
		{
			i = 0;
			while(i<usCnt)
			{
				*pByte = 0;
				for(offset=0;offset<8;offset++,i++)		// �� ֵд��һ���ֽ�
				{
					RegIndex = usStart + i;
					*pByte |= GetAIForceMark(RegIndex+1)<<offset;					 
				}
				pByte++;
			}		
		}
		else
		{
			Status = MB_ENOREG;
		}
		return Status;
	}
	return Status;
}

static MBErrorCode MBXWriteForceMarkCB( INT8U RegType, INT16U usAddr, INT16U Val )
{
	MBErrorCode  Status = MB_ENOERR;
	if (RegType == I_TYPE)
	{
		if (usAddr <= (MAX_I_CNT ))
		{
			SetIForceMark(usAddr+1,Val);
		}
		else
		{
			Status = MB_ENOREG;
		}
	}
	else if ( RegType == Q_TYPE )
	{
		if (usAddr <= (MAX_Q_CNT ))
		{
			SetQForceMark(usAddr+1,Val);
		}
		else
		{
			Status = MB_ENOREG;
		}
	}
	else if (RegType == AI_TYPE)
	{
		if (usAddr <= (MAX_AI_CNT ))
		{
			SetAIForceMark(usAddr+1,Val);
		}
		else
		{
			Status = MB_ENOREG;
		}
	}
	else if (RegType == AQ_TYPE)
	{
		if (usAddr <= (MAX_AQ_CNT ))
		{
			SetAQForceMark(usAddr+1,Val);
		}
		else
		{
			Status = MB_ENOREG;
		}
	}
	return Status;
}
/*********************************************************************************************************
** ��������: MBXWriteFileCB
** ��������: MBXWriteFileCB
**
** ���������� д�ļ�
**
** �䡡��:  INT8U * pFileData
** �䡡��:  INT8U * pLen
** �䡡��:  INT16U nPacketIdx
** �䡡��:  INT8U FileType
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��24��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static MBException MBXWriteFileCB( INT8U * pFileData, INT8U nLen,INT16U nPacketIdx, INT8U FileType )
{
	MBException  eStatus = MB_ENOERR;
	INT8U bRet = FALSE;

	if ( FileType == FCB_DATA_TYPE )
	{
		bRet =  PutFcbData(pFileData,nLen,nPacketIdx);
		if (bRet == FALSE)
			eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
	}
	else if ( FileType == BIN_DATA_TYPE )
	{
		bRet =  PutBinData(pFileData,nLen,nPacketIdx);
		if (bRet == FALSE)
			eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
	}
	else if ( FileType == SRC_DATA_TYPE )
	{
		bRet =  PutSrcData(pFileData,nLen,nPacketIdx);
		if (bRet == FALSE)
			eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
	}
	else
		eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;

	return eStatus;
}

static MBException MBXReadFileCB( INT8U * pFileData, INT8U nLen,INT32U nFileOffset, INT8U FileType )
{
	MBException  eStatus = MB_ENOERR;
	INT8U bRet = FALSE;

	if (FileType == FCB_DATA_TYPE)
	{
	}
	else if (FileType == BIN_DATA_TYPE)
	{		 
		bRet = ReadSrcDataBuf(pFileData, nFileOffset,nLen);
	}
	else if (FileType == SRC_DATA_TYPE)
	{		
		bRet = ReadSrcDataBuf(pFileData, nFileOffset,nLen);
	}
	else
		eStatus = MB_EX_ILLEGAL_FUNCTION;

	if (bRet != TRUE)
	{
		eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
	}

	return eStatus;
}

static MBErrorCode MBGetDeviceVer( INT8U * pucBuffer)
{
	MBErrorCode    eStatus = MB_ENOERR;

	return eStatus;
}


/*********************************************************************************************************
** ��������: MBGetFlashRamFcb
** ��������: MBGetFlashRamFcb
**
** ���������� ��ȡFLASH��RAM�е�FCB
**
** �䡡��:  INT8U * pFcbBuf
**          
** �䡡��:  MBErrorCode
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��11��14��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static MBErrorCode MBGetFlashRamFcb( INT8U * pFcbBuf)
{
	MBErrorCode eStatus = MB_ENOERR;
	INT8U err = 0;
	INT8U nPos = 0;
	INT8U nFcbLen = sizeof(FCB);
	INT8U *pFlashFcb = NULL;

	if (pFcbBuf == NULL)
		return MB_EINVAL;
	//����FLASH��FCB
	GetFcbBuff( &pFlashFcb,&err);
	memcpy(& pFcbBuf[nPos],pFlashFcb,nFcbLen);
	nPos += nFcbLen;
	memcpy(& pFcbBuf[nPos] , & Ram.Fcb ,nFcbLen);

	return eStatus;
}

/*********************************************************************************************************
** ��������: MBFuncReadCoils
** ��������: MBFuncReadCoils
**
** ���������� �������ģ���ִ�����Ȼ����֯�ɱ��ķ���
**
** �䡡��:  INT8U * pucFrame
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��15��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBException MBFuncReadCoils( INT8U *  pAduBuf, INT16U * usADULen )
{
	MBException   Status = MB_EX_NONE;
	INT16U      usRegAddress;
	INT16U      usCoilCount;
	INT8U       ucNBytes;
	INT8U       *pucFrameCur = NULL;
	MBErrorCode    RegStatus;
	INT8U * pPduFrame  = & pAduBuf[1];

	if( *usADULen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN+ MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1] );
//		usRegAddress++;

		usCoilCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_COILCNT_OFF] << 8 );
		usCoilCount |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_COILCNT_OFF + 1] );
		/* Check if the number of registers to read is valid. If not
		* return Modbus illegal data value exception. 
		*/
		if( ( usCoilCount >= 1 ) && ( usCoilCount < MB_PDU_FUNC_READ_COILCNT_MAX ) )
		{
			/* Set the current PDU data pointer to the beginning. */
			pucFrameCur = &pPduFrame[MB_PDU_FUNC_OFF];
			*usADULen = MB_SER_PDU_PDU_OFF+MB_PDU_FUNC_OFF;

			/* First byte contains the function code. */
			*pucFrameCur++ = MB_FUNC_READ_COILS;
			*usADULen += 1;

			/* Test if the quantity of coils is a multiple of 8. If not last
			* byte is only partially field with unused coils set to zero. */
			if( ( usCoilCount & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U )( usCoilCount / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U )( usCoilCount / 8 );
			}
			*pucFrameCur++ = ucNBytes;
			*usADULen += 1;

			RegStatus = MBRegCoilsCB( pucFrameCur, usRegAddress, usCoilCount,MBX_READ );

			/* If an error occured convert it into a Modbus exception. */
			if( RegStatus != MB_ENOERR )
			{
				Status = MBError2Exception( RegStatus );
			}
			else
			{
				/* The response contains the function code, the starting address
				* and the quantity of registers. We reuse the old values in the 
				* buffer because they are still valid. */
				*usADULen += ucNBytes;
			}
		}
		else
		{
			Status = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid read coil register request because the length
		* is incorrect. */
		Status = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return  Status;
}
/*********************************************************************************************************
** ��������: MBFuncWriteCoil
** ��������: MBFuncWriteCoil
**
** ����������д������Ȧ 
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncWriteCoil( INT8U * pAduBuf, INT16U * usLen )
{
	INT16U          usRegAddress;
	INT8U           ucBuf[2];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;
	INT8U * pPduFrame  = & pAduBuf[1];


	if( *usLen == ( MB_PDU_FUNC_WRITE_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_ADDR_OFF + 1] );
//		usRegAddress++;

		if( ( pPduFrame[MB_PDU_FUNC_WRITE_VALUE_OFF + 1] == 0x00 ) &&
			( ( pPduFrame[MB_PDU_FUNC_WRITE_VALUE_OFF] == 0xFF ) ||
			( pPduFrame[MB_PDU_FUNC_WRITE_VALUE_OFF] == 0x00 ) ) )
		{
			ucBuf[1] = 0;
			if( pPduFrame[MB_PDU_FUNC_WRITE_VALUE_OFF] == 0xFF )
			{
				ucBuf[0] = 1;
			}
			else
			{
				ucBuf[0] = 0;
			}
			eRegStatus = MBRegCoilsCB( &ucBuf[0], usRegAddress, 1, MBX_WRITE );

			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid write coil register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncWriteMultipleCoils
** ��������: MBFuncWriteMultipleCoils
**
** ���������� д�����Ȧ
**
** �䡡��:  UCHAR * pAduBuf
** �䡡��:  USHORT * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncWriteMultipleCoils( INT8U * pAduBuf, INT16U * usLen )
{
	INT16U          usRegAddress;
	INT16U          usCoilCnt;
	INT8U           ucByteCount;
	INT8U           ucByteCountVerify;
	INT8U * pPduFrame  = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usLen > ( MB_PDU_FUNC_WRITE_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF + 1] );
//		usRegAddress++;

		usCoilCnt = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_COILCNT_OFF] << 8 );
		usCoilCnt |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_COILCNT_OFF + 1] );

		ucByteCount = pPduFrame[MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF];

		/* Compute the number of expected bytes in the request. */
		if( ( usCoilCnt & 0x0007 ) != 0 )
		{
			ucByteCountVerify = ( INT8U )( usCoilCnt / 8 + 1 );
		}
		else
		{
			ucByteCountVerify = ( INT8U )( usCoilCnt / 8 );
		}

		if( ( usCoilCnt >= 1 ) &&
			( usCoilCnt <= MB_PDU_FUNC_WRITE_MUL_COILCNT_MAX ) &&
			( ucByteCountVerify == ucByteCount ) )
		{
			eRegStatus = MBRegCoilsCB( &pPduFrame[MB_PDU_FUNC_WRITE_MUL_VALUES_OFF],usRegAddress, usCoilCnt, MBX_WRITE );

			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
			else
			{
				/* The response contains the function code, the starting address
				* and the quantity of registers. We reuse the old values in the 
				* buffer because they are still valid. */
				*usLen = MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF + MB_SER_PDU_PDU_OFF;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid write coil register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncReadDiscreteInputs
** ��������: MBFuncReadDiscreteInputs
**
** ���������� ������
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usADULen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��28��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
MBException MBFuncReadDiscreteInputs( INT8U * pAduBuf, INT16U * usADULen )
{
	INT16U          usRegAddress;
	INT16U          usDiscreteCnt;
	INT8U           ucNBytes;
	INT8U          *pucFrameCur;
	INT8U * pPduFrame = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usADULen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1] );
//		usRegAddress++;

		usDiscreteCnt = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_DISCCNT_OFF] << 8 );
		usDiscreteCnt |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_DISCCNT_OFF + 1] );

		/* Check if the number of registers to read is valid. If not
		* return Modbus illegal data value exception. 
		*/
		if( ( usDiscreteCnt >= 1 ) &&
			( usDiscreteCnt < MB_PDU_FUNC_READ_DISCCNT_MAX ) )
		{
			/* Set the current PDU data pointer to the beginning. */
			pucFrameCur = &pPduFrame[MB_PDU_FUNC_OFF];
			*usADULen = MB_SER_PDU_PDU_OFF+MB_PDU_FUNC_OFF;

			/* First byte contains the function code. */
			*pucFrameCur++ = MB_FUNC_READ_DISCRETE_INPUTS;
			*usADULen += 1;

			/* Test if the quantity of coils is a multiple of 8. If not last
			* byte is only partially field with unused coils set to zero. */
			if( ( usDiscreteCnt & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U ) ( usDiscreteCnt / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U ) ( usDiscreteCnt / 8 );
			}
			*pucFrameCur++ = ucNBytes;
			*usADULen += 1;

			eRegStatus = MBRegDiscreteCB( pucFrameCur, usRegAddress, usDiscreteCnt );

			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
			else
			{
				/* The response contains the function code, the starting address
				* and the quantity of registers. We reuse the old values in the 
				* buffer because they are still valid. */
				*usADULen += ucNBytes;;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid read coil register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncReadInputRegister
** ��������: MBFuncReadInputRegister
**
** ���������� ��ģ��
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncReadInputRegister( INT8U * pAduBuf , INT16U * usLen )
{ 
	INT16U          usRegAddress;
	INT16U          usRegCount;
	INT8U          *pucFrameCur;
	INT8U * pPduFrame = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usLen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1] );
//		usRegAddress++;

		usRegCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_REGCNT_OFF] << 8 );
		usRegCount |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_REGCNT_OFF + 1] );

		/* Check if the number of registers to read is valid. If not
		* return Modbus illegal data value exception. 
		*/
		if( ( usRegCount >= 1 )	&& ( usRegCount < MB_PDU_FUNC_READ_REGCNT_MAX ) )
		{
			/* Set the current PDU data pointer to the beginning. */
			pucFrameCur = &pPduFrame[MB_PDU_FUNC_OFF];
			*usLen = MB_SER_PDU_PDU_OFF+MB_PDU_FUNC_OFF;

			/* First byte contains the function code. */
			*pucFrameCur++ = MB_FUNC_READ_INPUT_REGISTER;
			*usLen += 1;

			/* Second byte in the response contain the number of bytes. */
			*pucFrameCur++ = ( INT8U )( usRegCount * 2 );
			*usLen += 1;

			eRegStatus = MBRegInputCB( pucFrameCur, usRegAddress, usRegCount );

			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
			else
			{
				*usLen += usRegCount * 2;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid read input register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncReadHoldingRegister
** ��������: MBFuncReadHoldingRegister
**
** ���������� �������ͼĴ���
**
** �䡡��:  INT8U * pucFrame  ADU
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��10��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncReadHoldingRegister( INT8U * pAduBuf, INT16U * usADULen )
{
	INT16U          usRegAddress;
	INT16U          usRegCount;
	INT8U          *pucFrameCur;
	INT8U * pPduFrame = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usADULen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1] );
//		usRegAddress++;

		usRegCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_REGCNT_OFF] << 8 );
		usRegCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READ_REGCNT_OFF + 1] );

		/* Check if the number of registers to read is valid. If not
		* return Modbus illegal data value exception. 
		*/
		if( ( usRegCount >= 1 ) && ( usRegCount <= MB_PDU_FUNC_READ_REGCNT_MAX ) )
		{
			/* Set the current PDU data pointer to the beginning. */
			pucFrameCur = &pPduFrame[MB_PDU_FUNC_OFF];
			*usADULen = MB_SER_PDU_PDU_OFF + MB_PDU_FUNC_OFF;

			/* First byte contains the function code. */
			*pucFrameCur++ = MB_FUNC_READ_HOLDING_REGISTER;
			*usADULen += 1;

			/* Second byte in the response contain the number of bytes. */
			*pucFrameCur++ = ( INT8U ) ( usRegCount * 2 );
			*usADULen += 1;

			/* Make callback to fill the buffer. */
			eRegStatus = MBRegHoldingCB( pucFrameCur, usRegAddress, usRegCount, MBX_READ );
			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
			else
			{
				*usADULen += usRegCount * 2;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncWriteHoldingRegister
** ��������: MBFuncWriteHoldingRegister
**
** ���������� д�����Ĵ���
**
** �䡡��:  INT8U * pucFrame
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncWriteHoldingRegister( INT8U * pAduBuf, INT16U * usLen )
{
	INT16U          usRegAddress;
	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;
	INT8U * pPduFrame = & pAduBuf[1];

	if( *usLen == ( MB_PDU_FUNC_WRITE_SIZE + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF ) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_ADDR_OFF + 1] );
//		usRegAddress++;

		/* Make callback to update the value. */
		eRegStatus = MBRegHoldingCB( &pPduFrame[MB_PDU_FUNC_WRITE_VALUE_OFF],usRegAddress, 1, MBX_WRITE );

		/* If an error occured convert it into a Modbus exception. */
		if( eRegStatus != MB_ENOERR )
		{
			eStatus = MBError2Exception( eRegStatus );
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncWriteMultipleHoldingRegister
** ��������: MBFuncWriteMultipleHoldingRegister
**
** ���������� д����Ĵ���
**
** �䡡��:  INT8U * pucFrame
** �䡡��:  INT16U * usLen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncWriteMultipleHoldingRegister( INT8U * pAduBuf, INT16U * usLen )
{
	INT16U          usRegAddress;
	INT16U          usRegCount;
	INT8U           ucRegByteCount;
	INT8U * pPduFrame = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usLen >= ( MB_PDU_FUNC_WRITE_MUL_SIZE_MIN + MB_PDU_SIZE_MIN + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF + 1] );
//		usRegAddress++;

		usRegCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF] << 8 );
		usRegCount |= ( INT16U )( pPduFrame[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF + 1] );

		ucRegByteCount = pPduFrame[MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF];

		if( ( usRegCount >= 1 ) &&
			( usRegCount <= MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX ) &&
			( ucRegByteCount == ( INT8U ) ( 2 * usRegCount ) ) )
		{
			/* Make callback to update the register values. */
			eRegStatus = MBRegHoldingCB( &pPduFrame[MB_PDU_FUNC_WRITE_MUL_VALUES_OFF],usRegAddress, usRegCount, MBX_WRITE );

			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
			else
			{
				/* The response contains the function code, the starting
				* address and the quantity of registers. We reuse the
				* old values in the buffer because they are still valid.
				*/
				*usLen = MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF + MB_SER_PDU_PDU_OFF;
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncReadWriteMultipleHoldingRegister
** ��������: MBFuncReadWriteMultipleHoldingRegister
**
** ���������� ��/д����Ĵ���
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncReadWriteMultipleHoldingRegister( INT8U * pAduBuf, INT16U * usLen )
{
	INT16U          usRegReadAddress;
	INT16U          usRegReadCount;
	INT16U          usRegWriteAddress;
	INT16U          usRegWriteCount;
	INT8U           ucRegWriteByteCount;
	INT8U          *pucFrameCur;
	INT8U * pPduFrame = & pAduBuf[1];

	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	if( *usLen >= ( MB_PDU_FUNC_READWRITE_SIZE_MIN + MB_PDU_SIZE_MIN ) )
	{
		usRegReadAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF] << 8U );
		usRegReadAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF + 1] );
//		usRegReadAddress++;

		usRegReadCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF] << 8U );
		usRegReadCount |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF + 1] );

		usRegWriteAddress = ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF] << 8U );
		usRegWriteAddress |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF + 1] );
//		usRegWriteAddress++;

		usRegWriteCount = ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF] << 8U );
		usRegWriteCount |= ( INT16U )( pPduFrame[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF + 1] );

		ucRegWriteByteCount = pPduFrame[MB_PDU_FUNC_READWRITE_BYTECNT_OFF];

		if( ( usRegReadCount >= 1 ) && ( usRegReadCount <= 0x7D ) &&
			( usRegWriteCount >= 1 ) && ( usRegWriteCount <= 0x79 ) &&
			( ( 2 * usRegWriteCount ) == ucRegWriteByteCount ) )
		{
			/* Make callback to update the register values. */
			eRegStatus = MBRegHoldingCB( &pPduFrame[MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF],usRegWriteAddress, usRegWriteCount, MBX_WRITE );

			if( eRegStatus == MB_ENOERR )
			{
				/* Set the current PDU data pointer to the beginning. */
				pucFrameCur = &pPduFrame[MB_PDU_FUNC_OFF];
				*usLen = MB_SER_PDU_PDU_OFF + MB_PDU_FUNC_OFF;

				/* First byte contains the function code. */
				*pucFrameCur++ = MB_FUNC_READWRITE_MULTIPLE_REGISTERS;
				*usLen += 1;

				/* Second byte in the response contain the number of bytes. */
				*pucFrameCur++ = ( INT8U ) ( usRegReadCount * 2 );
				*usLen += 1;

				/* Make the read callback. */
				eRegStatus = MBRegHoldingCB( pucFrameCur, usRegReadAddress, usRegReadCount, MBX_READ );
				if( eRegStatus == MB_ENOERR )
				{
					*usLen += 2 * usRegReadCount;
				}
			}
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBXFuncReadForceMark
** ��������: MBXFuncReadForceMark
**
** ���������� ������ǿ�Ʊ�־
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��11��24��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXFuncReadForceMark( INT8U * pAduBuf, INT16U * usLen )
{
	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	INT8U * pPduFrame  = & pAduBuf[1];
	INT8U Len = pPduFrame[1]; //���ĳ���
	
	INT16U ICnt = 0;
	INT16U QCnt = 0;
	INT16U AICnt = 0;
	INT16U AQCnt = 0;

	INT16U IAddr = 0;
	INT16U QAddr = 0;
	INT16U AIAddr = 0;
	INT16U AQAddr = 0;

// 	INT16U  usRegAddress = 0;
// 	INT16U  usCount = 0;

	INT8U ucNBytes;
	INT8U RegType = 0;
	INT8U nIdx = 0;

	if( *usLen > ( MBX_PDU_FUNC_READ_FM_SIZE + MB_SER_PDU_PDU_OFF) )
	{
		//�����յ��ı���
		while (1)
		{
			RegType = pPduFrame[2+nIdx];
			if (RegType == I_TYPE)
			{
				IAddr = (INT16U) (pPduFrame[3+nIdx] << 8);
				IAddr |= (INT16U) (pPduFrame[4+nIdx]);

				ICnt = (INT16U) (pPduFrame[5+nIdx] << 8);
				ICnt |= (INT16U) (pPduFrame[6+nIdx]);
			}
			else if ( RegType == Q_TYPE )
			{
				QAddr = (INT16U) (pPduFrame[3+nIdx] << 8);
				QAddr |= (INT16U) (pPduFrame[4+nIdx]);

				QCnt = (INT16U) (pPduFrame[5+nIdx] << 8);
				QCnt |= (INT16U) (pPduFrame[6+nIdx]);
			}
			else if ( RegType == AI_TYPE )
			{
				AIAddr = (INT16U) (pPduFrame[3+nIdx] << 8);
				AIAddr |= (INT16U) (pPduFrame[4+nIdx]);

				AICnt = (INT16U) (pPduFrame[5+nIdx] << 8);
				AICnt |= (INT16U) (pPduFrame[6+nIdx]);
			}
			else if ( RegType == AQ_TYPE )
			{
				AQAddr = (INT16U) (pPduFrame[3+nIdx] << 8);
				AQAddr |= (INT16U) (pPduFrame[4+nIdx]);

				AQCnt = (INT16U) (pPduFrame[5+nIdx] << 8);
				AQCnt |= (INT16U) (pPduFrame[6+nIdx]);
			}
			else
			{
				break;
			}

			nIdx += 5;
			if (nIdx>=Len)
			{
				break;
			}
		}
		//��֯�ظ��ı���
		nIdx  = 0; //�ܵ��ֽڳ���
		if (ICnt >=1 && ICnt <= MAX_I_CNT )
		{
			if( ( ICnt & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U ) ( ICnt / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U ) ( ICnt / 8 );
			}
			pPduFrame[nIdx+2] = I_TYPE;
			pPduFrame[nIdx+3] = (INT8U) (ICnt >> 8);//�Ĵ�������
			pPduFrame[nIdx+4] = (INT8U) (ICnt);//�Ĵ�������

			eRegStatus = MBXReadForceMarkCB(& pPduFrame[nIdx+5] ,I_TYPE,IAddr,ICnt);
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
				return eStatus;
			}
			else
			{
				nIdx += 3;
				nIdx += ucNBytes;
			}
		}
		if (AICnt >=1 && AICnt <= MAX_AI_CNT )
		{
			if( ( AICnt & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U ) ( AICnt / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U ) ( AICnt / 8 );
			}
			pPduFrame[nIdx+2] = AI_TYPE;
			pPduFrame[nIdx+3] = (INT8U) (AICnt >> 8);//�Ĵ�������
			pPduFrame[nIdx+4] = (INT8U) (AICnt);//�Ĵ�������

			eRegStatus = MBXReadForceMarkCB(& pPduFrame[nIdx+5] ,AI_TYPE,AIAddr,AICnt);
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
				return eStatus;
			}
			else
			{
				nIdx += 3;
				nIdx += ucNBytes;
			}
		}
		if (QCnt >=1 && QCnt <= MAX_Q_CNT )
		{
			if( ( QCnt & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U ) ( QCnt / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U ) ( QCnt / 8 );
			}
			pPduFrame[nIdx+2] = Q_TYPE;
			pPduFrame[nIdx+3] = (INT8U) (QCnt >> 8);//�Ĵ�������
			pPduFrame[nIdx+4] = (INT8U) (QCnt);//�Ĵ�������

			eRegStatus = MBXReadForceMarkCB(& pPduFrame[nIdx+5] ,Q_TYPE,QAddr,QCnt);
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
				return eStatus;
			}
			else
			{
				nIdx += 3;
				nIdx += ucNBytes;
			}
		}
		if (AQCnt >=1 && AQCnt <= MAX_AQ_CNT )
		{
			if( ( AQCnt & 0x0007 ) != 0 )
			{
				ucNBytes = ( INT8U ) ( AQCnt / 8 + 1 );
			}
			else
			{
				ucNBytes = ( INT8U ) ( AQCnt / 8 );
			}
			pPduFrame[nIdx+2] = AQ_TYPE;
			pPduFrame[nIdx+3] = (INT8U) (AQCnt >> 8);//�Ĵ�������
			pPduFrame[nIdx+4] = (INT8U) (AQCnt);//�Ĵ�������

			eRegStatus = MBXReadForceMarkCB(& pPduFrame[nIdx+5] ,AQ_TYPE,AQAddr,AQCnt);
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
				return eStatus;
			}
			else
			{
				nIdx += 3;
				nIdx += ucNBytes;
			}
		}
		if (nIdx > 3)
		{
			pPduFrame[1] = nIdx;
			*usLen = nIdx + 2 + MB_SER_PDU_PDU_OFF;
		}
		else
			return MB_EX_ILLEGAL_DATA_VALUE;
	}
	else
	{
		/* Can't be a valid write coil register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
//д�����Ĵ�����ǿ�Ʊ�־
extern MBException MBXFuncWriteForceMark( INT8U * pAduBuf, INT16U * usLen )
{
	MBException    eStatus = MB_EX_NONE;
	MBErrorCode    eRegStatus;

	INT8U * pPduFrame  = & pAduBuf[1];
	INT8U RegType = pPduFrame[1]; // 

	INT16U          usRegAddress;
	 
	if( *usLen == ( MBX_PDU_WRITE_READ_FM_SIZE + MB_SER_PDU_PDU_OFF) )
	{
		usRegAddress = ( INT16U )( pPduFrame[2] << 8 );
		usRegAddress |= ( INT16U )( pPduFrame[2 + 1] );
		 
		if( ( pPduFrame[4 + 1] == 0x00 ) &&
			( ( pPduFrame[4] == 0xFF ) ||
			( pPduFrame[4] == 0x00 ) ) )
		{
		 	if( pPduFrame[4] == 0xFF )
			{
				eRegStatus = MBXWriteForceMarkCB(RegType,usRegAddress,TRUE);  
		 	}
			else
			{
				eRegStatus = MBXWriteForceMarkCB(RegType,usRegAddress,FALSE);		
			}
			/* If an error occured convert it into a Modbus exception. */
			if( eRegStatus != MB_ENOERR )
			{
				eStatus = MBError2Exception( eRegStatus );
			}
		}
		else
		{
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		}
	}
	else
	{
		/* Can't be a valid write coil register request because the length
		* is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBXFuncSetTime
** ��������: MBXFuncSetTime
**
** ������������ʱ����
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXFuncSetTime( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException    eStatus = MB_EX_NONE;
	INT8U * pPduFrame = & pAduBuf[1];
	INT8U nPduIdx = 2;

	INT16U year = 0;
	INT8U month = 0;
	INT8U day = 0;
	INT8U hr = 0;
	INT8U min = 0;
	INT8U sec = 0;
	INT8U bRespFlag = FALSE;

	INT8U bRet = FALSE;

	if( *usAduLen == MBX_PDU_FUNC_DEVICE_CTRL_LEN + MB_SER_PDU_PDU_OFF)
	{
		if (pAduBuf[0] != BROADCAST_ADDRESS && pPduFrame[nPduIdx] == 0XFF)
		{
			bRespFlag = TRUE;
		}
		else
		{
			bRespFlag = FALSE;
		}
		nPduIdx++;

		year = ( INT16U )( pPduFrame[nPduIdx] << 8U );
		nPduIdx++;

		year |= ( INT16U )( pPduFrame[nPduIdx] );
		nPduIdx++;

		month = pPduFrame[nPduIdx]  ;
		nPduIdx++;

		day =   pPduFrame[nPduIdx]  ;
		nPduIdx++;

		hr =   pPduFrame[nPduIdx]  ;
		nPduIdx++;

		min =   pPduFrame[nPduIdx]  ;
		nPduIdx++;

		sec =   pPduFrame[nPduIdx]  ;
		nPduIdx++;
		//���붪������
		bRet =  ClockSetDateTime(  month,   day,   year,   hr,   min,   sec);
		if (bRet == FALSE)
			eStatus = MB_EX_ILLEGAL_DATA_VALUE;
		if (bRespFlag == TRUE)
		{//�ظ�����
			*usAduLen = MB_SER_PDU_PDU_OFF+6;
			pPduFrame[2] = bRet == TRUE ? 0xff: 0x00; 
			pPduFrame[3] = 0;
			pPduFrame[4] = 0;
			pPduFrame[5] = 0;
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBXFuncReSetDevice
** ��������: MBXFuncReSetDevice
**
** ���������� ��λװ��
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��13��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXFuncReSetDevice( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException    eStatus = MB_EX_NONE;
 	INT8U * pPduFrame = & pAduBuf[1];


	Reset();


	return eStatus;
}
/*********************************************************************************************************
** ��������: MBFuncMEI
** ��������: MBFuncMEI
**
** ���������� 
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��14��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBFuncMEI( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException    eStatus = MB_EX_NONE;
	INT8U * pPduFrame = & pAduBuf[1];
	INT8U SubFuncCode = 0;
	INT8U ReadDevId = 0;
	INT8U ObjId = 0;
	INT8U nPduIdx = 0;
	 	
	if( *usAduLen == MB_PDU_FUNC_MEI_LEN + MB_SER_PDU_PDU_OFF)
	{
		SubFuncCode = pPduFrame[1];
		if (SubFuncCode == 0x0e)
		{
			ReadDevId = pPduFrame[2];
			if (ReadDevId == 0x01)
			{

			}			
			else if (ReadDevId == 0x02)
			{

			}
			else if (ReadDevId == 0x03)
			{


			}
			else if (ReadDevId == 0x04)
			{//ר�����ݶ���
				ObjId = pPduFrame[3];
				nPduIdx = 3;
				switch ( ObjId )
				{
				case MB_MEI_READ_DEV_VER:
					break;
				case MB_MEI_READ_DN_TM:
					break;
				case MB_MEI_READ_VER_TM:
					break;
				case MB_MEI_READ_CFG_VER:
					break;
				case MB_MEI_READ_FLASH_FCB:
					break;
				case MB_MEI_READ_RAM_FCB:
					break;
				case MB_MEI_READ_FLASHRAM_FCB:
					pPduFrame[nPduIdx] = 0; //һ����
					nPduIdx++;
					pPduFrame[nPduIdx] = 0; //����
					nPduIdx++;
					pPduFrame[nPduIdx] = 01; //��������
					nPduIdx++;
					pPduFrame[nPduIdx] = ObjId; //����ID
					nPduIdx++;
					pPduFrame[nPduIdx] = sizeof(FCB) *2; //���󳤶�

					nPduIdx++;
					MBGetFlashRamFcb(&pPduFrame[nPduIdx]);
					
					*usAduLen = sizeof(FCB) *2 + 9;

					break;
				default:
					break;
				}				 
			}
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}

	return eStatus;
} 

/*********************************************************************************************************
** ��������: MBXWriteFileRecord
** ��������: MBXWriteFileRecord
**
** ���������� 
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��23��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXWriteFileRecord( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException  eStatus = MB_EX_NONE;
	INT8U * pPduFrame = & pAduBuf[1];
	INT8U FileType = 0; //�ļ����ͣ�BIN/SRC/
	INT16U PacketIdx = 0;
	INT8U PacketLen = 0;
 
	if( *usAduLen >= ( MBX_PDU_FUNC_DN_FILE_SIZE_MIN + MB_PDU_SIZE_MIN ) )
	{
		FileType= pPduFrame[3];
		PacketLen = pPduFrame[4];

		PacketIdx = pPduFrame[5] << 8 & 0xff00 | pPduFrame[6]; //���ĵ�˳���
	 
		//д����
		eStatus = MBXWriteFileCB( & pPduFrame[7] ,PacketLen,PacketIdx,FileType);

		pPduFrame[1] = 6; //�ظ����ĳ���

		//���д������׼���ظ�����
		if (eStatus == MB_EX_NONE)
		{
			pPduFrame[7] = 0xff;
			*usAduLen = MBX_PDU_FUNC_DN_FILE_SIZE_MIN + MB_PDU_SIZE_MIN;
		}
		else
		{
			pPduFrame[7] = 0;
			*usAduLen = MBX_PDU_FUNC_DN_FILE_SIZE_MIN + MB_PDU_SIZE_MIN;
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
 	return eStatus;
}
/*********************************************************************************************************
** ��������: MBXWriteFileToFlash
** ��������: MBXWriteFileToFlash
**
** ���������� �ļ����ؿ������� �ļ����ؽ������·��˱��ģ�֪ͨװ���ļ����ؽ��� װ�ô�ramд��flash
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��27��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXWriteFileToFlash( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException  eStatus = MB_EX_NONE;
	INT8U * pPduFrame = & pAduBuf[1];
	INT8U  Ret = FALSE;
	INT8U  err = 0;

	if( *usAduLen >= ( 5 + MB_PDU_SIZE_MIN ) )
	{
		Ret = SaveData(&err);
		pPduFrame[1] = 0x03;//���ĳ���
		//��֯�ظ�����
		if (Ret)
		{//�ɹ�
			pPduFrame[3] = 0xff;
			pPduFrame[4] = 0xff;
			//ADU�ĳ��Ȳ���
		}
		else
		{
			pPduFrame[3] = 0x00; //ʧ�ܵı�־
			pPduFrame[4] = err;  //�����
		}
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
/*********************************************************************************************************
** ��������: MBXReadFileRecord
** ��������: MBXReadFileRecord
**
** ���������� �ϴ��ļ���Ϣ
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usAduLen
**          
** �䡡��:  extern MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��27��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern MBException MBXReadFileRecord( INT8U * pAduBuf, INT16U * usAduLen )
{
	MBException  eStatus = MB_EX_NONE;
	INT8U * pPduFrame = & pAduBuf[1];
	INT8U FileType = 0; //�ļ����ͣ�BIN/SRC/
	INT8U PacketLen = 0;
	INT32U BuffOffset = 0;


	if( *usAduLen >= ( MBX_PDU_FUNC_UP_FILE_SIZE_MIN + MB_PDU_SIZE_MIN ) )
	{
		FileType= pPduFrame[3];
		PacketLen = pPduFrame[4];

		BuffOffset =  (pPduFrame[5] << 24 & 0xff000000) | 
			(pPduFrame[6]  << 16 & 0x00ff0000 )|
			(pPduFrame[7] << 8 & 0xff00 )| pPduFrame[8]; //���ݵ�ƫ�Ƶ�ַ
		//������
		eStatus = MBXReadFileCB(&pPduFrame[3],PacketLen,BuffOffset,FileType);

		//���д������׼���ظ�����
		if (eStatus == MB_EX_NONE)
		{
			pPduFrame[1] = PacketLen + 1;//���ĳ���
			*usAduLen = pPduFrame[1] + 2 + MB_PDU_SIZE_MIN;
		}	
	}
	else
	{
		/* Can't be a valid request because the length is incorrect. */
		eStatus = MB_EX_ILLEGAL_DATA_VALUE;
	}
	return eStatus;
}
