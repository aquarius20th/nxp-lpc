// ClientSendView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientSendView.h"


// CClientSendView

IMPLEMENT_DYNCREATE(CClientSendView, CFormView)

CClientSendView::CClientSendView()
	: CFormView(CClientSendView::IDD)
{

}

CClientSendView::~CClientSendView()
{
}

void CClientSendView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientSendView, CFormView)
END_MESSAGE_MAP()


// CClientSendView ���

#ifdef _DEBUG
void CClientSendView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientSendView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientSendView ��Ϣ�������
