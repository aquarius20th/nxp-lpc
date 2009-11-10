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
#include "StringTable.h"
#include "Message.h"
#include "DC.h"
#include "ClockMgr.h"
#include "ExtScreen.h"

extern CScreenMgr  g_ScreeLib;

CRealTimeValScreen   RealTimeValScr;       //ʵʱ��ֵ   

static OS_TMR  *pValScrTmr = NULL;

/*********************************************************************************************************
** ��������: RealTimeValScrTimer
** ��������: RealTimeValScrTimer
**
** ����������  
**
** �䡡��:  void * ptmr
** �䡡��:  void * parg
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��6��24��
** ��  ע:  �ú������뾡���̣ܶ����Բ��ü�����Ϣ�ķ�ʽ�����÷���
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void RealTimeValScrTimer (void *ptmr, void *parg)
{
	if (pValScrTmr && pValScrTmr == ptmr)
	{
		PostEvent(&RealTimeValScr.Base,LCD_WM_TIMER,(INT32U)parg);
	}
}
/*********************************************************************************************************
** ��������: DrawValueScrStatic
** ��������: DrawValueScrStatic
**
** ����������  �����ڵľ�̬����
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��6��24��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void DrawValueScrStatic( )
{

}

static void DispRealTimeVal( )
{

}

static void OnMessageRealTimeValScreen(INT32U msg, INT32U param)  
{
	CRealTimeValScreen *pScreenExt = &RealTimeValScr;
	INT8U err = 0;
	switch ( msg )
	{
	case LCD_WM_INI:
	case LCD_WM_REFRASH: 
		{
			ClearScreen();
			//������
 			DrawStringById(LCD_WIDTH>>1,0,ID_STRING_LOGO,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);
			//����̬����
			DrawValueScrStatic( );
 		//	DrawStringById(LCD_WIDTH>>1,16,ID_STRING_BRANDING,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);	
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
static void OnKeyDownRealTimeValScreen(INT16U keyCode)   
{	
	// ����������£��˳���ʼ����
	if (keyCode!=0) 
	{
		// �˳��ȴ�״̬
		SwitchScreen(&g_ScreeLib,RealTimeValScr.Base.ParentID);
	}
}

static void OnInitRealTimeValScreen(void)
{
//	PostMessage(LCD_WM_INI,0);
	PostEvent(&RealTimeValScr.Base,LCD_WM_INI,0);
}
 
//�˳�ʱ����
static void OnDestoryRealTimeValScreen(void)
{
	INT8U err = 0;
	// �ض�ʱ��
	if (pValScrTmr)
	{
		OSTmrDel(pValScrTmr,&err);
		pValScrTmr = NULL;		
	}	
}
 

extern void InitRealTimeValScreen(CRealTimeValScreen *pScreenExt )
{
 	INT8U err = 0;
	 
	if (pScreenExt)
	{
		InitScreenBase( & pScreenExt->Base );
	 
		SetScreenInfo(& pScreenExt->Base,ID_MAIN_SCREEN, ID_REALTIME_VAL, ID_STRING_VALUE_TAB);
		pScreenExt->Base.pfnMessage = OnMessageRealTimeValScreen;
		pScreenExt->Base.pfnKeyDown = OnKeyDownRealTimeValScreen;
		pScreenExt->Base.pfnDestory = OnDestoryRealTimeValScreen;
		pScreenExt->Base.pfnInit    = OnInitRealTimeValScreen;
		pScreenExt->Base.pfnOnNotify = NULL;

		//��װ��ʱ��
		pValScrTmr = OSTmrCreate( 50,	100,OS_TMR_OPT_PERIODIC,RealTimeValScrTimer,(void *)pScreenExt,(INT8U *)0,&err);
		if (err == OS_ERR_NONE) 
		{/* Timer was created but NOT started */
			OSTmrStart(pValScrTmr,&err);
		}	

	}
}
 