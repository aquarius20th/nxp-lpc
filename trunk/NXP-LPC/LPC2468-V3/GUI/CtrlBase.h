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
#ifndef CTRL_BASE_H
#define	CTRL_BASE_H
#include "guiconst.h"
#include "global.h"


typedef struct CCtrlBase 
{
	INT8U           Focus;       //�Ƿ�۽�����ǰ�ؼ�
	LCDRECT			Block;	    	//����ؼ�λ��

	fnCreate   pfnCreate;
	fnDestory  pfnDestory;
	//�ص�����
	fnOnKeyDown pfnKeyDown;
	fnOnMessage pfnMessage;
	
}CCtrlBase;



//EDIT�ؼ������� ������/��������
typedef enum EDIT_TYPE
{
	EDIT_TYPE_NUMBER,
	EDIT_TYPE_ENUM
}EDIT_TYPE;

typedef struct CNumberChar
{
	char  ch;	//�ô��ַ�
	INT8U type;	//λ������
}CNumberChar;

typedef enum EVENT_EDITBOX 
{
	EVENT_REDRAW,	//�ؼ��ػ�
	EVENT_DRAWRECT	//��ˢ�޸�
}EVENT_EDITBOX;

/*�����Ϳؼ���Ҫ�õ��ı���*/
//���ַ�λ�õ���������
typedef enum CHAR_IDT
{
	CHAR_NONE,		//��Чλ��
	CHAR_SIGN,		//����λ
	CHAR_NUMBER,	//����λ
	CHAR_DOT		//С����λ
}CHAR_IDT;


//ö�����ͣ��ṹ��������
typedef struct CSValue
{
	INT16U	NameID;			//ö������
	INT16U	n;				//ֵ
}CSValue;//���������͵Ķ�ֵ������ֵ����

typedef struct CSEnum
{
	INT16U	count;				//ö�����͸���
	const CSValue * pSValue;	//ָ��ö�����������ָ��
	INT16U def;					//Ĭ��ֵ
}CSEnum;

#define MAX_CHARNUMBER 12

typedef struct CEditBox
{
	CCtrlBase  Base;

	//////////////////////////////////////////////////////////////////////////
	/*EDIT�ؼ��õ��ı���*/
	CSEnum  *m_pSEnum;
	INT32U   m_nValue;
	INT16U   m_nEnumIndex;
	INT32U   m_nMax;
	INT32U   m_nMin;
	INT8U   m_nPoint;



	INT8U   Type;		//EDIT�ؼ�����

	CNumberChar NumberChar[MAX_CHARNUMBER];
	INT8U       NumberCharCur;		//�۽���


	INT8U  m_bEditable;             // �Ƿ�ɱ༭
}CEditBox;

// �õ��༭�����ֵ��������ֵ����Ч��
//extern INT8U  GetValue(CEditBox *pEditBox , INT32U *pValue);
extern INT8U  GetValueInt(CEditBox *pEditBox,INT32U *pValue);
extern void SetEditable(CEditBox *pEditBox,INT8U bEditable);


typedef struct CEditBoxEx
{
	CEditBox BaseBox;


	INT8U    m_bShowToolTip;
	INT8U    m_bShowCaption;
	INT8U    m_bShowUnit;
	INT16U   m_nCaptionID;
	INT8U  *m_pUint;

}CEditBoxEx;




///////////////////////////////////////////////////////////////
//	��    �� : CLcdMenu
//	��    �� :  
//	��    �� : �˵��������ݽṹ
//	��    �� : �Բ˵����й���
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : 
//	ʱ    �� : 
//	��    ע : 
///////////////////////////////////////////////////////////////
#define MAX_MENU_ITEMS 0x30    // �˵������20���˵���

typedef struct  CLcdMenu
{
	CCtrlBase  Base;

//////////////////////////////////////////////////////////////////////////
	// �������ı���
	CMenuData  MenuLink[MAX_MENU_ITEMS]; //�˵�����
	INT16U     MenuCount;

	INT16U      MaxShowChars;           //�ÿؼ�����������ʾ���ַ���
	INT16U      MaxShowLines;           //�ÿؼ�����������ʾ������


	/*��̬������*/
	LCDRECT ScrollBarRect;		//������λ��
	INT8U   ShowScrollBar;		//�Ƿ���ʾ������
 
	INT16U   CurrentItem;		//��ǰ�۽���
}CLcdMenu;


extern void AddItemPtr(CLcdMenu *pMenu, const CMenuData * pMenuItem);

extern void AddItemID(CLcdMenu *pMenu,INT16U nMenuID, INT16U nResourceID);

extern void AddItems(CLcdMenu *pMenu,const  CMenuData Items[], INT16U nItemCount);



 

#endif
