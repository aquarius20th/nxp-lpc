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
#ifndef SCREEN_EXT_H
#define	SCREEN_EXT_H

typedef enum BRAND_STATE
{
	STATE_NORMAL=0,                       //һ����ʾ״̬
	STATE_COUNT                           //״̬���� 
}BRAND_STATE;

//	��    �� : ���������а汾��Ϣ����
//	��    �� : ��ʾ����ģ������ʱ��ʾ��˾�汾��Ϣ��LOGO
typedef struct CLogoScreen 
{
	CScreenBase  Base;

 

	INT8U   CurrentState;                       //��ǰ��ʾ״̬
	CLcdCursor Cursor[STATE_COUNT];   

	 
}CLogoScreen;

//
extern void InitLogoScreen(CLogoScreen *pScreenExt ); 

//	��    �� : Ĭ����ʾ����
//	��    �� : ѭ����ʾ������������״��
// ��ʾբ�ſ���/����
typedef struct CScreenDefault
{
	CScreenBase  Base;


	//������Ҫʹ�õĸ�����Դ
	INT8U   Toggle;                 //�л�ѭ����ʾ
	INT16U	CurrentTypeIndex;        //��ǰ��ʾ��ֵ������MeasDispType�е�����
	INT16U	CurrentMeasIndex;		//��ǰ��ʾ��ֵ��MeasDisp�е�����

}CScreenDefault;
 
extern void InitDefaultScreen(CScreenDefault *pScreenExt ); 

 
extern CLogoScreen      LogoScreen;       // �汾��������
extern CScreenDefault       defscreen;
 

#endif
