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
#include "GuiConst.h" 
#include "global.h"
#include "DC.h"
#include "MsgBox.h"
#include "Icon.h"
 

static LcdBuffer m_LcdSave;



extern void ShowMsgBoxStr(const char * szMsg, INT8U mode)
{
	ClearScreen();

	// ��Ϣ
	DrawStringByStr(1, 0,szMsg, PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_8);

	// ͼ�꼰��ť
	if(mode & LCD_MB_YESNO)  // ��YES NO����
	{
		DrawRect(32,20,48,30,COLOR_FR);
	    DrawIcon(36,21,ID_ICON_FALSE,PEN_COPY);
		DrawRect(64,20,80,30,COLOR_FR);
		DrawIcon(68,21,ID_ICON_TRUE,PEN_COPY);
	}
	else if(mode & LCD_MB_OK) // ��ȷ�ϰ���
	{
		DrawRect(48,20,80,30,COLOR_FR);
		DrawStringByStr(52,21,"ok" , PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_8);
	}

	if(mode & LCD_MB_INFO) // ����Ϣͼ��
	{
		DrawIcon(13<<3,0,ID_ICON_INFO,PEN_COPY);
	}
	else if(mode & LCD_MB_WARN) // �и澯ͼ��
	{
		DrawIcon(13<<3,0,ID_ICON_WARN,PEN_COPY);
	}

	// ��ʾ�߿�
	DrawRect(0,0,121,31,COLOR_FR);	
}

void ShowMsgBoxID(INT16U  nID, INT8U mode)
{
	ClearScreen();

	DrawStringById(1,0,nID, PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_8);// ��Ϣ

	// ͼ�꼰��ť
	if(mode & LCD_MB_YESNO)  // ��YES NO����
	{
		DrawRect(32,20,48,30,COLOR_FR);
		DrawIcon(36,21,ID_ICON_FALSE,PEN_COPY);
		DrawRect(64,20,80,30,COLOR_FR);
		DrawIcon(68,21,ID_ICON_TRUE,PEN_COPY);

	}
	else if(mode & LCD_MB_OK) // ��ȷ�ϰ���
	{
		DrawRect(48,20,80,30,COLOR_FR);
		DrawStringByStr(52,21,"ok", PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_8);
	}

	if(mode & LCD_MB_INFO) // ����Ϣͼ��
	{
		DrawIcon(13<<3,0,ID_ICON_INFO,PEN_COPY);
	}
	else if(mode & LCD_MB_WARN) // �и澯ͼ��
	{
		DrawIcon(13<<3,0,ID_ICON_WARN,PEN_COPY);
	}

	// ��ʾ�߿�
	DrawRect(0,0,121,31,COLOR_FR); 		
}
