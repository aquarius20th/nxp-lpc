#pragma once


// CNewSvrDlg �Ի���

class CNewSvrDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CNewSvrDlg)

public:
	CNewSvrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewSvrDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NEW_SVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	UINT m_nSvrPortNum;
protected:
	virtual void OnOK();
};
