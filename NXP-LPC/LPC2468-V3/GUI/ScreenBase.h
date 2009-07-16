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
#ifndef SCREEN_BASE_H
#define	SCREEN_BASE_H
#include "guiconst.h"
#include "global.h"





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
}CScreenBase;

extern void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName );


//�õ�/���ü���Ĵ���ID
extern INT8U   GetActiveWinID(void);
extern void    SetActiveWinID(const INT8U id);

//�õ�/���ñ����ڸ�����ID
extern INT8U GetFatherID(CScreenBase *pScreen);
extern void  SetFatherID(CScreenBase *pScreen, INT8U nID);



//�������
typedef struct CScreenMgr
{
	CScreenBase *m_ScreenArray[MAXSCREEN];   // ����ָ������
	INT16U 	     ScreensCnt;	          // ��������

}CScreenMgr;

extern void InitScreenMgr( CScreenMgr *pMgr );




// ����һ���µ���Ļ���������
extern INT8U  AppendScreen(CScreenMgr *pMgr,CScreenBase *pScreen);
// �ж����ScreenID��Ļ�Ƿ��ڼ���״̬
extern INT8U IsScreenActived(CScreenMgr *pMgr ,INT8U nScreenID) ;
// �õ�ָ�����ScreenID��Ļ��ָ��
extern  CScreenBase* GetScreenPtr(CScreenMgr *pMgr ,INT8U nScreenID);
// �õ���ǰ��Ļ��ָ��
extern CScreenBase* GetCurrentScreenPtr(CScreenMgr *pMgr);
// �õ���������
extern INT16U GetScreensCnt(CScreenMgr *pMgr) ;

// �л������ScreenID��Ļ
extern void  SwitchScreen(CScreenMgr *pMgr,INT8U nScreenID);

#endif
