/****************************************Copyright (c)**************************************************
**                                      �汾��������
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
#include <stdio.h>
#include "ScreenBase.h" 
#include "VersionScr.h"
#include "StringTable.h"
#include "extscreendef.h"
#include "GuiEvent.h"

#include "dc.h"

#if 0
CVersionScreen      VersionScreen;
 

static void OnMessageVersionScreen(INT32U msg, INT32U param)  
{
	CVersionScreen *pScreenExt = &VersionScreen;
	INT8U err = 0;
	switch ( msg )
	{
	case LCD_WM_INI:
	case LCD_WM_REFRASH: 
		{
			ClearScreen();
	//		DrawStringById(LCD_WIDTH>>1,0,ID_STRING_WISCOM,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);
	//		DrawStringById(LCD_WIDTH>>1,16,ID_STRING_BRANDING,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);	
		}
		break;
	case LCD_WM_TIMER:
		{
		 
		}
		break;
	default:
		break;
	}
}


//���������麯�� 
static void OnKeyDownVersionScreen(INT16U keyCode)   
{	
	// ����������£��˳���ʼ����
	if (keyCode!=0) 
	{
		// �˳��ȴ�״̬
		SwitchScreen(&g_ScreeLib,VersionScreen.Base.ParentID);
	}
}

static void OnInitVersionScreen(void)
{
//	PostMessage(LCD_WM_INI,0);
	PostEvent(&VersionScreen.Base,LCD_WM_INI,0);
}
 
//�˳�ʱ����
static void OnDestoryVersionScreen(void)
{
	 
}
/*********************************************************************************************************
** ��������: LogoScreenTimer
** ��������: LogoScreenTimer
**
** ���������� 
**
** �䡡��:  void * ptmr
** �䡡��:  void * parg
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��22��
** ��  ע:  �ú������뾡���̣ܶ����Բ��ü�����Ϣ�ķ�ʽ�����÷���
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void VersionScreenTimer (void *ptmr, void *parg)
{
	 
}

extern void InitVersionScreen(CVersionScreen *pScreenExt )
{
	INT8U i = 0;
	INT8U err = 0;

 
	if (pScreenExt)
	{
		InitScreenBase( & pScreenExt->Base );
	 
		SetScreenInfo(& pScreenExt->Base,ID_DEFAULT_SCREEN, ID_VER_SCREEN, ID_STRING_NONE);
		pScreenExt->Base.pfnMessage = OnMessageVersionScreen;
		pScreenExt->Base.pfnKeyDown = OnKeyDownVersionScreen;
		pScreenExt->Base.pfnDestory = OnDestoryVersionScreen;
		pScreenExt->Base.pfnInit    = OnInitVersionScreen;
		pScreenExt->Base.pfnOnNotify = NULL;

// 		if (pScreenExt->Base.pfnInit)
// 		{
// 			pScreenExt->Base.pfnInit();
// 		}

	 
	}
}
#endif
 

/*********************************************************************************************************
** ��������: VerScrCtor
** ��������: VerScrCtor
**
** ����������  ���캯��
**
** �䡡��:  CScreenBase * pScr
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��16��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void VerScrCtor( CScreenBase *pScr )
{

}
/*********************************************************************************************************
** ��������: VerScrDtor
** ��������: VerScrDtor
**
** ���������� �������� 
**
** �䡡��:  CScreenBase * pScr
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��16��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void VerScrDtor(CScreenBase *pScr)
{
	ASSERT(pScr);

}

//��������ʱ����
static void OnCreateVersionScreen( CScreenBase *pScr )
{
	ClearScreen();
 	DrawStringById(LCD_WIDTH>>1,0,ID_STRING_LOGO,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);
 	DrawStringById(LCD_WIDTH>>1,16,ID_STRING_LOGO,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);

}
//�˳�ʱ����
static void OnDestoryVersionScreen( CScreenBase *pScr )
{

}

static void OnInitVersionScreen( CScreenBase *pScr,INT32U wParam,INT32U lParam )
{

}

static INT32U VersionScreenProc (GUI_HWND hWnd, INT32U message, GUI_WPARAM wParam, GUI_LPARAM lParam)
{
	switch (message) 
	{
	case GUI_EVENT_CREATE:
		{
// 				int timeout = (int)GetWindowAdditionalData (hWnd);
// 				if (timeout >= 10)
// 					SetTimer (hWnd, _ID_TIMER, timeout / 10);
				break;
		}

	case GUI_EVENT_TIMER:
		//	KillTimer (hWnd, _ID_TIMER);
		//	ShowWindow (hWnd, SW_HIDE);
		break;

	case GUI_EVENT_PAINT:
		{
// 				HDC hdc;
// 				const char* text;
// 
// 				hdc = BeginPaint (hWnd);
// 
// 				text = GetWindowCaption (hWnd);
// 				SetBkMode (hdc, BM_TRANSPARENT);
// 				SelectFont (hdc, GetSystemFont (SYSLOGFONT_WCHAR_DEF));
// 				TabbedTextOut (hdc, _MARGIN, _MARGIN, text);
// 
// 				EndPaint (hWnd, hdc);
			return 0;
		}

	case GUI_EVENT_DESTROY:
		{
		//	KillTimer (hWnd, _ID_TIMER);
			return 0;
		}	 
	}

	return DefaultScreenProc(hWnd, message, wParam, lParam);
}


CScreenBase * InitVerScreen(void)
{
	INT32U nSize = sizeof(CVersionScreen);
	CScreenBase *pScr = NULL;

	pScr = CreateScreen(nSize ,VerScrCtor,VerScrDtor );
	ASSERT(pScr);
	SetScreenInfo(pScr,ID_DEFAULT_SCREEN, ID_VER_SCREEN, ID_STRING_NONE);
	pScr->ScreenProc = VersionScreenProc;
	return pScr;
}
