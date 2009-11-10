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

#ifndef SCREEN_BASE_H
#define	SCREEN_BASE_H
#include "guiconst.h"
#include "global.h"
//#include "Message.h"


typedef struct SCR_EVENT
{
	INT32U Msg;
	INT32U WParam;
	INT32U LParam;
	INT32U Flag;
}SCR_EVENT ,*pSCR_EVENT;

//��������
typedef  void  (*fnOnKeyDown)( INT16U keyCode);
//��Ϣ�����麯��
typedef  void   (*fnOnMessage)(INT32U msg, INT32U param);
//��ʼ������
typedef  void    (*fnInit)();
//�˳�ʱ����
typedef  void	(*fnDestory)();
//��Ϣ֪ͨ
typedef  void	(*fnOnNotify)(INT32U nf);

#define  MAX_ENENT_CNT  4

typedef struct CScreenBase 
{
	INT8U        ParentID;    //������ID��
	INT8U        CurrentID;   //������ID��
	INT16U       ScreenName; //����������

	//�ص�����
	fnOnKeyDown pfnKeyDown;
	fnOnMessage pfnMessage;
	fnInit      pfnInit;
	fnDestory   pfnDestory;
	fnOnNotify  pfnOnNotify;

	//���������¼�

//	UEVENT  Event[MAX_ENENT_CNT];
}CScreenBase;

//α�ṹ
typedef struct CScreen
{
	CScreenBase Base;
}CScreen;


extern void InitScreenBase(CScreenBase *pBase);

extern void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName );



//�¼�
extern INT8U HandleEvent(CScreenBase *pScreen);
extern INT8U PostEvent(CScreenBase *pScreen,INT32U msg,INT32U param);
extern INT8U SendEvent(CScreenBase *pScreen,INT32U msg,INT32U param);
extern void  ClearEvent(CScreenBase *pScreen);




//�������
typedef struct CScreenMgr
{
	CScreen *m_ScreenArray[MAXSCREEN];   // ����ָ������
	INT16U 	     ScreensCnt;	          // ��������

}CScreenMgr;

extern void InitScreenMgr( CScreenMgr *pMgr );




// ����һ���µ���Ļ���������
extern INT8U  AppendScreen(CScreenMgr *pMgr,CScreen *pScreen);
// �ж����ScreenID��Ļ�Ƿ��ڼ���״̬
extern INT8U IsScreenActived(CScreenMgr *pMgr ,INT8U nScreenID) ;
// �õ�ָ�����ScreenID��Ļ��ָ��
extern  CScreen* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID);
// �õ���ǰ��Ļ��ָ��
extern CScreen* GetCurrentScreenPtr(CScreenMgr *pMgr);
// �õ���������
extern INT16U GetScreensCnt(CScreenMgr *pMgr) ;

// �л������ScreenID��Ļ
extern void  SwitchScreen(CScreenMgr *pMgr,INT8U nScreenID);


extern void DrawScreenCaption( CScreen  *pScreen, INT16U nTotal, INT16U nCur);
extern void DrawScreenStatusBar( );

#endif
