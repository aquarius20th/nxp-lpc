// SvrListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrListView.h"


// CSvrListView

IMPLEMENT_DYNCREATE(CSvrListView, CView)

CSvrListView::CSvrListView()
{

}

CSvrListView::~CSvrListView()
{
}

BEGIN_MESSAGE_MAP(CSvrListView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSvrListView ��ͼ

void CSvrListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CSvrListView ���

#ifdef _DEBUG
void CSvrListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrListView ��Ϣ�������

int CSvrListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rectGrid;
	rectGrid.SetRectEmpty();

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);

	return 0;
}

void CSvrListView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if ( m_wndGrid.GetSafeHwnd())
	{
		CRect rectClient;
		GetClientRect (rectClient);
	 	m_wndGrid.MoveWindow(rectClient);
	}
	// TODO: �ڴ˴������Ϣ����������
}
