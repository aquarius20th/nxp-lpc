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
#include "list.h" 

struct GUI_EVENT_MGR
{
	GuiEventNode *pEvent;
	struct GuiListNode FreeListHead;
	struct GuiListNode UsedListHead;
};

typedef struct GUI_EVENT_MGR GuiEventMgr;
 //���ڵ���Ϣ���У�����ͬһ�������ڣ�
GuiEventMgr g_ScrEvent;


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
	GuiEventNode *pEvent = NULL;
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
			pEvent = CONTAINING_RECORD(pNode, GuiEventNode,NextNode);
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
			pEvent = CONTAINING_RECORD( pHead,GuiEventNode,NextNode );
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
	GuiEventNode *pEvent = NULL;
	struct GuiListNode *pNode = NULL;
	INT8U bRet = FALSE;
	if(pScr == NULL)
		return FALSE;
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
			if (pEvent->pScreen == NULL)
			{//���񼶵Ķ�ʱ��Ϣ
				return OnTaskTimer(pEvent->WParam,pEvent->LParam);				
			}
			break;
		default:
			break;
	}




	if (pEvent->pScreen == NULL)
	{//
	}

	return TRUE;
}
