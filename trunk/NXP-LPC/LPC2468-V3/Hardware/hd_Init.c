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
#include "filedata.h"
#include "hd_isr.h"
#include "VICControl.h"

static INT8U s_nEncoderType = INTERFACE_NONE;


OS_EVENT *g_pEvtI2C1Sem;
OS_EVENT *g_pEvtI2C1Mbox;
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
* ��	�ƣ�EINT12_Init()
* ��	�ܣ�EINT1��2��ʼ��,���岶�������
* ��ڲ�����
* ���ڲ�������
-----------------------------------------------------------------------*/
void  EINT12_Init(void)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif 
	OS_ENTER_CRITICAL();
	EXTMODE = 0x07;
	EXTPOLAR = 0x06;					//�½��ش���
	EXTINT = 1<<2 | 1<<3 | 1<<4;		// ���ⲿ�ж��жϱ�־
	OS_EXIT_CRITICAL();
}

/*-----------------------------------------------------------------------
* ��	�ƣ�I2C1_Init()
* ��	�ܣ���ģʽI2C��ʼ����������ʼ�����ж�Ϊ����IRQ�жϡ�
* ��ڲ�����fi2c		��ʼ��I2C�������ʣ����ֵΪ400K
* ���ڲ�������
-----------------------------------------------------------------------*/
void  I2C1_Init(INT32U fi2c)
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif 
	OS_ENTER_CRITICAL();

	if(fi2c>400000) 
		fi2c = 400000;

	I21SCLH = (Fpclk/fi2c + 1) / 2;	// ����I2Cʱ��Ϊfi2c
	I21SCLL = (Fpclk/fi2c) / 2;
	I21CONCLR = 0x2C;
	I21CONSET = 0x40;				// ʹ����I2C
	//������ʼ��
	g_pEvtI2C1Sem = OSSemCreate(1);
	g_pEvtI2C1Mbox = OSMboxCreate(NULL);
	if (g_pEvtI2C1Mbox == NULL)
	{
		return ;
	}
	if (g_pEvtI2C1Sem == NULL)
	{
		return ;
	}
	OS_EXIT_CRITICAL();
}

/*********************************************************************************************************
** ��������: Encoder_Init
** ��������: ��ģ���ڲ�ʹ�ã������⿪��
**
** ���������� ��ʼ������������IO�жϳ�����������
**
** �䡡��:  void
**          
** �䡡��:  INT16U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��5��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U  Encoder_Init( )
{	
	INT8U nType = INTERFACE_NONE;
	switch(FIO2PIN&0x9<<14)	//������ʶ�𣬹̶���Ӳ�����ţ����ܸı�
	{
	case 0:			//�����ͱ�����
		nType = INTERFACE_INCREMENTAL;
		EINT12_Init(); 
		break;
	case 0x1<<17:	//������SSI������
		nType = INTERFACE_SSI;
		break;			
	case 0x1<<14:	//�����Ͳ��ڱ�����
		nType = INTERFACE_PARALLEL;
		I2C1_Init(100000);//��ʼ������
	//	SetVICIRQ(VIC_I2C1, 10, (INT32U)I2C1_Exception);//�����ж����ȼ������ж�
		break;
	default:
		nType = INTERFACE_NONE;
		break;
	}	
	return nType;
}
/****************************************************************************
* ��	�ƣ�SPI_Init()
* ��	�ܣ���ʼ��SPI�ӿڣ�SPI0:DA�����SPI1:AD���� 
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
/****************************************************************************
** ���ܣ�
**************************************************************************/
void  SPI0_Init( void )				//DA
{	
	//OS_ENTER_CRITICAL();
	SSP0CR0=0x0000000F;
	SSP0CR1=0x02;
	SSP0CPSR=0x32;
	//OS_EXIT_CRITICAL();	
}

void  SPI1_Init( void )				//AD
{	
	//OS_ENTER_CRITICAL();
	SSP1CR0=0x0087;
	SSP1CR1=0x02;
	SSP1CPSR=0x32;

	SetVICIRQ(VIC_EINT3, 11, (INT32U)EINT3_Exception);
	DisableVICIRQ(VIC_EINT3);
	EXTINT = 0x08;					// ���ⲿ�ж�3�жϱ�־		

	hd_ADSoftReset();//��λAD
	hd_ADSoftReset();

	OPCODE_AD(0x28);
	OPCODE_AD(0x03);
	DelayNS(1);
	OPCODE_AD(0x2a);
	OPCODE_AD(0x03);
	//OS_EXIT_CRITICAL();
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

#if 0
	//�жϱ�����ģ�����ͣ������Ƿ��ʼ���ⲿ�ж�
	s_nEncoderType = Encoder_Init();
	//��ʱ����ʼ��
	Timer3_Init();//�����ж�
	//SPI��ʼ����for AD DA 
	EINT12_Init();
	SPI0_Init();
	SPI1_Init();
#endif
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

/****************************************************************************
* ��	�ƣ�
* ��	�ܣ�Ӳ�����ʼ����֮�󣬴򿪱��رյ��ж�
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void Enable_Interupt(void)
{
	EXTINT = 1<<2 | 1<<3;
	ReEnableVICIRQ(VIC_EINT1);
	ReEnableVICIRQ(VIC_EINT2);
	ReEnableVICIRQ(VIC_TIMER3);
	ReEnableVICIRQ(VIC_UART0);
	ReEnableVICIRQ(VIC_UART3);

	ReEnableVICIRQ(VIC_EINT3);
}
