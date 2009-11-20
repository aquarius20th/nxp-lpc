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
#include <stdlib.h> 
#include "applib.h"
#include "board.h"
#include <rtthread.h>
#include <rthw.h>
#include "uart.h" 
#include <LPC24xx.H>


#ifndef OPERATE_SUCCESS
#define OPERATE_SUCCESS		1         /* �����ɹ�                     */
#endif

#ifndef OPERATE_FAIL
#define OPERATE_FAIL	   -1          /* ����ʧ��                     */
#endif

#define     UART0_BASE_ADDR		    0xE000C000
#define     UART1_BASE_ADDR		    0xE0010000
#define     UART2_BASE_ADDR		    0xE0078000

typedef enum RS485_STATE
{
	RS485_RECV  =0,	// 
	RS485_SEND	=1	// 
}RS485_STATE;
 
/*********************************************************************************************************
   �������UART�����Ľṹ�壬�ж����������Ҫ��������ṹ��
*********************************************************************************************************/
static UART_INFO    UART0Info;        /*  ����UART0��һ���ṹ��       */
static UART_INFO    UART1Info;
static UART_INFO    UART2Info; 

/*********************************************************************************************************
   ����ʹ��ָ������������ṹ��ָ��,����Ը���������չ
*********************************************************************************************************/
UART_INFO *  UartInfoTab[UART_MAX_NUM] = {&UART0Info, &UART1Info,&UART2Info };

/*********************************************************************************************************
   ���涨����UART����ֵַ�����������UART���������ڸ�λ�������Ӧ�Ļ���ַ����
*********************************************************************************************************/
const INT32U    UartBaseAddrTab[UART_MAX_NUM] = {UART0_BASE_ADDR, UART1_BASE_ADDR,UART2_BASE_ADDR };
                                                         
/*********************************************************************************************************
   ���涨����UARTӲ��FIFOֵ�����������UART���������ڸ�λ�������Ӧ��ֵ����
*********************************************************************************************************/
const INT32U    UartFifoTab[UART_MAX_NUM] = {UART0FIFOLENFUN, UART1FIFOLENFUN,UART2FIFOLENFUN };
                                                     
/*********************************************************************************************************
   ���涨����UART�������FIFO��Сֵ�������������UART���������ڸ�λ�������Ӧ��ֵ����
*********************************************************************************************************/
const INT32U    QueueReviceFifoTab[UART_MAX_NUM] = {QUEUE0REVICEFIFOLENFUN, QUEUE1REVICEFIFOLENFUN,QUEUE2REVICEFIFOLENFUN };  

/*********************************************************************************************************
   ���涨����UART�������FIFOֵ�������������UART���������ڸ�λ�������Ӧ��ֵ����
*********************************************************************************************************/
const INT32U    QueueSendFifoTab[UART_MAX_NUM] = {QUEUE0SENDFIFOLENFUN, QUEUE1SENDFIFOLENFUN, QUEUE2SENDFIFOLENFUN };  
                                                              
/*********************************************************************************************************
   ���涨����UART0�����FIFO����
*********************************************************************************************************/ 
static INT8U Uatr0RxBuf[QUEUE0REVICEFIFOLENFUN];
static INT8U Uatr0TxBuf[QUEUE0SENDFIFOLENFUN];    

/*********************************************************************************************************
   ���涨����UART1�����FIFO����
*********************************************************************************************************/ 
static INT8U Uatr1RxBuf[QUEUE1REVICEFIFOLENFUN];
static INT8U Uatr1TxBuf[QUEUE1SENDFIFOLENFUN];
/*********************************************************************************************************
   ���涨����UART2�����FIFO����
*********************************************************************************************************/ 
static INT8U Uatr2RxBuf[QUEUE2REVICEFIFOLENFUN];
static INT8U Uatr2TxBuf[QUEUE2SENDFIFOLENFUN];
/*********************************************************************************************************
   ����ʹ��ָ������������UART���FIFO������׵�ַ
*********************************************************************************************************/ 
const INT8U *UartReviceTab[UART_MAX_NUM] = {Uatr0RxBuf, Uatr1RxBuf, Uatr2RxBuf};
const INT8U *UartSendTab[UART_MAX_NUM] = {Uatr0TxBuf, Uatr1TxBuf, Uatr2TxBuf}; 

/*********************************************************************************************************
** ��������: SetRS485Mode
** ��������: SetRS485Mode
**
** ���������� ����485ģʽ
**
** �䡡��:  INT32U uiId
** �䡡��:  INT8U Flag
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��8��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U SetRS485Mode(INT32U uiId, INT8U Flag )
{
	if (uiId == UART1)
	{
// 		if (Flag == RS485_SEND)
// 			FIO3CLR = RW_485;		
// 		else		
// 			FIO3SET = RW_485;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/*********************************************************************************************************
** Function name:			SetUartBandRate
** Descriptions:			��ʼ��UART�����ʲ���
** input parameters:		pUartInfo:          ָ��uart��Ϣ�ṹ���ָ��
**                          uibps:              ������ֵ
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
static INT32S SetUartBandRate (UART_INFO *pUartInfo, INT32U uibps)
{    
    volatile INT32U  uiOffBase;
	volatile INT32U *puiAddrBase;
        
	puiAddrBase = pUartInfo->puiAddrBase;	                            /*  ��ȡ�ṹ�����              */
	uiOffBase   = pUartInfo->uiOffBase;
	
	if ((uibps <= 115200) && (uibps >= 9600))                           /*  ��������                    */
	{
	    puiAddrBase[__B_UART_LCR << uiOffBase] |= 0x80;        		    /*  ������ʷ�Ƶ���ӼĴ���      */
	    			                                                    /*  ���ò�����                  */
	    puiAddrBase[__B_UART_DLM << uiOffBase] = ((Fpclk / uibps) / 16) / 256;   
		puiAddrBase[__B_UART_DLL << uiOffBase] = ((Fpclk / uibps) / 16) % 256;		
 		puiAddrBase[__B_UART_LCR << uiOffBase] &= 0x7f;             	/*  ��ֹ���ʷ�Ƶ���ӼĴ���      */
	    return UART_OK;
	}
    return UART_NOK;
}
 
/*********************************************************************************************************
** Function name:			SetUartMode
** Descriptions:			��ʼ��UART��ģʽ����
** input parameters:		pUartInfo:          ָ��uart��Ϣ�ṹ���ָ��
**                          uiParaData:         ����ָ��
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
static INT32S SetUartParam (UART_INFO *pUartInfo,  UART_PARAM *pUartParam)
{
    volatile INT32U uiOffBase;
	volatile INT32U *puiAddrBase;
	
    INT32U uiBak;
             
	puiAddrBase = pUartInfo->puiAddrBase;	                            /*  ��ȡ�ṹ�����              */
	uiOffBase   = pUartInfo->uiOffBase;

	/*  ��������                    */ 
	if ( pUartParam	)
	{
		if ((pUartParam->datab  <5) || (pUartParam->datab  > 8) )
		{
			 return UART_NOK;
		}
		if (( pUartParam->stopb  == 0) || (pUartParam->stopb  > 2))
		{ 	 
			return UART_NOK;
		}
		if ( pUartParam->parity > 4) 
		{
			return UART_NOK;
		}

		uiBak = pUartParam->datab - 5;
		if (pUartParam->stopb  == 2)
		{                                    /*  �ж��Ƿ�Ϊ2λֹͣλ         */
			uiBak |= 0x04;			
		}
		if (pUartParam->parity != 0) 
		{
			pUartParam->parity = pUartParam->parity - 1;
			uiBak |= 0x08;                    					            /*  ʹ����żУ��	            */   
		}
		uiBak |= pUartParam->parity << 4;							        /*  ������żУ��                */						 
		puiAddrBase[__B_UART_LCR << uiOffBase] = uiBak;           		    /*  ��ֹ���ʷ�Ƶ���ӼĴ���      */
	}
	return UART_OK;
}                                                 
/*********************************************************************************************************
** Function name:			UartCfgInit
** Descriptions:			��ʼ��UART,�˺�����UartInit����,���ṩ���û�
** input parameters:		pUartInfo:          ָ��uart��Ϣ�ṹ���ָ��
**                          uiParaData:         ����ָ��
**                          uiReBufSize:        uart�Ľ��ջ�������С
**                          uiSeBufSize:        uart�ķ��ͻ�������С
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
static INT32U UartCfgInit (UART_INFO *pUartInfo,  UART_PARAM *pUartParam, INT32U uiReBufSize,  INT32U uiSeBufSize)
{
//#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
//    OS_CPU_SR  cpu_sr = 0;
//#endif

    volatile INT32U *puiAddrBase;
	volatile INT32U uiOffBase;
	INT32U uiId;
	
	puiAddrBase = pUartInfo->puiAddrBase;
	uiOffBase   = pUartInfo->uiOffBase;
	uiId = pUartInfo->uiUartId;

// 	if (uiId == UART3)
// 	{//����485оƬ����
// 		FIO3SET =  1 << 21;	
// 	}
	
//    OS_ENTER_CRITICAL();                                                /*  ���ж�                     */     	
    if (QueueCreate(pUartInfo->pDQReviceBuf, uiReBufSize, NULL, NULL) == NOT_OK)
	{  /*  �������ջ�����             */	                                                                      
    	return UART_NOK;  
    } 			
    if (QueueCreate(pUartInfo->pDQSendBuf, uiSeBufSize, NULL, NULL) == NOT_OK)
	{    /*  �������ͻ�����             */ 	                                                                    
        return UART_NOK;
    }                                                               
	pUartInfo->uiUartFlag = 0x80;	    /*  7λ��λ��ʾ���÷��Ͷ��л���  Ҳ���ǽ�ֹ�����ж�         */
										
	  /*  ��������         */
	if (pUartParam)
	{
		if (pUartParam->bps < 9600 || pUartParam->bps > 115200)
		{
			pUartParam->bps = 9600;
		}

		if ((pUartParam->datab < 5) || (pUartParam->datab > 8)) 
		{	
			pUartParam->datab  = 8;
		}
		if (( pUartParam->stopb == 0) || ( pUartParam->stopb > 2))
		{ 	
			 pUartParam->stopb  = 1;
		}
		if (  pUartParam->parity  > 4) 
		{
			 pUartParam->parity  = 0;
		}
		if ( pUartParam->rtsctl != 0)
		{	
			pUartParam->rtsctl = 0;
		}

		if (OPERATE_FAIL == (SetUartBandRate(pUartInfo,pUartParam->bps))) 
		{
			return UART_NOK;
		}
		if(OPERATE_FAIL == (SetUartParam(pUartInfo,pUartParam)))
		{
			return UART_NOK;
		}    
		puiAddrBase[__B_UART_FCR << uiOffBase] = ((UartFifoTab[uiId] << 6) | 0x07);       
		/*  ��ʼ��FIFOΪN���ֽڴ���,WO	���ͺͽ��յ�FIFO��ʹ��      */                                                                        
		puiAddrBase[__B_UART_IER << uiOffBase] = 0x05;                      /*  ʹ�ܽ����ж�,��ʹ�ܷ����ж� */

		pUartInfo->uiUartFlag |= 0x10;                                      /*  4λ��λ��ʾ���Ͷ���ʹ��     */                       
	}

//    OS_EXIT_CRITICAL();
    
    return UART_OK;
}
void Uart0Isr (int vector);
void Uart1Isr (int vector);
void Uart2Isr (int vector);
/*********************************************************************************************************
** Function name:           InitUart
** Descriptions:            ���ڳ�ʼ�����ж�����
** input parameters:        uiId:       ���豸��
**                          pcArg:      �ַ���ָ��
**                          pRsv:       ��������
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
** Example:                 char pUart[]="BaudRate=9600,DataBits=8,StopBits=1,Parity=NONE,RtsControl=NONE"; 
**                          InitUart(0,pUart,0); 
*********************************************************************************************************/
INT32S InitUart (INT32U uiId,  UART_PARAM *pUartParam, void *pRsv)
{ 
    if ((uiId<UART_MAX_NUM) )
	{        
        UartInfoTab[uiId]->puiAddrBase = (INT32U *)UartBaseAddrTab[uiId];   /*  ����ַ                      */
                                                                        
        UartInfoTab[uiId]->uiOffBase = 0;                         /*  ��ַƫ����                  */
        
        UartInfoTab[uiId]->uiUartFlag = 0;                        /*  ��0��־                     */
        
        UartInfoTab[uiId]->uiQueueReviceFifoLen = QueueReviceFifoTab[uiId];    /*  ���FIFO���ճ���            */
                                                                        
        UartInfoTab[uiId]->uiQueueSendFifoLen = QueueSendFifoTab[uiId];      /*  ���FIFO���ͳ���            */
                                                                           
        UartInfoTab[uiId]->pDQReviceBuf = (DataQueue *)UartReviceTab[uiId];         /*  ��¼���ջ���                */
                                                                        
        UartInfoTab[uiId]->pDQSendBuf = (DataQueue *)UartSendTab[uiId];	       /*  ��¼���ͻ���                */
                                                                        
        UartInfoTab[uiId]->uiUartId =  uiId;                      /*  ��¼���Լ���ID��            */
     
        if (UartCfgInit(UartInfoTab[uiId], pUartParam, QueueReviceFifoTab[uiId], QueueSendFifoTab[uiId]) == OPERATE_FAIL)
		{
            return(UART_NOK);
        }
        else 
		{
			rt_sem_init( & (UartInfoTab[uiId]->RcvDataSem),"UART",0,RT_IPC_FLAG_FIFO);

			if (uiId == 0)
			{
				rt_hw_interrupt_install(UART0_INT, Uart0Isr, RT_NULL);	
				rt_hw_interrupt_umask(UART0_INT);
			}
			else if ( uiId == 1)
			{
				rt_hw_interrupt_install(UART1_INT, Uart1Isr, RT_NULL);	
				rt_hw_interrupt_umask(UART1_INT);
			}
			else if ( uiId == 2)
			{
				rt_hw_interrupt_install(UART2_INT, Uart2Isr, RT_NULL);	
				rt_hw_interrupt_umask(UART2_INT);
			} 
            return(UART_OK);
        }                                                                                                                               
    }
    else
	{
        return(UART_NOK);
    } 
}
/*********************************************************************************************************
** Function name:           SetUartMode
** Descriptions:            ���ô��ڵĲ���
** input parameters:        uiId      : ���豸��
**                          uiCmd     :���ò�����:CTMODE--����ģʽ;BAUDRATE--���ڲ�����
**                          pcArg     :�ַ���ָ��
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
** Example1:                char pUartBps[] = "BaudRate=9600";
**                          WdtSetMode( 0, BAUDRATE, pUartBps);  
** Example2:                char pUart[]="DataBits=8 StopBits=1 Parity=NONE RtsControl=NONE";
**                          WdtSetMode( 0, CTMODE, pUart);  
*********************************************************************************************************/
#define BAUDRATE    0   
#define CTMODE      1
INT32S SetUartMode (INT32U uiId, INT32U uiCmd, UART_PARAM *pParam)
{
	if ((uiId<UART_MAX_NUM))
	{
		switch(uiCmd) 
		{
		case BAUDRATE:
			return(SetUartBandRate(UartInfoTab[uiId],pParam->bps)); 
		case CTMODE:
			return(SetUartParam(UartInfoTab[uiId],pParam));					
		default:
			break;	
		}
	}		
	return UART_NOK;     
}
/*********************************************************************************************************
** Function name:			GetUartState
** Descriptions:			�ӵײ㴮�ڼĴ�����ȡ��ǰ���ڵĲ���
** input parameters:		uiId:               ���豸��
**							uiParaData:         �ַ���ָ��
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
INT32S GetUartState (INT32U uiId, UART_PARAM *pParam)
{
    volatile INT32U *puiAddrBase;
	volatile INT32U  uiOffBase;

	INT32U uiBak = 0;

	if (uiId < UART_MAX_NUM && pParam)
	{
		puiAddrBase = UartInfoTab[uiId]->puiAddrBase;
		uiOffBase   = UartInfoTab[uiId]->uiOffBase;

		uiBak = puiAddrBase[__B_UART_LCR << uiOffBase];
		puiAddrBase[__B_UART_LCR << uiOffBase] |= 0x80;                     /*  ������ʷ�Ƶ���ӼĴ���      */

		pParam->bps  = ((Fpclk /(puiAddrBase[__B_UART_DLL << uiOffBase] | (puiAddrBase[__B_UART_DLM << uiOffBase] << 8)) / 16));
		pParam->datab  = (uiBak & 0x03) + 5;
		pParam->stopb  = ((uiBak >> 2) & 0x01) + 1;
		if (( (uiBak >> 3) & 0x01) == 0)
			pParam->parity = 0;
		else
		{
			pParam->parity  = (((uiBak >> 4) & 0x03) + 1);   
		}

		puiAddrBase[__B_UART_LCR << uiOffBase] &= 0x7F;                     /*  ��ֹ���ʷ�Ƶ���ӼĴ���      */
	}
	else
		return UART_NOK;
	return UART_OK;	 					  
}
/*********************************************************************************************************
** Function name:           GetUartFifoStatus
** Descriptions:            ��ȡQueue���е�״̬
** input parameters:        uiId:           ���豸��
**                          uiWhichFifo:    TX_FIFO-���Ͷ���;RX_FIFO-���ն���
** Returned value:          ���Ͷ����пɲ����Ŀռ��С������ն����п������ݸ���
*********************************************************************************************************/
INT32S GetUartFifoStatus (INT32U uiId,INT32U uiWhichFifo)
{
	UART_INFO *pUartInfo  =NULL;

	if (uiId < UART_MAX_NUM)
	{
		pUartInfo = UartInfoTab[uiId];
		if ((uiWhichFifo == TX_FIFO) && ((pUartInfo->uiUartFlag) < 0x80))
		{
			return (pUartInfo->pDQSendBuf->MaxDataNum - pUartInfo->pDQSendBuf->DataCnt);
		}
		if (uiWhichFifo == RX_FIFO)
		{
			return (pUartInfo->pDQReviceBuf->DataCnt);
		}
		return 0;

	//	return _uartQueueStatus(UartInfoTab[uiId], uiWhichFifo);
	}
	else
		return 0;
}

/*********************************************************************************************************
** Function name:           FlushUartFifo
** Descriptions:            ��ս��ջ���Queue����
** input parameters:        uiId:        UART���豸��
**                          uiWhichFifo: TX_FIFO-���Ͷ���;RX_FIFO-���ն���
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
INT32S FlushUartFifo (INT32U uiId, INT32U uiWhichFifo)
{
	if (uiId >UART_MAX_NUM) 
	{
		return UART_NOK;
	}
	else if (uiWhichFifo == RX_FIFO) 
	{
		QueueFlush((void *)UartInfoTab[uiId]->pDQReviceBuf);  /*  ��ս��ն���                */
	}
	else if (uiWhichFifo == TX_FIFO) 
	{	 
		QueueFlush((void *)UartInfoTab[uiId]->pDQSendBuf);/*  ��շ��Ͷ���                */
	}
	else 
	{ 
		return UART_NOK;
	}
	return UART_OK;
}
/*********************************************************************************************************
** Function name:			GetUartCh
** Descriptions:			�޵ȴ�����һ���ֽ�
** input parameters:		pUartInfo      : ָ��uart��Ϣ�ṹ���ָ��
**                          uiRet       : �洢���յ�������
** Returned value:			UART_OK   : �ɹ�
**                          UART_EMPTY: ������
** Created by:				Chenmingji
** Created Date:			2006-09-08
*********************************************************************************************************/
static INT8U GetUartCh ( UART_INFO *pUartInfo, INT8U *uiRet)
{
    OS_CPU_SR  cpu_sr = 0;

    INT32U uiErr;

//    OS_ENTER_CRITICAL();
    
    uiErr = QueueRead(uiRet, pUartInfo->pDQReviceBuf);
    
//    OS_EXIT_CRITICAL();
    return uiErr;
} 
/*********************************************************************************************************
** Function name:           ReadUart
** Descriptions:            �Ӵ����豸��ȡ����
** input parameters:        uiId:        ���豸��
**                          puiBuf:      ���淵�����ݵ��ַ���ָ���ַ
**                          uiNum:       ��ȡ�����ݸ���
**                          pRsv:        ��������
** Output parameters:       puiBuf:      �����������׵�ַ      
** Returned value:          ʵ�ʶ�ȡ�����ݸ���
*********************************************************************************************************/
extern INT32S   ReadUart (INT32U uiId,   INT8U *puiBuf,  INT32U uiNum, void *pRsv)
{
    OS_CPU_SR  cpu_sr = 0;

	INT32U i;
	INT32U uiReviceNum = 0;	
	if (uiId < UART_MAX_NUM) 
	{
//		OS_ENTER_CRITICAL(); 
		
		for (i=0;i<uiNum;i++) 
		{			
			if (QUEUE_OK == ( GetUartCh(UartInfoTab[uiId],puiBuf++))) 
			{
				uiReviceNum ++;
			}
			else
				break;
		}
		
//	    OS_EXIT_CRITICAL();
	} 
	return uiReviceNum;	
}
/*********************************************************************************************************
** Function name:			__uartWrite
** Descriptions:			���Ͷ���ֽ�����
** input parameters:		pUartInfo:      ָ��uart��Ϣ�ṹ���ָ��
**                          puiData:        Ҫ���͵����ݵ��׵�ַ
**                          uiNumByte:      �������ݵĸ���
** Output parameters:       NONE
** Returned value:			�ɹ��������ݵĸ���
*********************************************************************************************************/
static INT16U __uartWrite (UART_INFO *pUartInfo, INT8U *puiData, INT32U uiNumByte)
{
    OS_CPU_SR  cpu_sr = 0;

    volatile INT32U *puiAddrBase = NULL;
	volatile INT32U  uiOffBase;
	
    INT16U uiSendNumbyte;	    
    INT8U uiTemp;
    
    uiSendNumbyte = uiNumByte;
    pUartInfo->uiUartFlag &= (~0x80);                                   /*  ʹ�ö�����Ϊ����            */
    if((pUartInfo->uiUartFlag) < 0x80) 
	{ 	
// 		while (uiSendNumbyte > 0)
// 		{
// 			if (QueueWrite((void *)pUartInfo->pDQSendBuf, *puiData++) == QUEUE_FULL)
// 			{
// 				break;
// 			}
// 			uiSendNumbyte--;
// 		}
		if (QueueWriteEx( pUartInfo->pDQSendBuf,  puiData,uiNumByte,&uiSendNumbyte ) == QUEUE_FULL)
		{//������,û�з��ͳɹ�
			return (uiNumByte - uiSendNumbyte);
		//	break;
		}
	//	uiSendNumbyte--;

		OS_ENTER_CRITICAL(); 

		pUartInfo->uiUartFlag |= 0x10;                                  /*  ʹ�ܷ��Ͷ���                */
		if (pUartInfo->uiUartFlag > 0x0f) 
		{
			puiAddrBase = pUartInfo->puiAddrBase;
			uiOffBase = pUartInfo->uiOffBase;

			if ((puiAddrBase[__B_UART_IER << uiOffBase] & 0x02) == 0)
			{				
				if (QUEUE_OK == QueueRead(&uiTemp, pUartInfo->pDQSendBuf))
				{	
					 /*  �������ж�                  */
					puiAddrBase[__B_UART_IER << uiOffBase] |= 0x02;    
					SetRS485Mode(pUartInfo->uiUartId,RS485_SEND);	
					 
					puiAddrBase[__B_UART_THR << uiOffBase] = uiTemp; 
				}		 	
			}
		}	
		OS_EXIT_CRITICAL();	 
	}	
    return (uiNumByte - uiSendNumbyte);
} 
/*********************************************************************************************************
** Function name:           WriteUart
** Descriptions:            �򴮿��豸д����
** input parameters:        uiId:       ���豸��
**                          puiBuf:     ������ݵ��ַ���ָ���ַ
**                          uiNum:      һ��д������ݸ���
**                          pRsv:       ��������
** Output parameters:       NONE
** Returned value:          ʵ�ʷ��͵����ݸ���
*********************************************************************************************************/
INT32S  WriteUart (INT32U uiId,   INT8U *puiBuf, INT32U uiNum,  void *pRsv)
{
	if (uiId < UART_MAX_NUM)
	{
		return (__uartWrite(UartInfoTab[uiId], puiBuf, uiNum));
	}		
	else
		return 0;
}
/*********************************************************************************************************
** Function name:           DirectWriteUart
** Descriptions:            �򴮿��豸ֱ�ӷ�������
** input parameters:        uiId      : ���豸��
**                          uiData    : ���������                            
** Output parameters:       NONE
** Returned value:          ʵ�ʷ��͵����ݸ���(1��0);
*********************************************************************************************************/
INT32S   DirectWriteUart (INT32U uiId, INT8U uiData)
{
    OS_CPU_SR  cpu_sr = 0;

	volatile INT32U *puiAddrBase;
	volatile INT32U  uiOffBase;
	UART_INFO  *pUartInfo = NULL;

	if (uiId >=UART_MAX_NUM) 
		return 0;

	pUartInfo = UartInfoTab[uiId];

	puiAddrBase = pUartInfo->puiAddrBase;
	uiOffBase   = pUartInfo->uiOffBase;
	
	OS_ENTER_CRITICAL(); 

	puiAddrBase[__B_UART_LCR << uiOffBase] &= (~0x80);                  /* DLAB = 0                     */
	
	puiAddrBase[__B_UART_THR << uiOffBase] = uiData;
	//  �ȴ�������
	//�����232ֻ��Ҫ��鷢��FIFOΪ��
	while ((puiAddrBase[__B_UART_LSR << uiOffBase] & 0x20) == 0);     
	//�����485 ��Ҫ��鷢����Ϊ��
//	while ((puiAddrBase[__B_UART_LSR << uiOffBase] & 0x40) == 0);     

	OS_EXIT_CRITICAL();
	return UART_OK;
}

INT32S  DirectWriteUartApi (INT32U uiId, INT8U *pBuf, INT16U nLen)
{
	INT16U k;
	volatile INT32U *puiAddrBase;
	volatile INT32U  uiOffBase;
	UART_INFO  *pUartInfo = NULL;

	if (uiId >=UART_MAX_NUM) 
		return 0;

	pUartInfo = UartInfoTab[uiId];

	puiAddrBase = pUartInfo->puiAddrBase;
	uiOffBase   = pUartInfo->uiOffBase;
	//��ֹ�����ж�
	puiAddrBase[__B_UART_IER << uiOffBase] = 0;    

	SetRS485Mode(uiId,RS485_SEND);	
	 
	// DLAB = 0                    
	puiAddrBase[__B_UART_LCR << uiOffBase] &= (~0x80);    
	
	for(k=0;k<nLen;k++)
	{
		puiAddrBase[__B_UART_THR << uiOffBase] = pBuf[k];
		// �ȴ����ͱ���THRΪ��
		while ((puiAddrBase[__B_UART_LSR << uiOffBase] & 0x20) == 0);    
	}
	
	while ((puiAddrBase[__B_UART_LSR << uiOffBase] & 0x40) == 0);     
	
	SetRS485Mode(uiId,RS485_RECV);	

	// ����ʹ��
	puiAddrBase[__B_UART_IER << uiOffBase] = 1;    
 	return nLen;
}
/*********************************************************************************************************
** Function name:			__uartIsr
** Descriptions:			UART�жϷ������
** input parameters:		pUartInfo:      ָ��uart��Ϣ�ṹ���ָ��
** Output parameters:       NONE
** Returned value:			��
*********************************************************************************************************/
static void __uartNone (UART_INFO *pUartInfo, volatile INT32U *puiAddrBase, INT32U  uiOffBase)
{
    pUartInfo = pUartInfo;
    puiAddrBase = puiAddrBase;
    uiOffBase = uiOffBase;
}

/*  �����ж�                   */
static void __uartThre (UART_INFO *pUartInfo, volatile INT32U *puiAddrBase, INT32U  uiOffBase)
{
    INT16U uiNum;
    DataQueue *dqSend;
    INT8U *pucOut, *pucEnd;
    
    pUartInfo-> uiUartState = 1;                                        /*  ��״̬                     */

    if (pUartInfo->uiUartFlag < 0x10)
	{
        puiAddrBase[__B_UART_IER << uiOffBase]  &= ~0x02;
        return;
    }
    
    dqSend = pUartInfo->pDQSendBuf;
    uiNum = pUartInfo->uiQueueSendFifoLen;
    
    if ( uiNum > dqSend->DataCnt) 
	{
         uiNum = dqSend->DataCnt;
    }
    
    if (uiNum == 0) 
	{
        puiAddrBase[__B_UART_IER << uiOffBase]  &= ~0x02;
        return;
    }

    dqSend->DataCnt -= uiNum;

    pucOut = dqSend->pOut;
    pucEnd = dqSend->pEnd;
    do 
	{
        puiAddrBase[__B_UART_THR << uiOffBase] = *pucOut++;

        while((puiAddrBase[__B_UART_LSR << uiOffBase]&0x40)==0)
			;        /*  �����Ƿ񷢳�ȥ              */
        if (pucOut >= pucEnd) 
		{
            pucOut = dqSend->Buf;
        }
    } while (--uiNum != 0);
    dqSend->pOut = pucOut;  
	 
	SetRS485Mode( pUartInfo->uiUartId,RS485_RECV );
//	UART3_RxEnable();			// ����ʹ��
}
/*  �����ж�                    */
static void __uartRevice(UART_INFO *pUartInfo, volatile INT32U *puiAddrBase, INT32U  uiOffBase)
{
    INT8U ucData; 
    DataQueue *pdqRevice;
    INT16U uiNum, uiMaxData;
    INT8U *pucIn, *pucEnd;

    pUartInfo-> uiUartState = 0;                                         /*  ��״̬                     */
    
    pdqRevice = pUartInfo->pDQReviceBuf;
    
    pucIn = pdqRevice->pIn;
    pucEnd = pdqRevice->pEnd;
    uiNum = pdqRevice->DataCnt;
    uiMaxData = pdqRevice->MaxDataNum;
    do
    {
        ucData = puiAddrBase[__B_UART_RBR << uiOffBase];
        if (uiNum < uiMaxData) 
		{
            *pucIn++ = ucData;
            if (pucIn >= pucEnd) 
			{
                pucIn = pdqRevice->Buf;
            }
            uiNum++;
        }
    } while ((puiAddrBase[__B_UART_LSR << uiOffBase] & 0x00000001) != 0);

    pdqRevice->pIn = pucIn;
    pdqRevice->DataCnt = uiNum; 
}

/* ������״̬                  */
static void __uartLine(UART_INFO *pUartInfo, volatile INT32U *puiAddrBase, INT32U  uiOffBase)
{
    INT8U uiState; 

    uiState = puiAddrBase[__B_UART_LSR << uiOffBase];
}

static void  (* const arrpfnUartTiom[16])(UART_INFO *pUartInfo,  volatile INT32U *puiAddrBase, 
                                         INT32U  uiOffBase) =
      {__uartNone,   __uartNone, __uartThre, __uartNone,  
       __uartRevice, __uartNone, __uartLine, __uartNone,
       __uartNone,   __uartNone, __uartNone, __uartNone,
       __uartRevice, __uartNone, __uartNone, __uartNone};
 
/*********************************************************************************************************
** Function name:           UartISR
** Descriptions:            UART�жϷ������
** input parameters:        uiId      : ���豸��
** Output parameters:       NONE
** Returned value:          ��
*********************************************************************************************************/
static __inline void UartISR (INT32U uiId)
{
	volatile INT32U *puiAddrBase;
	volatile INT32U  uiOffBase;

	INT8U uiState;
	UART_INFO *pUartInfo = NULL;

	if (uiId < UART_MAX_NUM) 
	{
		pUartInfo = UartInfoTab[uiId];
		puiAddrBase = pUartInfo->puiAddrBase;
		uiOffBase   = pUartInfo->uiOffBase;

		uiState = puiAddrBase[__B_UART_IIR << uiOffBase] & 0x0f;
		arrpfnUartTiom[uiState](pUartInfo, puiAddrBase, uiOffBase);   
    }
}

static __inline void Uart0Isr (int vector)
{
	UartISR(UART0);                                                     /*  UART�жϹ�����           */                                                               

	if (UartInfoTab[UART0]->uiUartState == 0)
	{   /*  ���ڽ���״̬               */
		rt_sem_release( & (UartInfoTab[UART0]->RcvDataSem) );
	}                                                              

	VICVectAddr = 0x00;                                                 /*  �жϴ������               */
} 
static __inline void Uart1Isr (int vector)
{
	UartISR(UART1); 

	if (UartInfoTab[UART1]->uiUartState == 0)
	{ /*  ���ڽ���״̬                */
		rt_sem_release( & (UartInfoTab[UART1]->RcvDataSem) );
 	}    

	VICVectAddr = 0x00;                                                 /*  �жϴ������                */
}
static __inline void Uart2Isr (int vector)
{
	UartISR(UART2); 

	if (UartInfoTab[UART2]->uiUartState == 0)
	{                   /*  ���ڽ���״̬                */
		rt_sem_release( & (UartInfoTab[UART2]->RcvDataSem) );
	}
	VICVectAddr = 0x00;                                                 /*  �жϴ������                */
}
 
INT8U UartRecvDataPend(INT32U nUartId,INT32U nTick)
{
	if (  rt_sem_take(& (UartInfoTab[UART1]->RcvDataSem),nTick ) == RT_EOK )
	{
		return TRUE;
	}
	return FALSE;
}


/*********************************************************************************************************
   END FILE
*********************************************************************************************************/


