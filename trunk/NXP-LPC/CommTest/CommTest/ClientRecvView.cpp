// ClientRecvView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientRecvView.h"


// CClientRecvView

IMPLEMENT_DYNCREATE(CClientRecvView, CFormView)

CClientRecvView::CClientRecvView()
	: CFormView(CClientRecvView::IDD)
{

}

CClientRecvView::~CClientRecvView()
{
}

void CClientRecvView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientRecvView, CFormView)
END_MESSAGE_MAP()


// CClientRecvView ���

#ifdef _DEBUG
void CClientRecvView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientRecvView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientRecvView ��Ϣ�������
