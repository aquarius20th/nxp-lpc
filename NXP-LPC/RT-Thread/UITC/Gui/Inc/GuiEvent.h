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


#define QS_NOTIFYMSG        0x10000000
 
#define QS_POSTMSG          0x40000000
#define QS_QUIT             0x80000000
#define QS_INPUT            0x01000000
#define QS_PAINT            0x02000000
#define QS_TIMER            0x0000FFFF
#define QS_EMPTY            0x00000000

 
/**
 * \def PM_NOREMOVE
 *
 * \sa PeekMessage PeekMessageEx
 */
#define PM_NOREMOVE     0x0000

/**
 * \def PM_REMOVE
 *
 * \sa PeekMessage PeekMessageEx PeekPostMessage
 */
#define PM_REMOVE       0x0001

/**
 * \def PM_NOYIELD
 *
 * \sa PeekMessage PeekMessageEx PeekPostMessage
 */
#define PM_NOYIELD      0x0002

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


//��ʼ����Ϣ����
INT8U InitGuiEventQueue( void );

INT8U SendScreenEvnent( GUI_HWND hWnd,INT32U Msg,INT32U wParam,INT32U lParam );
INT8U PostEvnent( GUI_HWND hWnd,INT32U Msg,INT32U wParam,INT32U lParam ,INT8U bNoCheck);

//���ڿؼ��򸸴����ʼ���Ϣ-֪ͨ��Ϣ
INT32U SendNotifyEvent(GUI_HWND hScr,INT32U Msg,INT32U WParam,INT32U LParam);




INT8U PostEventToGuiTask(  GuiEvent * pEvent );
INT8U GuiTaskEventRecv( GuiEvent * pEvent  );
INT8U HandleTaskEvent(  GuiEvent * pEvent );


#ifndef GUI_EVENT_DEF
#define  GUI_EVENT_DEF \
	INT32U Msg;\
	GUI_WPARAM WParam;\
	GUI_LPARAM LParam;\
	INT32U Flag;\
	GUI_HWND Handle;\
	INT32U  Time;	
#endif
