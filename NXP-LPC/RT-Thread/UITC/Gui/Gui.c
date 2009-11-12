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
#include "applib.h"
#include "GuiList.h"
#include "keydrv.h"
 
#include "ScreenBase.h"  
#include "GuiEvent.h"
#include "GuiConst.h"

#include "versionScr.h"
#include "devicecfgscreen.h"



//�������
struct SCREEN_MGR
{
	gui_list_t  ScrLib;  // ����ָ������
	INT16U 	    ScreensCnt;	 // ��������
	INT8U       ActiveScrID; //��ǰ�����ID
};

typedef struct SCREEN_MGR CScreenMgr;

static CScreenMgr g_ScreenLib;

 
/*********************************************************************************************************
** ��������: GetCurrentScreenPtr
** ��������: GetCurrentScreenPtr
**
** ����������  �õ���ǰ��Ļ��ָ��
**
** �䡡��:  CScreenMgr * pMgr
**          
** �䡡��:   CScreenBase*
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��12��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CScreenBase* GetCurrentScreenPtr(CScreenMgr *pMgr)
{
	CScreenBase *pScr = NULL ;
	gui_list_t *n = NULL;
	if(pMgr && GuiListIsEmpty(& pMgr->ScrLib ) )
	{
		ASSERT(pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID);
		if ( pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID )
		{//ѭ������
			for ( n = pMgr->ScrLib.pNext ; n != & pMgr->ScrLib; n = n->pNext )
			{
				pScr = CONTAINING_RECORD(n, CScreenBase,List);
				ASSERT(pScr);
				if (pScr && pScr->CurrentID == pMgr->ActiveScrID )
				{
					return pScr;
				}
			}
		}
	}
 	return NULL;
}  
// �õ�ָ�����ScreenID��Ļ��ָ��
CScreenBase* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID)
{
// 	if(pMgr == NULL || (nScreenID >= MAXSCREEN) || (nScreenID == ID_SCREEN_NULL))
// 		return NULL;
// 	else
// 		return (pMgr->m_ScreenArray[nScreenID]);
	CScreenBase *pScr = NULL ;
	gui_list_t *n = NULL;
	if(pMgr && GuiListIsEmpty(& pMgr->ScrLib ) )
	{
		ASSERT(pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID);
		if ( pMgr->ActiveScrID > ID_SCREEN_NULL && pMgr->ActiveScrID < MAX_SCREEN_ID )
		{//ѭ������
			for ( n = pMgr->ScrLib.pNext ; n != & pMgr->ScrLib; n = n->pNext )
			{
				pScr = CONTAINING_RECORD(n, CScreenBase,List);
				ASSERT(pScr);
				if (pScr && pScr->CurrentID == nScreenID )
				{
					return pScr;
				}
			}
		}
	}
	return NULL;
}
/*********************************************************************************************************
** ��������: SwitchScreen
** ��������: SwitchScreen
**
** ���������� �л������ScreenID��Ļ 
**
** �䡡��:  INT8U nScreenID
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��12��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SwitchScreen(INT8U nScreenID)
{
	CScreenBase * pScreen = NULL ;
	CScreenMgr *pMgr = &g_ScreenLib;

 	pScreen=GetCurrentScreenPtr(pMgr);

	//��������ԭ����
	if(pScreen && pScreen->pfnDestory)
	{
		pScreen->pfnDestory(pScreen);
	}

	//�л�����һ����
//	pScreen=GetScreenPtr(pMgr,nScreenID);

	if(pScreen == NULL)
		return;

 	//����л�����������򱣴���������򷵻ش���
 //	if(nScreenID == ID_PASSWORD || nScreenID == ID_MODALDIALOG)
 //		SetFatherID(& pScreen->Base,GetActiveWinID());

//	SetActiveWinID(nScreenID);

 	//�����Ļ,ģʽ�Ի�����ΪҪ�����ϸ������ͼ�����в���������
 //	if(nScreenID != ID_MODALDIALOG)
 //		ClearScreen();
	if(pScreen != NULL && pScreen->pfnInit)
 		pScreen->pfnInit(pScreen);// ����Ĭ�ϳ�ʼ�����룬���罨����Դ

}
/*********************************************************************************************************
** ��������: InitScreenLib
** ��������: InitScreenLib
**
** ����������  ��ʼ�����е���Ļ
**
**
** �䡡��:
**
** ȫ�ֱ���:
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��11��
** ��  ע:
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void InitScreenLib( )
{
	INT8U i = 0;
	CScreenBase *pScreen = NULL;

	//��ʼ��������
	GuiListInit(&(g_ScreenLib.ScrLib));

	//����LOGO SCREEN
	//pScreen = ( );

	pScreen = InitVerScreen();

	//��ӵ�������
	GuiListAppend(&(g_ScreenLib.ScrLib),&(pScreen->List));
	g_ScreenLib.ScreensCnt ++;

	pScreen = InitDevCfgScreen();
	GuiListAppend(&(g_ScreenLib.ScrLib),&(pScreen->List));
	g_ScreenLib.ScreensCnt ++;


//	InitScreenMgr(&g_ScreeLib);
//	InitLogoScreen( &LogoScreen );
// 	InitDefaultScreen(&DefScreen);
//	InitMainMenuScreen(&MainMenuScreen);
//
//	InitRealTimeValScreen(&RealTimeValScr);
//
//	for ( i=0;i<sizeof(screens)/sizeof(CScreenBase * );i++)
//	{
//		AppendScreen(&g_ScreeLib, screens[i]);
//	}
//	//����Ĭ�ϻ���
//	SwitchScreen(&g_ScreeLib, ID_START_SCREEN);
}
/*********************************************************************************************************
** ��������: HandleTaskEvent
** ��������: HandleTaskEvent
**
** ����������  �������񼶱����Ϣ
**
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��12��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U HandleTaskEvent( )
{

	return TRUE;
}

 
/*********************************************************************************************************
** ��������: SendEventN
** ��������: SendEventN
**
** ����������  �������ͣ��͸���ǰ��Ĵ���
**
** �䡡��:  INT32U msg
** �䡡��:  INT32U param
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��12��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U SendEventN(INT32U msg,INT32U param)
{
	CScreenBase *pScreen = NULL;
	CScreenMgr *pMgr = &g_ScreenLib;

	pScreen = GetCurrentScreenPtr(pMgr);

	if (pScreen == NULL)
		return FALSE;

	return SendScreenEvnent( pScreen ,msg,param );
}
static void GuiTask(void *pdata)
{
	INT16U  key = 0;
	pdata = pdata;

	while(TRUE)
	{
		//��ȡ����
		key = 0;
		if (KeyHit())
		{
			key = GetKey( 30 );
			if (key != KEY_NONE)
			{//�а���������LCD�ĵ�
			//	TurnOnLcd();
			//	nTimerID = SetTimer(nTimerID, 10000, NULL, NULL);

				//1.�������Ƿ��������ȹ��ܼ�

				//2.������Ϣ
			//	PostEventN(LCD_WM_KEYDOWN, key);

			}
			else
			{
				//�رյ�

			}
		}
		//�����Ƿ������������͹�������Ϣ


	}

}

//���������Ķ�ջ����
#define  GUI_TASK_STK_SIZE      512
#define  PRIO_GUI_TASK          30

static unsigned char  GuiTaskStk [GUI_TASK_STK_SIZE];
struct rt_thread Gui_Thread;

void InitGuiTask( void  )
{
	//��ʼ��������Ϣ����
	InitScrEventList(  );
	// �����ʼ��
	InitScreenLib();
	//��������
	rt_thread_init(&Gui_Thread,"Gui_Thread",GuiTask, RT_NULL, &GuiTaskStk[0], sizeof(GuiTaskStk),
			PRIO_GUI_TASK, 10);

	rt_thread_startup(&Gui_Thread);
}
