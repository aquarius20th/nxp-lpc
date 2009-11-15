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

#define MAX_SCR_SIZE 1024

/** Casts the function pointer to an rtgui_constructor */
#define SCR_CTOR(constructor)                ((scr_ctor)(constructor))
/** Casts the function pointer to an rtgui_constructor */
#define SCR_DTOR(destructor)                 ((scr_dtor)(destructor))

struct SCREEN_BASE;
typedef struct SCREEN_BASE CScreenBase;

//����
typedef void (*scr_ctor)(CScreenBase *object);
//����
typedef void (*scr_dtor)(CScreenBase *object);

//��Ϣ����
//��������
typedef  void  (*fnOnKeyDown)(CScreenBase *pScreen, INT32U keyCode);
//��Ϣ�����麯��
typedef  void   (*fnOnMessage)(CScreenBase *pScreen,INT32U msg, INT32U param);
//��ʼ������
typedef  void    (*fnInit)(CScreenBase *pScreen);
//�˳�ʱ����
typedef  void	(*fnDestory)(CScreenBase *pScreen);
//��Ϣ֪ͨ-֪ͨ�ؼ�
typedef  void	(*fnOnNotify)(CScreenBase *pScreen,INT32U nf);

 
struct SCREEN_BASE
{
	INT8U        ParentID;    //������ID��
	INT8U        CurrentID;   //������ID��
	INT16U       ScreenName; //����������  �ַ�����ID
	gui_list_t    List;

	/* constructor and destructor */
	scr_ctor Ctor;
	scr_dtor Dtor;

	//�ص�����
	fnOnKeyDown pfnKeyDown;
	fnOnMessage pfnMessage;
	fnInit      pfnInit;
	fnDestory   pfnDestory;
	fnOnNotify  pfnOnNotify;

	/* size of type */
	INT32U  Size;
};

//����һ����Ļ
CScreenBase * CreateScreen( INT32U nSize ,scr_ctor ctor,scr_dtor dtor);
//��̬��ʼ��һ����Ļ
void InitScreen(CScreenBase *pScr, scr_ctor ctor,scr_dtor dtor );
void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName );

#ifndef SCR_BASE_DEF
#define SCR_BASE_DEF   \
		INT8U        ParentID;     \
		INT8U        CurrentID;    \
		INT16U       ScreenName;   \
		gui_list_t    List;        \
	 	scr_ctor Ctor; \
		scr_dtor Dtor;\
		fnOnKeyDown pfnKeyDown;\
		fnOnMessage pfnMessage;\
		fnInit      pfnInit;\
		fnDestory   pfnDestory;\
		fnOnNotify  pfnOnNotify;\
	 	INT32U  Size;
#endif


