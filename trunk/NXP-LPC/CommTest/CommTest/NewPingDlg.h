#pragma once
#include "afxcmn.h"


// CNewPingDlg �Ի���

class CNewPingDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CNewPingDlg)

public:
	CNewPingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPingDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NEW_PING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CIPAddressCtrl m_ctlDestIp;
	UINT m_nPingDataSize;
	DWORD m_dwDestIp;
protected:
	virtual void OnOK();
public:
	UINT m_nIntTime;
	UINT m_nTaskCnt;
	BOOL m_bAutoDelay;
};
