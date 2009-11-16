 /****************************************Copyright (c)**************************************************
**							     
**     ���д��ڵ���Ϣ���� ������Ϣ������ͳһ����Ϣ�أ��������һ���߳��ڣ�              
**     ��������Ϣ���У�����IPC���й���                           
**     TODO:�����Ƿ���þ�̬�ڴ����ʵ�֣�
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:   GuiEvent.c
**��   ��   ��:   LiJin
**����޸�����: 2009-11-12
**��        ��:   
**��        ע :
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
#include <rtthread.h>
#include "applib.h"
#include "GuiConfig.h"
#include "GuiList.h"
#include "GuiEvent.h"
#include "ScreenBase.h"

struct GUI_EVENT_MGR
{
	GuiEvent *pEvent;
	struct GuiListNode FreeListHead;
	struct GuiListNode UsedListHead;
};

typedef struct GUI_EVENT_MGR GuiEventMgr;
 //���ڵ���Ϣ���У�����ͬһ�������ڣ�
GuiEventMgr g_ScrEvent;

/*********************************************************************************************************
** ��������: InitGuiEventMgr
** ��������: InitGuiEventMgr
**
** ����������  
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��12��
** ��  ע:  ���д��ڵ���Ϣ����
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U InitGuiEventMgr( void )
{
	INT16U i  = 0;
	GuiEvent *pEvent = NULL;
	g_ScrEvent.pEvent = rt_malloc( sizeof(GuiEvent) * GUI_EVENT_CNT );
	ASSERT(g_ScrEvent.pEvent );
	if (g_ScrEvent.pEvent == NULL)
		return FALSE;

	pEvent =g_ScrEvent.pEvent ;
	GuiListInit( &g_ScrEvent.FreeListHead );
	GuiListInit( &g_ScrEvent.UsedListHead );

	//��������
	for (i = 0; i < GUI_EVENT_CNT; i++)
	{	
		GuiListAppend( & g_ScrEvent.FreeListHead, & (pEvent[i].NextNode) );
	}


	return TRUE;
}
/*********************************************************************************************************
** ��������: SendEvnent
**
** ���������� ������Ϣ������ִ��
**
** �䡡��:
**
** �䡡��:
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
INT8U SendScreenEvnent( struct SCREEN_BASE *pScr,INT32U Msg,INT32U wParam,INT32U lParam )
{
	if(pScr == NULL)
		return FALSE;

	switch (Msg)
	{
	case GUI_EVENT_KEYDOWN:
		ASSERT(pScr->pfnKeyDown);
		if (pScr->pfnKeyDown)
		{
			pScr->pfnKeyDown(pScr,wParam);
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}
 



	return TRUE;
}
/*********************************************************************************************************
** ��������: PostScreenEvnent
** ��������: PostScreenEvnent
**
** ����������  ������Ϣ���ݴ�����������У�Ȼ����������ʵ�ʱ��ִ��
**
** �䡡��:  CScreenBase * pScr
** �䡡��:  INT32U Msg
** �䡡��:  INT32U wParam
** �䡡��:  INT32U lParam
** �䡡��:  BOOL bNoCheck  �Ƿ������ظ�����Ϣ
**          
** �䡡��:   INT8U
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
INT8U PostScreenEvnent( struct SCREEN_BASE *pScr,INT32U Msg,INT32U wParam,INT32U lParam ,INT8U bNoCheck)
{
	GuiEvent *pEvent = NULL;
	struct GuiListNode *pNode = NULL;
	struct GuiListNode* pHead = NULL;
	if(pScr == NULL)
		return FALSE;

	//��� ��Ϣ�Ƿ�Ϸ�

	//������Ϣ�Ƿ����ظ���
	if (bNoCheck == FALSE)
	{
		GuiListForEach( pNode, & g_ScrEvent.UsedListHead )
		{
			pEvent = CONTAINING_RECORD(pNode, GuiEvent,NextNode);
			ASSERT(pEvent);
			if(pEvent && pEvent->pScreen == pScr && pEvent->Msg == Msg && pEvent->WParam == wParam 
				&& pEvent->LParam == lParam )
			{
				pEvent->Flag ++;
				return TRUE;
			}
		}
	}

	//��free ��������һ����Ϣ
	if ( !GuiListIsEmpty(& g_ScrEvent.FreeListHead ) )
	{
		pHead = GuiListRemoveHead( & g_ScrEvent.FreeListHead );
		if (pHead)
		{
			GuiListAppend(  & g_ScrEvent.UsedListHead, pHead);
			pEvent = CONTAINING_RECORD( pHead,GuiEvent,NextNode );
			ASSERT(pEvent);
			if (pEvent)
			{
				pEvent->pScreen = pScr;
				pEvent->Msg = Msg;
				pEvent->WParam = wParam;
				pEvent->LParam = lParam;
				//
				return TRUE;
			}
		}
	}
	return FALSE;
}
/*********************************************************************************************************
** ��������: EventHandler
** ��������: EventHandler
**
** ����������  
**
** �䡡��:  GuiEvent * pEvent
**          
** �䡡��:   INT8U
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
static INT8U EventHandler( GuiEvent *pEvent )
{
	ASSERT(pEvent && pEvent->pScreen);
	if (pEvent == NULL || pEvent->pScreen == NULL)
		return FALSE;


	return TRUE;
}
/*********************************************************************************************************
** ��������: HandleScreenEvent
** ��������: HandleScreenEvent
**
** ����������  
**
** �䡡��:  CScreenBase * pScr
**          
** �䡡��:   INT8U
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
INT8U HandleScreenEvent(struct SCREEN_BASE *pScr)
{
	GuiEvent *pEvent = NULL;
	struct GuiListNode *pNode = NULL;
	INT8U bRet = FALSE;
	if(pScr == NULL)
		return FALSE;
	//ѭ��������Ϣ�б���������ڱ����ڵģ���ִ�У���ɾ��
	GuiListForEach( pNode, & g_ScrEvent.UsedListHead )
	{
		pEvent = CONTAINING_RECORD(pNode, GuiEvent,NextNode);
		ASSERT(pEvent);
		if(pEvent && pEvent->pScreen == pScr)
		{
			//��Ӧ��Ϣ
			bRet = EventHandler(pEvent);
			//����
			GuiListRemove( &g_ScrEvent.UsedListHead , pNode );
			GuiListAppend(  &g_ScrEvent.FreeListHead , pNode  );
		}
	}
	return bRet;
}

static rt_mailbox_t g_mbTask ;

INT8U InitTaskEvent( void )
{
// 	g_mbTask = rt_mb_create("TSK_ENT",sizeof(GuiEvent)*GUI_EVENT_CNT/4,RT_IPC_FLAG_FIFO);
// 	if (g_mbTask == RT_NULL)
// 		return FALSE;

//TODO: ����Ϣ������ʵ�ֱȽϺ���
}

/*********************************************************************************************************
** ��������: GuiTaskEventRecv
** ��������: GuiTaskEventRecv
**
** ����������  ����GUI���� ������������������Ϣ
**
**          
** �䡡��:   INT8U
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
INT8U GuiTaskEventRecv( )
{

	return TRUE;
}
/*********************************************************************************************************
** ��������: PostEventToGuiTask
** ��������: PostEventToGuiTask
**
** ����������  ��������������Ϣ��GUI  
**
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��16��
** ��  ע:  ͨ������ʱ�������Ͷ�ʱ�������������͹�����MessageBox
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U PostEventToGuiTask( )
{

	return TRUE;
}
