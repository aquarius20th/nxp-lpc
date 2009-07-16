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
#include "includes.h" 
#include "ScreenBase.h"
#include "LogoScreen.h"
#include "Gui.h"
#include "DC.h"
#include "TaskDef.h"
#include "Key.h"

CScreenMgr  g_ScreeLib;

CScreenBase * const screens[]=
{
	(CScreenBase*)&LogoScreen,
//	(CScreenBase*)&defscreen

};
 


// �������ڿ�
void InitScreenLib( )
{
	INT8U i = 0;
	INT8U nScreenCnt = 0;

	InitLogoScreen( &LogoScreen );

//	InitDefaultScreen(&defscreen);

	for ( i=0;i<sizeof(screens)/sizeof(CScreenBase * );i++) 
	{
		AppendScreen(&g_ScreeLib, screens[i]);
	}


	//����Ĭ�ϻ���
	SwitchScreen(&g_ScreeLib, ID_START_WINDOW);
}

static void Gui_Task(void *pdata)
{
	INT8U	status;
	INT16U key = 0;
	pdata = pdata;

	while (TRUE)
	{
		//��ȡ����
		key = 0;
		if (key)
		{//�а���������LCD�ĵ�

			//1.�������Ƿ��������ȹ��ܼ�

			//2.������Ϣ

		}
		else
		{
			//�رյ�

		}

		//��Ϣ����
		HandleMessage();
		OSTimeDlyHMSM(0,0,0,200);
	//	OSTimeDly(OS_TICKS_PER_SEC/4);
	}
}



static OS_STK  GUITaskStk [GUI_TASK_STK_SIZE];


extern void InitGuiTask( )
{
	//LCD��ʼ��
	GXM12232_SED1520_initlcd();

	//������ʼ��
//	KeyPress_Initial();

	//��ֵ��ʾ��ʼ��
//	MeasDisp_Initial();

	// �����ʼ��
	InitScreenLib();
	//����Һ��
	//����Һ��
	TurnOnLed();



	//��������
	OSTaskCreate (Gui_Task, (void *)0, 	&GUITaskStk[GUI_TASK_STK_SIZE-1], PRIO_GUI_TASK);

	//��������ɨ��ģ��
	InitKeyDriver ( );
}
 

 