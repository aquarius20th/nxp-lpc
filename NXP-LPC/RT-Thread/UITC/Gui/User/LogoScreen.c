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
#include "LogoScreen.h"
#include "StringTable.h"
#include "Message.h"
#include "DC.h"
#include "ClockMgr.h"

extern CScreenMgr  g_ScreeLib;

CLogoScreen      LogoScreen;       // �汾��������

static OS_TMR *BrandingTmr;


CDefaultScreen       DefScreen;

static OS_TMR  *DefScrTmr;

static void OnMessageLogoScreen(INT32U msg, INT32U param)  
{
	CLogoScreen *pScreenExt = &LogoScreen;
	INT8U err = 0;
	switch ( msg )
	{
	case LCD_WM_INI:
		{
			ClearScreen();
			DrawStringById(LCD_WIDTH>>1,0,ID_STRING_LOGO,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);
			InvalidateScreen(TRUE); 
		}
		break;
	case LCD_WM_REFRASH: 
		{
			UpdateScreen(TRUE);
		}
		break;
	case LCD_WM_TIMER:
		{
			// 5��ȴ���ʱ����Ϣ���˳����������Ĭ����ʾ����
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
//	PostMessage(LCD_WM_INI,0);
	PostEvent(&LogoScreen.Base,LCD_WM_INI,0);
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
static void LogoScreenTimer (void *ptmr, void *parg)
{
	if (BrandingTmr && BrandingTmr == ptmr)
	{
	//	PostMessage(LCD_WM_TIMER,(INT32U)parg);
		PostEvent(&LogoScreen.Base,LCD_WM_TIMER,(INT32U)parg);
	}
}

extern void InitLogoScreen(CLogoScreen *pScreenExt )
{
	INT8U i = 0;
	INT8U err = 0;

	BrandingTmr = NULL;

	if (pScreenExt)
	{
		InitScreenBase( & pScreenExt->Base );
		//��װ��ʱ��
		BrandingTmr = OSTmrCreate( 50,	100,OS_TMR_OPT_PERIODIC,LogoScreenTimer,(void *)pScreenExt,(INT8U *)0,&err);
		if (err == OS_ERR_NONE) 
		{/* Timer was created but NOT started */
			OSTmrStart(BrandingTmr,&err);
		}	

		SetScreenInfo(& pScreenExt->Base,ID_MAIN_SCREEN, ID_START_SCREEN, ID_STRING_NONE);
		pScreenExt->Base.pfnMessage = OnMessageLogoScreen;
		pScreenExt->Base.pfnKeyDown = OnKeyDownLogoScreen;
		pScreenExt->Base.pfnDestory = OnDestoryLogoScreen;
		pScreenExt->Base.pfnInit    = OnInitLogoScreen;
		pScreenExt->Base.pfnOnNotify = NULL;

// 		if (pScreenExt->Base.pfnInit)
// 		{
// 			pScreenExt->Base.pfnInit();
// 		}

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
static void InitDftScreenDispNum(CDefaultScreen *pScreenExt,INT16U nTypeIndex)
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
/*********************************************************************************************************
** ��������: DefScreenTimer
** ��������: DefScreenTimer
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
static void DefScreenTimer (void *ptmr, void *parg)
{
	if (DefScrTmr && DefScrTmr == ptmr)
	{
		//	PostMessage(LCD_WM_TIMER,(INT32U)parg);
	 	PostEvent(&DefScreen.Base,LCD_WM_TIMER,(INT32U)parg);
	}
}
/*********************************************************************************************************
** ��������: DispTime
** ��������: DispTime
**
** ����������  
**
** �䡡��:  CDefaultScreen * pScreen
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��27��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void DispTime(CDefaultScreen *pScreen )
{
	char szTxt[16] = {0};
	CDateTime DataTime;
	
	if (pScreen == NULL)
		return;

	ClockGetDataTime(&DataTime);
#define _OFFSET (40) //�˵���������߼��

 
	DrawStringById(LCD_WIDTH>>1,0,ID_STRING_LOGO,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);	

//	DrawStringById(16+_OFFSET,0,ID_STRING_MAIN_MENU,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);	
	//	theDC.DrawString(0,0,isprintf("%02d-%02d-%02d",dt.y,dt.mon,dt.d));
	//	theDC.DrawString(0,8,isprintf("%02d:%02d:%02d",dt.h,dt.min,dt.s));
 	sprintf(szTxt,"%02d-%02d-%02d[%d]",DataTime.wYear,DataTime.wMonth,DataTime.wDay,OSCPUUsage );
 //	DrawStringByStr( 0,32,szTxt,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);

 	sprintf(szTxt,"%02d:%02d:%02d:%03d", DataTime.wHour,DataTime.wMinute,DataTime.wSecond,DataTime.wMilliseconds);
 //	DrawStringByStr( 0,40,szTxt,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);
 
	 
}

/*********************************************************************************************************
** ��������: DispValue
** ��������: DispValue
**
** ����������  ��ʾ��ֵ����������Ҫ������ʾ��������˺�����Ҫ����
**
** �䡡��:  CDefaultScreen * pScreen
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��27��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void DispValue( CDefaultScreen *pScreen )
{
	if (pScreen == NULL)
		return;


}

// ѭ����ʾģʽʱ����ѭ����ʾ��������ѭ����ʾ
static 	void LoopDisp (CDefaultScreen *pScreen)
{
	if (pScreen == NULL)
		return;
//	ClearScreenEx(TRUE);

	DispTime(pScreen);

//	ClearScreenEx(TRUE);
}


static void OnMessageDefaultScreen(INT32U msg, INT32U param)  
{
	CDefaultScreen *pScreenExt = &DefScreen;
	switch ( msg )
	{
	case LCD_WM_INI:	
	case LCD_WM_REFRASH: 
		{
			// ˢ�½����������ʾ
			LoopDisp(pScreenExt);
	 	}
		break;
	case LCD_WM_TIMER:
		{
			// ˢ�½����������ʾ
			LoopDisp(pScreenExt);
		}
		break;
	default:
		break;
	}
}


//���������麯�� 
static void OnKeyDownDefaultScreen(INT16U keyCode)   
{	
	switch(keyCode)
	{
	case KEY_1:
		{	// �л���ͣѭ����ʾ
			DefScreen.Toggle = !DefScreen.Toggle;
		}
		break;
	case KEY_2:
		{	// �˳��ô��ڣ����븸����
			SwitchScreen(&g_ScreeLib,DefScreen.Base.ParentID);
		}
		break;
	case KEY_3:
		{
			// ����һ����������ʾ
	//		m_nCurrentMeasIndex--;
	//		if(m_nCurrentMeasIndex<0)
	//		{
	//			m_nCurrentMeasIndex=nLoopDispNum-1;	//ΪnLoopDispNumʱ��ʾ���в�ֵ
	//		}
	//		OnMessage(LCD_WM_REFRASH,NULL);
			PostEvent(&DefScreen.Base,LCD_WM_REFRASH,0);
		}
		break;
	case KEY_4:
		{
			// ����һ����������ʾ
	//		m_nCurrentMeasIndex++;
	//		if(m_nCurrentMeasIndex>=nLoopDispNum)
	//		{
	//			m_nCurrentMeasIndex=0;
	//		}
	//		OnMessage(LCD_WM_REFRASH,NULL);
			PostEvent(&DefScreen.Base,LCD_WM_REFRASH,0);
		}
		break;
	case KEY_5:
		{
			// ѡ��ѭ����ʾ��ģʽ
	//		m_nCurrentTypeIndex--;
	//		if(m_nCurrentTypeIndex<0)
	//		{
	//			m_nCurrentTypeIndex = MeasDispType.MeasTypeCount;
	//		}
	//		InitDispNum(m_nCurrentTypeIndex);
			PostEvent(&DefScreen.Base,LCD_WM_REFRASH,0);
		}
		break;
	case KEY_6:
		{
			// ѡ��ѭ����ʾ��ģʽ
// 		 	m_nCurrentTypeIndex++;
// 			if(m_nCurrentTypeIndex>MeasDispType.MeasTypeCount)
// 			{
// 				m_nCurrentTypeIndex = 0;
// 			}
// 			InitDispNum(m_nCurrentTypeIndex);
			PostEvent(&DefScreen.Base,LCD_WM_REFRASH,0);
		}
		break;
	default:
		break;
	}
}

static void OnInitDefaultScreen(void)
{
	INT8U err = 0;
	DefScrTmr = OSTmrCreate( 0,10,OS_TMR_OPT_PERIODIC,DefScreenTimer,(void *)(&DefScreen),(INT8U *)0,&err);
	if (err == OS_ERR_NONE) 
	{/* Timer was created but NOT started */
		OSTmrStart(DefScrTmr,&err);
	}	
	PostEvent(&DefScreen.Base,LCD_WM_INI,0);
}

//�˳�ʱ����
static void OnDestoryDefaultScreen(void)
{
	INT8U err = 0;
	// �ض�ʱ��
	if (DefScrTmr)
	{
		OSTmrDel(DefScrTmr,&err);
	}	
}

/*********************************************************************************************************
** ��������: InitDefaultScreen
** ��������: InitDefaultScreen
**
** ���������� ��������ʱ�ĳ�ʼ��
**
** �䡡��:  CScreenDefault * pScreenExt
**          
** �䡡��:   extern void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��27��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void InitDefaultScreen(CDefaultScreen *pScreenExt )
{
	INT8U err = 0;

	if (pScreenExt == NULL)
		return;

	InitScreenBase( & pScreenExt->Base );
	SetScreenInfo(& pScreenExt->Base,ID_MAIN_SCREEN, ID_DEFAULT_SCREEN, ID_STRING_NONE);
	pScreenExt->Base.pfnMessage = OnMessageDefaultScreen;
	pScreenExt->Base.pfnKeyDown = OnKeyDownDefaultScreen;
	pScreenExt->Base.pfnDestory = OnDestoryDefaultScreen;
	pScreenExt->Base.pfnInit    = OnInitDefaultScreen;
	pScreenExt->Base.pfnOnNotify = NULL;

	pScreenExt->Toggle       = TRUE;     
	pScreenExt->CurrentTypeIndex=0;
	pScreenExt->CurrentMeasIndex=0;
	
	//Ĭ����ʾ������
// 	for (i=0;i<MeasDispType.MeasTypeCount;i++) 
// 	{
// 		if(MeasDispType.MeasDisp[i].nMeasType==ID_STRING_MEASTYPE_MEAS)
// 		{
// 			m_nCurrentTypeIndex=i;
// 			break;
// 		}
// 	}
 }
