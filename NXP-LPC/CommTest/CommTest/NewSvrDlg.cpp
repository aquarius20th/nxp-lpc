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
	, m_nSvrPortNum(999)
{
//	m_dwLocalIp = 0;
	m_szLocalIp = _T("127.0.0.1");
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
	CComboBox *pBox =(CComboBox *) GetDlgItem(IDC_COMBO_HOST_IP);
	ASSERT(pBox);
	if(pBox)
	{
		pBox->ResetContent();
		CString szTxt;

		if(bRet && ip_list.size())
		{
			std::list <std::string>::iterator iter = ip_list.begin();
			for ( ; iter != ip_list.end(); ++iter)
			{
				szTxt = CA2W(iter->c_str());
				pBox->AddString( szTxt  );
			}
		}
		szTxt = _T("0.0.0.0");
		pBox->AddString( szTxt  );
// 		if (pBox->GetCount() <= 0)
// 		{
// 			szTxt = _T("127.0.0.1");
// 			pBox->AddString( szTxt  );
// 		}
		if (pBox->GetCount())
		{
//			pBox->SetCurSel(pBox->GetCount()-1);
			pBox->SetCurSel( 0 );
		}
	}


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CNewSvrDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	CComboBox *pBox =(CComboBox *) GetDlgItem(IDC_COMBO_HOST_IP);
	ASSERT(pBox);
	if(pBox)
	{	 
		pBox->GetWindowText(m_szLocalIp);
//		m_dwLocalIp = htonl( inet_addr(CW2A(szIp)));
	}


	CBCGPDialog::OnOK();
}
