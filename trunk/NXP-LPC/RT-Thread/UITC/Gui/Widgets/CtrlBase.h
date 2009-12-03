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
 
typedef struct CTRL_BASE CCtrlBase;

//����
typedef void (*ctrl_ctor)(CCtrlBase *object);
//����
typedef void (*ctrl_dtor)(CCtrlBase *object);

typedef  void    (*fnInitCtrl)(CCtrlBase *pCtrl,INT32U wParam, INT32U lParam);

typedef  void    (*fnCreateCtrl)(CCtrlBase *pCtrl);

//��������
typedef  void  (*fnOnKeyDownCtrl)(CCtrlBase *pCtrl, INT16U keyCode);
//��Ϣ�����麯��
typedef  void   (*fnOnMessageCtrl)(CCtrlBase *pCtrl,INT32U msg, INT32U param);
//�˳�ʱ����
typedef  void	(*fnDestoryCtrl)(CCtrlBase *pCtrl); 

struct CTRL_BASE 
{
	/* constructor and destructor */
	ctrl_ctor Ctor;
	ctrl_dtor Dtor;

	GUI_HANDLE   Handle;

 	CGuiRect	    Block;	    	//����ؼ�λ��

	fnCreateCtrl   pfnCreate;
	fnDestoryCtrl  pfnDestory;
	//�ص�����
	fnOnKeyDownCtrl pfnKeyDown;
	fnOnMessageCtrl pfnMessage;	
};

__inline GUI_HANDLE GetCtrlHandle( CCtrlBase *pCtrl )
{
	return pCtrl->Handle;
}

void EraseBackground(CCtrlBase *pCtrlbase);

#ifndef CTRL_BASE_DEF
#define CTRL_BASE_DEF   \
	ctrl_ctor Ctor; \
	ctrl_dtor Dtor;\
	GUI_HANDLE   Handle; \
	CGuiRect	    Block;     \
	fnInitCtrl      pfnInit;\
	fnCreateCtrl    pfnCreate;\
	fnDestoryCtrl   pfnDestory;\
	fnOnKeyDownCtrl pfnKeyDown;\
	fnOnMessageCtrl pfnMessage;
#endif
 
