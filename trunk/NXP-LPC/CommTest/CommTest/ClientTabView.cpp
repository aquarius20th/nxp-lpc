// ClientTabView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientTabView.h"
#include "ClientRecvView.h"
#include "ClientCommDoc.h"
#include "ClientStatisView.h"


// CClientTabView

IMPLEMENT_DYNCREATE(CClientTabView, CBCGPTabView)

CClientTabView::CClientTabView()
{

}

CClientTabView::~CClientTabView()
{
}

BEGIN_MESSAGE_MAP(CClientTabView, CBCGPTabView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CClientTabView ��ͼ

void CClientTabView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CClientTabView ���

#ifdef _DEBUG
void CClientTabView::AssertValid() const
{
	CBCGPTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientTabView::Dump(CDumpContext& dc) const
{
	CBCGPTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientTabView ��Ϣ�������

int CClientTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tabs window:
	if (!m_wndTabs.Create (  CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create tab window\n");
		return -1;      // fail to create
	}

	m_wndTabs.SetFlatFrame ();
	m_wndTabs.SetTabBorderSize (0);
	m_wndTabs.AutoDestroyWindow (FALSE);

	CBCGPTabWnd::Style style = CBCGPTabWnd::STYLE_3D_ONENOTE;

	m_wndTabs.ModifyTabStyle (style);

//	CFrameWnd *pFrame = (CFrameWnd*)theApp.m_pMainWnd;
	//	ASSERT(pFrame);
	CClientCommDoc* pDoc = (CClientCommDoc*)GetDocument ();
	ASSERT(pDoc);

	// TODO:  �ڴ������ר�õĴ�������
	CCreateContext context;
	memset(&context,0,sizeof(CCreateContext));	
	context.m_pCurrentDoc = pDoc;	
	AddView(RUNTIME_CLASS(CClientRecvView),_T("������Ϣ"),-1,&context);
	AddView(RUNTIME_CLASS(CClientStatisView),_T("ͳ����Ϣ"),-1,&context);

	return 0;
}

void CClientTabView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabs.GetSafeHwnd())
	{
		m_wndTabs.SetWindowPos (NULL, -1, -1, cx + 1, cy + 1,SWP_NOACTIVATE | SWP_NOZORDER);
	}
	// TODO: �ڴ˴������Ϣ����������
}
