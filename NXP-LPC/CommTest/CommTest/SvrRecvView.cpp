// SvrRecvView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrRecvView.h"


// CSvrRecvView

 

IMPLEMENT_DYNCREATE(CSvrRecvView, CBCGPFormView)

CSvrRecvView::CSvrRecvView()
: CBCGPFormView(CSvrRecvView::IDD)
{

}

CSvrRecvView::~CSvrRecvView()
{
}

void CSvrRecvView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSvrRecvView, CBCGPFormView)
END_MESSAGE_MAP()


// CSvrRecvView ���

#ifdef _DEBUG
void CSvrRecvView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrRecvView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrRecvView ��Ϣ�������
