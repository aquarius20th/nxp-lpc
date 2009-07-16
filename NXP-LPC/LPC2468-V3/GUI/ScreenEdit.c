/****************************************Copyright (c)**************************************************
**                             �ṩ�༭���ܣ���Ϣ����ʾ���ܵĴ���         
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
#include "ScreenEdit.h"
#include "global.h"


static __inline void SetState(CScreenEdit *pScreenEdit,INT16U nState)
{
	if (pScreenEdit)
	{
		pScreenEdit->m_nState |=nState;
	}
}
static __inline void ClrState(CScreenEdit *pScreenEdit,INT16U nState)
{
	if (pScreenEdit)
	{
		pScreenEdit->m_nState &= ~nState ;
	}
}

static void EnableEdit(CScreenEdit *pScreenEdit,INT8U bEdit)
{
	if (pScreenEdit)
	{
		if(bEdit)
		{
			SetState(pScreenEdit,STATE_EDIT);
		}
		else
		{
			ClrState(pScreenEdit,STATE_EDIT);
		}

//		m_EditBox.SetEditable(bEdit);

	}
}

 