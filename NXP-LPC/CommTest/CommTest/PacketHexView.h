#pragma once

#include "XTHexEdit.h"


// CPacketHexView ��ͼ

class CPacketHexView : public CView
{
	DECLARE_DYNCREATE(CPacketHexView)

protected:
	CPacketHexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPacketHexView();

public:
	CXTHexEdit  m_wndEdit;

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
};


