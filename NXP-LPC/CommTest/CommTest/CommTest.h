
// CommTest.h : CommTest Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCommTestApp:
// �йش����ʵ�֣������ CommTest.cpp
//

class CCommTestApp : public CWinApp,
	public CBCGPWorkspace
{
public:
	CCommTestApp();


// ��д
public:
	virtual BOOL InitInstance();

	CMultiDocTemplate* m_pDocTemplate;
	CMultiDocTemplate* m_pPingDocTemplate;
	CMultiDocTemplate* m_pClientDocTemplate;
	CMultiDocTemplate* m_pSvrDocTemplate;


// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CCommTestApp theApp;
