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

#include "TaskDef.h"
#include "hd_drive.h"	  
#include "IoAdapter.h"
#include "hd_Init.h"
#include "ram.h"
#include "UEInit.h"
#include "viccontrol.h"
#include "TimerMgr.h"
#include "ClockMgr.h"
#include "MODBUS.h"
#include "AdvCalc.h"
#include "Gui.h"
#include "FRamMgr.h"

 
 

void FlickerLed( )
{
	INT32U i = 0;
	for (i = 0; i < 12; i++)
	{
		SetLed(i,TRUE);	 
	}
	OSTimeDlyHMSM(0,0,0,500);   	 
	for (i = 0; i < 12; i++)
	{
		SetLed(i,FALSE);	 
	}

   	OSTimeDlyHMSM(0,0,0,300);  
	for (i = 0; i < 12; i++)
	{
		SetLed(i,TRUE);	 
	}
	OSTimeDlyHMSM(0,0,0,300);   	 
	for (i = 0; i < 12; i++)
	{
		SetLed(i,FALSE);	 
	}
	OSTimeDlyHMSM(0,0,0,200);  
	for (i = 0; i < 12; i++)
	{
		SetLed(i,TRUE);	 
	}
	for (i = 0; i < 12; i++)
	{
		SetLed(i,TRUE);
	 	OSTimeDlyHMSM(0,0,0,300);
		SetLed(i,FALSE);
	}
	OSTimeDlyHMSM(0,0,0,200);  
	 	 
	for (i = 0; i < 12; i++)
	{
		SetLed(i,FALSE);	 
	}
	for (i = 11; ;i--)
	{
		SetLed(i,TRUE);
	 	OSTimeDlyHMSM(0,0,0,300);
		SetLed(i,FALSE);
		if (i == 0)
			break;
	}
}

extern void IRQASMTimer3(void);

void IRQCTimer3(void)
{
 
	T3IR = 0x01; //����жϱ�־
	VICVectAddr = 0;  //֪ͨVIC�жϴ������
 	TimerMgrInIsr(1); 
}
 

static void DelayS (INT32U dly)
{
	INT32U i;
	for ( ; dly>0; dly--)
		for (i=0; i<5000; i++);
}
 
void MainTask(void *pdata)
{
	INT8U bRet = FALSE;

	INT8U count = 0;
	INT16U nTimerId = 1;
 	INT8U nLedState = FALSE; 

	pdata = pdata;
	BSP_init();
   	CPU_PIN_Init(); 
 
	//Ӳ����ʼ��
	SetupHardware();
	//�幷
	// 	hd_ClearWatchDog();
	//��ʱһ��ʱ�䣬�ȴ�Ӳ���������ȶ�
	DelayS(300);
	//�����ʼ��
	bRet = InitConfData( &Ram ); 
	if (bRet == FALSE)
	{
		SetLed(LED_FAULT,TRUE);
	}
	//��ʼ��װ������汾��
	InitDeviceVer ( &Ram );
	//��ʱ������
	InitTimerMgr();
	//��ʼ��FRAM,����FRAM������س�װ��ʱ��
	InitFRamMgrTsk();
	//��ʼ��ʱ��ģ��
	InitClockMgr();

	InitGatageTsk( );
	//ͨ������
	InitMBXTsk();

	InitGuiTask();

	//���ж�
//	Enable_Interupt();

 
	T3IR  = 0xFF;	  //���ȫ���жϱ�־
	T3TC  = 0x00;	  //��ʱ��������
	T3TCR = 0x01;     //������ʱ��
	T3MCR = 0x03;     //ƥ��Ĵ���,����ʱ����TCֵ��MR0ƥ��ʱ,��ʱ����λ,�������ж�
	T3MR0 = MS_TIMER;

//  VICIntEnClr	= (1 << 0X1B);	 //�ж�ʹ������ �Ĵ���
// 	VICVectAddr27 	= (INT32U)IRQASMTimer3;
// 	VICVectPri27 	= (0x20 | 0x05);
// 	VICIntEnable 	= (1 <<  0X1B);		 //�ж�ʹ�� �Ĵ���


   	vicIrqFuncSet(VIC_TIMER3,2,(INT32U)IRQASMTimer3);
 

	 FlickerLed( );
    //vicIrqEnable(4);
	SetTimer(nTimerId,1000,NULL,NULL);
	 while(1)
	 {
 	//	OSTimeDlyHMSM(0,0,0,500);
 	//	FlickerLed( );
		 
		 bRet = IsTimeTo(nTimerId);
		 if (bRet)
		 {
			 nLedState = !nLedState;
			 SetLed(LED_RUN,nLedState);

			 //����
			 TestMemData();				
		 }

// 		 nLedState = !nLedState;
// 		 SetLed(LED_RUN+1,nLedState);
		 OSTimeDlyHMSM(0,0,0,200);
	//    FlickerLed( );
	//	 OSTimeDly(OS_TICKS_PER_SEC/20 + 1);	//50ms
	 } 	
}

