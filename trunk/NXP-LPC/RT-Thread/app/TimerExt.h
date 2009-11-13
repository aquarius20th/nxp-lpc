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
**��        ע : �����ʱ����ò�Ҫ����ѭ����
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
#pragma once


#if !defined(TIMER_MGR_H)
#define TIMER_MGR_H


#define  EXT_TMR_CFG_TICKS_PER_SEC 10  

#define  EXT_TIMER_CB_EN   0
#define  EXT_TASK_TMR_STK_SIZE    256
#define  PRIO_TMR_MGR              32

#if  EXT_TIMER_CB_EN > 0
typedef void (*fnTimerProcess)( void *pParam  );
typedef struct TIMER_MSG
{
	fnTimerProcess pFunc;
	void         *pParam;
}TIMER_MSG;
#endif //  EXT_TIMER_CB_EN


struct EXT_TIMER
{
	INT32U Count;		//ʱ�������
	INT32U TimeOut;		//������
	INT8U  Enable; 	    //ʹ�ܱ�־
	INT8U  Flag ;       //�Ƿ��Ѿ���ʱ��־
#if  EXT_TIMER_CB_EN > 0
 	fnTimerProcess pFunc;
	void   *pFuncParam;
#endif //  EXT_TIMER_CB_EN
} ;

typedef struct EXT_TIMER TimerExt;

void InitTimerMgr( void );

//ʹ�ýӿ�  nTimerID ��1��ʼ������ <= 32

//���ö�ʱ��
#if  EXT_TIMER_CB_EN > 0
INT32U  SetTimer  (INT32U nTimerID, INT32U nTime,fnTimerProcess fnProc,void *pFuncParam );
#else
INT32U  SetTimer  (INT32U nTimerID, INT32U nTime);
#endif
// �ض�ʱ��
INT8U   KillTimer (INT32U nTimerID);

INT8U ResetTimer(INT32U nTimerID);

//
INT8U IsTimeTo(INT32U TimerID ); 
//��TICK�ж��������
void   ExtTimerTick( void );


#endif 
