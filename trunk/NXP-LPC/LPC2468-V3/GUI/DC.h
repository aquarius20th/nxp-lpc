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

//����
extern void DrawLine(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr);
extern void DrawLineEx(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/, PEN pen/*=PEN_COPY*/);

 
extern void DrawBlock(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/);

extern void DrawBlockRect( LCDRECT *pRect, COLOR cr);

extern void DrawRect(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/);

extern void DrawStringByStr(LcdPos x, LcdPos y, const char * pString, PEN pen/*=PEN_COPY*/, ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType);
extern void DrawStringById(LcdPos x, LcdPos y, INT16U uStringResID, PEN pen/*=PEN_COPY*/, ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType);

extern void DrawIcon(LcdPos x, LcdPos y, INT16U iIconID, PEN pen/*=PEN_COPY*/);

//Һ���ػ�
extern void ClearScreen(void);

extern void TurnOnLed(void);
extern void TurnOffLed(void);

#endif

