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
#include "CtrlBase.h" 
#include "dc.h"


//��������
void EraseBackground(CCtrlBase *pCtrlbase)
{
	SetScreenRect(& pCtrlbase->Block,GUI_COLOR_BK);
 //	DrawBlockRect(& pCtrlbase->Block,GUI_COLOR_BK);
}

void InitCtrlBase( CCtrlBase *pBase )
{
	if (pBase)
	{
 		memset( &pBase->Block,0,sizeof(CGuiRect));	    	//����ؼ�λ��

		pBase->pfnCreate = NULL;
		pBase->pfnDestory= NULL;
		//�ص�����
		pBase->pfnKeyDown= NULL;
		pBase->pfnMessage= NULL;
	}
}
/*********************************************************************************************************
** ��������: OnCtrlKeyDown
** ��������: OnCtrlKeyDown
**
** ���������� ��Ӧ������Ϣ
**
** �䡡��:  CCtrlBase * pBase
** �䡡��:  INT16U KeyCode
**          
** �䡡��:   extern void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��4��24��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void OnCtrlKeyDown( CCtrlBase  *pCtrl,INT16U KeyCode )
{
	if (pCtrl == NULL)
		return;
	if (pCtrl->pfnKeyDown)
	{
		pCtrl->pfnKeyDown(pCtrl, KeyCode );
	}
}
void OnCtrlMsg( CCtrlBase  *pCtrl,INT32U msg, INT32U param  )
{
	if (pCtrl == NULL)
		return;

	if (pCtrl->pfnMessage)
	{
		pCtrl->pfnMessage( pCtrl,msg,param );
	}
} 


INT8U DefaultControlProc (GUI_HWND hWnd, INT32U message, INT32U wParam, INT32U lParam)
{

	return TRUE;
}
