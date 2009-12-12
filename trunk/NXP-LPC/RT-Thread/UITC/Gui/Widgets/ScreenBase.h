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
#pragma  once
#include "applib.h"
#include "guilist.h"
#include "GuiDef.h"

#define MAX_SCR_SIZE 1024

struct SCREEN_BASE;
typedef struct SCREEN_BASE CScreenBase;

//����
typedef void (*scr_ctor)(CScreenBase *object);
//����
typedef void (*scr_dtor)(CScreenBase *object);

/** Casts the function pointer to an rtgui_constructor */
#define SCR_CTOR(constructor)                ((scr_ctor)(constructor))
/** Casts the function pointer to an rtgui_constructor */
#define SCR_DTOR(destructor)                 ((scr_dtor)(destructor))


typedef INT32U (* SCREENPROC)(GUI_HWND, INT32U, GUI_WPARAM, GUI_LPARAM);

#if 0
//��Ϣ����
//��������
typedef  void  (*fnOnKeyDown)(CScreenBase *pScreen, INT32U keyCode);
//��Ϣ�����麯��
typedef  void   (*fnOnMessage)(CScreenBase *pScreen,INT32U msg, INT32U param);
//��ʼ������
typedef  void    (*fnInit)(CScreenBase *pScreen,INT32U wParam, INT32U lParam);
//����
typedef  void    (*fnCreate)(CScreenBase *pScreen);
//�˳�ʱ����
typedef  void	(*fnDestory)(CScreenBase *pScreen);
//��Ϣ֪ͨ-֪ͨ�ؼ�
typedef  void	(*fnOnNotify)(CScreenBase *pScreen,INT32U nf);
#endif

 
struct SCREEN_BASE
{
	/* constructor and destructor */
	scr_ctor Ctor;
	scr_dtor Dtor;

	INT8U   WinType;          // the window type
	INT8U   Style;
	INT16U  ExtStyle;

	GUI_HWND   Handle;
	INT8U      ParentID;    //������ID��
	INT8U      CurrentID;   //������ID��
	INT16U     ScreenName; //����������  �ַ�����ID
	gui_list_t    List;
	INT32U (*ScreenProc)(GUI_HWND, INT32U, GUI_WPARAM, GUI_LPARAM); 
	/* size of type */
	INT32U  Size;
};

//��̬����һ����Ļ
CScreenBase * CreateScreen( INT32U nSize ,scr_ctor ctor,scr_dtor dtor);
//��̬��ʼ��һ����Ļ
void InitScreen(CScreenBase *pScr, scr_ctor ctor,scr_dtor dtor );

__inline GUI_HWND GetScreenHandle( CScreenBase *pScreen )
{
	if (pScreen) 
		return pScreen->Handle;	 
	return HWND_NULL;
}

void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName );
//���ñ���
void SetScreenTitle( void );

INT32U DefaultScreenProc (GUI_HWND hWnd, INT32U message, GUI_WPARAM wParam, GUI_LPARAM lParam);
 

#define GET_SCREEN_PTR(hWnd)   ((CScreenBase *)hWnd) 

INT8U IsScreen( GUI_HWND hWnd );


#ifndef SCR_BASE_DEF
#define SCR_BASE_DEF   \
	scr_ctor Ctor; \
	scr_dtor Dtor; \
	INT8U   WinType;  \
	INT8U   Style;   \
	INT16U  ExtStyle; \
	GUI_HWND   Handle; \
	INT8U        ParentID; \
	INT8U        CurrentID;   \
	INT16U       ScreenName; \
	gui_list_t    List; \
	INT32U (*ScreenProc)(GUI_HWND, INT32U, GUI_WPARAM, GUI_LPARAM); \
	INT32U  Size;
#endif

 

