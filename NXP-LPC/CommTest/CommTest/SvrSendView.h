
#pragma once
#include "afxwin.h"


// CSvrSendView ������ͼ

class CSvrSendView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CSvrSendView)

protected:
	CSvrSendView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSvrSendView();

public:
	enum { IDD = IDD_DLG_SVR_SEND };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


