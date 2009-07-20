/****************************************Copyright (c)**************************************************
**                                  Һ���ײ�����      
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
#include "includes.h" 
#include "hd_Const.h"
#include "LcdDriver.h"

#define ECPRO610

#ifdef ECPRO610

/*************************************************************************************
** Һ��ģ������
** LCD
**************************************************************************************/
void read_status1(void)
{	
	INT8U status;
	FIO1DIR &=0xfc03ffff;//����
	FIO1CLR =LCD_DIR;//���ݶ��룬245DIRΪ��
	FIO0CLR = LCD_E1;  //�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬ 
	FIO4CLR = LCD_A0;  //"L"=write command status "H"=write data status
	FIO2SET = LCD_RW;  //"H"=read status "L"=write status
    FIO0SET = LCD_E1;  
	status = (FIO1PIN&LCD_DB)>>18;	
	FIO0CLR = LCD_E1;
	FIO1DIR = 0x1ffc0000;
	
}

void GXM12232_SED1520_delay1s(INT16U delay_xms)
{
	INT16U i,j,m;
	for(i=0;i<delay_xms;i++)
	{
		for(j=0;j<280;j++)
		{
			for(m=0;m<125;m++)
			{
				ASM_NOP;
				ASM_NOP;
				ASM_NOP;
				ASM_NOP;
			}
		}
	}
}

//***********delay50us************************//
void GXM12232_SED1520_delay50us(INT8U count50us)
{
    INT8U  k ;
	ASM_NOP;
    for(k=0;k<2*count50us;k++)
    {
     ASM_NOP;     ASM_NOP;     ASM_NOP;     ASM_NOP;     ASM_NOP;
    }
}

//*************Write  lift screen data*****************//
void  GXM12232_SED1520_LWriteData(INT8U dat)
{	
	FIO1DIR |=0x03fc0000;//���
	FIO1SET =LCD_DIR; //245DIR=1
	FIO2CLR=LCD_E1;
	//�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬ 
	FIO4SET = LCD_A0;  //"L"=write command status "H"=write data status
	FIO2CLR = LCD_RW;  //"H"=read status "L"=write status
	FIO1CLR = LCD_DB; FIO1SET =dat<<18;
	ASM_NOP;
	ASM_NOP;
	FIO0SET = LCD_E1;   
	FIO0CLR = LCD_E1;
	ASM_NOP;
	ASM_NOP;
	
}

//*************Write  Right screen data*****************//
void  GXM12232_SED1520_RWriteData(INT8U dat)
{	
	FIO1DIR |=0x03fc0000;//���
	FIO1SET =LCD_DIR; //245DIR=1
	FIO0CLR=LCD_E2;
	//�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬ 
	FIO4SET = LCD_A0;  //"L"=write command status "H"=write data status
	FIO2CLR = LCD_RW;  //"H"=read status "L"=write status
	FIO1CLR = LCD_DB; FIO1SET =dat<<18;
	ASM_NOP;
	ASM_NOP;
	FIO0SET = LCD_E2;   
	FIO0CLR = LCD_E2;
	ASM_NOP;
	ASM_NOP;
	
}

//****************write Lift screen command*******************//
void  GXM12232_SED1520_LWritecommand(INT8U command)
{	
	FIO1DIR |=0x03fc0000;//���
	FIO1SET =LCD_DIR; //245DIR=1
	FIO0CLR=LCD_E1;
	//�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬ 
	FIO4CLR = LCD_A0;  //"L"=write command status "H"=write data status
	FIO2CLR = LCD_RW;  //"H"=read status "L"=write status
	FIO1CLR = LCD_DB; FIO1SET =command<<18;
	ASM_NOP;
	ASM_NOP;
	FIO0SET = LCD_E1;   
	FIO0CLR = LCD_E1;
	ASM_NOP;
	ASM_NOP;
	
}
//****************write Right screen command*******************//
void  GXM12232_SED1520_RWritecommand(INT8U command)
{	
	FIO1DIR |=0x03fc0000;//���
	FIO1SET =LCD_DIR; //245DIR=1
	FIO0CLR=LCD_E2;
	//�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬ 
	FIO4CLR = LCD_A0;  //"L"=write command status "H"=write data status
	FIO2CLR = LCD_RW;  //"H"=read status "L"=write status
	FIO1CLR = LCD_DB; FIO1SET =command<<18;
	ASM_NOP;
	ASM_NOP;
	FIO0SET = LCD_E2;   
	FIO0CLR = LCD_E2;
	ASM_NOP;
	ASM_NOP;
	
}

/***************************************************************/     
void GXM12232_SED1520_initlcd(void)
{   
	/*******************************************************************************************
	**��LCD Work at 68 MPU mode  ����������ʽ
	*******************************************************************************************/
	FIO1CLR	= LCD_RESET;
	GXM12232_SED1520_delay50us(1);
	FIO1SET	= LCD_RESET;
  
	FIO1SET = LCD_CL;  
	FIO4CLR = LCD_A0;  //"H"=write command status "L"=write data status//
	FIO2SET = LCD_RW;   //"H"=read status "L"=write status//
	FIO0CLR = LCD_E1;  //�½���Ϊд�������ߵ�ƽΪ���������͵�ƽ����Ϊ����״̬//
	FIO0CLR = LCD_E2;
    read_status1();
     
	GXM12232_SED1520_LWritecommand(0xe2);//;�����λ
    GXM12232_SED1520_RWritecommand(0xe2);//;�����λ
      
    GXM12232_SED1520_LWritecommand(0xa4);//;�˳�����״̬
    GXM12232_SED1520_RWritecommand(0xa4);//;�˳�����״̬
          
    GXM12232_SED1520_LWritecommand(0xa9);//;����λ32λռ�ձ�
    GXM12232_SED1520_RWritecommand(0xa9);//;����λ32λռ�ձ�

    GXM12232_SED1520_LWritecommand(0xa0);//;ADC SECLECT SEG0~SEG61
    GXM12232_SED1520_RWritecommand(0xa0);//;ADC SECLECT SEG0~SEG61
         
    GXM12232_SED1520_LWritecommand(0xc0);//;������ʼ��
    GXM12232_SED1520_RWritecommand(0xc0);//;������ʼ��
      
    GXM12232_SED1520_LWritecommand(0xaf);//;��ʾ��
    GXM12232_SED1520_RWritecommand(0xaf);//;��ʾ��
    read_status1();
}

/***************************************************************/
//����Һ��
void  hd_LightLCD(INT8U bLightOn)
{
	if(bLightOn)
	{  
		FIO1SET = LCD_CL;
	}
	else
	{
		FIO1CLR = LCD_CL;
	}
}

//LCD����
void hd_LCD_ClearScreen(void)
{
	INT8U i,j;
	INT8U page_address;
	for(i=0;i<4;i++) 
	{
    	page_address=i;
   		page_address=page_address|0x0b8;
    	GXM12232_SED1520_LWritecommand(page_address);//;����ҳ��ַ
    	GXM12232_SED1520_RWritecommand(page_address);//;����ҳ��ַ
    
    	GXM12232_SED1520_LWritecommand(0x00);//;�е�ַ
    	GXM12232_SED1520_RWritecommand(0x00);//;�е�ַ

    	for(j=0;j<61;j++)
    	{
     		GXM12232_SED1520_LWriteData(0x00);
     		GXM12232_SED1520_RWriteData(0x00);
    	}
     
   }
}

//LCDд����
///////////////////////////////////////////////////////////////
//	�� �� �� : hd_LCD_WriteData
//	�������� : ��Һ��д��
//	������� : 
//	��    ע : 
//	��    �� : ��ΰ
//	ʱ    �� : 2006��1��24��
//	�� �� ֵ : void
//	����˵�� : INT8U x,			//������
//				 INT8U y,		//������
//				 INT8U val		//ֵ
///////////////////////////////////////////////////////////////
extern void hd_LCD_WriteData(INT8U x, INT8U y, INT8U val)
{
	INT8U page_address;

	if((x>LCD_WIDTH-1) || (y>LCD_HEIGHT-1))
		return;
	
	page_address=y|0xb8;

	// ����
	if(x<61)
	{
		GXM12232_SED1520_LWritecommand(page_address); //����ҳ��ַ
		GXM12232_SED1520_LWritecommand(x);            //�е�ַ
		GXM12232_SED1520_LWriteData(val);             //��ֵ
	}
	else // �Ұ��
	{ 
		GXM12232_SED1520_RWritecommand(page_address); //����ҳ��ַ
		GXM12232_SED1520_RWritecommand(x-61);         //�е�ַ
		GXM12232_SED1520_RWriteData(val);             //��ֵ
	}
} 

#endif // ECPRO610
