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
