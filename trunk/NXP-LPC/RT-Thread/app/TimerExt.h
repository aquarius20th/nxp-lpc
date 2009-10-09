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

#define  EXT_TIMER_CNT  8 
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


typedef struct EXT_TIMER
{
	rt_uint32_t Count;		//ʱ�������
	rt_uint32_t TimeOut;		//������
	rt_uint8_t  Enable; 	    //ʹ�ܱ�־
	rt_uint8_t  Flag ;       //�Ƿ��Ѿ���ʱ��־
#if  EXT_TIMER_CB_EN > 0
 	fnTimerProcess pFunc;
	void   *pFuncParam;
#endif //  EXT_TIMER_CB_EN
}EXT_TIMER;

void InitTimerMgr( void );

//ʹ�ýӿ�  nTimerID ��1��ʼ������ <= 32

//���ö�ʱ��
#if  EXT_TIMER_CB_EN > 0
rt_uint16_t  SetTimer  (rt_uint16_t nTimerID, rt_uint32_t nTime,fnTimerProcess fnProc,void *pFuncParam );
#else
rt_uint16_t  SetTimer  (rt_uint16_t nTimerID, rt_uint32_t nTime);
#endif
// �ض�ʱ��
rt_uint8_t   KillTimer (rt_uint16_t nTimerID);

rt_uint8_t  ResetTimer(rt_uint16_t nTimerID);

//
rt_uint8_t IsTimeTo(rt_uint16_t TimerID ); 
//��TICK�ж��������
void   ExtTimerTick( void );


#endif 
