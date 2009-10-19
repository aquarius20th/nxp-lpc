// NewPingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "NewPingDlg.h"


// CNewPingDlg �Ի���

IMPLEMENT_DYNAMIC(CNewPingDlg, CBCGPDialog)

CNewPingDlg::CNewPingDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CNewPingDlg::IDD, pParent)
	, m_nPingDataSize(32)
{

}

CNewPingDlg::~CNewPingDlg()
{
}

void CNewPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_PING_DEST, m_ctlDestIp);
	DDX_Text(pDX, IDC_EDIT_PING_DATA_SIZE, m_nPingDataSize);
	DDV_MinMaxUInt(pDX, m_nPingDataSize, 32, 64000);
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

void CNewPingDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);

	m_ctlDestIp.GetAddress(m_dwDestIp);


	CBCGPDialog::OnOK();
}
