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
#include "TimerExt.h"

static EXT_TIMER  g_Timer[EXT_TIMER_CNT];

#if  EXT_TIMER_CB_EN > 0
static OS_STK	TimerMgrTaskStk [EXT_TASK_TMR_STK_SIZE];
static OS_EVENT *s_pTmrQeue = NULL;
void *TmrFuncQeueTbl[EXT_TIMER_CNT];
static OS_MEM  *s_pParamMem = NULL;
static TIMER_MSG TimerMsgPartition[EXT_TIMER_CNT];
#endif
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
#if  EXT_TIMER_CB_EN > 0
void TimerFuncHandleTask(void *pdata)
{	
	TIMER_MSG  *pTimer = NULL;
	rt_uint8_t err = 0;

	pdata = pdata;
	while (RT_TRUE)
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
#endif
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
#if  EXT_TIMER_CB_EN > 0
	rt_uint8_t err = 0;
#endif
	rt_uint8_t i = 0;

	for ( i = 0; i < EXT_TIMER_CNT; i++)
	{
		g_Timer[i].Enable = RT_FALSE;
		g_Timer[i].Count = 0;
		g_Timer[i].TimeOut = 0;
		g_Timer[i].Flag = RT_FALSE;
#if  EXT_TIMER_CB_EN > 0
		g_Timer[i].pFunc = NULL;
		g_Timer[i].pFuncParam = NULL;
#endif
	}
#if  EXT_TIMER_CB_EN > 0
	//��������
	s_pTmrQeue = OSQCreate(& TmrFuncQeueTbl[0] ,EXT_TIMER_CNT);
	// 	//�����ڴ���������ڱ���ص���������
	s_pParamMem = OSMemCreate(TimerMsgPartition,EXT_TIMER_CNT,sizeof(TIMER_MSG ),&err );
	//��������
	OSTaskCreate (TimerFuncHandleTask, (void *)0, 	&TimerMgrTaskStk[EXT_TASK_TMR_STK_SIZE-1], PRIO_TMR_MGR);
#endif

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
void ExtTimerTick(  )
{
	rt_uint16_t  i = 0;
#if  EXT_TIMER_CB_EN > 0
	TIMER_MSG *pTimerMsg = NULL;
	rt_uint8_t err = 0;
#endif

#ifdef EXT_TMR_CFG_TICKS_PER_SEC
	rt_uint16_t nCnt = EXT_TMR_CFG_TICKS_PER_SEC;
#else
	rt_uint16_t nCnt = 1000/OS_TICKS_PER_SEC;
#endif // _DEBUG
	if(nCnt == 0)
   		nCnt = 10;

//	OS_ENTER_CRITICAL();	
	for ( i = 0; i < EXT_TIMER_CNT; i++)
	{
		if (g_Timer[i].Enable && g_Timer[i].TimeOut  )
		{
			g_Timer[i].Count += nCnt; //10����һ��TICK
			if (g_Timer[i].Count >= g_Timer[i].TimeOut )
			{
				g_Timer[i].Flag = RT_TRUE;
				g_Timer[i].Count = 0;
#if  EXT_TIMER_CB_EN > 0
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
#endif
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
** �䡡��:  rt_uint16_t TimerID
** �䡡��:  rt_uint32_t nTime
** �䡡��:  fnTimerProcess fnProc ��ʱ���Ļص�����
** �䡡��:  void * pFuncParam     �ص������Ĳ���
**          
** �䡡��:  rt_uint16_t
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
#if  EXT_TIMER_CB_EN > 0
rt_uint16_t  SetTimer(rt_uint16_t TimerID, rt_uint32_t nTime,fnTimerProcess fnProc,void *pFuncParam )
#else
rt_uint16_t  SetTimer(rt_uint16_t TimerID, rt_uint32_t nTime )
#endif
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	rt_uint16_t i = 0;

	if (TimerID>0 && TimerID <= EXT_TIMER_CNT && nTime)
	{
		OS_ENTER_CRITICAL();	

		g_Timer[TimerID-1].Enable = RT_TRUE;
		g_Timer[TimerID-1].TimeOut = nTime;
		g_Timer[TimerID-1].Count = 0;
#if  EXT_TIMER_CB_EN > 0	
		g_Timer[TimerID-1].pFunc = fnProc;
		g_Timer[TimerID-1].pFuncParam = pFuncParam;
#endif
		OS_EXIT_CRITICAL();
		return TimerID;
	}
	else if ( TimerID == 0 && nTime )
	{
		OS_ENTER_CRITICAL();	
		for ( i = 0; i < EXT_TIMER_CNT ; i++)
		{
			if (g_Timer[i].Enable == RT_FALSE)
			{
				g_Timer[i].Enable = RT_TRUE;
				g_Timer[i].TimeOut = nTime;
				g_Timer[i].Count = 0;
#if  EXT_TIMER_CB_EN > 0
				g_Timer[i].pFunc = fnProc;
				g_Timer[i].pFuncParam = pFuncParam;
#endif
				OS_EXIT_CRITICAL();
				return i+1;
			}
		}
	}
	return RT_FALSE;
}

/*********************************************************************************************************
** ��������: KillTimer
** ��������: KillTimer
**
** ���������� ɾ����ʱ��
**
** �䡡��:  rt_uint16_t TimerID
**          
** �䡡��:  rt_uint8_t
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
rt_uint8_t   KillTimer (rt_uint16_t  TimerID)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	if (TimerID>0 && TimerID <= EXT_TIMER_CNT )
	{		
		g_Timer[TimerID-1].TimeOut = 0;
		g_Timer[TimerID-1].Count = 0;
		g_Timer[TimerID-1].Flag = RT_FALSE;
		if (g_Timer[TimerID-1].Enable)
		{
			OS_ENTER_CRITICAL();	
			g_Timer[TimerID-1].Enable = RT_FALSE;
#if  EXT_TIMER_CB_EN > 0
			g_Timer[TimerID-1].pFunc = NULL; //���ܻ������� 
			g_Timer[TimerID-1].pFuncParam = NULL;
#endif
			OS_EXIT_CRITICAL();
			return RT_TRUE;
		}		
	}
	return RT_FALSE;
}

/*********************************************************************************************************
** ��������: ResetTimer
** ��������: ResetTimer
**
** ���������� ��ʱ���¼�ʱ
**
** �䡡��:  rt_uint16_t TimerID
**          
** �䡡��:  rt_uint8_t
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
rt_uint8_t  ResetTimer(rt_uint16_t TimerID)
{
	if (TimerID>0 && TimerID <= EXT_TIMER_CNT )
	{
		if (g_Timer[TimerID-1].Enable)
		{
		 	g_Timer[TimerID-1].Count = 0;
			return RT_TRUE;
		}		
	}
	return RT_FALSE;
}

/*********************************************************************************************************
** ��������: IsTimeTo
** ��������: IsTimeTo
**
** ���������� �ж϶�ʱ�Ƿ񵽡�
**
** �䡡��:  rt_uint16_t TimerID
**          
** �䡡��:  rt_uint8_t
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
rt_uint8_t IsTimeTo(rt_uint16_t TimerID )
{
	if (TimerID>0 && TimerID <= EXT_TIMER_CNT)
	{
		if (g_Timer[TimerID-1].Enable && g_Timer[TimerID-1].Flag == RT_TRUE)
		{
			g_Timer[TimerID-1].Flag = RT_FALSE;
			return RT_TRUE;
		}
	}
	return RT_FALSE;
}

/*
//�����õĶ�ʱ���ص�����
void TimerTestFunc( void * pPara )
{
	rt_uint16_t *pCnt =  pPara ;

	rt_uint16_t aa = *pCnt;

	aa++;

}

void TestTimer( )
{
	rt_uint16_t cnt = 0;
	rt_uint8_t bRet = RT_FALSE;
	rt_uint32_t nTest = 0;

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
