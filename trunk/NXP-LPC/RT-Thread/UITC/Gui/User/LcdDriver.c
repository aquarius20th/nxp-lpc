 /****************************************Copyright (c)**************************************************
**							     LCD Ӳ���������֣��ⲿ����Ҫ���ݲ�ͬ��Ӳ����ʵ��
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:   LcdDriver.c
**��   ��   ��:   Lijin
**����޸�����:   2009-11-15
**��        ��:   
**��        ע :   
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


#include "applib.h"
#include "lcddriver.h"


/*LCD����  */
#define   LCD_RESET (*((volatile unsigned short *) 0x82000010))
#define   LCD_CS (*((volatile unsigned short *) 0x82000014))
#define   LCD_WR (*((volatile unsigned short *) 0x82000018))
#define   LCD_RD (*((volatile unsigned short *) 0x82000020))
#define   LCD_DATA (*((volatile unsigned short *) 0x82000024))
#define   LCD_ADDR (*((volatile unsigned short *) 0x82000028))
#define   LCD_BACK (*((volatile unsigned short *) 0x82000030))


//Һ����״̬
static INT8U g_nLcdLed;

//��Һ������
#define  LCD_BACK_OFF(ignore)  LCD_BACK =0x80;
//��Һ������
#define  LCD_BACK_ON(ignore)  LCD_BACK =0x00;
//����Һ����
void TurnOnLcd(void)
{
 	LCD_BACK_ON( );
	g_nLcdLed=TRUE;
}
//Ϩ��Һ����
void TurnOffLcd(void)
{
 	LCD_BACK_OFF( );
	g_nLcdLed=FALSE;
}
//�����ָ��
#define NOP   __asm{ NOP }
///////////////////////////////////////////////////////////////
//	�� �� �� : hd_Delay
//	�������� : ��ʱ����ms
//	������� :
//	��    ע :
//	��    �� : ��ΰ
//	ʱ    �� : 2005��9��29��
//	�� �� ֵ : void
//	����˵�� : INT16U ms
///////////////////////////////////////////////////////////////
void GuiDelayMS(INT16U ms)
{
	//ִ��11059200����䣬��ʱ3.570S�����ÿms����3097�����
	INT32U count=3339*ms;
	INT32U i;
	for (i=0;i<count;i++)
	{
		NOP;
	}
}
///////////////////////////////////////////////////////////////
//	�� �� �� : hd_DelayNS
//	�������� : ��ʱ����
//	������� :
//	��    ע :
//	��    �� :
//	ʱ    �� : 2005��10��7��
//	�� �� ֵ : void
//	����˵�� : INT16U ns
///////////////////////////////////////////////////////////////
void GuiDelayNS(INT16U ns)
{
	INT32U count=3*ns;
	INT32U i;
	for (i=0;i<count;i++)
	{
		NOP;
	}
}

void LCD_Senddata(INT8U dat) //д����
{
	LCD_CS=0x00;
	LCD_ADDR = 0x80;
	LCD_RD = 0x80;
	LCD_WR = 0x00;
	LCD_DATA = dat;
//	ASM_NOP; ASM_NOP; ASM_NOP;
	GuiDelayNS(1);
	LCD_WR = 0x80;
}
/*********************************************************************************/
void LCD_SendCmd(INT8U cmd) //д����
{
	LCD_CS=0x00;
	LCD_ADDR = 0x00;
	LCD_RD = 0x80;
	LCD_WR = 0x00;
	LCD_DATA = cmd;
//	ASM_NOP; ASM_NOP; ASM_NOP;
	GuiDelayNS(1);
	LCD_WR = 0x80;
}

//��Һ��д��
void LCD_WriteData(INT8U x, INT8U y, INT8U val)
{
	INT8U page_address = y >> 3;

	if ((x >= LCD_WIDTH) || (y >= LCD_HEIGHT))
		return;

	page_address = (y & 0x0f) | 0xb0;

	LCD_SendCmd(page_address); //����ҳ��ַ

	//�е�ַ
	LCD_SendCmd(x & 0x0f);
	LCD_SendCmd(0x10 + (INT8U) ((x & 0xf0) >> 4));

	LCD_Senddata(val); //��ֵ
}

//LCD����
void LCD_ClearScreen(void)
{
	INT16U i,j;
	LCD_SendCmd(0XB0); /*SET PAGE ADDRESS*/
	LCD_SendCmd(0X10); /*SET COLUMN ADDRESS MSB(00000000)*/
	LCD_SendCmd(0X00); /*SET COLUMN ADDRESS LSB(00000000)*/
	LCD_SendCmd(0X89); /*SET RAM ADDRESS CONTROL*/
	for(i=0;i<LCD_HEIGHT>>3;i++)
	{
		for(j=0;j<LCD_WIDTH;j++)
			LCD_Senddata(0X00);
	}
}

//�����ڴ��ȡλ��
void LCD_SetDisplayPos(INT8U page_address, INT8U col_address)
{
	LCD_SendCmd(0xb0 + (INT8U) (page_address & 0x0f));
	LCD_SendCmd(col_address & 0x0f);
	LCD_SendCmd(0x10 + (INT8U) ((col_address & 0xf0) >> 4));
}

void LCD_WriteDataApi(INT8U val)
{
	LCD_Senddata(val);             //��ֵ
}
static void  LCD_Init(void)  //Һ����ʼ��
{
	LCD_RESET=0;
	GuiDelayMS(10);
	LCD_RESET=0x80;
	GuiDelayMS(10);
	LCD_SendCmd(0xE2);        //system reset
	GuiDelayMS(1);
	LCD_SendCmd(0xe9);        //set lcd bias ratio (10b=12.0)
	LCD_SendCmd(0x27);        //set mux rate and temperature compensation (11b=-0.20%/c)
	LCD_SendCmd(0x81);        //
	LCD_SendCmd(0xc0);        //set gain and potentiometer(double-byte command)

	LCD_SendCmd(0x2f);        //set power control
	LCD_SendCmd(0x40);        //set start line to 0
	LCD_SendCmd(0xa4);        //set ALL_PIXEL_ON to OFF
	LCD_SendCmd(0xa6);        //set Inverse Display to OFF
	LCD_SendCmd(0x89);        //set RAM Address Cntrol
	LCD_SendCmd(0xc8);        //set Map Control:
	LCD_SendCmd(0xaf);		  //Display Enable;
}
/*********************************************************************************************************
** ��������: InitLcd
** ��������: InitLcd
**
** ���������� ����ʱ���� 
**
** �䡡��:  void
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��15��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void InitLcd(void)
{
	//LCD��ʼ��
	LCD_Init();
	LCD_ClearScreen();
}









