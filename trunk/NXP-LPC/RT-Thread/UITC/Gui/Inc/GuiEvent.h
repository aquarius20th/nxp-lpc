/****************************************Copyright (c)**************************************************
**                                   ��Ϣ����
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

enum GUI_EVENT_TYPE
{
	GUI_EVENT_INIT=10,                 // ��ʼ��
	GUI_EVENT_CREATE,			/* create a window 		*/
	GUI_EVENT_DESTROY,		   /* destroy a window 	*/

	GUI_EVENT_REDRAW,                // ��������ˢ��
	GUI_EVENT_TIMER,                 // ��ʱ����Ϣ
	GUI_EVENT_PAINT,                 // ���ͻ���
	GUI_EVENT_NCPAINT,               // �ǿͻ��� ,�������
	GUI_EVENT_KEYDOWN,                // ������Ϣ
 	GUI_EVENT_USER,              /* user command 		*/

};
typedef enum GUI_EVENT_TYPE GuiEventType;
struct SCREEN_BASE;

struct GUI_EVENT
{
	INT32U Msg;
	GUI_WPARAM WParam;
	GUI_LPARAM LParam;
	INT32U Flag;
	GUI_HWND Handle;
	INT32U  Time;
};

typedef struct GUI_EVENT GuiEvent;

#ifndef GUI_EVENT_DEF
#define  GUI_EVENT_DEF \
	INT32U Msg;\
	GUI_WPARAM WParam;\
	GUI_LPARAM LParam;\
	INT32U Flag;\
	GUI_HWND Handle;\
	INT32U  Time;	
#endif


struct GUI_EVENT_NODE
{
	GUI_EVENT_DEF
	struct GuiListNode NextNode;
};

typedef struct GUI_EVENT_NODE GuiEventNode;

//��ʼ����Ϣ����
INT8U InitGuiEventQueue( void );

INT8U SendScreenEvnent( GUI_HWND *pWnd,INT32U Msg,INT32U wParam,INT32U lParam );
INT8U PostScreenEvnent( GUI_HWND *pWnd,INT32U Msg,INT32U wParam,INT32U lParam ,INT8U bNoCheck);
INT8U HandleScreenEvent(struct SCREEN_BASE *pScr);

//���ڿؼ��򸸴����ʼ���Ϣ-֪ͨ��Ϣ
INT8U SendNotifyEvent(GUI_HWND hScr,INT32U Msg,INT32U WParam,INT32U LParam);




INT8U PostEventToGuiTask(  GuiEvent * pEvent );
INT8U GuiTaskEventRecv( GuiEvent * pEvent  );
INT8U HandleTaskEvent(  GuiEvent * pEvent );

