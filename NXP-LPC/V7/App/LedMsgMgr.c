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
#include "includes.h" 
#include "LedMsgMgr.h"
#include "heap_mem.h"
#include "bsp.h"
 

#define  MAX_LED_NO 8
 
static  OS_EVENT *pLedMsgQ = NULL;
#define MAX_LEDMSG_CNT 10
void *LedMsgQeueTbl[MAX_LEDMSG_CNT];

struct LED_MSG
{
	INT8U  LedNo;
	INT8U  Time; // ʱ��
};

void InitLedMsgMgr( )
{
	pLedMsgQ = OSQCreate(LedMsgQeueTbl,MAX_LEDMSG_CNT );
}

INT8U SendLedMsg( INT8U nLedNo, INT8U Time )
{
	INT8U err = 0;
	struct LED_MSG *pMsg = NULL;

	if(nLedNo == 0 || nLedNo > MAX_LED_NO)
		return OS_FALSE;
	if (Time == 0)
		Time = 1;
	
	pMsg = rt_malloc(sizeof(struct LED_MSG));
 
	if (pMsg == NULL)
		return OS_FALSE;

	err = OSQPost(pLedMsgQ,pMsg);
	if (err == OS_NO_ERR)
		return OS_TRUE;

	rt_free(pMsg);

	return OS_FALSE;
}

void LedMsgMgrHandler(void)
{
	INT8U err = 0 ;
	struct LED_MSG *pMsg = NULL;
	if (pLedMsgQ == NULL)
		return;

	pMsg = OSQAccept(pLedMsgQ,&err);
	if (err == OS_NO_ERR && pMsg)
	{		 
		if (pMsg->LedNo > 0 &&  pMsg->LedNo <= MAX_LED_NO)
		{
			LED_On(pMsg->LedNo);
			OSTimeDlyHMSM(0,0,0,pMsg->Time*100);
			LED_Off(pMsg->LedNo);
			rt_free(pMsg);
		}	 
	}
}
