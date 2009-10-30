// SvrListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrListView.h"
#include "SvrCommDoc.h"


typedef enum  SVR_GRID_COL
{
	SVR_GRID_COLUMN_IDX,  // ���
	SVR_GRID_COLUMN_IP,  // 
	SVR_GRID_COLUMN_PORT , // 
	SVR_GRID_COLUMN_RECV,
	SVR_GRID_COLUMN_SEND  // 
};

BEGIN_MESSAGE_MAP(CSvrListGridCtrl, CBCGPGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

void CSvrListGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPGridCtrl::OnLButtonDblClk(nFlags, point);
	if (GetParent() && GetParent()->IsKindOf(RUNTIME_CLASS(CSvrListView)))
	{
		CBCGPGridRow* pSel = GetCurSel ();
		if (pSel)
		{
			DWORD_PTR pData = pSel->GetData();
			((CSvrListView*)GetParent())->OnDblclkGrid(pData);

		}

	}
}


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
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
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

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, ID_SEVER_LIST);

	m_wndGrid.SetSingleSel(TRUE);
	m_wndGrid.SetWholeRowSel (TRUE);
	m_wndGrid.EnableMarkSortedColumn (FALSE);
	m_wndGrid.EnableMultipleSort(FALSE);
	m_wndGrid.EnableHeader (TRUE,BCGP_GRID_HEADER_MOVE_ITEMS); 		 
	m_wndGrid.EnableLineNumbers(TRUE);

	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_IDX, _T("���"), 70);
	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_IP, _T("IP"), 160);
	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_PORT, _T("�˿ں�"), 80);
// 	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_RECV, _T("  "),240);
// 	m_wndGrid.InsertColumn (SVR_GRID_COLUMN_RECV, _T("������ʱ"),100);
 
	return 0;
}

void CSvrListView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if ( m_wndGrid.GetSafeHwnd())
	{
		 m_wndGrid.SetWindowPos (NULL, -1, -1, cx, cy,SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CSvrListView::OnDblclkGrid(DWORD_PTR pClient ) 
{
	CSvrCommDoc *pDoc = (CSvrCommDoc *)GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	//TEST
 	pDoc->OpenSvrCommFrm((CClientNode *)pClient);
}

void CSvrListView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
}

BOOL CSvrListView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}

void CSvrListView::OnDestroy()
{
	m_wndGrid.DestroyWindow();
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

void CSvrListView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);
	if (m_wndGrid.GetSafeHwnd() != NULL)
	{
		m_wndGrid.SetFocus();
	}
	// TODO: �ڴ˴������Ϣ����������
}