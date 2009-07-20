/****************************************Copyright (c)**************************************************
**                                 
**            ��ʱ�ӵĴ���ϵͳʱ�䴦��                          
**            ʱ�������������޸�ʱ��ʱ����������                          
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
#include <stdlib.h>
#include "includes.h"
#include "Ram.h"
#include "ClockMgr.h"
#include "TaskDef.h"
 

static OS_EVENT   *ClkSem = NULL;            /* Semaphore used to access the time of day clock               */
static OS_EVENT   *ClkSemSec = NULL;         /* Counting semaphore used to keep track of seconds             */

static  OS_STK      ClkTaskStk[CLK_TASK_STK_SIZE];
 

// One-based array of days in year at month start
const INT16U _MonthDays[13] =
	{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

//�ж��Ƿ�������
/*
��������������������Ϊyear����

��1����year��400��������ʱΪ���꣬������ʾΪ��

year%400= =0

��2����year��4����������������100��������ʱΪ���꣬����Ϊ��

    year%4= =0 && year%100 != 0
*/

#define IsLeapYear(nYear) ((((nYear) & 3) == 0) && (((nYear) % 100) != 0 || ((nYear) % 400) == 0))

//����ĳ��ĳ���ж�����
#define GetDaysInMonth(nYear, nMon) (_MonthDays[nMon] - _MonthDays[(nMon)-1] + (((nMon) == 2 && IsLeapYear(nYear)) ? 1 : 0))

//ʱ������һ��
static void Time_AddSecond(CDateTime * pNow)
{
	INT16U nDaysInMonth;
	pNow->s++;
	if(pNow->s >= 60)
	{
		pNow->s = 0;
		pNow->min++;
		if(pNow->min >= 60)
		{
			pNow->min = 0;
			pNow->h++;
			if(pNow->h >= 24)
			{
				pNow->h = 0;
				pNow->d++;
				
				//���㵱ǰ���ж�����
				nDaysInMonth =GetDaysInMonth(pNow->y, pNow->mon);
				
				if(pNow->d > nDaysInMonth)	//����һ����
				{
					if(pNow->mon==12)
					{
						//��һ��
						pNow->d = 1;
						pNow->mon = 1;
						pNow->y++;
					}
					else
					{
						pNow->d = 1;
						pNow->mon++;
					}
				}
			}
		}
	}		
}
/*********************************************************************************************************
** ��������: ClockMgrSignal
** ��������: ClockMgrSignal
**
** ���������� �����ж��У���ʱ�ӽ��м�ʱ����
**
** �䡡��:  void
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��19��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void ClockMgrSignal(INT16U nMsCnt)
{
	Ram.now.ms += nMsCnt; //1����һ��TICK
	if(Ram.now.ms>=1000)
	{
		Ram.now.ms=0;
		//����һ��
		OSSemPost(ClkSemSec);               /* Signal that one second elapsed                          */
//		Time_AddSecond((CDateTime *)&Ram.now);
	}
}

static void  ClockMgrTask (void *data)
{
	INT8U err = 0;

	for (;;) 
	{
		OSSemPend(ClkSemSec, 0, &err);

		OSSemPend(ClkSem, 0, &err);         /* Gain exclusive access to time-of-day clock              */
		
		Time_AddSecond((CDateTime *)&Ram.now);
		
		OSSemPost(ClkSem);                  /* Release access to time-of-day clock                     */
	}
}

extern void InitClockMgr( void )
{
	ClkSem     = OSSemCreate(1);       /* Create time of day clock semaphore                           */
	ClkSemSec  = OSSemCreate(0);       /* Create counting semaphore to signal the occurrence of 1 sec. */
 
	OSTaskCreate(ClockMgrTask, (void *)0, &ClkTaskStk[CLK_TASK_STK_SIZE-1], CLK_TASK_PRIO);
}

static INT8U CheckTime(CDateTime * pTime)
{
	if (pTime->y > 99 || pTime->mon < 1 || pTime->mon > 12)
		return FALSE;

	if (pTime->d < 1 || pTime->h > 23 || pTime->min > 59 || pTime->s > 59 || pTime->ms>999)
	{
		return FALSE;
	}

	return TRUE;
}

//����ϵͳʱ��
INT8U SetDeviceSystemTime(CDateTime * pTime)
{
	if(CheckTime(pTime))
	{
		Ram.now=*pTime;

	//	ModeifyRTCTime(pTime);

		return TRUE;
	}
	else
		return FALSE;
}

static INT8U CheckClockTime( INT8U hr, INT8U min, INT8U sec)
{ 
	if (  hr > 23 || min > 59 || sec > 59)
	{
		return FALSE;
	}

	return	TRUE;
}

static INT8U CheckClockDate( INT8U month, INT8U day, INT16U year)
{
	if (year > 99 ||month < 1 || month > 12 || day<1 || day >31)
		return FALSE;
	return	TRUE;
}

extern INT8U  ClockSetDateTime(INT8U month, INT8U day, INT16U year, INT8U hr, INT8U min, INT8U sec)
{
	INT8U err = 0;
	INT8U ret = 0;

	ret = CheckClockDate( month,day,year );
	if (ret == FALSE)
		return FALSE;

	ret =CheckClockTime( hr,min,sec);
	if (ret == FALSE)
		return FALSE;

	OSSemPend(ClkSem, 0, &err);                  /* Gain exclusive access to time-of-day clock         */

	Ram.now.y = year;
	Ram.now.mon = month;
	Ram.now.d = day;
	Ram.now.h = hr;
	Ram.now.min = min;
	Ram.now.s = sec;

	OSSemPost(ClkSem);                           /* Release access to time-of-day clock                */
	return	TRUE;
}

extern INT8U   ClockSetTime(INT8U hr, INT8U min, INT8U sec)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	INT8U ret = 0;

	ret =CheckClockTime( hr,min,sec);
	if (ret == FALSE)
		return FALSE;

	OS_ENTER_CRITICAL();                         /* Gain exclusive access to time-of-day clock         */
 
	Ram.now.h = hr;
	Ram.now.min = min;
	Ram.now.s = sec;

	OS_EXIT_CRITICAL();                          /* Release access to time-of-day clock                */

	return	TRUE;
}

extern INT8U   ClockSetDate(INT8U month, INT8U day, INT16U year)
{
	INT8U err = 0;
	INT8U ret = 0;

	ret = CheckClockDate( month,day,year );
	if (ret == FALSE)
		return FALSE;

	OSSemPend(ClkSem, 0, &err);                  /* Gain exclusive access to time-of-day clock         */
	Ram.now.y = year;
	Ram.now.mon = month;
	Ram.now.d = day;
	OSSemPost(ClkSem);                           /* Release access to time-of-day clock                */

	return	TRUE;
}

// void RtcTime2DateTime(const TRtcTime * pRtcTime, CDateTime * pTime)
// {
// 	//��
// 	pTime->s=BCD2HEX(pRtcTime->sec);
// 	//��
// 	pTime->min=BCD2HEX(pRtcTime->min);
// 	//ʱ
// 	pTime->h=BCD2HEX(pRtcTime->hour);	//ת��Ϊ24Сʱ��ʽ
// 	//��
// 	pTime->d=BCD2HEX(pRtcTime->date);
// 	//��
// 	pTime->mon=BCD2HEX(pRtcTime->mon);
// 	//��
// 	pTime->y=BCD2HEX(pRtcTime->year);
// 
// 	pTime->ms=0;
// }

// void DateTime2RtcTime(const TDateTime * pTime, TRtcTime * pRtcTime)
// {
// 	//��
// 	pRtcTime->sec=HEX2BCD(pTime->s);
// 	//��
// 	pRtcTime->min=HEX2BCD(pTime->min);
// 	//ʱ
// 	pRtcTime->hour=HEX2BCD(pTime->h);
// 	//��
// 	pRtcTime->date=HEX2BCD(pTime->d);
// 	//��
// 	pRtcTime->mon=HEX2BCD(pTime->mon);
// 	//��
// 	pRtcTime->year=HEX2BCD(pTime->y);
// }

 

 