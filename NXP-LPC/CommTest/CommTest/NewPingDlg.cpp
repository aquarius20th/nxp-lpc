// NewPingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "NewPingDlg.h"


// CNewPingDlg �Ի���

IMPLEMENT_DYNAMIC(CNewPingDlg, CBCGPDialog)

CNewPingDlg::CNewPingDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CNewPingDlg::IDD, pParent)
{

}

CNewPingDlg::~CNewPingDlg()
{
}

void CNewPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewPingDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CNewPingDlg ��Ϣ�������

BOOL CNewPingDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	 
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	EnableVisualManagerStyle();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
