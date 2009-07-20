///////////////////////////////////////////////////////////////
//	�� �� �� : hd_Init.h
//	�ļ����� : Ӳ����ʼ��
//	��    �� : 
//	����ʱ�� : 2007������
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע : 
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////

#ifndef HD_INIT_H
#define HD_INIT_H


/* ���崮��ģʽ�������ݽṹ */
typedef  struct  UART_MODE
{  
	INT16U datab;         // �ֳ��ȣ�5/6/7/8
	INT16U stopb;         // ֹͣλ��1/2
	INT16U parity;    	  // ��żУ��λ��0Ϊ��У�飬1����У�飬2Ϊż��У��
}UART_MODE;

typedef struct tagTI2C
{
	INT8U 	I2C_sla;			//I2C�����ӵ�ַ
	INT8U 	I2C_suba_num;		//I2C�ӵ�ַ�ֽ���
	INT8U 	*I2C_buf;			//��д���ݻ�����ָ��
	INT8U 	I2C_end;			//I2C���߽�����־��������������1
	INT8U 	I2C_suba_en;		/* 	�ӵ�ַ���ơ�
								0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
								1--��ȡ����
								2--д����
								*/
	INT16U	I2C_num;			//Ҫ��ȡ/д������ݸ���
	INT16U	I2C_suba;			//I2C�����ڲ��ӵ�ַ
}TI2C;

//�������ʱ��ʱ��T1MR3�ıȽ�ֵ
#define MS_TIMER Fpclk/1000

#define COMM_485_TIMER	20000

//�����ж�Դ
#define		VIC_EINT1		0x0F
#define		VIC_EINT2		0x10
#define		VIC_EINT3		0x11
#define		VIC_TIMER0		0x04
#define		VIC_TIMER1		0x05
#define		VIC_TIMER2		0x1A
#define		VIC_TIMER3		0x1B
#define		VIC_UART0		0x06
#define		VIC_UART3		0x1D
#define		VIC_PWM0		0x08
#define		VIC_I2C1		0x13
#define		VIC_I2C2		0x1E


#define Fosc                11059200			//	OSC = 11.0592MHz
#define Fcclk	(Fosc * 4)							// ��Ƶ Fcclk = 44.2368MHz
#define Fcco    (Fcclk* 6)
	
#define Fpclk	(Fcclk / 4)
	
#define PLL_NValue			1	
#define PLL_MValue			(((Fcco/Fosc)*(PLL_NValue+1)/2)-1)
#define CCLKDivValue		(Fcco/Fcclk-1)
#define USBCLKDivValue		254		

/* ���崮��ģʽ�������ݽṹ */
//typedef  struct  UART_MODE
//{  
//	INT16U datab;         // �ֳ��ȣ�5/6/7/8
//	INT16U stopb;         // ֹͣλ��1/2
//	INT16U parity;    	  // ��żУ��λ��0Ϊ��У�飬1����У�飬2Ϊż��У��
//}UART_MODE;

extern void CPU_PIN_Init(void);
extern void SetupHardware(void); 
#endif

