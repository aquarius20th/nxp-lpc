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
#include <stdio.h>
#include "includes.h"
#include "ScreenBase.h" 
#include "VersionScr.h"
#include "StringTable.h"
#include "Message.h"
#include "DC.h"
#include "ClockMgr.h"

extern CScreenMgr  g_ScreeLib;

CVersionScreen      VersionScreen;       // �汾�������� 
 

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

 