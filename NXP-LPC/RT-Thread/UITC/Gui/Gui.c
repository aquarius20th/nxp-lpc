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
#include "Message.h"
#include "ScreenBase.h"
#include "Gui.h"
#include "DC.h"
#include "TaskDef.h"
#include "Key.h"
#include "TimerMgr.h"


#include "LogoScreen.h"
#include "MainMenuScreen.h"
#include "ExtScreen.h"

CScreenMgr  g_ScreeLib;

CScreen * const screens[]=
{
	(CScreen*)&LogoScreen,
  	(CScreen*)&DefScreen,
	(CScreen*)&MainMenuScreen ,

	(CScreen*)&RealTimeValScr ,

};
 


// �������ڿ�
static void InitScreenLib( )
{
	INT8U i = 0;

	InitScreenMgr(&g_ScreeLib);
	InitLogoScreen( &LogoScreen );
 	InitDefaultScreen(&DefScreen); 	
	InitMainMenuScreen(&MainMenuScreen);

	InitRealTimeValScreen(&RealTimeValScr);

	for ( i=0;i<sizeof(screens)/sizeof(CScreenBase * );i++) 
	{
		AppendScreen(&g_ScreeLib, screens[i]);
	}
	//����Ĭ�ϻ���
	SwitchScreen(&g_ScreeLib, ID_START_SCREEN);
}

static void HandleScreenEvent(void)
{
	CScreen *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreeLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return;

	HandleEvent( & pScreen->Base  )	;
}
//�������ͣ��͸���ǰ��Ĵ���
static INT8U PostEventN(INT32U msg,INT32U param)
{
	CScreen *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreeLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return FALSE;

	return PostEvent( & pScreen->Base,msg,param );
}
//����������¼�
static UEVENT  g_GuiTaskEvent[MAX_ENENT_CNT];
/*********************************************************************************************************
** ��������: PostGuiTaskEvent
** ��������: PostGuiTaskEvent
**
** ����������  ��GUI���������Ϣ
**
** �䡡��:  INT32U msg
** �䡡��:  INT32U WParam
** �䡡��:  INT32U LParam
**          
** �䡡��:   extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��6��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U PostGuiTaskEvent( INT32U msg,INT32U WParam,INT32U LParam)
{ 
	INT8U  i = 0;
	INT8U Flag = FALSE;
	
	//�鿴�Ƿ����ظ����¼�
	for(i = 0;i < MAX_ENENT_CNT;i++)
	{
		if (g_GuiTaskEvent[i].Flag && g_GuiTaskEvent[i].Msg == msg)
		{
			g_GuiTaskEvent[i].Flag++;
			Flag = TRUE;
			return Flag;;
		}
	}
	for(i = 0;i < MAX_ENENT_CNT;i++)
	{
		if (g_GuiTaskEvent[i].Flag  == FALSE )
		{
			g_GuiTaskEvent[i].Msg = msg;
			g_GuiTaskEvent[i].WParam = WParam;
			g_GuiTaskEvent[i].LParam = LParam;
			g_GuiTaskEvent[i].Flag  = TRUE;
			Flag = TRUE;
			break;
		}
	}
	return Flag;
}
/*********************************************************************************************************
** ��������: HandleTaskEvent
** ��������: HandleTaskEvent
**
** ���������� ��������������¼� 
**
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��6��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U HandleTaskEvent( )
{
	INT8U Flag = FALSE;
	INT8U i = MAX_ENENT_CNT;
	UEVENT Event;

	memset(&Event,0,sizeof(UEVENT));

	for (;;)
	{
		if (g_GuiTaskEvent[i-1].Flag)
		{//
			//���Ƴ���
			Event.Msg = g_GuiTaskEvent[i-1].Msg;
			Event.WParam = g_GuiTaskEvent[i-1].WParam;
			Event.LParam = g_GuiTaskEvent[i-1].LParam;
			Event.Flag = TRUE;

			g_GuiTaskEvent[i-1].Flag = 0;
			g_GuiTaskEvent[i-1].Msg = 0;
			g_GuiTaskEvent[i-1].WParam = 0;
			g_GuiTaskEvent[i-1].LParam = 0;
			Flag = TRUE;

			break;
		}
		if(i == 0)
			break;
		i--;	
	}
	if(Flag)
	{//�����¼�
		if (Event.Msg == LCD_WM_PAINT)
		{
			UpdateScreen((INT8U)Event.WParam);
			return TRUE;
		}	
	}
	return FALSE;
}
static void GuiTask(void *pdata)
{
	INT16U  key = 0;
	INT16U  nTimerID = 0;
	pdata = pdata;
	
	//����Һ��
	TurnOnLcd();
	//5���ر�Һ��
	nTimerID = SetTimer(nTimerID,5000,NULL,NULL);

	while (TRUE)
	{
		//��ȡ����
		key = 0;
		if (KeyHit())
		{
			key = GetKey( 0 );
			if (key !=KEY_NONE )
			{//�а���������LCD�ĵ�
				TurnOnLcd();
				nTimerID = SetTimer(nTimerID,10000,NULL,NULL);
				 


				//1.�������Ƿ��������ȹ��ܼ�

				//2.������Ϣ
				PostEventN(LCD_WM_KEYDOWN,key );


			}
			else
			{
				//�رյ�

			}
		}
		else
		{//û�а���
			if (nTimerID)
			{
				if (IsTimeTo(nTimerID))
				{//��ʱ���� 
					TurnOffLcd();
					KillTimer(nTimerID);
					nTimerID = 0;
				}
			}
		}
	

		//��Ϣ����
		HandleMessage();
		HandleScreenEvent( );
		HandleTaskEvent( );
		OSTimeDlyHMSM(0,0,0,200);
	//	OSTimeDly(OS_TICKS_PER_SEC/4);
	}
}



static OS_STK  GUITaskStk [GUI_TASK_STK_SIZE]; 

extern void InitGuiTask( )
{
	//LCD��ʼ��
	InitLcd( );
	// �����ʼ��
	InitScreenLib();
	//��������
	OSTaskCreate (GuiTask, (void *)0, 	&GUITaskStk[GUI_TASK_STK_SIZE-1], PRIO_GUI_TASK);

	//��������ɨ��ģ��
	InitKeyDriver ( );
}
