#pragma once


// CNewPingDlg �Ի���

class CNewPingDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CNewPingDlg)

public:
	CNewPingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPingDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NEW_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
