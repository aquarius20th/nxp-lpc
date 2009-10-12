
// ClientChildFrame.cpp : CClientChildFrame ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "MainFrm.h"
#include "ClientChildFrm.h"
#include "ClientSendView.h"
#include "ClientRecvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClientChildFrame

IMPLEMENT_DYNCREATE(CClientChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CClientChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CClientChildFrame ����/����

CClientChildFrame::CClientChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CClientChildFrame::~CClientChildFrame()
{
}


BOOL CClientChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style &= ~WS_SYSMENU; 
	return TRUE;
}

// CClientChildFrame ���

#ifdef _DEBUG
void CClientChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CClientChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

void CClientChildFrame::ActivateFrame(int nCmdShow)
{
	CBCGPMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

// CClientChildFrame ��Ϣ�������

int CClientChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	

	return 0;
}

BOOL CClientChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_wndSplitter.GetSafeHwnd () != NULL)
	{
		return FALSE;
	}

	if (!m_wndSplitter.CreateStatic (this, 2,1))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	m_wndSplitter.ModifyStyle (WS_HSCROLL | WS_VSCROLL, 0);

	CRect rectClient;
	GetClientRect (rectClient);

	m_wndSplitter.CreateView (0, 0, pContext->m_pNewViewClass, CSize(0, 0), pContext);
	m_wndSplitter.CreateView (1, 0, RUNTIME_CLASS (CClientRecvView), CSize(0, 0), pContext);

	m_wndSplitter.SetRowInfo(0, rectClient.Height () / 3 , 30);
	m_wndSplitter.SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (), SWP_NOZORDER | SWP_NOREDRAW);
	m_wndSplitter.RecalcLayout();
	return TRUE;

	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CClientChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGPMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: �ڴ˴������Ϣ����������
}

void CClientChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CBCGPMDIChildWnd::OnClose();
}

void CClientChildFrame::OnDestroy()
{
	CMainFrame*pMain = (CMainFrame*) GetMDIFrame();
	ASSERT(pMain);
	if (pMain)
	{
		pMain->CloseChildFrm(this);
	}

	CBCGPMDIChildWnd::OnDestroy();
	

	// TODO: �ڴ˴������Ϣ����������
}
