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
#include "includes.h" 
#include "hd_Init.h"
#include "uart.h" 
#include "ram.h"
#include "hd_Init.h"
#include "Viccontrol.h"


/*********************************************************************************************************
** ��������: InitCom
** ��������: InitCom
**
** ���������� ����������Ϣ��ʼ��Ӳ��
**
** �䡡��:  MB_PORT * pPort  ����˲���Ϊ��[û��������Ϣ]�������Ĭ�����ý��г�ʼ��
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
extern void IRQASMUart0(void);
extern void IRQASMUart3(void);

static void InitCom( MB_PORT *pPort )
{
	INT32U nBaud = 0;
	UART_MODE uart;	
	UART_PARAM UartParam;
	
	if (pPort == NULL)
		return;	
	else
	{
		poeUart0ReviceSem = NULL;  
		poeUart3ReviceSem = NULL;  

		UartParam.bps=9600;        //������
		UartParam.datab=8;         // �ֳ��ȣ�5/6/7/8
		UartParam.stopb=1;         // ֹͣλ��1/2
		UartParam.parity=0;    	  // ��żУ��λ��0Ϊ��У�飬1����У�飬2Ϊż��У��
 
		//���ڳ�ʼ��
	//	UART0_Init(9600,&uart);
		InitUart( UART0, &UartParam,NULL);
		SetVICIRQ(VIC_UART0, 9, (INT32U)IRQASMUart0);
//		DisableVICIRQ(VIC_UART0);

		UartParam.bps = pPort->Baud;        //������
		UartParam.datab = pPort->DataBit;         // �ֳ��ȣ�5/6/7/8
		UartParam.stopb = 1;//pPort->StopBit;         // ֹͣλ��1/2
		UartParam.parity = pPort->ParityBit;      // ��żУ��λ��0Ϊ��У�飬1����У�飬2Ϊż��У��
		InitUart( UART3, &UartParam,NULL);
		SetVICIRQ(VIC_UART3, 8, (INT32U)IRQASMUart3);

//	 	DisableVICIRQ(VIC_UART3); 
// 		nBaud = pPort->Baud;
// 		uart.datab = pPort->DataBit;
// 		uart.stopb = pPort->StopBit + 1;
// 		uart.parity = pPort->ParityBit;
// 		UART3_Init(nBaud ,&uart);
		return;
	}
}
/*********************************************************************************************************
** ��������: LoadConfData
** ��������: LoadConfData
**
** ���������� ��flash����������Ϣ
**
** �䡡��:  CRamMain * pRam
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U LoadConfData(CRamMain *pRam)
{
	INT8U err = 0;
	INT16U nRet = 0;
	INT8U bRet = FALSE;
	INT8U *pBuff = NULL;
	INT32U nDataLen = 0; 
	INT32U nRetLen = 0;

	if (pRam == NULL)
		return FALSE;

 //	LoadFlashData();
	
	//����FCB
	nRet = LoadFcb( & pRam->Fcb,&err);
	if (nRet < sizeof(FCB) || nRet == 0)
		return FALSE;

	//����BIN�ļ����ڴ���
	bRet = GetBinDataBuff(&pBuff,&nDataLen );
	if (bRet == FALSE)
		return FALSE;
	//����BIN
	nRetLen = LoadBinData(pBuff, &pRam->BinData );
	if (nRetLen != nDataLen)
		return FALSE;

	return TRUE;
}
/*********************************************************************************************************
** ��������: InitConfData
** ��������: InitConfData
**
** ���������� ��ʼ��������Ϣ���ȴ�flash���أ��������ʧ�ܣ�����Ĭ����������
**
** �䡡��:  CRamMain * pRam
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U InitConfData(CRamMain *pRam)
{
	INT8U bRet = FALSE;

//	if (pRam == NULL)
//		return FALSE;

	bRet = LoadConfData(pRam);
	if (bRet == FALSE)
	{//����ʧ��  ����Ĭ������
		InitDefaultBinData(& pRam->BinData);
	}
	else
	{//�ɹ�

	}

	//��ʼ���ڴ�
	InitMemData();

	//����װ��
	SetDeviceAddr( pRam->BinData.HdCfg.CpuCfg.Port.Addr );
	
	//��������������ص�Ӳ��

	//����ͨ�ſ�
 	InitCom( & pRam->BinData.HdCfg.CpuCfg.Port );

	return bRet;
}