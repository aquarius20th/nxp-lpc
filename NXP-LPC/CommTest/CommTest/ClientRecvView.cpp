// ClientRecvView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "ClientRecvView.h"
#include "ClientCommDoc.h"
#include "MainFrm.h"

#include "ChildFrm.h"


// CClientRecvView

IMPLEMENT_DYNCREATE(CClientRecvView, CBCGPFormView)

CClientRecvView::CClientRecvView()
	: CBCGPFormView(CClientRecvView::IDD)
{

}

CClientRecvView::~CClientRecvView()
{
}

void CClientRecvView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientRecvView, CBCGPFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECV, &CClientRecvView::OnBnClickedButtonClearRecv)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientRecvView ���

#ifdef _DEBUG
void CClientRecvView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClientRecvView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CClientRecvView ��Ϣ�������

int CClientRecvView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	EnableVisualManagerStyle();

 	CRect rectGrid;
	rectGrid.SetRectEmpty();
	 
	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	
	m_wndGrid.SetReadOnly ();
	m_wndGrid.SetWholeRowSel ();
	m_wndGrid.EnableHeader (TRUE, 0);

	return 0;
}

void CClientRecvView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������	
	 if ( m_wndGrid.GetSafeHwnd())
	{
		CRect rectClient;
		GetClientRect (rectClient);
		rectClient.InflateRect (2, 2);

		rectClient.top = rectClient.top + 40;
		m_wndGrid.MoveWindow(rectClient);
	}
}

void CClientRecvView::OnBnClickedButtonClearRecv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//TEST
//	GetParentFrame()
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame);
	if (pFrame == NULL)
		return;	

	CClientCommDoc *pDoc = (CClientCommDoc *) GetDocument();
	ASSERT(pDoc);
	if (pDoc == NULL)
		return;

	CMDIChildWnd *pChildWnd = NULL;
 
	CCreateContext context;
	context.m_pCurrentDoc = pDoc;
	context.m_pCurrentFrame = pFrame;
	context.m_pNewDocTemplate = (CDocTemplate*) theApp.m_pDocTemplate;

	CRuntimeClass* pFrameClass = RUNTIME_CLASS(CChildFrame);   		 

// 	HMENU hMenu = NULL;       // default menu resource for this frame
// 	HACCEL hAccelTable = NULL;       // accelerator table
// 	hAccelTable = ::LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_FBD_FRAME));
// 	//	ASSERT( hAccelTable );
// 	hMenu = ::LoadMenu(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_FBD_FRAME));
// 	ASSERT(hMenu);
	pChildWnd = pFrame->CreateNewChild( pFrameClass, IDR_MAINFRAME );
//	pChildWnd->SetHandles(hMenu,hAccelTable);

	pFrame->MDIActivate( pChildWnd );

}

void CClientRecvView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CBCGPFormView::OnTimer(nIDEvent);
}
