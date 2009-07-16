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
#ifndef GLOBAL_DEF_H
#define	GLOBAL_DEF_H

#include "LcdDriver.h"

//����λ��
#ifndef LcdPos
#	define LcdPos INT16U
#endif

//������ɫ
#ifndef COLOR
#	define COLOR INT8U
#endif

//���廭��
#ifndef PEN
#	define PEN INT8U
#endif

#ifndef ALIGN
#	define ALIGN INT8U
#endif

//������ɫ
typedef enum GUI_COLOR
{
	COLOR_BK	=0,		//����ɫ
	COLOR_FR	=1		//ǰ��ɫ
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


//������λ���������ݽṹ
typedef struct LCD_POS
{
	LcdPos Row;			//�� 
	LcdPos Col;			//��
} LCD_POS;


typedef enum LCD_EN_FONT
{
	LCD_EN_FONT_8_8,     // Ӣ���ַ���С8��8
	LCD_EN_FONT_8_16     // Ӣ���ַ���С8��16
}LCD_EN_FONT;


//���� X ����λ�ã��������������Ӧ������
#define GetXIndex(x) (x)
//Y������
#define GetYIndex(y)  (((LcdPos)(y))>>3)
// Y���ڰ�λ�е�λ
#define GetYBitPos(y) (((INT8U)(y)) & 0x07)
// Y���ڰ�λ�е�Mask 0x10��ʽ
#define GetYBitMask(y) (1<<GetYBitPos(y))

/******************
1. ����Һ���ı��ŷ�ʽ���з�ʽ������ͼ��ʾ
|||||||||||...
|||||||||||...
|||||||||||...
|||||||||||...
122 * 32�����Һ�������л��֣���ͼһ�����߱�ʾһ���ֽڣ�����ʱ��������ֽ�Ϊ����ġ�
����ֽڵĻ���Ϊ122*4���ֽ�
*******************/
//������ʾ����������
#define GetLCDBufferWidth(ignore) LCD_WIDTH
#define GetLCDBufferHeight(ignore) (LCD_HEIGHT>>3)  // (32/8)=4

//�õ�Һ���ĳ���
#define GetLCDWidth(ignore) LCD_WIDTH
#define GetLCDHeight(ignore) LCD_HEIGHT

//�����ַ�����󳤶�
#define STRING_MAXLEN 256

//���ֿ�������ʾ��ַ
#define CNZI_FIRST_INDEX 10000


typedef INT8U LcdBuffer[GetLCDBufferWidth()][GetLCDBufferHeight()];

typedef struct tagLCDRECT
{
	LcdPos    left;
	LcdPos    top;
	LcdPos    right;
	LcdPos    bottom;
} LCDRECT, *LPLCDRECT;

typedef const LCDRECT* LPCLCDRECT;    // pointer to read/only RECT

typedef struct tagLCDPOINT
{
	LcdPos  x;
	LcdPos  y;
} LCDPOINT, *LPLCDPOINT;

typedef const LCDPOINT* LPCLCDPOINT;

typedef struct tagLCDSIZE
{
	LcdPos     cx;
	LcdPos     cy;
} LCDSIZE, *LPLCDSIZE;

typedef const LCDSIZE* LPCLCDSIZE;
//
extern void NormalizeRect(LPLCDRECT  pRect);

//������λ���������ݽṹ
typedef struct CLcdCursor
{
	LcdPos Row;			//�� 
	LcdPos Col;			//��
} CLcdCursor;


//����˵�����
typedef struct  CMenuData
{
	INT16U		nMenuID;          //�˵�ID��
	INT16U		nResourceID;      //�˵�������
	INT32U		nItemData;		  //�˵�������
}CMenuData;

//��������
typedef  void  (*fnOnKeyDown)( INT16U keyCode);
//��Ϣ�����麯��
typedef  void   (*fnOnMessage)(INT32U msg, INT32U param);
//��ʼ������
typedef  void    (*fnInit)();
//�˳�ʱ����
typedef  void	(*fnDestory)();
//��Ϣ֪ͨ
typedef  void	(*fnOnNotify)(INT32U nf);


typedef  void    (*fnCreate)(void);



extern const INT32U TenMultiple[];
 

#endif

