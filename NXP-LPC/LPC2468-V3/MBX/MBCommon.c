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
#include "MODBUS.h"
#include "Func.h"
#include "IoAdapter.h"
#include "uart.h"
#include "MBFunc.h"


typedef enum RECV_FRAME_STATE
{
	RECV_FRAME_ERR = 0,
	RECV_FRAME_BYTE_OK = 1,
	RECV_FRAME_OK = 2
}RECV_FRAME_STATE;
/*********************************************************************************************************
** ��������: GetOneFrame
** ��������: GetOneFrame
**
** ���������� 
**
** �䡡��:  MBX * pMbx
** �䡡��:  INT8U c
**          
** �䡡��:  INT8U  0����1�����գ�2������ȷ�����
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��12��
** ��  ע:   
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U GetOneFrame(MBX * pMbx, INT8U c)
{
	INT16U chkcrc = 0;
 
	if (pMbx == NULL)
		return 0;
	
	//���ڷ���̬�����ҵ�ǰû��������
	if(pMbx->RxCount<MAX_ADU_LENGTH)	
	{	
		//�峬ʱ����
		pMbx->RxTimer=0;
		pMbx->RxBuff[pMbx->RxCount++]=c;
		
		/** 0. �ӻ���ַ **/
		if(pMbx->RxCount==1)
		{
			if(c==pMbx->Address )
			{
				pMbx->ModbusRxCRC=0xFFFF;
				crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				pMbx->Broadcast = FALSE;
			}
			else if (c == BROADCAST_ADDRESS )
			{
				pMbx->Broadcast = TRUE;
				pMbx->ModbusRxCRC=0xFFFF;
				crc16_ex(&c,1,& pMbx->ModbusRxCRC);
			}
			else
			{
				pMbx->RxCount=0;
				pMbx->Broadcast = FALSE;
				pMbx->RxLen = 0;
				return RECV_FRAME_ERR;
			}
		}
		/** 1. ������ **/
		else if(pMbx->RxCount==2)
		{
			//֧�ֵĹ�������
 		 	if(c==MB_FUNC_READ_COILS 
				|| c==MB_FUNC_READ_DISCRETE_INPUTS 
				|| c == MB_FUNC_READ_HOLDING_REGISTER 
				|| c == MB_FUNC_READ_INPUT_REGISTER
				|| c == MB_FUNC_WRITE_REGISTER
				|| c == MB_FUNC_WRITE_SINGLE_COIL
				)
			{
				if (pMbx->Broadcast == FALSE)
				{//���ϱ��Ĳ�֧�ֹ㲥����
					pMbx->FuncCode=c;
					/** ��ѯQuery��ı���(��д�����Ĵ���/��Ȧ)�����ĳ���һ��Ϊ6(������CRC��) **/
					pMbx->RxLen=6;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}		
  			}
			else if ( c == MBX_FUNC_DEVICE_CTRL )//�����豸����
			{
				pMbx->FuncCode=c;
				pMbx->RxLen = MBX_PDU_FUNC_DEVICE_CTRL_LEN;
				crc16_ex(&c,1,& pMbx->ModbusRxCRC);
			}
			//�������͵Ĺ����룬�����ʱ���޷��϶��˷ⱨ���ж೤
			else if ( c == MB_FUNC_WRITE_MULTIPLE_COILS 
				|| c == MB_FUNC_WRITE_MULTIPLE_REGISTERS
				|| c == MB_FUNC_READ_FILE_RECORD    //�ļ���д
				|| c == MB_FUNC_WRITE_FILE_RECORD
				)
			{
				if (pMbx->Broadcast == FALSE)
				{
					pMbx->FuncCode=c;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					pMbx->RxLen = 0;
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}		
			}
			else if ( c== MBX_FUNC_READ_FORCEMARK )
			{//��ǿ�Ʊ�־
				if (pMbx->Broadcast == FALSE)
				{
					pMbx->FuncCode=c;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					pMbx->RxLen = 0;
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}	
			}
			else if ( c== MBX_FUNC_WRITE_FORCEMARK )
			{//дǿ�Ʊ�־
				if (pMbx->Broadcast == FALSE)
				{//���ϱ��Ĳ�֧�ֹ㲥����
					pMbx->FuncCode=c;
					/**  ���ĳ���һ��Ϊ7(������CRC��) **/
					pMbx->RxLen=7;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}		
			}
			else if (c == MB_FUNC_READWRITE_MULTIPLE_REGISTERS)
			{
				if (pMbx->Broadcast == FALSE)
				{
					pMbx->FuncCode=c;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					pMbx->RxLen = 0;
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}					
			}
			else if ( c == MB_FUNC_MEI )
			{//���豸��Ϣ				
				if (pMbx->Broadcast == FALSE)
				{
					pMbx->FuncCode = c;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					pMbx->RxLen = 0;
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}		
			}
			else
			{
				pMbx->RxCount=0;
				pMbx->Broadcast = FALSE;
				pMbx->RxLen = 0;
				return RECV_FRAME_ERR;
			} 
		}		 
		else if (pMbx->RxCount>=3  )
		{
			/** CRCУ��� **/
			if( pMbx->RxLen && pMbx->RxCount==(pMbx->RxLen+2))
			{
				chkcrc=MAKEWORD(pMbx->RxBuff[pMbx->RxCount-2], c);
				//	pMbx->ModbusRxCRC == GetCRC16( pMbx->RxBuff,pMbx->RxLen);
				if(pMbx->ModbusRxCRC==chkcrc)
				{//���յ�һ����ȷ��ͨ�ű���

					pMbx->RxTotalLen += pMbx->RxCount;
					pMbx->RxTotoalCnt ++;

					return RECV_FRAME_OK;
				}
				else
				{
					pMbx->RxCrcErr ++;
					pMbx->RxCount=0;
					return RECV_FRAME_ERR;
				}
			}

			if (pMbx->RxCount <= (pMbx->RxLen))
			{
				crc16_ex(&c,1,& pMbx->ModbusRxCRC);
			}
			
			 //���ĳ��Ȼ���δ֪
			if ( pMbx->FuncCode == MB_FUNC_WRITE_MULTIPLE_COILS 
				|| pMbx->FuncCode == MB_FUNC_WRITE_MULTIPLE_REGISTERS
				)
			{
				if (pMbx->RxCount==7 && pMbx->Broadcast == FALSE)
				{
					pMbx->RxLen = c +  6;
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				}
				else
				{
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}	
			}
			else if ( pMbx->FuncCode == MBX_FUNC_READ_FORCEMARK )
			{//��ȡǿ�Ʊ�־
				if (pMbx->RxCount==3 && pMbx->Broadcast == FALSE)
				{
					pMbx->RxLen = c + 3; //����CRC��
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				}	
				else if ( pMbx->Broadcast == TRUE)
				{//��֧�ֹ㲥
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}
			}
			else if ( pMbx->FuncCode == MB_FUNC_READ_FILE_RECORD
				|| pMbx->FuncCode == MB_FUNC_WRITE_FILE_RECORD
				)
			{//�ļ���д����֧�ֹ㲥����
				if (pMbx->RxCount==3 && pMbx->Broadcast == FALSE)
				{
					pMbx->RxLen = c + 3; //����CRC��
					crc16_ex(&c,1,& pMbx->ModbusRxCRC);
				}
				else if ( pMbx->RxCount==4 && pMbx->Broadcast == FALSE )
				{
					if (c == 0x06 || c == 0x07)
					{//Ŀǰֻ���������ӹ�����
						pMbx->SubFuncCode = c;
					//	crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					}
					else
					{
						pMbx->RxCount=0;
						pMbx->Broadcast = FALSE;
						pMbx->RxLen = 0;
						return RECV_FRAME_ERR;
					}				
				}				 
				else if ( pMbx->Broadcast == TRUE)
				{//��֧�ֹ㲥
					pMbx->RxCount=0;
					pMbx->Broadcast = FALSE;
					pMbx->RxLen = 0;
					return RECV_FRAME_ERR;
				}					
			}
			else if ( pMbx->FuncCode == MBX_FUNC_DEVICE_CTRL )
			{//֧�ֹ㲥����
				if (pMbx->RxCount == 3)
				{					
					if (c == MBX_CTRL_SET_TIME
						|| MBX_CTRL_RESET
						|| MBX_CTRL_CLEAR_FLASH
						|| MBX_CTRL_CLEAR_FRAM)
					{//�豸������ı��ĳ��ȹ̶�Ϊ13�ֽ�
						pMbx->SubFuncCode = c;
						pMbx->RxLen = MBX_PDU_FUNC_DEVICE_CTRL_LEN + MB_SER_PDU_PDU_OFF ;
					}
					else
					{
						pMbx->RxCount=0;
						pMbx->Broadcast = FALSE;
						pMbx->RxLen = 0;
						return RECV_FRAME_ERR;
					}
				}
			}
			else if (  pMbx->FuncCode == MB_FUNC_MEI  )
			{
				if (pMbx->RxCount == 3)
				{
					pMbx->SubFuncCode = c;
					if ( c== 0x0E  )
					{
						pMbx->RxLen = MB_PDU_FUNC_MEI_LEN+ MB_SER_PDU_PDU_OFF;
						crc16_ex(&c,1,& pMbx->ModbusRxCRC);
					}
					else
					{
						pMbx->FuncCode=0;
						pMbx->RxCount=0;
						pMbx->RxLen = 0;
						return RECV_FRAME_ERR;
					}
				}
			}
			else if ( pMbx->FuncCode  == MB_FUNC_READWRITE_MULTIPLE_REGISTERS &&  pMbx->RxCount==10 )
			{
				pMbx->RxLen = c +  10;
			}			 		
		}		
	}
	return RECV_FRAME_BYTE_OK;
}
/*********************************************************************************************************
** ��������: RecvData
** ��������: RecvData
**
** ���������� 
**
** �䡡��:  MBX * pMbx
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��9��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U RecvData( MBX * pMbx )
{
	INT8U  Err = 0;
	INT16U nRecvNum = 0;
	INT16U i = 0;

	if (pMbx == NULL)
		return	FALSE; 
	
	OSSemPend(pMbx->pUartRecvSem, 0, &Err);

	//������
	if (Err != OS_NO_ERR)
		return FALSE;	

    // �鿴�յ���������  
	nRecvNum = GetUartFifoStatus(pMbx->UartId, RX_FIFO);      
	if (nRecvNum==0 || nRecvNum > MAX_ADU_LENGTH)
	{
		FlushUartFifo(pMbx->UartId, RX_FIFO);
		return FALSE;
	}
	 
	nRecvNum = ReadUart (pMbx->UartId,pMbx->TempBuf , min(nRecvNum,MAX_ADU_LENGTH), NULL);	    
	if (nRecvNum==0 || nRecvNum > MAX_ADU_LENGTH)
		return FALSE;

	while (TRUE)
	{
		Err= GetOneFrame(pMbx, pMbx->TempBuf[i] );
		if (Err == 0)
		{//���Ĳ���Ҫ��,������һ���ֽ�
			i++;
			if (i>=nRecvNum || i>=MAX_ADU_LENGTH)
				return FALSE;
		}
		else if ( Err == 1 )
		{//���ķ���Ҫ�󣬵���û�����꣬������
			i++;
			if (i>=nRecvNum || i>=MAX_ADU_LENGTH)
				return FALSE;
		}
		else if ( Err == 2 )
		{//���Ľ�����ȫ��ȷ
			pMbx->RxCount=0;

			return TRUE;
		}
		else 
			return FALSE;
	} 
	return FALSE;
}
/*********************************************************************************************************
** ��������: PasreMsg
** ��������: PasreMsg
**
** ���������� �������ģ���������Ӧ�Ĵ��������������������ѭ�����õ�
**
** �䡡��:  MBX * pBuff
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��15��
** ��  ע:  ��ʱ�յ��ı�����һ����ȷ�ı���
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U PasreMsg(MBX * pMbx)
{
	MBException eException = MB_EX_NONE;
	INT16U chkcrc = 0;

#ifdef _DEBUG
	memset(pMbx->TxBuff,0,sizeof(INT8U)*MAX_ADU_LENGTH);	
#endif // _DEBUG

	//�ӽ��ջ��������Ƶ�����
	memcpy( pMbx->TxBuff,pMbx->RxBuff,pMbx->RxLen );
	pMbx->TxLen = pMbx->RxLen;	
	pMbx->RxLen = 0;

	switch ( pMbx->FuncCode)
	{
		//��Ȧ���� 
	case MB_FUNC_READ_COILS:
		eException = MBFuncReadCoils( pMbx->TxBuff,&  pMbx->TxLen );
		break;
	case MB_FUNC_WRITE_SINGLE_COIL:
		eException = MBFuncWriteCoil( pMbx->TxBuff,&  pMbx->TxLen );
		break;
	case MB_FUNC_WRITE_MULTIPLE_COILS:
		eException = MBFuncWriteMultipleCoils( pMbx->TxBuff,&  pMbx->TxLen );
		break;
		//���벿��
	case MB_FUNC_READ_DISCRETE_INPUTS:
		eException = MBFuncReadDiscreteInputs (pMbx->TxBuff,&  pMbx->TxLen );
		break;
		//�������ͼĴ��� AQ MW
	case MB_FUNC_READ_HOLDING_REGISTER:
		eException = MBFuncReadHoldingRegister(pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MB_FUNC_WRITE_REGISTER:
		eException = MBFuncWriteHoldingRegister(pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MB_FUNC_WRITE_MULTIPLE_REGISTERS:
		eException = MBFuncWriteMultipleHoldingRegister(pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MB_FUNC_READWRITE_MULTIPLE_REGISTERS:
		eException = MBFuncReadWriteMultipleHoldingRegister(pMbx->TxBuff,& pMbx->TxLen );
		break;
		//����Ĵ��� AI
	case MB_FUNC_READ_INPUT_REGISTER:
		eException = MBFuncReadInputRegister( pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MB_FUNC_READ_FILE_RECORD:
		eException = MBXReadFileRecord( pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MB_FUNC_WRITE_FILE_RECORD:
		{
			if (pMbx->SubFuncCode == 0x06)
			{
				eException = MBXWriteFileRecord( pMbx->TxBuff,& pMbx->TxLen );
				break;
			}
			else if ( pMbx->SubFuncCode == 0x07 )
			{
				eException = MBXWriteFileToFlash( pMbx->TxBuff,& pMbx->TxLen );
				break;
			}
			break;
		}
	case MBX_FUNC_READ_FORCEMARK:
		eException = MBXFuncReadForceMark( pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MBX_FUNC_WRITE_FORCEMARK:
		eException = MBXFuncWriteForceMark( pMbx->TxBuff,& pMbx->TxLen );
		break;
	case MBX_FUNC_DEVICE_CTRL:
		{
			if (pMbx->SubFuncCode == MBX_CTRL_SET_TIME )
			{
				eException = MBXFuncSetTime( pMbx->TxBuff,& pMbx->TxLen );
				
			}
			else if ( pMbx->SubFuncCode == MBX_CTRL_RESET )
			{

			}
			else
			{

			}

			if (pMbx->TxLen == 0)
			{//���������Ӧ��ģ���ֱ�ӷ���
				return FALSE;
			}
		}
	case MB_FUNC_MEI:
		{
			if (pMbx->SubFuncCode == 0x0E)
			{
				eException = MBFuncMEI( pMbx->TxBuff,& pMbx->TxLen );
			}
		}


		break;


	default:
		return FALSE;	 
	}

	if( eException != MB_EX_NONE )
	{//���������������
		/* An exception occured. Build an error frame. */
		pMbx->TxLen = 1;
		pMbx->TxBuff[pMbx->TxLen++] = ( INT8U )( pMbx->FuncCode | MB_FUNC_ERROR );
		pMbx->TxBuff[pMbx->TxLen++] = eException;
	}

	//У��CRC
	chkcrc = GetCRC16( pMbx->TxBuff,pMbx->TxLen);
	pMbx->TxBuff[pMbx->TxLen++]=LOBYTE(chkcrc);			
	pMbx->TxBuff[pMbx->TxLen++]=HIBYTE(chkcrc);

	//������֯���
	pMbx->TxCount=0;

 	return TRUE; 
}

static void SendResponse(MBX *pMbx)
{
	INT32U temp = 0;

	if (pMbx == NULL)
		return; 

	if( pMbx->TxCount<pMbx->TxLen)
	{
		temp = WriteUart (pMbx->UartId, &pMbx->TxBuff[pMbx->TxCount], pMbx->TxLen-pMbx->TxCount,  NULL);

		pMbx->TxTotalLen += pMbx->TxCount;
		pMbx->TxTotoalCnt ++;

		pMbx->TxCount+=temp;
	}
}
/*********************************************************************************************************
** ��������: ModbusMainCycle
** ��������: ModbusMainCycle
**
** ���������� ��������õ���ѭ��
**
** �䡡��:  MBX * pBuff
**          
** �䡡��:  void
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
extern void ModbusMainCycle(MBX * pMBX)
{
	INT8U bRet = FALSE;

// 	if(pMBX->bSend)	//�ڷ���̬
// 	{
// 		//��鷢�ͳ�ʱ
// 		if(pMBX->TxTimer>TX_OVERTIME)
// 		{
// 			//�����Ѿ���ʱ���ý���̬
// 			pMBX->bSend=FALSE;
// 			pMBX->TxLen=pMBX->TxCount=0;
// 			pMBX->TxTimer=0;
// 
// 			//�������
// 			pMBX->pfnTxEnable();
// 		}
// 	}
// 	else if(pMBX->RxCount>0 && pMBX->RxTimer>RX_OVERTIME)	//�ڽ���̬
	
// 	if(pMBX->RxCount>0 && pMBX->RxTimer>RX_OVERTIME)	//�ڽ���̬
// 	{//���ճ�ʱ����
// 		OS_ENTER_CRITICAL();
// 		pMBX->RxCount=0;
// 		pMBX->RxTimer=0;
// 		OS_EXIT_CRITICAL();
// 	}

	bRet = RecvData(pMBX);
	if (bRet == FALSE)
		return;

	//��LED��
	SetLed(LED_COMM,TRUE);

	//��������Ҫ����
	//���ݴ���
	bRet = PasreMsg(pMBX);

	OSTimeDlyHMSM(0,0,0,200);

	 //����Ƿ���������Ҫ����
	if(bRet)
	{
		SendResponse(pMBX);
	}
	SetLed(LED_COMM,FALSE); 
}
/*********************************************************************************************************
** ��������: InitMBX
** ��������: InitMBX
**
** ���������� ��ʼ��Ĭ��ֵ
**
** �䡡��:  MBX * pMBX
**          
** �䡡��:  void
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
extern void InitMBX( MBX *pMBX )
{
	if (pMBX == NULL)
		return;
//	pMBX->Address = 0;

	memset(pMBX->RxBuff,0,sizeof(INT8U)*MAX_ADU_LENGTH);
	pMBX->RxLen = 0;					//���ܳ���
	pMBX->RxCount = 0;					//���ܼ���

	memset(pMBX->TxBuff,0,sizeof(INT8U)*MAX_ADU_LENGTH);

	pMBX->TxLen = 0;					//���ͳ���
	pMBX->TxCount = 0;					//���ͼ���
 	
	pMBX->RxTimer = 0;					//����ʱ�������
	pMBX->TxTimer = 0;					//���ͳ�ʱ������
 
	pMBX->pUartRecvSem = OSSemCreate(0); //�����ź���                     


 	pMBX->ModbusRxCRC = 0;				//ModbusCRCУ��
	pMBX->FuncCode = 0;					//����������	
	pMBX->SubFuncCode = 0;

	pMBX->RxTotalLen = 0;
	pMBX->RxTotoalCnt =0;

	pMBX->TxTotalLen = 0;
	pMBX->TxTotoalCnt = 0;

	pMBX->RxCrcErr = 0;
}
