// NewSvrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "NewSvrDlg.h"
#include "UEServer.h"

// CNewSvrDlg �Ի���

IMPLEMENT_DYNAMIC(CNewSvrDlg, CBCGPDialog)

CNewSvrDlg::CNewSvrDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CNewSvrDlg::IDD, pParent)
	, m_nSvrPortNum(0)
{

}

CNewSvrDlg::~CNewSvrDlg()
{
}

void CNewSvrDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SVR_PORTNUM, m_nSvrPortNum);
}


BEGIN_MESSAGE_MAP(CNewSvrDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CNewSvrDlg ��Ϣ�������

BOOL CNewSvrDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	EnableVisualManagerStyle();

	std::list<std::string> ip_list;
	bool bRet = false;

	bRet = CUEServer::GetIpList(ip_list);


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
