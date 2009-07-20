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
**��        ��:   �����ʱ��,��ʱ�ӵĴ���ϵͳʱ�䴦��
**��        ע :  ��ʱ���Ļص�����������ִ�з�����һ�����ں����ж�����ֱ��ִ�У�����һ���Զ��д洢��Ȼ��
                  ����������ִ�У�������ȱ�㣬��ģ����ú���ʵ��
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
#include "TaskDef.h"
#include "TimerMgr.h"

static OS_STK	TimerMgrTaskStk [TIMERMR_TASK_STK_SIZE];

static TIMER  g_Timer[MAX_TIMER_CNT];

static OS_EVENT *s_pTmrQeue = NULL;
void *TmrFuncQeueTbl[MAX_TIMER_CNT];

static OS_MEM  *s_pParamMem = NULL;
// INT8U  Param[MAX_TIMER_CNT][4];
static TIMER_MSG TimerMsgPartition[MAX_TIMER_CNT];

/*********************************************************************************************************
** ��������: TimerFuncHandle_Task
** ��������: TimerFuncHandle_Task
**
** ���������� ����ʱ������Ļص�
**
** �䡡��:  void * pdata
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void TimerFuncHandle_Task(void *pdata)
{	
	TIMER_MSG  *pTimer = NULL;
	INT8U err = 0;

	pdata = pdata;
	while (TRUE)
	{
		pTimer = (TIMER_MSG *)OSQPend(s_pTmrQeue,0,&err);
		if (err == OS_NO_ERR) 
		{
			if (pTimer && pTimer->pFunc)
			{
				pTimer->pFunc(  pTimer->pParam );
				//�ͷ���Ϣ��ռ�õ��ڴ�
				OSMemPut(s_pParamMem,pTimer);
			}
		}
		OSTimeDlyHMSM(0,0,0,100);
	}
}    
/*********************************************************************************************************
** ��������: InitTimerMgr
** ��������: InitTimerMgr
**
** ���������� 
**
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void InitTimerMgr(void )
{
	INT8U err = 0;
	INT8U i = 0;
	//��������
	s_pTmrQeue = OSQCreate(& TmrFuncQeueTbl[0] ,MAX_TIMER_CNT);

// 	//�����ڴ���������ڱ���ص���������
  	s_pParamMem = OSMemCreate(TimerMsgPartition,MAX_TIMER_CNT,sizeof(TIMER_MSG ),&err );

	for ( i = 0; i < MAX_TIMER_CNT; i++)
	{
		g_Timer[i].Enable = FALSE;
		g_Timer[i].Count = 0;
		g_Timer[i].TimeOut = 0;
		g_Timer[i].Flag = FALSE;
		g_Timer[i].pFunc = NULL;
		g_Timer[i].pFuncParam = NULL;
	}

	//��������
	OSTaskCreate (TimerFuncHandle_Task, (void *)0, 	&TimerMgrTaskStk[TIMERMR_TASK_STK_SIZE-1], PRIO_TMR_MGR);
}
/*********************************************************************************************************
** ��������: TimerMgrInMsInt
** ��������: TimerMgrInMsInt
**
** ���������� �ں����ж��������
**
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע:  ���������һ����Դ��ͻ���������������ν�ġ�
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: ISR �����Ѿ����˱�����
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void TimerMgrInIsr( INT16U nCnt )
{
	INT8U err = 0;
	INT16U  i = 0;
	TIMER_MSG *pTimerMsg = NULL;

	if(nCnt == 0)
   		nCnt = 10;

//	OS_ENTER_CRITICAL();	

	for ( i = 0; i < MAX_TIMER_CNT; i++)
	{
		if (g_Timer[i].Enable && g_Timer[i].TimeOut  )
		{
			g_Timer[i].Count += nCnt; //10����һ��TICK
			if (g_Timer[i].Count >= g_Timer[i].TimeOut )
			{
				g_Timer[i].Flag = TRUE;
				g_Timer[i].Count = 0;

				if (g_Timer[i].pFunc)
				{	
					//����һ���ڴ�
					pTimerMsg = OSMemGet( s_pParamMem , &err);
					if (pTimerMsg)
					{
						pTimerMsg->pFunc = g_Timer[i].pFunc;
						pTimerMsg->pParam = g_Timer[i].pFuncParam;

						//����Ϣ�Ļص�������post����������
						err = OSQPost(s_pTmrQeue,(void *)pTimerMsg );
						if (err != OS_NO_ERR)
						{//���post���ɹ��Ļ���������ڴ棬��ֹ�ڴ�����
							OSMemPut(s_pParamMem,pTimerMsg);
						}
					}
				}		
			}
		}	
	}
//	OS_EXIT_CRITICAL();
}
 
/*********************************************************************************************************
** ��������: SetTimer
** ��������: SetTimer
**
** ���������� ��װһ����ʱ��
**
** �䡡��:  INT16U TimerID
** �䡡��:  INT32U nTime
** �䡡��:  fnTimerProcess fnProc ��ʱ���Ļص�����
** �䡡��:  void * pFuncParam     �ص������Ĳ���
**          
** �䡡��:  INT16U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT16U  SetTimer(INT16U TimerID, INT32U nTime,fnTimerProcess fnProc,void *pFuncParam )
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	if (TimerID>0 && TimerID <= MAX_TIMER_CNT && nTime)
	{
		OS_ENTER_CRITICAL();	

		g_Timer[TimerID-1].Enable = TRUE;
		g_Timer[TimerID-1].TimeOut = nTime;
		
		g_Timer[TimerID-1].pFunc = fnProc;
		g_Timer[TimerID-1].pFuncParam = pFuncParam;

		OS_EXIT_CRITICAL();
		return TimerID;
	}
	return FALSE;
}

/*********************************************************************************************************
** ��������: KillTimer
** ��������: KillTimer
**
** ���������� ɾ����ʱ��
**
** �䡡��:  INT16U TimerID
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U   KillTimer (INT16U  TimerID)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	if (TimerID>0 && TimerID <= MAX_TIMER_CNT )
	{
		
		g_Timer[TimerID-1].TimeOut = 0;
		g_Timer[TimerID-1].Count = 0;
		g_Timer[TimerID-1].Flag = FALSE;
		if (g_Timer[TimerID-1].Enable)
		{
			OS_ENTER_CRITICAL();	
			g_Timer[TimerID-1].Enable = FALSE;
			g_Timer[TimerID-1].pFunc = NULL; //���ܻ������� 
			g_Timer[TimerID-1].pFuncParam = NULL;
			OS_EXIT_CRITICAL();
			return TRUE;
		}		
	}
	return FALSE;
}

/*********************************************************************************************************
** ��������: ResetTimer
** ��������: ResetTimer
**
** ���������� ��ʱ���¼�ʱ
**
** �䡡��:  INT16U TimerID
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U  ResetTimer(INT16U TimerID)
{
	if (TimerID>0 && TimerID <= MAX_TIMER_CNT )
	{
		if (g_Timer[TimerID-1].Enable)
		{
		 	g_Timer[TimerID-1].Count = 0;
			return TRUE;
		}		
	}
	return FALSE;
}

/*********************************************************************************************************
** ��������: IsTimeTo
** ��������: IsTimeTo
**
** ���������� �ж϶�ʱ�Ƿ񵽡�
**
** �䡡��:  INT16U TimerID
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��17��
** ��  ע:  �˽ӿڱ����ú󣬶�ʱ����־�ͱ���ת��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U IsTimeTo(INT16U TimerID )
{
	if (TimerID>0 && TimerID <= MAX_TIMER_CNT)
	{
		if (g_Timer[TimerID-1].Enable && g_Timer[TimerID-1].Flag == TRUE)
		{
			g_Timer[TimerID-1].Flag = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

/*
//�����õĶ�ʱ���ص�����
void TimerTestFunc( void * pPara )
{
	INT16U *pCnt =  pPara ;

	INT16U aa = *pCnt;

	aa++;

}

void TestTimer( )
{
	INT16U cnt = 0;
	INT8U bRet = FALSE;
	INT32U nTest = 0;

	SetTimer(1,100,TimerTestFunc,&cnt);
	SetTimer(2,1000,NULL,NULL);

	while (1)
	{
		OSTimeDly(2);
		bRet = IsTimeTo(2);
		if (bRet)
		{
			 nTest ++;
		}
	}
}*/
