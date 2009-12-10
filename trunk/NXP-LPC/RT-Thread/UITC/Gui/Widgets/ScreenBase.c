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


#include "ScreenBase.h"


/*********************************************************************************************************
** ��������: SetScreenInfo
** ��������: SetScreenInfo
**
** ����������  
**
** �䡡��:  CScreenBase * pScreen
** �䡡��:  INT8U ParentID
** �䡡��:  INT8U CurrentID
** �䡡��:  INT16U nScreenName
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
void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName )
{
	if (pScreen)
	{
		pScreen->ParentID = ParentID;
		pScreen->CurrentID = CurrentID;
		pScreen->ScreenName = nScreenName;
	}
}
/*********************************************************************************************************
** ��������: CreateScreen
** ��������: CreateScreen
**
** ����������  ��̬����һ����Ļ �Ӷ��д���
**
** �䡡��:  INT32U nSize
** �䡡��:  scr_ctor ctor
** �䡡��:  scr_dtor dtor
**          
** �䡡��:   CScreenBase *
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
CScreenBase * CreateScreen( INT32U nSize,scr_ctor ctor,scr_dtor dtor )
{
	CScreenBase *pObj;

	if (nSize <= 0 || nSize > MAX_SCR_SIZE)
		return RT_NULL;

	pObj = rt_malloc(nSize);
	if (pObj == RT_NULL)
		return RT_NULL;

	pObj->Ctor = ctor;
	pObj->Dtor = dtor;
	pObj->Size = nSize;

	if(ctor)
	{
		ctor(pObj);
	}
	pObj->Handle = (GUI_HWND) pObj;
	return pObj;
}
/*********************************************************************************************************
** ��������: 
**
** ���������� ��̬����һ������
**
** �䡡��:
**
** �䡡��:
**
** ȫ�ֱ���:
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��3��
** ��  ע:
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void InitScreen(CScreenBase *pScr, scr_ctor ctor,scr_dtor dtor )
{
	ASSERT(pScr);
	if(pScr)
	{
		pScr->Ctor = ctor;
		pScr->Dtor = dtor;
		pScr->Size = 0; //��̬

		if(ctor)
		{
			ctor(pScr);
		}
		pScr->Handle = (GUI_HWND) pScr;
	}
	return;
}


void DrawScreenCaption( CScreenBase *pScreen, INT16U nTotal, INT16U nCur)
{
	if (pScreen == NULL)
		return;
	if (pScreen->ScreenName)
	{
		//���λ��
 //		ClrRectScreenBuf(&g_rcCaption,COLOR_BK);
//		DrawStringById(LCD_WIDTH>>1,0,pScreen->Base.ScreenName,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_16);
	}
	if(nTotal)
	{
		char szTxt[8] = {0};
		snprintf( szTxt,sizeof(szTxt),"%02d/%02d",nCur,nTotal) ;
//		DrawStringByStr( LCD_WIDTH-1,0, szTxt,PEN_COPY,ALIGN_RIGHT,LCD_EN_FONT_8_16);
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

void DrawScreenStatusBar( void )
{
	char szTxt[32] = "2009.8.8-14:32:34";
	INT8U addr = 32;
	FP32  val = 12.86;
#if 0
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
#endif
}


