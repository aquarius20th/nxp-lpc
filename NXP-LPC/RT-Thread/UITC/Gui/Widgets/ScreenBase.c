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
#include <string.h>
#include "GuiConst.h"
#include "ScreenBase.h"
#include "global.h"
#include "DC.h"
#include "StringTable.h"
 
/************************************************************************/
/*  ������                                                              */
/************************************************************************/
static  LCDRECT g_rcCaption={0,0,LCD_WIDTH-1,15};
static  LCDRECT g_rcPageInfo={LCD_WIDTH-56,0,LCD_WIDTH-1,15};

static INT8U        g_ActiveID;    //����Ĵ���ID

/*********************************************************************************************************
** ��������: HandleEvent
** ��������: HandleEvent
**
** ����������  ����Ϊ�ʱ,�Ŵ����¼�
**
** �䡡��:  CScreenBase * pScreen
**          
** �䡡��:   extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��24��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U HandleEvent(CScreenBase *pScreen)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif

	INT8U Flag = FALSE;
	INT8U i = MAX_ENENT_CNT;
	UEVENT Event;

	memset(&Event,0,sizeof(UEVENT));

	if (pScreen == NULL)
		return FALSE;

	if (pScreen->pfnMessage == NULL)
		return FALSE;

	for (;;)
	{
		OS_ENTER_CRITICAL();
		if (pScreen->Event[i-1].Flag)
		{//
			//���Ƴ���
			Event.Msg = pScreen->Event[i-1].Msg;
			Event.WParam = pScreen->Event[i-1].WParam;
			Event.Flag = TRUE;

			pScreen->Event[i-1].Flag = 0;
			pScreen->Event[i-1].Msg = 0;
			pScreen->Event[i-1].WParam = 0;

			Flag = TRUE;
			OS_EXIT_CRITICAL();	 
			break;
		}
		OS_EXIT_CRITICAL();	

		if(i == 0)
			break;
		i--;	
	}
	if(Flag)
	{//�����¼�
		if (Event.Msg == LCD_WM_KEYDOWN && pScreen->pfnKeyDown)
		{
			pScreen->pfnKeyDown((INT16U) Event.WParam );
		}
		else if (  pScreen->pfnMessage )
		{
			pScreen->pfnMessage(Event.Msg ,Event.WParam);
		}	
		 
		return TRUE;
	}
	return FALSE;
}
/*********************************************************************************************************
** ��������: PostEvent
** ��������: PostEvent
**
** ����������  
**
** �䡡��:  CScreenBase * pScreen
** �䡡��:  INT32U msg
** �䡡��:  INT32U param
**          
** �䡡��:   extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��24��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U PostEvent(CScreenBase *pScreen,INT32U msg,INT32U param)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	INT8U  i = 0;
	INT8U Flag = FALSE;

	if (pScreen == NULL)
		return FALSE;

	OS_ENTER_CRITICAL();
	//�鿴�Ƿ����ظ����¼���������ظ��ģ������
	for(i = 0;i < MAX_ENENT_CNT;i++)
	{
		if (pScreen->Event[i].Flag && pScreen->Event[i].Msg == msg)
		{
			pScreen->Event[i].Flag++;
			Flag = TRUE;
			OS_EXIT_CRITICAL();	 
			return Flag;
		}
	}
	for(i = 0;i < MAX_ENENT_CNT;i++)
	{
		if (pScreen->Event[i].Flag  == FALSE )
		{
			pScreen->Event[i].Msg = msg;
			pScreen->Event[i].WParam = param;
			pScreen->Event[i].Flag  = TRUE;
			Flag = TRUE;
			break;
		}
	}
	OS_EXIT_CRITICAL();	 
	return Flag;
}

extern INT8U SendEvent(CScreenBase *pScreen,INT32U msg,INT32U param)
{
	if (pScreen == NULL)
		return FALSE;

	if (msg == LCD_WM_KEYDOWN && pScreen->pfnKeyDown)
	{
		pScreen->pfnKeyDown((INT16U)param );
	}
	else if (  pScreen->pfnMessage )
	{
		pScreen->pfnMessage(msg ,param);
	}	 
	return TRUE;
}
extern void  ClearEvent(CScreenBase *pScreen)
{
	INT8U i = 0;
	if (pScreen)
	{
		for(i = 0;i < MAX_ENENT_CNT;i++)
		{
			if (pScreen->Event[i].Flag )
			{
				pScreen->Event[i].Msg = 0;
				pScreen->Event[i].WParam = 0;
				pScreen->Event[i].Flag  = FALSE;			 
			}
		}
	}
}

//�õ�/���ü���Ĵ���ID 
extern __inline INT8U  GetActiveWinID(void)
{
	return g_ActiveID;
}  

extern __inline void   SetActiveWinID(const INT8U id)
{
	g_ActiveID = id;
}  


//�õ�/���ñ����ڸ�����ID
extern __inline INT8U GetFatherID(CScreenBase *pScreen)
{
	if (pScreen)
	{
		return pScreen->ParentID;
	}

	return 0;
}

static __inline void  SetFatherID(CScreenBase *pScreen, INT8U nID)
{
	if (pScreen)
	{
		pScreen->ParentID = nID;
	}
}
extern void InitScreenBase(CScreenBase *pBase)
{
	if (pBase)
	{
		pBase->ParentID = 0;    //������ID��
		pBase->CurrentID = 0;   //������ID��
		pBase->ScreenName = 0; //����������

		//�ص�����
		pBase-> pfnKeyDown = NULL;
		pBase-> pfnMessage = NULL;
		pBase-> pfnInit = NULL;
		pBase->pfnDestory = NULL;
		pBase->pfnOnNotify = NULL;
	}
}

extern void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName )
{
	if (pScreen)
	{
		pScreen->ParentID = ParentID;
		pScreen->CurrentID = CurrentID;
		pScreen->ScreenName = nScreenName;
	}
}

extern void InitScreenMgr( CScreenMgr *pMgr )
{
	INT16U i = 0;

	if (pMgr)
	{
		for( i=0; i<MAXSCREEN; i++)
			pMgr->m_ScreenArray[i] = NULL;             // ����ָ������

		pMgr->ScreensCnt    = 0;                       // ��������
	}
}

// �ж����ScreenID��Ļ�Ƿ��ڼ���״̬
extern INT8U IsScreenActived(CScreenMgr *pMgr ,INT8U nScreenID) 
{
	if (pMgr)
	{
		if (nScreenID == GetActiveWinID())
			return TRUE;		
	}
	return FALSE;
}

// �õ�ָ�����ScreenID��Ļ��ָ��
extern  CScreen* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID)
{
	if(pMgr == NULL || (nScreenID >= MAXSCREEN) || (nScreenID == ID_SCREEN_NULL))
		return NULL;
	else
		return (pMgr->m_ScreenArray[nScreenID]);
}
// �õ���ǰ��Ļ��ָ��
extern CScreen* GetCurrentScreenPtr(CScreenMgr *pMgr)
{
	if(pMgr)
		return (pMgr->m_ScreenArray[GetActiveWinID()]);
	return NULL;
}
// �õ���������
extern __inline INT16U GetScreensCnt(CScreenMgr *pMgr)  
{
	if (pMgr)
	{
		return pMgr->ScreensCnt;
	}
	return 0;	
}	

// ����һ���µ���Ļ���������
extern INT8U  AppendScreen(CScreenMgr *pMgr,CScreen *pScreen)
{
	if (pScreen== (CScreen*)0 || pMgr == (CScreenMgr *)0)
		return FALSE;	

	if( pMgr->ScreensCnt >= MAXSCREEN)
		return FALSE;
	else
	{
		pMgr->ScreensCnt++;
		pMgr->m_ScreenArray[pScreen->Base.CurrentID] =pScreen;  
		return TRUE;
	}	
} 

// �л������ScreenID��Ļ
void SwitchScreen(CScreenMgr *pMgr,INT8U nScreenID)
{
	CScreen* pScreen = NULL;
	if (pMgr == NULL)
		return ;
	
	pScreen=GetCurrentScreenPtr(pMgr);

	//��������ԭ����
	if(pScreen && pScreen->Base.pfnDestory)
	{
		pScreen->Base.pfnDestory();
	}
	
	//�л�����һ����
	pScreen=GetScreenPtr(pMgr,nScreenID); 

	if(pScreen == NULL)
		return;
 
 	//����л�����������򱣴���������򷵻ش���
 	if(nScreenID == ID_PASSWORD || nScreenID == ID_MODALDIALOG)
 		SetFatherID(& pScreen->Base,GetActiveWinID());
 	   
	SetActiveWinID(nScreenID);
 
 	//�����Ļ,ģʽ�Ի�����ΪҪ�����ϸ������ͼ�����в���������
 	if(nScreenID != ID_MODALDIALOG)
 		ClearScreen();
	if(pScreen != NULL && pScreen->Base.pfnInit)
 		pScreen->Base.pfnInit();// ����Ĭ�ϳ�ʼ�����룬���罨����Դ
}

extern void DrawScreenCaption( CScreen *pScreen, INT16U nTotal, INT16U nCur)
{ 
	if (pScreen == NULL)
		return;
	if (pScreen->Base.ScreenName)
	{
		//���λ��
 		ClrRectScreenBuf(&g_rcCaption,COLOR_BK);
		DrawStringById(LCD_WIDTH>>1,0,pScreen->Base.ScreenName,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);	
	}
	if(nTotal)
	{
		char szTxt[8] = {0};
		snprintf( szTxt,sizeof(szTxt),"%02d/%02d",nCur,nTotal) ;
		DrawStringByStr( LCD_WIDTH-1,0, szTxt,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);	
	}
#if 0	
	if(pStr)
	{
		//�ñ������ֻ�������
		pOldEnFont = SetEnFontID(&theScreenDC, EN_8_16_BMPFONT);

		DrawText(&theScreenDC, pStr,strlen(pStr),&g_rcCaption,DT_CENTER|DT_VCENTER);
	}
	if(nTotal)
	{
		DrawString(&theScreenDC,GUI_LCM_XMAX-1,0,isprintf("%02d/%02d",nCur,nTotal),PEN_COPY,ALIGN_RIGHT);	
	}
	//����ԭ�ȵ�����
	SetEnFont(&theScreenDC, pOldEnFont);
	LCD_PutRectBuff2Scr(&g_rcCaption);
#endif
}

extern void DrawScreenStatusBar( )
{
	char szTxt[32] = "2009.8.8-14:32:34";
	INT8U addr = 32;
	FP32  val = 12.86;
	//����
	 DrawLine(0, 100,LCD_WIDTH-1, 100, COLOR_FR);
	 //ʱ�估��ַ
	 DrawStringByStr(0,104,szTxt,PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_8);
	 snprintf( szTxt,sizeof(szTxt),"ADD[ %d ]",addr) ;
	 DrawStringByStr(LCD_WIDTH-1,104,szTxt,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_8);

	 //բ�ſ���  ID_STRING_GATAGE
	 DrawStringById(0,112,ID_STRING_GATAGE,PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_16);
	 snprintf( szTxt,sizeof(szTxt)," %0.2f ",val) ;
	 DrawStringByStr(LCD_WIDTH-1-40-32-32-16,112,szTxt,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);
	 DrawStringById(LCD_WIDTH-1-40-32-16-16,112,ID_STRING_M,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);

	 //״̬
	 DrawStringById(LCD_WIDTH-1-40,112,ID_STRING_STATE,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);
	 DrawStringById(LCD_WIDTH-1,112,ID_STRING_STOP,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);

}

