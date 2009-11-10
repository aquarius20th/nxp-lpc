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
#include "includes.h"  
#include "global.h"
#include "ScreenBase.h"
#include "Gui.h"
 


/*******************************************************************/
//	10�ı�������
/*******************************************************************/
const INT32U TenMultiple[]=
{
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000
};

extern void NormalizeRect(LPLCDRECT pRect)
{
	LcdPos nTemp;
	if (pRect)
	{
		if (pRect->left > pRect->right)
		{
			nTemp = pRect->left;
			pRect->left = pRect->right;
			pRect->right = nTemp;
		}
		if (pRect->top > pRect->bottom)
		{
			nTemp = pRect->top;
			pRect->top = pRect->bottom;
			pRect->bottom = nTemp;
		}
	}
} 
 
extern void SetLcdRect(LCDRECT *pRect, LcdPos l, LcdPos t, LcdPos r, LcdPos b)
{
	pRect->left = l; pRect->top = t; pRect->right = r; pRect->bottom = b; 
}

extern void SetLcdRectEmpty(LCDRECT * pRect)
{
	pRect->left=0;pRect->right=0;pRect->top=0;pRect->bottom=0; 
}

/************************************************************************/
//  ����Ԫ��λ�ö���
/************************************************************************/
const LCDRECT LCD_RECT_MENU={0,16,GetLCDWidth()-1,GetLCDHeight()-1};	//�˵�λ��
const LCDRECT LCD_RECT_VARBAR={GetLCDWidth()-16,0,GetLCDWidth()-1,GetLCDHeight()-1};//������λ��
const LCDRECT LCD_RECT_NUMEDIT={0,24,88,31};		//���ֱ༭��λ��
const LCDRECT LCD_RECT_ENUMEDIT={0,16,120,31};		//ö�ٱ༭��λ��

const LCDPOINT LCD_POINT_EDIT_TOOLTIP={0,16};		//����༭����ʾ��Ϣλ��
const LCDPOINT LCD_POINT_EDIT_UNIT={GetLCDWidth()-32,GetLCDHeight()-8};			//����༭��λ��Ϣλ��
const LCDPOINT LCD_POINT_EDIT_CAPTION={0,0};		//����༭�������Ϣλ��
