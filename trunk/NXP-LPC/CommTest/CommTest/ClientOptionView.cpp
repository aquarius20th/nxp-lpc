// ClientOptionView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientOptionView.h"


// CClientOptionView

IMPLEMENT_DYNCREATE(CClientOptionView, CBCGPFormView)

CClientOptionView::CClientOptionView()
	: CBCGPFormView(CClientOptionView::IDD)
{

}

CClientOptionView::~CClientOptionView()
{
}

void CClientOptionView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientOptionView, CBCGPFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CClientOptionView ���

#ifdef _DEBUG
void CClientOptionView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientOptionView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientOptionView ��Ϣ�������

int CClientOptionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();
	return 0;
}
