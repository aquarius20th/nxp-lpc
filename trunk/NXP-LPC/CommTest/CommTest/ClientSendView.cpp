// ClientSendView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientSendView.h"


// CClientSendView

IMPLEMENT_DYNCREATE(CClientSendView, CBCGPFormView)

CClientSendView::CClientSendView()
	: CBCGPFormView(CClientSendView::IDD)
{

}

CClientSendView::~CClientSendView()
{
}

void CClientSendView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientSendView, CBCGPFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CClientSendView::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CClientSendView ���

#ifdef _DEBUG
void CClientSendView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientSendView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientSendView ��Ϣ�������

int CClientSendView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();

	return 0;
}

void CClientSendView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CWnd *pEdit = GetDlgItem(IDC_EDIT_SEND_TXT);
	if (pEdit && pEdit->GetSafeHwnd())
	{
		CRect rcEdit;
		CRect rectClient;

		GetClientRect (rectClient);
		pEdit->GetWindowRect(rcEdit);
		ScreenToClient (rcEdit);

		rcEdit.left = rectClient.left + 2;
		rcEdit.right = rectClient.right - 3;
		rcEdit.bottom = rectClient.bottom - 3;
		pEdit->MoveWindow(rcEdit);
	}
}

void CClientSendView::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
