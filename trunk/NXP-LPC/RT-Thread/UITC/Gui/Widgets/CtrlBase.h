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

#pragma once
#include "GuiDef.h"
#include "ScreenBase.h"
 

#define MAX_CTRL_SIZE 1024

typedef struct CTRL_BASE CCtrlBase;
struct SCREEN_BASE;
//����
typedef void (*ctrl_ctor)(CCtrlBase *object);
//����
typedef void (*ctrl_dtor)(CCtrlBase *object);

struct CTRL_BASE 
{
	/* constructor and destructor */
	ctrl_ctor Ctor;
	ctrl_dtor Dtor;
	INT8U   WinType;       
	INT8U   Style;
 	INT16U  ExStyle;

	INT32U  ID; //��ԴID

	GUI_HWND   Handle;
	GUI_HWND   ScreenHandle;
	GUI_HWND   ParentCtrlHandle;

 	CGuiRect   Block;	    	//����ؼ�λ��
	INT32U (*ControlProc)(GUI_HWND, INT32U, GUI_WPARAM, GUI_LPARAM);

	INT32U  Size;
};

__inline GUI_HWND GetCtrlHandle( CCtrlBase *pCtrl )
{
	if(pCtrl)
		return pCtrl->Handle;
	return HWND_NULL;
}

//��̬����һ���ؼ�
CCtrlBase * CreateControl( INT32U nSize ,ctrl_ctor ctor,ctrl_dtor dtor);
//��̬��ʼ��һ���ؼ�
void InitControl(CCtrlBase * pCtrl, ctrl_ctor ctor,ctrl_dtor dtor );

#define GET_CTRL_PTR(hWnd)   ((CCtrlBase *)hWnd) 

INT8U IsControl( GUI_HWND hWnd );

void EraseBackground(CCtrlBase *pCtrlbase);



#ifndef CTRL_BASE_DEF
#define CTRL_BASE_DEF   \
	ctrl_ctor Ctor; \
	ctrl_dtor Dtor;\
	INT8U  WinType;  \
	INT8U   Style; \
	INT16U  ExStyle; \
	INT32U  ID;\
	GUI_HWND   Handle; \
	GUI_HWND   ScreenHandle; \
	GUI_HWND   ParentCtrlHandle; \
	CGuiRect	    Block;     \
	INT32U (*ControlProc)(GUI_HWND, INT32U, GUI_WPARAM, GUI_LPARAM);\
	INT32U  Size;
#endif
 
