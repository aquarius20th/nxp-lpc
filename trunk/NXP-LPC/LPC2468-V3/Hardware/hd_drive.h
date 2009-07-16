///////////////////////////////////////////////////////////////
//	�� �� �� : hd_drive.h
//	�ļ����� : Ӳ������
//	��    �� :  
//	����ʱ�� : 
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#ifndef _HD_DRIVE_H
#define	_HD_DRIVE_H

#include "hd_init.h"
 								  
//#define SetTickVic(ignore) ReEnableVICIRQ(VIC_TIMER0); //�������ж�
/*******************************************************************************************
** �������� �� ��ʱ
*******************************************************************************************/
void DelayNS (INT32U dly);
//void Delayus (INT32U dly);
#define hd_GetDigitalIn(ignore) (~(INT16U)FIO4PIN & 0x0FFF)

#define Reset 	Reset_Handler


/****************************************************************************
* ���ƣ�GeAnalogIn()
* ���ܣ�AD�ɼ�
* ��ڲ�������
** ���ڲ����AADת��ֵ
****************************************************************************/
extern void hd_GetAnalogIn(INT8U chNo);


/* �������ں�I2C2�жϴ�����Ϣ��ȫ�ֱ��� */
extern volatile INT8U 	I2C_sla;			/* I2C�����ӵ�ַ 					*/
extern volatile INT32U	I2C_suba;			/* I2C�����ڲ��ӵ�ַ 				*/
extern volatile INT8U 	I2C_suba_num;		/* I2C�ӵ�ַ�ֽ���					*/
extern volatile INT8U 	*I2C_buf;        	/* ���ݻ�����ָ��  					*/
extern volatile INT32U 	I2C_num;			/* Ҫ��ȡ/д������ݸ��� 			*/
extern volatile INT8U 	I2C_end;			/* I2C���߽�����־��������������1 	*/
extern volatile INT8U 	I2C_suba_en;		/* 	�ӵ�ַ���ơ�
											0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
											1--��ȡ����
											2--д����
											*/

/* �������ں�I2C1�жϴ�����Ϣ��ȫ�ֱ��� */
extern volatile INT8U 	I2C1_sla;			/* I2C�����ӵ�ַ 					*/
extern volatile INT32U	I2C1_suba;			/* I2C�����ڲ��ӵ�ַ 				*/
extern volatile INT8U 	I2C1_suba_num;		/* I2C�ӵ�ַ�ֽ���					*/
extern volatile INT8U 	*I2C1_buf;        	/* ���ݻ�����ָ��  					*/
extern volatile INT32U 	I2C1_num;			/* Ҫ��ȡ/д������ݸ��� 			*/
extern volatile INT8U 	I2C1_end;			/* I2C���߽�����־��������������1 	*/
extern volatile INT8U 	I2C1_suba_en;		/* 	�ӵ�ַ���ơ�
											0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
											1--��ȡ����
											2--д����
											*/
#endif

