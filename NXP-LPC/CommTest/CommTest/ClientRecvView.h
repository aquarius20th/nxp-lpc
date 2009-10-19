#pragma once
#include "afxwin.h"

class CPacket;
class CPacketGridCtrl : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CPacketGridCtrl)

public:
	CPacketGridCtrl();
	virtual ~CPacketGridCtrl();

	CBCGPGridRow * AddEmptyRow ( BOOL bAllowEdit = FALSE ,BOOL bSetAutoID = TRUE);
	CBCGPGridRow * AddPacketRow ( CPacket *pPacket  );
	CBCGPGridRow* CreateNewRow ();
	CBCGPGridRow* GetHeadRow ();
	CBCGPGridRow* GetTailRow ();

protected:

#ifdef _DEBUG
	int AddRowEx (CBCGPGridRow* pItem );
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
 
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

// CClientRecvView ������ͼ
class CPacketDecodeFrm;
class CClientRecvView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CClientRecvView)

protected:
	CClientRecvView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientRecvView();

public:
	enum { IDD = IDD_DLG_RECV };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CPacketGridCtrl		m_wndGrid;

	CPacketDecodeFrm    *m_pDecodeFrm;

	void LoadPacket( );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonClearRecv();
	afx_msg void OnTimer(UINT_PTR nIDEvent); 
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnPacketDecode();
};


