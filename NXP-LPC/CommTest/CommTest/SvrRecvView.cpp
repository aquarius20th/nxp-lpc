// SvrRecvView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrRecvView.h"


// CSvrRecvView

IMPLEMENT_DYNCREATE(CSvrRecvView, CView)

CSvrRecvView::CSvrRecvView()
{

}

CSvrRecvView::~CSvrRecvView()
{
}

BEGIN_MESSAGE_MAP(CSvrRecvView, CView)
END_MESSAGE_MAP()


// CSvrRecvView ��ͼ

void CSvrRecvView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CSvrRecvView ���

#ifdef _DEBUG
void CSvrRecvView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrRecvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSvrRecvView ��Ϣ�������
