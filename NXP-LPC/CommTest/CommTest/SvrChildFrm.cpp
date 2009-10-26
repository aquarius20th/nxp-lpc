
// SvrChildFrm.cpp : CSvrChildFrame ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "SvrChildFrm.h" 
#include "SvrOptionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSvrChildFrame

IMPLEMENT_DYNCREATE(CSvrChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CSvrChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CSvrChildFrame ����/����

CSvrChildFrame::CSvrChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CSvrChildFrame::~CSvrChildFrame()
{
}


BOOL CSvrChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style &= ~WS_SYSMENU;
//	cs.style  &= ~FWS_ADDTOTITLE ;
	return TRUE;
}

// CSvrChildFrame ���

#ifdef _DEBUG
void CSvrChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CSvrChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

void CSvrChildFrame::ActivateFrame(int nCmdShow)
{
	CBCGPMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

// CSvrChildFrame ��Ϣ�������

int CSvrChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������


	return 0;
}

BOOL CSvrChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
		return FALSE;
	m_wndSplitter1.SetXMoveLimit(144,180);

	if (!m_wndSplitter1.CreateView(0, 0, pContext->m_pNewViewClass, CSize(200, 100), pContext) )
	{
		m_wndSplitter1.DestroyWindow();
		return FALSE;
	}
	m_wndSplitter2.CreateView (0, 1, RUNTIME_CLASS (CSvrOptionView), CSize(0, 0), pContext);
// 	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter1,	// our parent window is the first splitter
// 		2, 1,											// the new splitter is 2 rows, 1 column
// 		WS_CHILD | WS_VISIBLE | WS_BORDER,				// style, WS_BORDER is needed
// 		m_wndSplitter1.IdFromRowCol(0, 1)))				// new splitter is in the first row, 3rd column of first splitter
// 	{
// 		TRACE0("Failed to create nested splitter\n");
// 		return FALSE;
// 	}

	//	m_wndSplitter1.ModifyStyle (WS_HSCROLL | WS_VSCROLL, 0);
	CRect rectClient;
	GetClientRect (rectClient);

// 	m_wndSplitter2.CreateView (0, 0, RUNTIME_CLASS (CPingTestView), CSize(0, 0), pContext);
// 	m_wndSplitter2.CreateView (1, 0, RUNTIME_CLASS (CPingStatisView), CSize(0, 0), pContext);
// 
// 	//	m_wndSplitter1.SetColumnInfo(0, rectClient.Width() / 4 , 30);
// 
// 	m_wndSplitter2.SetRowInfo(0, rectClient.Height () *3/4 , 120);
// 	m_wndSplitter2.SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (), SWP_NOZORDER | SWP_NOREDRAW);
// 	m_wndSplitter2.RecalcLayout();

	return TRUE;
	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}
