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
**��        ��:  ����ͨ������232���Կ���485�ڵ�������ܵ���Ҫ�ֳ�2�����������
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
#include "MODBUS.h"
#include "TaskDef.h"
//#include "hd_drive.h"
#include "uart.h"
#include "MBCommon.h"

static OS_STK	DbgMbxTaskStk [DBGMBX_TASK_STK_SIZE];
static OS_STK	CommMbxTaskStk [COMMMBX_TASK_STK_SIZE];

static  MBX  DbgMbx; 
static  MBX  CommMbx;

void MBX_Task(void *pdata)
{	
	MBX * pMBX = NULL;
	pMBX = (MBX *) pdata;

	while (TRUE)
	{
		ModbusMainCycle( pMBX);
		OSTimeDlyHMSM(0,0,0,200);
	}
}    
/*********************************************************************************************************
** ��������: SetDeviceAddr
** ��������: SetDeviceAddr
**
** ���������� ����װ�õ�ַ
**
** �䡡��:  INT8U Addr
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��22��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetDeviceAddr( INT8U Addr )
{
	DbgMbx.Address = Addr;
	CommMbx.Address = Addr;
}
 
/*********************************************************************************************************
** ��������: InitMBXTsk
** ��������: InitMBXTsk
**
** ���������� 
**
** �䡡��:  INT8U Addr
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��22��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U InitMBXTsk( void )
{
	InitMBX(&DbgMbx);
//	DbgMbx.pUartRecvSem = OSSemCreate(0);
	poeUart0ReviceSem  =  DbgMbx.pUartRecvSem ;
	
	DbgMbx.UartId = UART0;

	InitMBX(&CommMbx);
//	CommMbx.pUartRecvSem = OSSemCreate(0);
 	poeUart3ReviceSem =  CommMbx.pUartRecvSem  ;
  	CommMbx.UartId = UART3;

	//�������Կ�ͨ������
//   OSTaskCreate (DbgMBX_Task, 0, 	&DbgMbxTaskStk[DBGMBX_TASK_STK_SIZE-1], DBGMBX_TASK_PRIO);

	//����ͨ�ſڿ�ͨ������
//	OSTaskCreate (CommMBX_Task, 0, 	&CommMbxTaskStk[COMMMBX_TASK_STK_SIZE-1], COMMMBX_TASK_PRIO);

	OSTaskCreateExt (MBX_Task, (void *)&CommMbx, &CommMbxTaskStk[COMMMBX_TASK_STK_SIZE-1],
		COMMMBX_TASK_PRIO,
		COMMMBX_TASK_PRIO,
		&CommMbxTaskStk [0],
		COMMMBX_TASK_STK_SIZE,
		(void *)&CommMbx,
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 

	OSTaskCreateExt (MBX_Task, (void *)&DbgMbx, &DbgMbxTaskStk[DBGMBX_TASK_STK_SIZE-1],
		DBGMBX_TASK_PRIO,
		DBGMBX_TASK_PRIO,
		&DbgMbxTaskStk [0],
		DBGMBX_TASK_STK_SIZE,
		(void *)&DbgMbx,
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 

	return TRUE;
}

extern void CommTimerHandle( )
{
	DbgMbx.RxTimer++;
	DbgMbx.TxTimer++;
	 
	CommMbx.RxTimer++;
	CommMbx.TxTimer++;
	 	
	if(DbgMbx.RxCount>0 && DbgMbx.RxTimer>RX_OVERTIME)	//�ڽ���̬
	{
		DbgMbx.RxCount=0;
		DbgMbx.RxTimer=0;
	}
	if(CommMbx.RxCount>0 && CommMbx.RxTimer>RX_OVERTIME)	//�ڽ���̬
	{
		CommMbx.RxCount=0;
		CommMbx.RxTimer=0;
	}	
}
