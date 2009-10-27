// SvrOptionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrOptionView.h"
#include "SvrCommDoc.h"


// CSvrOptionView

IMPLEMENT_DYNCREATE(CSvrOptionView, CBCGPFormView)

CSvrOptionView::CSvrOptionView()
	: CBCGPFormView(CSvrOptionView::IDD)
	, m_nPortNum(999)
{

}

CSvrOptionView::~CSvrOptionView()
{
}

void CSvrOptionView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SVR_PORTNUM_OPT, m_nPortNum);
}

BEGIN_MESSAGE_MAP(CSvrOptionView, CBCGPFormView)
	ON_BN_CLICKED(IDC_BUTTON_SVR_START, &CSvrOptionView::OnBnClickedButtonSvrStart)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CSvrOptionView ���

#ifdef _DEBUG
void CSvrOptionView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrOptionView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrOptionView ��Ϣ�������


int CSvrOptionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	EnableVisualManagerStyle();

	// TODO:  �ڴ������ר�õĴ�������
	
	return 0;
}

void CSvrOptionView::OnBnClickedButtonSvrStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSvrCommDoc *pDoc = (CSvrCommDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;
	pDoc->m_SvrComm.Start();

}
void CSvrOptionView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	std::list<std::string> ip_list;
	bool bRet = false;

	bRet = CUEServer::GetIpList(ip_list);
	CComboBox *pBox =(CComboBox *) GetDlgItem(IDC_COMBO_HOST_IP_OPT);
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
		if (pBox->GetCount() <= 0)
		{
			szTxt = _T("127.0.0.1");
			pBox->AddString( szTxt  );
		}
		if (pBox->GetCount())
		{
			pBox->SetCurSel(pBox->GetCount()-1);
		}
	}

}
