 /****************************************Copyright (c)**************************************************
**						��ʾӲ������������ֻ֧��1����ʾ�ӿ�	     
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:   LcdDriver.h
**��   ��   ��:   Author: admin
**����޸�����: Created on: 2009-11-15
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

#pragma once 

#include "applib.h" 
#include "GuiDef.h"

struct GUI_HW_DRIVER
{
	/* screen Width and Height */
	INT32U Width;
	INT32U Height;

	/* screen update */
	void (*ScreenUpdate)(CGuiRect* rect);
	INT8U *pFrameBuffer;

	/* set and get pixel in (x, y) */
	void (* SetPixel) (GUI_COLOR *c, INT32U x, INT32U y);
	void (* GetPixel) (GUI_COLOR *c, INT32U x, INT32U y);

	void (*DrawHLine)(GUI_COLOR *c, INT32U x1, INT32U x2, INT32U y);
	void (*DrawVLine)(GUI_COLOR *c, INT32U x , INT32U y1, INT32U y2);
};

typedef struct GUI_HW_DRIVER CGuiHwDriver;

 