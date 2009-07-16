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
#include "LogoScreen.h"
#include "StringTable.h"
#include "Message.h"
#include "DC.h"

extern CScreenMgr  g_ScreeLib;

CLogoScreen      LogoScreen;       // �汾��������

static OS_TMR *BrandingTmr;


CScreenDefault       defscreen;

static void OnMessageLogoScreen(INT32U msg, INT32U param)  
{
	CLogoScreen *pScreenExt = NULL;
	INT8U err = 0;
	switch ( msg )
	{
	case LCD_WM_INI:
	case LCD_WM_REFRASH: 
		{
			ClearScreen();
			DrawStringById(LCD_WIDTH>>1,0,ID_STRING_WISCOM,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);
			DrawStringById(LCD_WIDTH>>1,16,ID_STRING_BRANDING,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);	
		}
		break;
	case LCD_WM_TIMER:
		{
			// 2��ȴ���ʱ����Ϣ���˳����������Ĭ����ʾ����
	//		if(param&TimerMask(TIMER_0))
			if(OSTmrStop(BrandingTmr,OS_TMR_OPT_NONE,(void *)0,&err))
			{
				// �˳��ȴ�״̬
				 SwitchScreen(&g_ScreeLib,pScreenExt->Base.ParentID);
			}
		}
		break;
	default:
		break;
	}
}


//���������麯�� 
static void OnKeyDownLogoScreen(INT16U keyCode)   
{	
	// ����������£��˳���ʼ����
	if (keyCode!=0) 
	{
		// �˳��ȴ�״̬
		SwitchScreen(&g_ScreeLib,LogoScreen.Base.ParentID);
	}
}

static void OnInitLogoScreen(void)
{
	PostMessage(LCD_WM_INI,0);
}
 
//�˳�ʱ����
static void OnDestoryLogoScreen(void)
{
	INT8U err = 0;
	// �ض�ʱ��
	if (BrandingTmr)
	{
		OSTmrDel(BrandingTmr,&err);
	}	
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
void LogoScreenTimer (void *ptmr, void *parg)
{
	if (BrandingTmr && BrandingTmr == ptmr)
	{
		PostMessage(LCD_WM_TIMER,parg);
	}
}

extern void InitLogoScreen(CLogoScreen *pScreenExt )
{
	INT8U i = 0;
	INT8U err = 0;

	BrandingTmr = NULL;

	if (pScreenExt)
	{
		//��װ��ʱ��
		BrandingTmr = OSTmrCreate( 100,	2000,OS_TMR_OPT_PERIODIC,LogoScreenTimer,(void *)pScreenExt,(INT8U *)0,&err);
		if (err == OS_ERR_NONE) 
		{/* Timer was created but NOT started */
			OSTmrStart(BrandingTmr,&err);
		}	

		SetScreenInfo(& pScreenExt->Base,ID_DEFAULTSCREEN, ID_START_WINDOW, ID_STRING_NONE);
		pScreenExt->Base.pfnMessage = OnMessageLogoScreen;
		pScreenExt->Base.pfnKeyDown = OnKeyDownLogoScreen;
		pScreenExt->Base.pfnDestory = OnDestoryLogoScreen;
		pScreenExt->Base.pfnInit    = OnInitLogoScreen;
		pScreenExt->Base.pfnOnNotify = NULL;

		if (pScreenExt->Base.pfnInit)
		{
			pScreenExt->Base.pfnInit();
		}

		//�ô��ڹ��
		for(i=0; i<STATE_COUNT; i++)
		{
			pScreenExt->Cursor[i].Row = 0;
			pScreenExt->Cursor[i].Col = 0;
		}

		//��ǰ��ʾ״̬
		pScreenExt->CurrentState = STATE_NORMAL;  
	}
}




// ����ѭ����ʾ�������ͳ�ʼ����ʾ���ݸ���
static void InitDftScreenDispNum(CScreenDefault *pScreenExt,INT16U nTypeIndex)
{
	INT16U nTypeString=0;

	if (pScreenExt == NULL)
		return;

	pScreenExt->CurrentTypeIndex=nTypeIndex;
	pScreenExt->CurrentMeasIndex=0;

// 	if(nTypeIndex<MeasDispType.MeasTypeCount)
// 	{
// 		nTypeString=MeasDispType.MeasDisp[nTypeIndex].nMeasType;
// 	}
// 	else
// 	{
// 		nTypeString=ID_STRING_MEASTYPE_ALL;
// 	}

 	 ClearScreen();
//     DrawString(60,8,nTypeString,PEN_COPY,ALIGN_CENTER);
}

extern void InitDefaultScreen(CScreenDefault *pScreenExt )
{
	if (pScreenExt)
	{

	}
}

