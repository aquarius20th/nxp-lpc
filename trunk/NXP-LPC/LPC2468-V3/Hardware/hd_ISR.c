///////////////////////////////////////////////////////////////
//	�� �� �� : hd_ISR.c
//	�ļ����� : Ӳ���жϷ������
//	��    �� : 
//	����ʱ�� : 2007������
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע : 
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#include "includes.h" 
#include "hd_ISR.h"
#include "hd_Init.h"
#include "hd_drive.h"
#include "IoAdapter.h"
 

extern OS_EVENT *g_pEvtI2C1Mbox;
extern OS_EVENT *g_pEvtI2C2Mbox;
 

/*********************************************************************************************************
** �������� ��IRQ_EINT1/2
** �������� ���жϷ�����򣬼�����������
*********************************************************************************************************/
void EINT1_Exception (void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	OS_ENTER_CRITICAL();	
//	Ram.Abz_Pulse++;
	EXTINT = 2;						// ���ⲿ�ж�1�жϱ�־		
	VICVectAddr = 0x00;				// ֪ͨVIC�жϴ������
	OS_EXIT_CRITICAL();
}

void EINT2_Exception (void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	OS_ENTER_CRITICAL();
//	Ram.Abz_Pulse--;
	EXTINT = 4;						// ���ⲿ�ж�2�жϱ�־		
	VICVectAddr = 0x00;				// ֪ͨVIC�жϴ������
	OS_EXIT_CRITICAL();
} 
INT16U  OPCODE_AD(INT16U ssp1)
{
	INT16U	cnt = 0;
	INT16U	ADcode = 0;
   SSP1DR = ssp1;
//   while((SSP1SR&0x01)==0);		// �ȴ�SPIF��λ�����ȴ����ݷ������
   while((SSP1SR&0x01)==0)
   {	
   		cnt++;
   		if((SSP1SR&0x01) || cnt > 1000)
   			break;
   }
   ADcode = SSP1DR; 
   return ADcode;
}


//void __irq EINT3_Exception (void)
void EINT3_Exception (void)
{
	CpuGetAinVal(   );
	 
	EXTINT = 0x08;						// ���ⲿ�ж�2�жϱ�־		
	VICVectAddr = 0x00;					// ֪ͨVIC�жϴ������
 
} 
/****************************************************************************
* ��	�ƣ�Timer3_Exception()
* ��	�ܣ���ʱ��3�жϷ���
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
#if   0
void Timer3_Exception(void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
	OS_ENTER_CRITICAL();

	T3IR = 0x01;
    VICVectAddr = 0;

 
	OS_EXIT_CRITICAL();//Ϊ���������ͺ������ж���Ӧʱ�䣬ֻ���Ƚ���Ҫ�Ĵ���������

	CommTimerHandle();

	//��ʾ���ְ��������ڶ�ʱ��
//	DispProc_InMsInt();
	//ϵͳʱ��
	ClockMgrSignal(); 
}
#endif // 0
 
