// PacketTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PacketTreeView.h"


// CPacketTreeView

IMPLEMENT_DYNCREATE(CPacketTreeView, CView)

CPacketTreeView::CPacketTreeView()
{

}

CPacketTreeView::~CPacketTreeView()
{
}

BEGIN_MESSAGE_MAP(CPacketTreeView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPacketTreeView ��ͼ

void CPacketTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPacketTreeView ���

#ifdef _DEBUG
void CPacketTreeView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPacketTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPacketTreeView ��Ϣ�������

int CPacketTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
