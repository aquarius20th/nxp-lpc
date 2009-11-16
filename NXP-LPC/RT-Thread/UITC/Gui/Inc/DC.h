/****************************************Copyright (c)**************************************************
**                                      
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
#ifndef GUI_DC_H
#define	GUI_DC_H 
#pragma  once

#include "GuiDef.h"
#include "LcdDriver.h"

typedef INT8U LCD_BUFF[LCD_WIDTH][LCD_WIDTH>>3];


typedef enum LCD_EN_FONT
{
	LCD_EN_FONT_8_8,     // Ӣ���ַ���С8��8
	LCD_EN_FONT_8_16     // Ӣ���ַ���С8��16
}LCD_EN_FONT;


//������ɫ
typedef enum GUI_COLOR
{
	GUI_COLOR_BK	=0,		//����ɫ
	GUI_COLOR_FR	=1		//ǰ��ɫ
}GUI_COLOR;

// ����ģʽ
typedef enum GUI_PEN
{
	PEN_COPY,		// ֱ��copy����
	PEN_NOT,		// NOT
	PEN_OR,			// OR
	PEN_XOR,        // XOR
	PEN_AND			//AND
}GUI_PEN;

// ���뷽ʽ
typedef enum GUI_ALIGN
{
	ALIGN_LEFT,     //�����
	ALIGN_CENTER,   //���ж���
	ALIGN_RIGHT     //�Ҷ���
}GUI_ALIGN;


/* DrawText ��ʽ*/
#define DT_VMASK	    	0x0000000F
#define DT_TOP		    	0x00000001         ///< ������
#define DT_VCENTER	     	0x00000002         ///< ��ֱ���ж���
#define DT_BOTTOM	     	0x00000004         ///< �׶���
#define DT_HMASK	    	0x000000F0
#define DT_LEFT		    	0x00000010         ///< �����
#define DT_CENTER	    	0x00000020         ///< ˮƽ���ж���
#define DT_RIGHT	    	0x00000040         ///< �Ҷ�����


__inline INT16U GetLcdWidth( )
{
	return LCD_WIDTH;
}


//����
void DrawLine(LCD_POS x0, LCD_POS y0, LCD_POS x1, LCD_POS y1, GUI_COLOR cr);
void DrawLineEx(LCD_POS x0, LCD_POS y0, LCD_POS x1, LCD_POS y1, GUI_COLOR cr/*=COLOR_FR*/, GUI_PEN pen/*=PEN_COPY*/);


void DrawBlock(LCD_POS x0, LCD_POS y0, LCD_POS x1, LCD_POS y1, GUI_COLOR cr/*=COLOR_FR*/);

void DrawBlockRect( CGuiRect *pRect, GUI_COLOR cr);

void DrawRect(LCD_POS x0, LCD_POS y0, LCD_POS x1, LCD_POS y1, GUI_COLOR cr/*=COLOR_FR*/);

void DrawStringByStr(LCD_POS x, LCD_POS y,const char * pString, GUI_PEN pen/*=PEN_COPY*/, GUI_ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType);
void DrawStringById(LCD_POS x, LCD_POS y, INT16U uStringResID, GUI_PEN pen/*=PEN_COPY*/, GUI_ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType);

void DrawIcon(LCD_POS x, LCD_POS y, INT16U iIconID, GUI_PEN pen/*=PEN_COPY*/);

//Һ���ػ�
void ClearScreen(void);
void ClearScreenEx(INT8U bClear/* = FALSE*/);


void ClrRectScreenBuf(CGuiRect* rc,GUI_COLOR color);

void InvalidateScreen( INT8U bErase );
void UpdateScreen(  INT8U bErase);

void ReverseClrRect(CGuiRect * rc);
#endif

