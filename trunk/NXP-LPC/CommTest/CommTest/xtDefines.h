/************************************************************************************/
/*     �ļ���:	Defines.h															*/
/*     ����:	����TabView����Ҫ�ĳ����ͺ궨��										*/
/*     ����:    snowfly																*/
/*     ʱ��:    2004.8.1															*/
/************************************************************************************/
#ifndef		_DEFINES_H
#define     _DEFINES_H


const UINT TVIS_FOCUSED            = 0x0001;  // For determining tree item focus state.


// �Զ�����Ϣ��
const UINT TCN_XT_SELCHANGE = (WM_USER + 2520); 
const UINT TCN_XT_SELCHANGING = (WM_USER + 2521); 
const UINT XTWM_INITIAL_UPDATE = (WM_USER + 2526); 


// һ��궨��
//////////////////////////////////////////////////////////////////////
// Summary: This macro will free the dynamically allocated memory specified by 
//			'p' and set its value to NULL. 
#define SAFE_DELETE(p)  if(p) { delete p; p = NULL; }
//#define _delete			SAFE_DELETE			 

//////////////////////////////////////////////////////////////////////
// Summary: This macro will free the dynamically allocated memory for an array 
//			specified by 'p' and set its value to NULL. 
#define SAFE_DELETE_AR(p)	if(p) { delete [] p; p = NULL; }
#define _deleteArray		SAFE_DELETE_AR

//////////////////////////////////////////////////////////////////////
// Summary: This macro will release the resources for the COM object specified 
//			by 'p' and set its value to NULL. 
#define SAFE_RELEASE(p)		if(p) { (p)->Release(); (p)=NULL; }

#define COLOR_GRADIENTACTIVECAPTION     27

//:Ignore

#endif