// PingTestView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PingTestView.h"


// CPingTestView

IMPLEMENT_DYNCREATE(CPingTestView, CView)

CPingTestView::CPingTestView()
{

}

CPingTestView::~CPingTestView()
{
}

BEGIN_MESSAGE_MAP(CPingTestView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPingTestView ��ͼ

void CPingTestView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPingTestView ���

#ifdef _DEBUG
void CPingTestView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPingTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPingTestView ��Ϣ�������

int CPingTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rectGrid;
	rectGrid.SetRectEmpty();

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);


	return 0;
}

void CPingTestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_wndGrid.GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);
		m_wndGrid.MoveWindow(rc);
	}
	// TODO: �ڴ˴������Ϣ����������
}
