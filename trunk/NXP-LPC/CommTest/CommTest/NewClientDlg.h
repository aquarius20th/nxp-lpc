#pragma once


// CNewClientDlg �Ի���

class CNewClientDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CNewClientDlg)

public:
	CNewClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewClientDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NEW_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
