
// CommTestView.cpp : CClientCommView ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "ClientCommDoc.h"
#include "ClientCommView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientCommView

IMPLEMENT_DYNCREATE(CClientCommView, CView)

BEGIN_MESSAGE_MAP(CClientCommView, CView) 
END_MESSAGE_MAP()

// CClientCommView ����/����

CClientCommView::CClientCommView()
{
	// TODO: �ڴ˴���ӹ������

}

CClientCommView::~CClientCommView()
{
}

BOOL CClientCommView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CClientCommView ����

void CClientCommView::OnDraw(CDC* /*pDC*/)
{
	CClientCommDoc* pDoc = (CClientCommDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CClientCommView ��ӡ

 
void CClientCommView::OnContextMenu(CWnd* pWnd, CPoint point)
{
//	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CClientCommView ���

#ifdef _DEBUG
void CClientCommView::AssertValid() const
{
	CView::AssertValid();
}

void CClientCommView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCClientCommDoc* CClientCommView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCClientCommDoc)));
	return (CCClientCommDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientCommView ��Ϣ�������
