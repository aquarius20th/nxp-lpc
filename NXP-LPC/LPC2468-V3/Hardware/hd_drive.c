///////////////////////////////////////////////////////////////
//	�� �� �� : hd_drive.c
//	�ļ����� : Ӳ������
//	��    �� :  
//	����ʱ�� : 
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#include "includes.h"
#include "hd_drive.h" 
#include "hd_Init.h"
#include "hd_Const.h"
//#include "VIC_Control.h" 

/* �������ں�I2C2�жϴ�����Ϣ��ȫ�ֱ��� */
volatile INT8U 	I2C_sla;			/* I2C�����ӵ�ַ 					*/
volatile INT32U	I2C_suba;			/* I2C�����ڲ��ӵ�ַ 				*/
volatile INT8U 	I2C_suba_num;		/* I2C�ӵ�ַ�ֽ���					*/
volatile INT8U 	*I2C_buf;        	/* ���ݻ�����ָ��  					*/
volatile INT32U I2C_num;			/* Ҫ��ȡ/д������ݸ��� 			*/
volatile INT8U 	I2C_end;			/* I2C���߽�����־��������������1 	*/
volatile INT8U 	I2C_suba_en;		/* 	�ӵ�ַ���ơ�
									0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
									1--��ȡ����
									2--д����
									*/

/* �������ں�I2C1�жϴ�����Ϣ��ȫ�ֱ��� */
volatile INT8U 	I2C1_sla;			/* I2C�����ӵ�ַ 					*/
volatile INT32U	I2C1_suba;			/* I2C�����ڲ��ӵ�ַ 				*/
volatile INT8U 	I2C1_suba_num;		/* I2C�ӵ�ַ�ֽ���					*/
volatile INT8U 	*I2C1_buf;        	/* ���ݻ�����ָ��  					*/
volatile INT32U I2C1_num;			/* Ҫ��ȡ/д������ݸ��� 			*/
volatile INT8U 	I2C1_end;			/* I2C���߽�����־��������������1 	*/
volatile INT8U 	I2C1_suba_en;		/* 	�ӵ�ַ���ơ�
									0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
									1--��ȡ����
									2--д����
									*/
extern OS_EVENT *g_pEvtI2C1Sem;


extern OS_EVENT *g_pEvtI2C1Mbox;



extern OS_EVENT *g_pEvtI2C1Sem;
extern OS_EVENT *g_pEvtI2C1Mbox;

/*******************************************************************************************
** �������� �� DelayNS
*******************************************************************************************/
void DelayNS (INT32U dly)
{
	INT32U i;
	for ( ; dly>0; dly--)
		for (i=0; i<5000; i++);
}

void hd_SetOneLED(INT8U led_num)
{	
	switch(led_num)
	{
		case 0:
		FIO2CLR =LED1;	break;
		case 1:
		FIO0CLR =LED2;	break;			
		case 2:
		FIO2CLR =LED3;	break;	
		case 3:
		FIO3CLR =LED4;	break;
		case 4:
		FIO3CLR =LED5;	break;
		case 5:
		FIO0CLR =LED6;	break;			
		case 6:
		FIO3CLR =LED7;	break;	
		case 7:
		FIO2CLR =LED8;	break;
		case 8:
		FIO2CLR =LED9;	break;
		case 9:
		FIO0CLR =LED10;	break;			
		case 10:
		FIO0CLR =LED11;	break;	
		case 11:
		FIO2CLR =LED12;	break;
	}
}

void hd_ClearOneLED(INT8U led_num)
{	
	switch(led_num)
	{
		case 0:
		FIO2SET =LED1;	break;
		case 1:
		FIO0SET =LED2;	break;			
		case 2:
		FIO2SET =LED3;	break;	
		case 3:
		FIO3SET =LED4;	break;
		case 4:
		FIO3SET =LED5;	break;
		case 5:
		FIO0SET =LED6;	break;			
		case 6:
		FIO3SET =LED7;	break;	
		case 7:
		FIO2SET =LED8;	break;
		case 8:
		FIO2SET =LED9;	break;
		case 9:
		FIO0SET =LED10;	break;			
		case 10:
		FIO0SET =LED11;	break;	
		case 11:
		FIO2SET =LED12;	break;
	}	
}

/****************************************************************************
* ���ƣ�GeAnalogIn()
* ���ܣ�AD�ɼ�
* ��ڲ�������
** ���ڲ����AADת��ֵ
****************************************************************************/
void hd_GetAnalogIn(INT8U chNo)
{
	if(chNo == 1)
	{
		OPCODE_AD(0x38);
		OPCODE_AD(0x40);
	}
	else if(chNo == 2)
	{
		OPCODE_AD(0x3a);
		OPCODE_AD(0x40);
	}
	DelayNS(10);

	//	while(FIO2PIN&1<<13)
	//	EINT3_Exception();	
}

/****************************************************************************
* ���ƣ�hd_ADSoftReset()
* ���ܣ�AD��λ
* ��ڲ�������
** ���ڲ����A
****************************************************************************/
void hd_ADSoftReset(void)
{
	OPCODE_AD(0x00);
	OPCODE_AD(0xFF);
	OPCODE_AD(0xFF);
	OPCODE_AD(0xFF);
	OPCODE_AD(0xFF);
	DelayNS(10);
}