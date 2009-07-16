#define IN_TARGET
#include "includes.h"
#include "hd_init.h"
#include "vicControl.h"
#include "TimerMgr.h"
#include "ClockMgr.h"


void FIQ_Exception(void)
{
    while(1);                   // change it to your code  ��һ���滻Ϊ�Լ��Ĵ���
}
 

void IRQCTimer0(void)
//void __irq  IRQCTimer0(void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	OS_ENTER_CRITICAL();
	T0IR = 0x01;
	VICVectAddr = 0;
	OS_EXIT_CRITICAL();

	OSTimeTick();
// 	TimerMgrInIsr(10);
	ClockMgrSignal(10);
}
		 

void BSP_init(void)
{
	extern void IRQASMTimer0(void);
//	extern void IRQASMTimer3(void);
	VICIntEnClr 	= 0xFFFFFFFFL;

    T0IR = 0xff;
    T0TCR = 0x03;
    T0TC = 0;
    T0MCR = 0x03;
    T0MR0 = (Fpclk / OS_TICKS_PER_SEC);
    T0TCR = 0x01;
	vicIrqFuncSet(4,0,(INT32U)IRQASMTimer0);
 //	vicIrqFuncSet(4,1,(INT32U)IRQCTimer0);
 
	PCONP |= 3<<22;//ʹ�ܶ�ʱ��2��3
	PCONP |= 1<<25;//ʹ��Uart3
	PCONP |= 1<<30;//ʹ��Ethnet

	return;
#if 0
// 	VICIntEnClr	= (1 << 4);
// 	VICVectAddr4 	= (INT32U)IRQASMTimer0;
// 	VICVectPri4 	= (0x20 | 0x04);
// 	VICIntEnable 	= (1 << 4);


	PCONP |= 3<<22;//ʹ�ܶ�ʱ��2��3
	PCONP |= 1<<25;//ʹ��Uart3
	PCONP |= 1<<30;//ʹ��Ethnet

  	 
   
//	Timer3_Init();//�����ж�
  	T3IR  = 0xFF;	  //���ȫ���жϱ�־
	T3TC  = 0x00;	  //��ʱ��������
	T3TCR = 0x01;     //������ʱ��
	T3MCR = 0x03;     //ƥ��Ĵ���,����ʱ����TCֵ��MR0ƥ��ʱ,��ʱ����λ,�������ж�
	T3MR0 = MS_TIMER;

//  VICIntEnClr	= (1 << 0X1B);	 //�ж�ʹ������ �Ĵ���
// 	VICVectAddr27 	= (INT32U)IRQASMTimer3;
// 	VICVectPri27 	= (0x20 | 0x05);
// 	VICIntEnable 	= (1 <<  0X1B);		 //�ж�ʹ�� �Ĵ���


    vicIrqFuncSet(VIC_TIMER3,2,(INT32U)IRQASMTimer3);
    return;


	T0IR  = 0xFF;
	T0TC  = 0x00;
	T0TCR = 0x01;
	T0MCR = 0x03;
	T0MR0 = (Fosc / OS_TICKS_PER_SEC );
	VICIntEnClr	= (1 << 4);
	VICVectAddr4 	= (INT32U)IRQASMTimer0;
	VICVectPri14 	= (0x20 | 0x04);
	VICIntEnable 	= (1 << 4);
#endif
}
