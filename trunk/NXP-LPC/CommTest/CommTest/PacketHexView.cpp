// PacketHexView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PacketHexView.h"


// CPacketHexView

IMPLEMENT_DYNCREATE(CPacketHexView, CView)

CPacketHexView::CPacketHexView()
{

}

CPacketHexView::~CPacketHexView()
{
}

BEGIN_MESSAGE_MAP(CPacketHexView, CView)
END_MESSAGE_MAP()


// CPacketHexView ��ͼ

void CPacketHexView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPacketHexView ���

#ifdef _DEBUG
void CPacketHexView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPacketHexView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPacketHexView ��Ϣ�������
