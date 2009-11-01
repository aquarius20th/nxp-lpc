// SvrSendView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrSendView.h"


// CSvrSendView

IMPLEMENT_DYNCREATE(CSvrSendView, CBCGPFormView)

CSvrSendView::CSvrSendView()
	: CBCGPFormView(CSvrSendView::IDD)
{

}

CSvrSendView::~CSvrSendView()
{
}

void CSvrSendView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSvrSendView, CBCGPFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSvrSendView ���

#ifdef _DEBUG
void CSvrSendView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrSendView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrSendView ��Ϣ�������

void CSvrSendView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	// TODO: �ڴ˴������Ϣ����������
	CWnd *pEdit = GetDlgItem(IDC_EDIT_SVR_SEND_TXT);
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
