// NewClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "NewClientDlg.h"


// CNewClientDlg �Ի���

IMPLEMENT_DYNAMIC(CNewClientDlg, CBCGPDialog)

CNewClientDlg::CNewClientDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CNewClientDlg::IDD, pParent)
	, m_nDestPort(0)
	, m_nLocalPort(0)
{
	m_dwDestIp = 0;
}

CNewClientDlg::~CNewClientDlg()
{
}

void CNewClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_DEST, m_ctlDestIp);
	DDX_Text(pDX, IDC_EDIT_DEST_PORT, m_nDestPort);
	DDX_Text(pDX, IDC_EDIT_LOCAL_PORT, m_nLocalPort); 
}


BEGIN_MESSAGE_MAP(CNewClientDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CNewClientDlg ��Ϣ�������

BOOL CNewClientDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	EnableVisualManagerStyle();

	DWORD dwIp = htonl( inet_addr("192.9.200.101"));
	m_ctlDestIp.SetAddress(dwIp);
	m_nDestPort = 505;


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CNewClientDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);

 	m_ctlDestIp.GetAddress(m_dwDestIp);

	CBCGPDialog::OnOK();
}
