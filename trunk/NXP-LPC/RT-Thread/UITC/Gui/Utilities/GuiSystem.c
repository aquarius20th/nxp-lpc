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
#include <stddef.h>
#include "applib.h"
#include "ScreenBase.h"
#include "guisystem.h"
#include "GuiEvent.h"

/*********************************************************************************************************
** ��������: TimerCB
** ��������: TimerCB
**
** ����������  ��ʱ���Ļص�����
**
** �䡡��:  void * pData
**          
** �䡡��:   void
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
static void TimerCB( void *pData)
{//��ʱ��ʱ�䵽�ˣ�֪ͨGUI����

	GuiEvent Event;
	ASSERT(pData);
	if(pData)
	{
		//��֯EVENT

		PostEventToGuiTask(&Event);
	}
}


struct GUI_TIMER
{
	CScreenBase *pScreen;
	INT32U       nIDEvent;
	rt_timer_t   pSysTimer;
	gui_list_t   list;
};
typedef struct GUI_TIMER CGuiTimer;

static CGuiTimer g_lstGuiTimerHead;

void InitGuiTimerMgr( void )
{
	GuiListInit(&g_lstGuiTimerHead.list);
	g_lstGuiTimerHead.pScreen = NULL;
	g_lstGuiTimerHead.nIDEvent = 0;
	g_lstGuiTimerHead.pSysTimer = NULL;
}
/*********************************************************************************************************
** ��������: SetGuiTimer
** ��������: SetGuiTimer
**
** ����������  
**
** �䡡��:  CScreenBase * pScr
** �䡡��:  INT32U nIdEvent
** �䡡��:  INT32U nMsTime
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��13��
** ��  ע:  TODO: ��ʱ���ĵ�λ��TICK����ȷ��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetGuiTimer(CScreenBase *pScr,INT32U nIdEvent,INT32U nMsTime)
{
	//���ݴ��ڵ����ƺ�ID���鿴�Ƿ������ظ��Ķ�ʱ�������û�У���̬����һ����ʱ��GUI_TIMER�����ҵ�������
	struct GUI_TIMER *pGuiTimer = NULL;
 	gui_list_t *pNode = NULL;
	INT8U bFindFlag = FALSE;

	//
	GuiListForEach(pNode, &(g_lstGuiTimerHead.list))
	{
		pGuiTimer = CONTAINING_RECORD(pNode, CGuiTimer,list);
		ASSERT(pGuiTimer);
 		if (pGuiTimer && pGuiTimer->pScreen == pScr && pGuiTimer->nIDEvent == nIdEvent)
		{
 			bFindFlag = TRUE;
 			break;
		}
	}

	if (bFindFlag)
	{//������ظ��ģ�����������һ�¶�ʱ��
		if(pGuiTimer && pGuiTimer->pSysTimer)
		{
			rt_timer_control(pGuiTimer->pSysTimer,RT_TIMER_CTRL_SET_TIME,&nMsTime);
			//������ʱ��
			rt_timer_start(pGuiTimer->pSysTimer);
		}
	}
	else
	{
		pGuiTimer = rt_malloc(sizeof(CGuiTimer));
		ASSERT(pGuiTimer);
		if (pGuiTimer)
		{		
			//�ҽӵ���������
			GuiListAppend(&	(g_lstGuiTimerHead.list),&(pGuiTimer->list));

			//����ϵͳ��ʱ��
			pGuiTimer->pSysTimer = rt_timer_create("GuiTm", TimerCB, (void *) pGuiTimer, nMsTime,
					RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
			ASSERT(pGuiTimer->pSysTimer);
			pGuiTimer->pScreen = pScr;
			pGuiTimer->nIDEvent = nIdEvent;
		 
			//������ʱ��
			rt_timer_start(pGuiTimer->pSysTimer);
		}
	}
}
/*********************************************************************************************************
** ��������: KillGuiTimer
** ��������: KillGuiTimer
**
** ����������  
**
** �䡡��:  CScreenBase * pScr
** �䡡��:  INT32U nIdEvent
**          
** �䡡��:   INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��11��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U KillGuiTimer( CScreenBase *pScr,INT32U nIdEvent )
{
	struct GUI_TIMER *pGuiTimer = NULL;
	gui_list_t *pNode = NULL;

	if(pScr == NULL)
		return FALSE;

	GuiListForEach(pNode, &(g_lstGuiTimerHead.list))
	{
		pGuiTimer = CONTAINING_RECORD(pNode, CGuiTimer,list);
		ASSERT(pGuiTimer);
		if (pGuiTimer && pGuiTimer->pScreen == pScr && pGuiTimer->nIDEvent
				== nIdEvent)
		{
			GuiListRemove( &(g_lstGuiTimerHead.list), & (pGuiTimer->list));
			rt_free( pGuiTimer );

			return TRUE;
		}
	}
	return FALSE;
}
