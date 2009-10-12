#pragma once
#include "afxcmn.h"



// CClientOptionView ������ͼ

class CClientOptionView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CClientOptionView)

protected:
	CClientOptionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CClientOptionView();

public:
	enum { IDD = IDD_DLG_CLIENT_OPTIONS };
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CIPAddressCtrl m_wndDestIp;
	UINT m_nDestPortNum;
	BOOL m_bRandromLocalPort;
	UINT m_nLocalPortNum;
	int m_nProtocolType;
	afx_msg void OnBnClickedCheckLocalPort();
	virtual void OnInitialUpdate();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
 
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonReset();
	UINT m_nSendCnt;
	UINT m_nRecvCnt;
};


