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
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
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

int CSvrRecvView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();

	return 0;
}

void CSvrRecvView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CSvrRecvView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPFormView::OnTimer(nIDEvent);
}
