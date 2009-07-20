///////////////////////////////////////////////////////////////
//	�� �� �� : hd_Init.c
//	�ļ����� : Ӳ����ʼ��
//	��    �� : 
//	����ʱ�� : 2007��8����
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע : 
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#include <stdlib.h>
#include "includes.h"
#include "hd_Init.h"
#include "hd_const.h"
#include "lpc2400.h" 
 
#include "VICControl.h" 

 
/****************************************************************************
* ��	�ƣ�CPU_PIN_Init()
* ��	�ܣ�I/Oģʽ��ʼ��
* ��ڲ�������
* ���ڲ�������
****************************************************************************/


void CPU_PIN_Init(void)
{	
	SCS |= 0x01;				
    PINSEL0 = 0x000aa05f;		//PIN����
    PINSEL1 = 0x01400000;
    PINSEL2 = 0x50150105;
    PINSEL3 = 0x00000005;
    PINSEL4 = 0x05500000;
    PINSEL5 = 0x00c0f000;
    PINSEL9 = 0x0f000a00;
    PINSEL10 = 0x00000000;	    //Ҫ����
   
    PINMODE0=0x00000000;
    PINMODE1=0x00000000;
    PINMODE2=0x00000000;
    PINMODE3=0x00000000;
    PINMODE4=0x00000000;
    PINMODE5=0x00000000;
    PINMODE6=0x00000000;
    PINMODE7=0x00000000;
    PINMODE8=0x00000000;
    PINMODE9=0x00000000;
     
    FIO0DIR = 0xe0019c00;
    FIO1DIR = 0x1c000000;
    FIO2DIR = 0x130c8380;    					 
    FIO3DIR = 0x07270080;
    FIO4DIR = 0x08857000;
} 
  

/*-----------------------------------------------------------------------
* ��	�ƣ�Timer3_Init()
* ��	�ܣ�Timer3��ʼ��,
* ��ڲ�����
* ���ڲ�������
-----------------------------------------------------------------------*/
void  Timer3_Init(void)
{   
	//OS_ENTER_CRITICAL();
	T3IR = 0xff;
	T3TCR = 0x01;
	T3TC = 0;
	T3MCR = 0x03;
	T3MR0 = MS_TIMER;
	//OS_EXIT_CRITICAL();
}
/****************************************************************************
* ��	�ƣ�
* ��	�ܣ�Ӳ����ʼ�������Ӳ����û�иı䣬����Ԫ�ĳ�ʼ����������ı�
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void SetupHardware(void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif 
	OS_ENTER_CRITICAL();

 
//    SetVICIRQ(VIC_TIMER3, 5, (INT32U)Timer3_Exception);
//   DisableVICIRQ(VIC_TIMER3);
	

	//������ж����ȼ��������������жϹ���ӿں���
	//VICInit();
	//��IRQ�ж�
	//IRQEnable();

	OS_EXIT_CRITICAL();

// 	VICIntSelect = 0;
// 	VICIntEnClr = 0xffffffff;
// 
//  	Timer3_Init();//�����ж�
//   	vicIrqFuncSet(VIC_TIMER3,5,(INT32U)Timer3_Exception);
//  	vicIrqDisable(VIC_TIMER3);

// 	T3IR  = 0xFF;
// 	T3TC  = 0x00;
// 	T3TCR = 0x01;
// 	T3MCR = 0x03;
// 	T3MR0 = MS_TIMER;
// 	VICIntEnClr	= (1 << 0X1B);
// 	VICVectAddr5 	= (INT32U)Timer3_Exception;
// 	VICVectPri27 	= (0x20 | 0x05);
// 	VICIntEnable 	= (1 << 4);

}
 
