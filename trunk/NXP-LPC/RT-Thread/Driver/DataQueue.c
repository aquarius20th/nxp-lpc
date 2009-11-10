/***********************************************Copyright (c)*********************************************
**                                
**                                     
**                                      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    queue.c
** Last modified Date:      2007-09-20
** Last Version:		    1.0
** Descriptions:		    �м������
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    chengmingji
** Created date:		    2007-07-15
** Version:				    1.0
** Descriptions:		    
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    lixiaocheng
** Modified Date:		    2007-09-20
** Version:				    1.0
** Descriptions:		    ���Ű��ʽ�����˵���
**
*********************************************************************************************************/
#include <stdlib.h>
#include <string.h> 

#include "applib.h"
#include "DataQueue.h"

/*********************************************************************************************************
** Function name:           QueueCreate
** Descriptions:            ��ʼ�����ݶ���
** Input parameters:        pDataQ      ��Ϊ���з���Ĵ洢�ռ��ַ
**                          SizeOfBuf��Ϊ���з���Ĵ洢�ռ��С���ֽڣ�
**                          ReadEmpty��Ϊ���ж���ʱ�������
**                          WriteFull��Ϊ����д��ʱ�������
** Output parameters:       NONE
** Returned value:          NOT_OK  :��������
**                          QUEUE_OK:�ɹ�
*********************************************************************************************************/
INT8U QueueCreate (DataQueue *pDataQ, INT32U  SizeOfBuf,  INT8U   (* ReadEmpty)(), INT8U   (* WriteFull)() )
{	
	OS_CPU_SR  cpu_sr = 0; 

	DataQueue *pQueue = NULL;
	if (pDataQ != NULL && SizeOfBuf >= (sizeof(DataQueue))) 
	{ /* �жϲ����Ƿ���Ч             */
        pQueue = (DataQueue *)pDataQ;

        OS_ENTER_CRITICAL(); 
        /* ��ʼ���ṹ������             */
        pQueue->MaxDataNum = (INT16U)( ( SizeOfBuf - (INT32U)( ((DataQueue *)0)->Buf ) ) /sizeof(QUEUE_DATA_TYPE) );                      /* ������п��Դ洢��������Ŀ   */
        pQueue->pEnd = pQueue->Buf + pQueue->MaxDataNum;    /* �������ݻ���Ľ�����ַ       */
        pQueue->pOut = pQueue->Buf;
        pQueue->pIn = pQueue->Buf;
        pQueue->DataCnt = 0;
        pQueue->ReadEmpty = ReadEmpty;
        pQueue->WriteFull = WriteFull;

        OS_EXIT_CRITICAL();
        return QUEUE_OK;
    } 
	else
	{
        return NOT_OK;
    }
}
/*********************************************************************************************************
** Function name:           QueueRead
** Descriptions:            ��ȡ�����е�����
** Input parameters:        pRet:�洢���ص���Ϣ�ĵ�ַ
**                          Buf:ָ����е�ָ��
** Output parameters:       NONE
** Returned value:          NOT_OK     ����������
**                          QUEUE_OK   ���յ���Ϣ
**                          QUEUE_EMPTY�����п�
*********************************************************************************************************/
INT8U QueueRead (QUEUE_DATA_TYPE *pRet, DataQueue *Buf)
{
    OS_CPU_SR  cpu_sr = 0;

    INT8U err = NOT_OK;
    DataQueue *Queue = NULL;
  
    if (Buf != NULL)
	{                                                  /* �����Ƿ���Ч                 */
        Queue = (DataQueue *)Buf;
        
        OS_ENTER_CRITICAL();
        
        if (Queue->DataCnt > 0) 
		{                                         /* �����Ƿ�Ϊ��                 */                                                               
            *pRet = Queue->pOut[0];                 /* ���ݳ���                     */
            Queue->pOut++;                                               
            
            if (Queue->pOut >= Queue->pEnd)
			{  /* ��������ָ��                 */
                Queue->pOut = Queue->Buf;
            }
            
            Queue->DataCnt--;                                             /* ���ݼ���                     */
            err = QUEUE_OK;
        } 
		else 
		{                                                               
            err = QUEUE_EMPTY;
            
            if (Queue->ReadEmpty != NULL)
			{                             /* �գ������û�������         */
                err = Queue->ReadEmpty(pRet, Queue);
            }
        }
        OS_EXIT_CRITICAL();
    }
    return err;
}

/*********************************************************************************************************
** Function name:           QueueWrite
** Descriptions:            FIFO��ʽ��������
** Input parameters:        Buf :ָ����е�ָ��
**                          Data:���͵�����
** Output parameters:       NONE
** Returned value:          NOT_OK    : ��������
**                          QUEUE_FULL: ������
**                          QUEUE_OK  : ���ͳɹ�
*********************************************************************************************************/
INT8U QueueWrite (DataQueue *Buf, QUEUE_DATA_TYPE Data)
{
	OS_CPU_SR  cpu_sr = 0;
	INT8U err = NOT_OK;
	DataQueue *Queue = NULL;
		  
    if (Buf != NULL)
	{                                                  /* �����Ƿ���Ч                 */
        Queue = (DataQueue *)Buf;
        
        OS_ENTER_CRITICAL(); 
        
        if (Queue->DataCnt < Queue->MaxDataNum) 
		{                            /* �����Ƿ���                   */
            Queue->pIn[0] = Data;                                        /* �������                     */
            Queue->pIn++;
                                                           
            if (Queue->pIn >= Queue->pEnd)
			{                              /* �������ָ��                 */
                Queue->pIn = Queue->Buf;
            }
            
            Queue->DataCnt++;                                             /* ��������                     */
            err = QUEUE_OK;
        } 
		else 
		{                                                        /* ��                           */
            err = QUEUE_FULL;
            if (Queue->WriteFull != NULL) 
			{                             /* �����û�������             */
                err = Queue->WriteFull(Queue, Data, Q_WRITE_MODE);
            }
        }
        OS_EXIT_CRITICAL();
    }
    return err;
}

//����
extern INT8U QueueWriteEx (DataQueue *Buf, QUEUE_DATA_TYPE *pData,INT16U nLen,INT16U *pnRetLen)
{
 	OS_CPU_SR  cpu_sr = 0;
 
	INT8U err = NOT_OK;
	DataQueue *Queue = (DataQueue *)Buf;
	INT16U nQLen = 0;
 
	  /* �����Ƿ���Ч                 */
	if (Queue != NULL && pData != NULL && nLen > 0 && nLen <= Queue->MaxDataNum )
	{   
		OS_ENTER_CRITICAL(); 

		if (Queue->DataCnt + nLen < Queue->MaxDataNum) 
		{      /* �����Ƿ���  */
		 //	Queue->pIn[0] = Data;                                        /* �������                     */
		//	Queue->pIn++;
			memcpy(& Queue->pIn[0] ,pData, nLen );
			Queue->pIn += nLen;

			if (Queue->pIn >= Queue->pEnd)
			{                              /* �������ָ��                 */
				Queue->pIn = Queue->Buf;
			}

			  /* ��������              */
			Queue->DataCnt += nLen;
			*pnRetLen = nLen;
			err = QUEUE_OK;
		} 
		else if ( Queue->DataCnt + nLen >= Queue->MaxDataNum )
		{/* �������ֻ�ܴ�Ų���  */
			nQLen = Queue->MaxDataNum - Queue->DataCnt;
			memcpy(& Queue->pIn[0] ,pData, nQLen );
			Queue->pIn += nQLen;

			if (Queue->pIn >= Queue->pEnd)
			{                              /* �������ָ��                 */
				Queue->pIn = Queue->Buf;
			}

			/* ��������              */
			Queue->DataCnt += nQLen;
			*pnRetLen = nQLen;
			err = QUEUE_OK;
		}
		else if (Queue->DataCnt == Queue->MaxDataNum)
	 	{ /* �Ѿ���  */
			*pnRetLen = 0;
			err = QUEUE_FULL;
			if (Queue->WriteFull != NULL) 
			{                             /* �����û�������             */
				err = Queue->WriteFull(Queue, pData[0], Q_WRITE_MODE);
			}
		}
		OS_EXIT_CRITICAL();
	}
	return err;
}

/*********************************************************************************************************
** Function name:           QueueWriteFront
** Descriptions:            LIFO��ʽ��������
** Input parameters:        Buf :ָ����е�ָ��
**                          Data:���͵�����
** Output parameters:       NONE
** Returned value:          NOT_OK    : ��������
**                          QUEUE_FULL: ������
**                          QUEUE_OK  : ���ͳɹ�
*********************************************************************************************************/
INT8U QueueWriteFront (DataQueue *Buf, QUEUE_DATA_TYPE Data)
{
	OS_CPU_SR  cpu_sr = 0;
	INT8U err = NOT_OK;
	DataQueue *Queue = NULL;
	    
    if (Buf != NULL) 
	{                                                  /* �����Ƿ���Ч                 */
        Queue = (DataQueue *)Buf;
        
        OS_ENTER_CRITICAL();
        if (Queue->DataCnt < Queue->MaxDataNum)
		{                            /* �����Ƿ���                   */
            Queue->pOut--; 

			if (Queue->pOut < Queue->Buf) 
			{ /* ��������ָ��                 */
				Queue->pOut = Queue->pEnd - 1;
			}
            
            Queue->pOut[0] = Data;                                       /* �������                     */
            Queue->DataCnt++;                                             /* ������Ŀ����                 */
            err = QUEUE_OK;
        }
		else
		{                                                        /* ��                           */
            err = QUEUE_FULL;
            if (Queue->WriteFull != NULL) 
			{                             /* �����û�������             */
                err = Queue->WriteFull(Queue, Data, Q_WRITE_FRONT_MODE);
            }
        }
        OS_EXIT_CRITICAL();
    }
    return err;
}
/*********************************************************************************************************
** Function name:           GetQueueDataCnt
** Descriptions:            ȡ�ö�����������
** Input parameters:        Buf :ָ����е�ָ��
** Output parameters:       NONE
** Returned value:          ���а���������
*********************************************************************************************************/
INT16U GetQueueDataCnt (DataQueue *Buf)
{
	OS_CPU_SR  cpu_sr = 0;

    INT16U temp = 0;                                                           /* ������Ч����0                */
    
    if (Buf != NULL)
	{
        OS_ENTER_CRITICAL(); 
        temp = ((DataQueue *)Buf)->DataCnt;
        OS_EXIT_CRITICAL();
    }
    return temp;
} 
/*********************************************************************************************************
** Function name:           GetQueueSize
** Descriptions:            ȡ�ö���������
** Input parameters:        Buf :ָ����е�ָ��
** Output parameters:       NONE
** Returned value:          ����������
*********************************************************************************************************/
INT16U GetQueueSize (DataQueue *Buf)
{
    OS_CPU_SR  cpu_sr = 0;
 
    INT16U temp = 0;        /* ������Ч����0                */
    
    if (Buf != NULL)
	{
        OS_ENTER_CRITICAL();
        temp = ((DataQueue *)Buf)->MaxDataNum;
        OS_EXIT_CRITICAL();
    }
    return temp;
} 
/*********************************************************************************************************
** Function name:           OSQFlush
** Descriptions:            ��ն���
** Input parameters:        Buf :ָ����е�ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void QueueFlush (DataQueue *Buf)
{
     OS_CPU_SR  cpu_sr = 0;
 
    DataQueue *Queue = NULL;
    
    if (Buf != NULL) 
	{                                                  /* �����Ƿ���Ч                 */
        Queue = (DataQueue *)Buf;
        OS_ENTER_CRITICAL();
        Queue->pOut = Queue->Buf;
        Queue->pIn = Queue->Buf;
        Queue->DataCnt = 0;                                               /* ������ĿΪ0                  */
        OS_EXIT_CRITICAL();
    }
}
                                                    

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
