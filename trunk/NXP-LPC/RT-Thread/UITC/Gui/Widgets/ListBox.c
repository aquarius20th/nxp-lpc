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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>  
#include "ListBox.h" 
#include "DC.h"
#include "icon.h"


#define MENU_OFFSET (40) //�˵���������߼��

/*********************************************************************************************************
** ��������: OnPaintCtrl
**
** ���������� ��ʾ�˵� �ڲ�˽�нӿ�
**
** �䡡��:  CLcdMenu * pMenu
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��22��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void OnPaintCtrl(CCtrlBase *pCtrl)
{
	INT8U i,start,end;
	INT8U row = 0;
	CGuiListBox *pListBox = (CGuiListBox *)pCtrl;
	CGuiRect rcBlock;

	char szTxt[16] = {0};

	if (pListBox == NULL)
		return;

	if(pListBox->ItemCount == 0)
	{
		DrawStringByStr( pListBox->Block.left,pListBox->Block.top,"NO MENU ITEM",PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_8);
		return;
	}
	// ��ʾ�˵�
	start =pListBox->CurItem/pListBox->MaxShowLines* (pListBox->MaxShowLines);
	end   = start + pListBox->MaxShowLines-1;
	if(end>=pListBox->ItemCount)
		end = pListBox->ItemCount-1;

	for( i = start; i <= end; i++)
	{
		row=i-start;
		//DrawStringByStr(pMenu->Base.Block.left,pMenu->Base.Block.top+row*16,"." ,PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_8);
		snprintf(szTxt,sizeof(szTxt),"%d",row+start+1);
	//	DrawStringByStr( LCD_WIDTH>>1,32,szTxt,PEN_COPY,ALIGN_CENTER,LCD_EN_FONT_8_8);
		DrawStringByStr( pListBox->Block.left+MENU_OFFSET+16,pListBox->Block.top+row*16,szTxt,PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_16);

		// ������ʾ�˵�ѡ��
		if( i== pListBox->CurItem)
		{
			//��ʾС��
			DrawIcon(pListBox->Block.left+MENU_OFFSET ,pListBox->Block.top+row*16,ID_ICON_HAND, PEN_COPY);
			// ��ʾ�˵�����
		//	DrawStringById(pListBox->Block.left+MENU_OFFSET+32,pListBox->Block.top+row*16,pMenu->MenuLink[i].nResourceID, PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_16);
			SetGuiRect(&rcBlock,pListBox->Block.left+MENU_OFFSET+24,pListBox->Block.top+row*16,pListBox->Block.right-MENU_OFFSET,pListBox->Block.top+(row+1)*16-1);
			ReverseClrRect(&rcBlock);// ��ʾ�ڿ�	
	 	}
		else
		{
			//С��λ��
		//	SetGuiRect(&rcBlock,pMenu->Base.Block.left+MENU_OFFSET,pMenu->Base.Block.top+row*16,pMenu->Base.Block.left+MENU_OFFSET+16 ,pMenu->Base.Block.top+(row+1)*16-1);
		//	ClrRectScreenBuf(&rcBlock,COLOR_BK);
			// ��ʾ�˵�����
		//	SetGuiRect(&rcBlock,pMenu->Base.Block.left+MENU_OFFSET+24,pMenu->Base.Block.top+row*16,pMenu->Base.Block.right-MENU_OFFSET,pMenu->Base.Block.top+(row+1)*16-1);
		//	ClrRectScreenBuf(&rcBlock,COLOR_BK);
		//	DrawStringById(pMenu->Base.Block.left+MENU_OFFSET+32,pMenu->Base.Block.top+row*16,pMenu->MenuLink[i].nResourceID, PEN_COPY, ALIGN_LEFT,LCD_EN_FONT_8_16);
		}
	} 
// 	if(pMenu->ShowScrollBar)
// 	{
// 		DispScrollBar(pMenu);
// 	}
	InvalidateScreen(FALSE);
}
 