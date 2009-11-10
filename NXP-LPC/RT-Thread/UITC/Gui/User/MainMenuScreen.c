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
#include "ScreenBase.h"
#include "MainMenuScreen.h"
#include "StringTable.h"
#include "Message.h"
#include "DC.h"

extern CScreenMgr  g_ScreeLib;

CMainMenuScreen  MainMenuScreen;

/************************************************************************
* �õ���ȫ�ֱ���
************************************************************************/
 
const CMenuData MainMenu[]=
{
 	{ID_REALTIME_VAL,	ID_STRING_VALUE_TAB},  //ʵ��ֵһ����
  	{ID_GATE_CTRL,		ID_STRING_GATE_CTRL }, //բ�Ų���
	{ ID_DEVICE_CFG, ID_STRING_DEVICE_CFG  },   //װ�ò���

// 	{ID_SYSSET,			ID_STRING_SYSSET},   //ϵͳ���ã�
// 	{ID_PROJSET,		ID_STRING_PRJSET},  // �������ã�
// 	{ID_SYSINFO,		ID_STRING_SYSINFO},  //ϵͳ��Ϣ
// 	{ID_DEVICE,			ID_STRING_DEVICEMODEL},	//װ������
// 	{ID_DEVICEDEBUG,	ID_STRING_DEBUG},    //װ�õ��ԣ�
// 	{ID_OTHER,			ID_STRING_OTHER} 	 //�������ã�
	{ ID_RUN_STAT, ID_STRING_RUN_STAT }, //բ������ͳ��
	{ ID_VER_INFO, ID_STRING_VER_INFO } //�汾��Ϣ

};


static void OnMessage(INT32U msg, INT32U param)  
{
	switch ( msg )
	{
	case LCD_WM_INI:
		{
			ClearScreen();
			DrawScreenCaption((CScreen*)&MainMenuScreen,0,0  );
			//	DrawStringById(LCD_WIDTH>>1,0,ID_STRING_DEVICE_CFG,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);
			// 	DrawStringById(LCD_WIDTH>>1,16,ID_STRING_REALTIME_VAL,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);	

			DrawScreenStatusBar( );
			InvalidateScreen( FALSE );
		}
		break;
	case LCD_WM_REFRASH: 
		{ 
			UpdateScreen(TRUE);		
		}
		break;
	case LCD_WM_TIMER:
		{
			
		}
		break;
	default:
		break;
	}
	OnCtrlMsg((CCtrl *) &MainMenuScreen.Menu,msg,param );
}


//���������麯�� 
static void OnKeyDown (INT16U keyCode)   
{	
	if(keyCode == KEY_3)
		// �˳��ô��ڣ�������һ������
		SwitchScreen(&g_ScreeLib,  GetCurrentMenuID(& MainMenuScreen.Menu) );
 	else if(keyCode == KEY_4)	
		// �˳��ô��ڣ����븸����
		SwitchScreen(&g_ScreeLib,MainMenuScreen.Base.ParentID);

	// �˵�������Ӧ����
// 	if (MainMenuScreen.Menu.Base.pfnKeyDown)
// 	{
// 		MainMenuScreen.Menu.Base.pfnKeyDown( &MainMenuScreen.Menu.Base,keyCode );
// 	}
	OnCtrlKeyDown((CCtrl *) &MainMenuScreen.Menu ,keyCode );
}

static void OnInitScreen(void)
{
//	PostMessage(LCD_WM_INI,0);
	PostEvent( & MainMenuScreen.Base,LCD_WM_INI,0 );
}

//�˳�ʱ����
static void OnDestory(void)
{
//	ClearEvent( &(MainMenuScreen.Base) );	 
}
 


static void SetupResource( CMainMenuScreen *pScreenExt )
{
	if (pScreenExt)
	{
		 CreateLcdMenu( & pScreenExt->Menu,(LCDRECT*)  & LCD_RECT_MENU,(LCDRECT*)  & LCD_RECT_VARBAR )	 ;
		// �˵�����
//		pScreenExt->Menu.AddItem( MainMenu, sizeof(MainMenu)/sizeof(CMenuData));
		 AddMenuItems( & pScreenExt->Menu,MainMenu, sizeof(MainMenu)/sizeof(CMenuData));
		// �۽���ǰѡ��Ĳ˵�
//		pScreenExt->Menu.SetFocus();	
	}

}
extern void InitMainMenuScreen(CMainMenuScreen *pScreenExt )  
{ 
	if (pScreenExt)
	{	 
		InitScreenBase( & pScreenExt->Base );
		SetScreenInfo(& pScreenExt->Base,ID_MAIN_SCREEN,ID_MAIN_SCREEN,ID_STRING_MAIN_MENU);
		pScreenExt->Base.pfnMessage = OnMessage;
		pScreenExt->Base.pfnKeyDown = OnKeyDown;
		pScreenExt->Base.pfnDestory = OnDestory;
		pScreenExt->Base.pfnInit    = OnInitScreen;
		pScreenExt->Base.pfnOnNotify = NULL;

// 		if (pScreenExt->Base.pfnInit)
// 		{
// 			pScreenExt->Base.pfnInit();
// 		}	
		SetupResource ( pScreenExt );
	}
}

 