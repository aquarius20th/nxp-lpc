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
#include <string.h>
#include "applib.h" 
#include "guidef.h"
#include "GraphicDriver.h"


//����Һ������
#define LCD_WIDTH 240
#define LCD_HEIGHT 128

typedef INT8U FRAME_BUFF[LCD_WIDTH][LCD_WIDTH>>3];
static FRAME_BUFF g_LcdBuff;

static void  LcdSetPixel (GUI_COLOR *c, INT32U x, INT32U y);
static void  LcdGetPixel (GUI_COLOR *c, INT32U x, INT32U y);
static void LcdDrawHLine(GUI_COLOR *c, INT32U x1, INT32U x2, INT32U y);
static void LcdDrawVLine(GUI_COLOR *c, INT32U x1, INT32U x2, INT32U y);
static void LcdUpdate(CGuiRect *rect);
//static LCD_BUFF_FLAG g_LcdBuffFlag;


static CGuiHwDriver LcdDrvier = 
{
	LCD_WIDTH,
	LCD_HEIGHT,
	LcdUpdate,
	&g_LcdBuff[0][0],
	LcdSetPixel,
	LcdGetPixel,
	LcdDrawHLine,
	LcdDrawVLine	
};

//�����ָ��
#define NOP   __asm{ NOP }
void GuiDelayNS(INT16U ns)
{
	INT32U count=3*ns;
	INT32U i;
	for (i=0;i<count;i++)
	{
		NOP;
	}
}
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

/*LCD����  */
#define   LCD_RESET (*((volatile unsigned short *) 0x82000010))
#define   LCD_CS (*((volatile unsigned short *) 0x82000014))
#define   LCD_WR (*((volatile unsigned short *) 0x82000018))
#define   LCD_RD (*((volatile unsigned short *) 0x82000020))
#define   LCD_DATA (*((volatile unsigned short *) 0x82000024))
#define   LCD_ADDR (*((volatile unsigned short *) 0x82000028))
#define   LCD_BACK (*((volatile unsigned short *) 0x82000030))


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


// Y���ڰ�λ�е�λ
#define GetYBitPos(y) (((INT8U)(y)) & 0x07)
// Y���ڰ�λ�е�Mask 0x10��ʽ
#define GetYBitMask(y) (1<<GetYBitPos(y))
/*********************************************************************************************************
** ��������: WriteLcdBufData
** ��������: WriteLcdBufData
**
** ����������  дһ���ֽڵ�Һ������
**
** �䡡��:  LCD_POS col
** �䡡��:  LCD_POS row
** �䡡��:  INT8U data
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��6��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void WriteLcdBufData( LCD_POS col, LCD_POS row ,INT8U data )
{
	if (col>=LCD_WIDTH|| row >= LCD_HEIGHT)
		return;
// 	if( g_LcdBuff[col][row] != data)
// 		g_LcdBuffFlag[col][row] = TRUE;

	g_LcdBuff[col][row] = data;	
}
/*********************************************************************************************************
** ��������: LcdSetPixel
** ��������: LcdSetPixel
**
** ���������� ��һ���� 
**
** �䡡��:  GUI_COLOR * c
** �䡡��:  INT32U x
** �䡡��:  INT32U y
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��14��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void  LcdSetPixel (GUI_COLOR *pClr, INT32U x, INT32U y)
{
	INT8U b = 0 ; 

	if(x>=LCD_WIDTH || y>= LCD_HEIGHT || pClr == NULL)
		return;	 
 	b=g_LcdBuff[x][y>>3];

	if (*pClr == GUI_COLOR_BK)
	{
		b &= ~ GetYBitMask(y);
	}
	else
	{
		b |= GetYBitMask(y);
	}


//	LCD_WriteData(x,y,*c); 
}

static void LcdGetPixel(GUI_COLOR *pClr, INT32U x, INT32U y)
{ 
	if(x>=LCD_WIDTH || y>= LCD_HEIGHT || pClr == NULL)
		return;	 

}
/*********************************************************************************************************
** ��������: LcdDrawHLine
** ��������: LcdDrawHLine
**
** ����������  ��ˮƽ��
**
** �䡡��:  GUI_COLOR * c
** �䡡��:  INT32U x1
** �䡡��:  INT32U x2
** �䡡��:  INT32U y
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��14��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void LcdDrawHLine(GUI_COLOR *c, INT32U x1, INT32U x2, INT32U y)
{
	INT32U i  = 0;
	INT8U page_address = y >> 3;

	if ((x1 >= LCD_WIDTH) ||(x2 >= LCD_WIDTH) || (y >= LCD_HEIGHT))
		return;

	if(x1>x2)
	{
		i=x1;
		x1=x2;
		x2=i;
	}

	page_address = (y & 0x0f) | 0xb0;

	LCD_SendCmd(page_address); //����ҳ��ַ
	for (i=x1;i<x2;i++)
	{
		//�е�ַ
		LCD_SendCmd(i & 0x0f);
		LCD_SendCmd(0x10 + (INT8U) ((i & 0xf0) >> 4));

		LCD_Senddata(*c); //��ֵ 
	}  
}
/*********************************************************************************************************
** ��������: LcdDrawVLine
** ��������: LcdDrawVLine
**
** ����������  ��ֱ��
**
** �䡡��:  GUI_COLOR * c
** �䡡��:  INT32U x
** �䡡��:  INT32U y1
** �䡡��:  INT32U y2
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��12��14��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void LcdDrawVLine(GUI_COLOR *c, INT32U x, INT32U y1, INT32U y2)
{

}

static void LcdUpdate(CGuiRect *rect)
{
	/* nothing for none-DMA mode driver */
}