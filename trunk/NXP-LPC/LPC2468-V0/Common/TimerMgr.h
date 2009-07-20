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

#if !defined(TIMER_MGR_H)
#define TIMER_MGR_H


#define  MAX_TIMER_CNT  16

typedef void (*fnTimerProcess)( void *pParam  );

typedef struct TIMER_MSG
{
	fnTimerProcess pFunc;
	void         *pParam;

}TIMER_MSG;

typedef struct TIMER
{
	INT32U Count;		//ʱ�������
	INT32U TimeOut;		//������
	INT8U  Enable; 	    //ʹ�ܱ�־
	INT8U  Flag ;       //�Ƿ��Ѿ���ʱ��־
 	fnTimerProcess pFunc;
	void   *pFuncParam;
}TIMER;

extern void InitTimerMgr( void );

//ʹ�ýӿ�  nTimerID ��1��ʼ������ <= 32

//���ö�ʱ��
extern  INT16U  SetTimer  (INT16U nTimerID, INT32U nTime,fnTimerProcess fnProc,void *pFuncParam );
// �ض�ʱ��
extern  INT8U   KillTimer (INT16U nTimerID);

extern  INT8U  ResetTimer(INT16U nTimerID);

//
extern INT8U IsTimeTo(INT16U TimerID );



//�ں����ж��������
extern void TimerMgrInIsr(INT16U nCnt );


#endif 
