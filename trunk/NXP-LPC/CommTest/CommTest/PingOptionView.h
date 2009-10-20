#pragma once
#include "afxcmn.h"



// CPingOptionView ������ͼ

class CPingOptionView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CPingOptionView)

protected:
	CPingOptionView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPingOptionView();

public:
	enum { IDD = IDD_DLG_PING_OPTIONS };
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
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	CIPAddressCtrl m_wndDestIp;
	UINT m_nTaskCnt;
	UINT m_nPingDataSize;
	UINT m_nIntTime;
	BOOL m_bAutoDelay;
	afx_msg void OnBnClickedButtonPingStart();
};


