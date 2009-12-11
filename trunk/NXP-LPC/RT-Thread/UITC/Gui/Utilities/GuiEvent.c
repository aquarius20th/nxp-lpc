 /****************************************Copyright (c)**************************************************
**							     
**     ���д��ڵ���Ϣ���� ������Ϣ������ͳһ����Ϣ�أ��������һ���߳��ڣ�              
**     ��������Ϣ���У�����IPC���й���                           
**     TODO:�����Ƿ���þ�̬�ڴ����ʵ�֣���Ϣ�Ĵ����Ƿ���Ҫ����ϸ�����£�Ŀǰֻ������Screen������Ϣ��û��
**     �ؼ�����Ϣ����
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

struct GUI_EVENT_NODE
{
	GUI_EVENT_DEF
	struct GuiListNode NextNode;
};

typedef struct GUI_EVENT_NODE GuiEventNode;

struct GUI_EVENT_QUEUE
{
	INT32U State;
	GuiEventNode *pEvent;
	struct GuiListNode FreeListHead;
	struct GuiListNode UsedListHead;
};

typedef struct GUI_EVENT_QUEUE GuiEventQueue;
 //���ڵ���Ϣ���У�����ͬһ�������ڣ�
static GuiEventQueue g_ScrEvent;

static rt_mq_t g_mqTask ;

static INT8U InitTaskEvent( void )
{
	//TODO: ����Ϣ������ʵ�ֱȽϺ���
	g_mqTask = rt_mq_create("GT_EVNT",sizeof(GuiEvent)*GUI_EVENT_CNT,GUI_EVENT_CNT,RT_IPC_FLAG_FIFO);
	if (g_mqTask == RT_NULL)
		return FALSE;

	return TRUE;
}
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
INT8U InitGuiEventQueue( void )
{
	INT16U i  = 0;
	GuiEventNode *pEvent = NULL;
	InitTaskEvent();
	g_ScrEvent.State = 0;
	g_ScrEvent.pEvent = rt_malloc( sizeof(GuiEventNode) * GUI_EVENT_CNT );
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
INT8U SendScreenEvnent(  GUI_HWND hWnd,INT32U Msg,INT32U wParam,INT32U lParam )
{
// 	if(pScr == NULL)
// 		return FALSE;
// 
// 	switch (Msg)
// 	{
// 	case GUI_EVENT_KEYDOWN:
// 		ASSERT(pScr->pfnKeyDown);
// 		if (pScr->pfnKeyDown)
// 		{
// 			pScr->pfnKeyDown(pScr,wParam);
// 		}
// 		break;
// 	default:
// 		ASSERT(FALSE);
// 		break;
// 	}
 



	return TRUE;
}
/*********************************************************************************************************
** ��������: PostEvnent
** ��������: PostEvnent
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
INT8U PostEvnent(  GUI_HWND hWnd,INT32U Msg,INT32U wParam,INT32U lParam ,INT8U bNoCheck)
{
	GuiEventNode *pEvent = NULL;
	struct GuiListNode *pNode = NULL;
	struct GuiListNode* pHead = NULL;
 
	//��� ��Ϣ�Ƿ�Ϸ�
	if (hWnd == HWND_INVALID || hWnd == HWND_NULL)
		return FALSE;
	if (Msg == GUI_EVENT_PAINT) 
	{
		g_ScrEvent.State |= QS_PAINT;
	 	return FALSE;
	}
	//������Ϣ�Ƿ����ظ���
 
	if (bNoCheck == FALSE)
	{
		GuiListForEach( pNode, & g_ScrEvent.UsedListHead )
		{
			pEvent = CONTAINING_RECORD(pNode, GuiEventNode,NextNode);
			ASSERT(pEvent);
			if(pEvent && pEvent->Handle == hWnd && pEvent->Msg == Msg && pEvent->WParam == wParam 
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
			pEvent = CONTAINING_RECORD( pHead,GuiEventNode,NextNode );
			ASSERT(pEvent);
			if (pEvent)
			{
				pEvent->Handle = hWnd;
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
** ��������: GetScrEvent
** ��������: GetScrEvent
**
** ����������  
**
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��11��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U GetScrEvent( GuiEvent *pEvent )
{

	return TRUE;
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
static INT8U EventHandler( GuiEventNode *pEvent )
{
//	ASSERT(pEvent && pEvent->pScreen);
//	if (pEvent == NULL || pEvent->pScreen == NULL)
//		return FALSE;


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
	GuiEventNode *pEvent = NULL;
	struct GuiListNode *pNode = NULL;
	INT8U bRet = FALSE;
	if(pScr == NULL)
		return FALSE;
#if 0
	//ѭ��������Ϣ�б���������ڱ����ڵģ���ִ�У���ɾ��
	GuiListForEach( pNode, & g_ScrEvent.UsedListHead )
	{
		pEvent = CONTAINING_RECORD(pNode, GuiEventNode,NextNode);
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
#endif
	return bRet;
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
INT8U GuiTaskEventRecv( GuiEvent * pEvent  )
{
	rt_err_t result;
	 
	if (g_mqTask == NULL || pEvent == NULL)
		return FALSE;
	result = rt_mq_recv(g_mqTask, (void*)pEvent, sizeof(GuiEvent), 0);
	if (result == RT_EOK)
	{


		return TRUE;
	}
	return FALSE;
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
INT8U PostEventToGuiTask(  GuiEvent * pEvent )
{
	rt_mq_send(g_mqTask, (void*)pEvent, sizeof(GuiEvent));

	return TRUE;
}
/*********************************************************************************************************
** ��������: HandleTaskEvent
** ��������: HandleTaskEvent
**
** ����������  �������񼶱����Ϣ
**
**          
** �䡡��:   INT8U
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
extern INT8U OnTaskTimer(INT32U nEventID,INT32U Param);
INT8U HandleTaskEvent(  GuiEvent * pEvent )
{
	ASSERT(pEvent);
	if(pEvent == NULL)
		return FALSE;
	switch(pEvent->Msg)
	{
		case GUI_EVENT_TIMER:
//			if (pEvent->pScreen == NULL)
//			{//���񼶵Ķ�ʱ��Ϣ
//				return OnTaskTimer(pEvent->WParam,pEvent->LParam);				
//			}
			break;
		default:
			break;
	}




//	if (pEvent->pScreen == NULL)
//	{//
//	}

	return TRUE;
}
/*********************************************************************************************************
** ��������: PeekEvent
** ��������: PeekEvent
**
** ����������  
**
** �䡡��:  GuiEvent * pMsg
** �䡡��:  HWND hWnd
** �䡡��:  BOOL bWait
** �䡡��:  UINT uRemoveMsg
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��11��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U PeekEvent(GuiEvent *pMsg, GUI_HWND hWnd, INT8U bWait, INT8U uRemoveMsg)
{
	if (pMsg == NULL || !IsScreen(hWnd))
		return FALSE;

	memset (pMsg, 0, sizeof(GuiEvent));





	return TRUE;
}
/*********************************************************************************************************
** ��������: TranslateEvent
** ��������: TranslateEvent
**
** ����������  �������������Ϣת��Ϊ�ַ���Ϣ
**
** �䡡��:  GuiEvent * pMsg
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��11��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U TranslateEvent(GuiEvent* pMsg)
{

	return TRUE;
}

static __inline SCREENPROC GetScreenProc (GUI_HWND hWnd)
{
	return ((CScreenBase*)hWnd)->ScreenProc;
}
/*********************************************************************************************************
** ��������: DispatchEvent
** ��������: DispatchEvent
**
** ����������  �ַ���Ϣ
**
** �䡡��:  GuiEvent * pMsg
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��11��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT32U DispatchEvent(GuiEvent* pMsg)
{
	SCREENPROC ScrProc = NULL;
	INT32U nRet = 0;
 	if (pMsg == NULL || pMsg->Handle == HWND_INVALID || pMsg->Handle == HWND_NULL)  
	{ 
		return FALSE;
	} 

	if (!(ScrProc = GetScreenProc (pMsg->Handle)))
		return -1;

 	nRet = (*ScrProc)(pMsg->Handle, pMsg->Msg, pMsg->WParam, pMsg->LParam); 
	return nRet;
}


INT32U SendNotifyEvent (GUI_HWND hWnd, INT32U nMsg, GUI_WPARAM wParam, GUI_LPARAM lParam)
{
#if 0
	PMSGQUEUE pMsgQueue;
	PQMSG pqmsg;

	MG_CHECK_RET (MG_IS_WINDOW(hWnd), ERR_INV_HWND);

	if (!(pMsgQueue = GetMsgQueue(hWnd)))
		return ERR_INV_HWND;

	pqmsg = QMSGAlloc();
 
	/* queue the notification message. */
	pqmsg->Msg.hwnd = hWnd;
	pqmsg->Msg.message = iMsg;
	pqmsg->Msg.wParam = wParam;
	pqmsg->Msg.lParam = lParam;
	pqmsg->next = NULL;

	if (pMsgQueue->pFirstNotifyMsg == NULL)
	{
		pMsgQueue->pFirstNotifyMsg = pMsgQueue->pLastNotifyMsg = pqmsg;
	}
	else
	{
		pMsgQueue->pLastNotifyMsg->next = pqmsg;
		pMsgQueue->pLastNotifyMsg = pqmsg;
	}

	g_ScrEvent.State |= QS_NOTIFYMSG;
#endif


	return TRUE;
}