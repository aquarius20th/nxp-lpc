// PingStatisView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PingStatisView.h"


// CPingStatisView

IMPLEMENT_DYNCREATE(CPingStatisView, CView)

CPingStatisView::CPingStatisView()
{

}

CPingStatisView::~CPingStatisView()
{
}

BEGIN_MESSAGE_MAP(CPingStatisView, CView)
END_MESSAGE_MAP()


// CPingStatisView ��ͼ

void CPingStatisView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPingStatisView ���

#ifdef _DEBUG
void CPingStatisView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPingStatisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPingStatisView ��Ϣ�������
