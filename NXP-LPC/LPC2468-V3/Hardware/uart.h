/***********************************************Copyright (c)*********************************************
**                                Guangzou ZLG-MCU Development Co.,LTD.
**                                     
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    uart.h
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    uartͷ�ļ�
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    wengshujie
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:		    ��ͷ�ļ���CONFIG.h�а���
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    
** Modified Date:		    
** Version:				    
** Descriptions:		    
**
*********************************************************************************************************/
#ifndef __UART_H
#define __UART_H
#include "Queue.h"



/*********************************************************************************************************
   UART�������,�û������޸�
*********************************************************************************************************/
#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3

/*********************************************************************************************************
  ����ʹ�õ���UART�Ĵ���ƫ�Ƶ�ַ,�û������޸�
*********************************************************************************************************/
#define __B_UART_RBR    0  //����������Ĵ��� ֻ��
#define __B_UART_THR    0  //���ͱ��ּĴ��� ֻд
#define __B_UART_DLL    0
#define __B_UART_DLM    1
#define __B_UART_IER    1
#define __B_UART_IIR    2
#define __B_UART_FCR    2
#define __B_UART_LCR    3
#define __B_UART_LSR    5  //��״̬�Ĵ�����ֻ��
#define __B_UART_SCR    7

/*********************************************************************************************************
   ��ʶ�ǽ��ն��л��Ƿ��Ͷ���,�û������޸�
*********************************************************************************************************/
#define RX_FIFO     0
#define TX_FIFO     1

/*********************************************************************************************************
   ������������,�û������޸�
*********************************************************************************************************/
#define UART_OK             1                                           /*  ���ڲ����ɹ�                */                
#define UART_NOK            0                                           /*  ���ڲ���ʧ��                */

/*********************************************************************************************************
   ����Uart������Ŀ
*********************************************************************************************************/
#define UART_MAX_NUM    4                                             /*  LPC23xx��4��UART            */

/*********************************************************************************************************
   UART������Ϣ�ṹ�ṹ��,�û������޸�
*********************************************************************************************************/
typedef struct UART_INFO 
{
                INT32U      uiOffBase;                                  /*  uart�Ĵ������= 1 << OffBase*/                         
    volatile    INT32U     *puiAddrBase;                                /*  uart�Ĵ�������ַ            */  
                 
                INT32U      uiQueueReviceFifoLen;                       /*  �������FIFO����            */
                INT32U      uiQueueSendFifoLen;                         /*  �������FIFO����            */
                
                DataQueue  *pDQSendBuf;                                 /*  ���Ͷ���                    */
                DataQueue  *pDQReviceBuf;                               /*  ���ն���                    */
                
                INT32U      uiUartFlag;                                 /*  7λ��λ��ʾ���ö��л���
                                                                            
                                                                            4λ��λ���ڶ���ʹ��         */                                                                                                        
                
                INT32U      uiUartId;                                   /*  ���ڼ�¼�Լ���UARTͨ����    */
                INT32U      uiUartState;                                /*  ��¼�շ�״̬1��ʾ��,0��ʾ�� */
}UART_INFO; 
                            /*  ��������                    */
typedef UART_INFO   *__PUART_INFO;                              /*  ����ָ��                    */

typedef  struct  UART_PARAM
{  
	INT32U bps;           //������
	INT16U datab;         // �ֳ��ȣ�5/6/7/8
	INT16U stopb;         // ֹͣλ��1/2
	INT16U parity;    	  // ��żУ��λ��0Ϊ��У�飬1����У�飬2Ϊż��У��
	INT16U rtsctl;        
}UART_PARAM;

/*********************************************************************************************************
   ����UARTӲ��FIFO����,�û����޸�,��û��Ҫʱ��Ҫ�޸�,�޸�ǰ���˽�Ӳ��FIFO
*********************************************************************************************************/ 
#define UARTFIFOLEN1     0     
#define UARTFIFOLEN4     1
#define UARTFIFOLEN8     2
#define UARTFIFOLEN14    3

#define UART0FIFOLENFUN  UARTFIFOLEN8                                /*  ����UART0�Ľ���FIFO�������   */

#define UART1FIFOLENFUN  UARTFIFOLEN8                                /*  ����UART1�Ľ���FIFO�������   */

#define UART2FIFOLENFUN  UARTFIFOLEN8                                /*  ����UART2�Ľ���FIFO�������   */

#define UART3FIFOLENFUN  UARTFIFOLEN8                                /*  ����UART3�Ľ���FIFO�������   */

/*********************************************************************************************************
   ����UART���FIFO����,�û����޸�
*********************************************************************************************************/  
#define QUEUE0REVICEFIFOLEN      256                                    /*  �û����ڴ��޸Ľ�����FIFO��С*/ 
#define QUEUE0SENDFIFOLEN        256                                    /*  �û����ڴ��޸ķ�����FIFO��С*/ 
#define QUEUE0REVICEFIFOLENFUN   QUEUE0REVICEFIFOLEN+28                 /*  �û���Ҫ�޸�                */
#define QUEUE0SENDFIFOLENFUN     QUEUE0SENDFIFOLEN+28                   /*  �û���Ҫ�޸�                */
                                                
#define QUEUE1REVICEFIFOLEN      128                                    /*  �û����ڴ��޸Ľ�����FIFO��С*/ 
#define QUEUE1SENDFIFOLEN        128                                    /*  �û����ڴ��޸ķ�����FIFO��С*/ 
#define QUEUE1REVICEFIFOLENFUN   QUEUE1REVICEFIFOLEN+28                 /*  �û���Ҫ�޸�                */
#define QUEUE1SENDFIFOLENFUN     QUEUE1SENDFIFOLEN+28                   /*  �û���Ҫ�޸�                */

#define QUEUE2REVICEFIFOLEN      128                                    /*  �û����ڴ��޸Ľ�����FIFO��С*/ 
#define QUEUE2SENDFIFOLEN        128                                    /*  �û����ڴ��޸ķ�����FIFO��С*/ 
#define QUEUE2REVICEFIFOLENFUN   QUEUE2REVICEFIFOLEN+28                 /*  �û���Ҫ�޸�                */
#define QUEUE2SENDFIFOLENFUN     QUEUE2SENDFIFOLEN+28                   /*  �û���Ҫ�޸�                */

#define QUEUE3REVICEFIFOLEN      256                                    /*  �û����ڴ��޸Ľ�����FIFO��С*/ 
#define QUEUE3SENDFIFOLEN        256                                    /*  �û����ڴ��޸ķ�����FIFO��С*/ 
#define QUEUE3REVICEFIFOLENFUN   QUEUE3REVICEFIFOLEN+28                 /*  �û���Ҫ�޸�                */
#define QUEUE3SENDFIFOLENFUN     QUEUE3SENDFIFOLEN+28                   /*  �û���Ҫ�޸�                */

/*********************************************************************************************************
** Function name:           InitUart
** Descriptions:            ���ڳ�ʼ��
** input parameters:        uiId:       ���豸��
**                          pcArg:      �ַ���ָ��
**                          pRsv:       ��������
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
** Example:                 char pUart[]="BaudRate=9600,DataBits=8,StopBits=1,Parity=NONE,RtsControl=NONE"; 
**                          InitUart(0,pUart,0); 
*********************************************************************************************************/
extern INT32S InitUart (INT32U uiId, UART_PARAM *pUartParam, void *pRsv);


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
**                          SetUartMode( 0, BAUDRATE, pUartBps);  
** Example2:                char pUart[]="DataBits=8,StopBits=1,Parity=NONE,RtsControl=NONE";
**                          SetUartMode( 0, CTMODE, pUart);  
*********************************************************************************************************/
extern INT32S SetUartMode (INT32U uiId,  INT32U uiCmd,   UART_PARAM *pParam);

/*********************************************************************************************************
** Function name:           uartGetState
** Descriptions:            ��ȡ��ǰ���ڵĲ���
** input parameters:        uiId:               ���豸��
**                          pcArg:              �ַ���ָ��
** Output parameters:       pcArg:              ����ַ�������
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
extern INT32S GetUartState (INT32U uiId, UART_PARAM *pParam);

/*********************************************************************************************************
** Function name:           GetUartFifoStatus
** Descriptions:            ��ȡQueue���е�״̬
** input parameters:        uiId:           ���豸��
**                          uiWhichFifo:    TX_FIFO-���Ͷ���;RX_FIFO-���ն���
** Returned value:          ���Ͷ����пɲ����Ŀռ��С������ն����п������ݸ���
*********************************************************************************************************/
extern INT32S GetUartFifoStatus (INT32U uiId, INT32U uiWhichFifo);

/*********************************************************************************************************
** Function name:           FlushUartFifo
** Descriptions:            ��ս��ջ���Queue����
** input parameters:        uiId:        UART���豸��
**                          uiWhichFifo: TX_FIFO-���Ͷ���;RX_FIFO-���ն���
** Output parameters:       NONE
** Returned value:			OPERATE_SUCCESS:    �����ɹ�
**                          OPERATE_FAIL:       ����ʧ��
*********************************************************************************************************/
extern INT32S FlushUartFifo (INT32U uiId, INT32U uiWhichFifo);

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
extern INT32S   ReadUart (INT32U uiId, INT8U *puiBuf, INT32U uiNum, void *pRsv);

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
extern INT32S    WriteUart (INT32U uiId, INT8U *puiBuf, INT32U uiNum,  void *pRsv);

/*********************************************************************************************************
** Function name:           DirectWriteUart
** Descriptions:            �򴮿��豸ֱ�ӷ�������
** input parameters:        uiId      : ���豸��
**                          uiData    : ���������                            
**                          Rsv     : ��������(NULL)
** Output parameters:       NONE
** Returned value:          ʵ�ʷ��͵����ݸ���(1��0);
*********************************************************************************************************/
extern INT32S  DirectWriteUart (INT32U uiId, INT8U uiData);
extern INT32S  DirectWriteUartApi (INT32U uiId, INT8U *pBuf, INT16U nLen);
/*********************************************************************************************************
** Function name:           UartISR
** Descriptions:            UART�жϷ������
** input parameters:        uiId      : ���豸��
** Output parameters:       NONE
** Returned value:          ��
*********************************************************************************************************/
extern void UartISR (INT32U uiId);

/*********************************************************************************************************
** Function name:           uart0Isr
** Descriptions:            UART0�ж���ں���
** input parameters:        NONE
** Output parameters:       NONE
** Returned value:          ��
********************************************************************************************************/
extern __PUART_INFO UartInfoTab[4];
 
extern OS_EVENT *poeUart0ReviceSem;                                    /*  ����UART0���ݱ�־          */  
extern void uart0Isr (void);

/*********************************************************************************************************
** Function name:           uart1Isr
** Descriptions:            UART1�ж���ں���
** input parameters:        NONE
** Output parameters:       NONE
** Returned value:          ��
*********************************************************************************************************/
extern OS_EVENT *poeUart1ReviceSem;                                    /*  ����UART1���ݱ�־           */
extern  void uart1Isr (void);

/*********************************************************************************************************
** Function name:           uart2Isr
** Descriptions:            UART2�ж���ں���
** input parameters:        NONE
** Output parameters:       NONE
** Returned value:          ��
*********************************************************************************************************/
extern OS_EVENT *poeUart2ReviceSem;                                    /*  ����UART2���ݱ�־           */
extern  void uart2Isr (void);
/*********************************************************************************************************
** Function name:           uart3Isr
** Descriptions:            UART3�ж���ں���
** input parameters:        NONE
** Output parameters:       NONE
** Returned value:          ��
*********************************************************************************************************/
extern OS_EVENT *poeUart3ReviceSem;                                    /*  ����UART3���ݱ�־           */
extern void uart3Isr (void);


#endif                                                                  /*  __UART_H                    */
/*********************************************************************************************************
   END FILE
*********************************************************************************************************/
