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
