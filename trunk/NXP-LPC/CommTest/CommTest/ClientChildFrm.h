
// ClientChildFrame.h : CClientChildFrame ��Ľӿ�
//

#pragma once

#include "SplitterWndExt.h"
 
class CClientChildFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CClientChildFrame)
public:
	CClientChildFrame();

// ����
public:
	CSplitterWndExt  m_wndSplitter1;
	CBCGPSplitterWnd  m_wndSplitter2;

// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow);

// ʵ��
public:
	virtual ~CClientChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
