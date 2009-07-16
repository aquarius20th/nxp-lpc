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
#include "includes.h" 
#include "GuiConst.h"
#include "CtrlBase.h"
#include "global.h"
#include "DC.h"


//��������
static void EraseBackground(CCtrlBase *pCtrlbase)
{
	DrawBlockRect(& pCtrlbase->Block,COLOR_BK);
}














//EDITBOX �ڲ�˽�нӿ�


static INT32U GetValue(CEditBox *pEditBox)
{
	INT32U nValue=0;
	INT32U index=0;
	INT32U i = 0;
	if (pEditBox == NULL)
		return -1;

	if(pEditBox->Type==EDIT_TYPE_NUMBER)
	{		
		for ( i=0;i<MAX_CHARNUMBER;i++) 
		{
			if(pEditBox->NumberChar[i].type==CHAR_NUMBER)
			{
				nValue+=(pEditBox->NumberChar[i].ch-'0')*TenMultiple[index];
				index++;
			}
			else if(pEditBox->NumberChar[i].type==CHAR_SIGN)
			{
				if(pEditBox->NumberChar[i].ch=='-')
				{
					nValue=0-nValue;	
				}

				break;
			}
			else if(pEditBox->NumberChar[i].type==CHAR_NONE)
			{
				break;
			}
		}

		return nValue;
	}
	else if(pEditBox->Type==EDIT_TYPE_ENUM)
	{
		return pEditBox->m_pSEnum->pSValue[pEditBox->m_nEnumIndex].n;
	}
	return 0;
}
// ��Ч�Լ��
static INT8U DDX(CEditBox *pEditBox)
{
	if (pEditBox == NULL)
		return FALSE;

	pEditBox->m_nValue = GetValue(pEditBox);

	if(pEditBox->Type==EDIT_TYPE_NUMBER)
	{
		if((pEditBox->m_nValue>pEditBox->m_nMax) || (pEditBox->m_nValue<pEditBox->m_nMin))
			return FALSE;
		else
			return TRUE;
	}
	else if (pEditBox->Type==EDIT_TYPE_ENUM)
	{
		if((pEditBox->m_nEnumIndex>pEditBox->m_pSEnum->count) || (pEditBox->m_nEnumIndex<0))
			return FALSE;
		else
			return TRUE;
	}
	return FALSE;
}

extern INT8U  GetValueInt(CEditBox *pEditBox,INT32U *pValue)
{
	INT8U bValid= FALSE;
	
	if (pEditBox == NULL || pValue == NULL )
	{
		return FALSE;
	}

	bValid= DDX(pEditBox);
	*pValue = pEditBox->m_nValue;
	return bValid;
}


extern void SetEditable(CEditBox *pEditBox,INT8U bEditable)
{
	if (pEditBox)
	{
		pEditBox->m_bEditable = bEditable;
		if (pEditBox->Base.pfnMessage)
		{
			pEditBox->Base.pfnMessage(LCD_WM_INI, NULL);
		}
	}
}


 


 
static __inline CMenuData * GetItem(CLcdMenu *pMenu,INT16U nItemIndex) 
{
	if (pMenu)
	{
		return & pMenu->MenuLink[nItemIndex];
	}
	else
		return NULL;
}

static __inline void SetItemData(CLcdMenu *pMenu,INT16U nItemIndex, INT32U nItemData)
{
	if (pMenu == NULL)
		return;

	if(nItemIndex < pMenu->MenuCount)
	{
		pMenu->MenuLink[nItemIndex].nItemData=nItemData;
	}
}

static __inline INT32U  GetItemData(CLcdMenu *pMenu,INT16U nItemIndex) 
{
	if (pMenu)
	{
		return pMenu->MenuLink[nItemIndex].nItemData;
	}
	else 
		return 0;
}

extern INT16U GetCurrentMenuID(CLcdMenu *pMenu) 
{
	CMenuData menu ;
	if (pMenu)
	{
		menu =* GetItem(pMenu,pMenu->CurrentItem );
		return menu.nMenuID;
	}
	return 0;
}

extern void SetCurrentItem(CLcdMenu *pMenu,INT16U nItem)
{
	if (pMenu && nItem<pMenu->MenuCount)
	{
		pMenu->CurrentItem = nItem;
	}
}


extern void AddItemPtr(CLcdMenu *pMenu, const CMenuData * pMenuItem)
{
	if (pMenu == NULL || pMenuItem == NULL )
		return;
	if (pMenu->MenuCount>=MAX_MENU_ITEMS)
		return;
 
	pMenu->MenuLink[pMenu->MenuCount++] = *pMenuItem;
	return;
}

extern void AddItemID(CLcdMenu *pMenu,INT16U nMenuID, INT16U nResourceID)
{
	CMenuData Item;

	if (pMenu == NULL )
		return;
	if (pMenu->MenuCount>=MAX_MENU_ITEMS)
		return;

	Item.nMenuID=nMenuID;
	Item.nResourceID=nResourceID;
	Item.nItemData=0;
	AddItemPtr(pMenu,&Item);
}

extern void AddItems(CLcdMenu *pMenu, const CMenuData Items[], INT16U nItemCount)
{
	INT16U i = 0;

	for ( i=0;i<nItemCount;i++)
	{
		AddItemPtr(pMenu, &Items[i]);
	}
}

/*********************************************************************************************************
** ��������: DispMenu
** ��������: DispMenu
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
static void DispMenu(CLcdMenu *pMenu)
{
	INT8U i,start,end;

	if (pMenu == NULL)
		return;

	ClearScreen();

	if(pMenu->MenuCount == 0)
	{
		DrawStringByStr( pMenu->Base.Block.left,pMenu->Base.Block.top,"NO MENU ITEM",PEN_COPY,ALIGN_LEFT,LCD_EN_FONT_8_8);
		return;
	}

}