#pragma once


// CClientTabView ��ͼ

class CClientTabView : public CBCGPTabView
{
	DECLARE_DYNCREATE(CClientTabView)

protected:
	CClientTabView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientTabView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


