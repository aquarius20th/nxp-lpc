
// CommTestView.cpp : CCommTestView ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "CommTestDoc.h"
#include "CommTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommTestView

IMPLEMENT_DYNCREATE(CCommTestView, CView)

BEGIN_MESSAGE_MAP(CCommTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCommTestView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCommTestView ����/����

CCommTestView::CCommTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CCommTestView::~CCommTestView()
{
}

BOOL CCommTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCommTestView ����

void CCommTestView::OnDraw(CDC* /*pDC*/)
{
	CCommTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCommTestView ��ӡ


void CCommTestView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CCommTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCommTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCommTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CCommTestView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCommTestView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCommTestView ���

#ifdef _DEBUG
void CCommTestView::AssertValid() const
{
	CView::AssertValid();
}

void CCommTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommTestDoc* CCommTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommTestDoc)));
	return (CCommTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CCommTestView ��Ϣ�������
