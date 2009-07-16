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
#include "GuiConst.h"
#include "ScreenBase.h"
#include "global.h"
#include "DC.h"


static INT8U        g_ActiveID;    //����Ĵ���ID



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

extern __inline void  SetFatherID(CScreenBase *pScreen, INT8U nID)
{
	if (pScreen)
	{
		pScreen->ParentID = nID;
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
			pMgr->m_ScreenArray[i] = NULL;                        // ����ָ������

		pMgr->ScreensCnt	         = 0;                       // ��������
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
extern  CScreenBase* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID)
{
	if(pMgr == NULL || (nScreenID >= MAXSCREEN) || (nScreenID == ID_WINDOW_NULL))
		return NULL;
	else
		return (pMgr->m_ScreenArray[nScreenID]);
}
// �õ���ǰ��Ļ��ָ��
extern CScreenBase* GetCurrentScreenPtr(CScreenMgr *pMgr)
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
extern INT8U  AppendScreen(CScreenMgr *pMgr,CScreenBase *pScreen)
{
	if (pScreen== (CScreenBase*)0 || pMgr == (CScreenMgr *)0)
		return FALSE;	

	if( pMgr->ScreensCnt >= MAXSCREEN)
		return FALSE;
	else
	{
		pMgr->ScreensCnt++;
		pMgr->m_ScreenArray[pScreen->CurrentID] =pScreen;  
		return TRUE;
	}	
} 

// �л������ScreenID��Ļ
void SwitchScreen(CScreenMgr *pMgr,INT8U nScreenID)
{
	CScreenBase* pScreen = NULL;
	if (pMgr == NULL)
		return ;
	
	pScreen=GetCurrentScreenPtr(pMgr);

	//��������ԭ����
	if(pScreen && pScreen->pfnDestory)
	{
		pScreen->pfnDestory();
	}
	
	//�л�����һ����
	pScreen=GetScreenPtr(pMgr,nScreenID); 
 
 	//����л�����������򱣴���������򷵻ش���
 	if(nScreenID == ID_PASSWORD || nScreenID == ID_MODALDIALOG)
 		SetFatherID(pScreen,GetActiveWinID());
 	   
	SetActiveWinID(nScreenID);
 
 	//�����Ļ,ģʽ�Ի�����ΪҪ�����ϸ������ͼ�����в���������
 	if(nScreenID != ID_MODALDIALOG)
 		ClearScreen();
	if(pScreen != NULL && pScreen->pfnInit)
 		pScreen->pfnInit();// ����Ĭ�ϳ�ʼ�����룬���罨����Դ
}
