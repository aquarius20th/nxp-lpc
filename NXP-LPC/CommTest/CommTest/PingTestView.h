#pragma once

#include "CommMsg.h"

// CPingTestView ��ͼ
class CPingMsgGridCtrl : public CBCGPGridCtrl
{
public:
	CBCGPGridRow * AddMsgRow ( CPingMsg *pMsg  );
	CBCGPGridRow* CreateNewRow ();
	CBCGPGridRow* GetHeadRow ();
	CBCGPGridRow* GetTailRow ();
protected:
#ifdef _DEBUG
	int AddRowEx (CBCGPGridRow* pItem );
#endif
};

class CPingTestView : public CView
{
	DECLARE_DYNCREATE(CPingTestView)

protected:
	CPingTestView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPingTestView();

	CPingMsgGridCtrl  m_wndGrid;

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void LoadPingEvent( );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


