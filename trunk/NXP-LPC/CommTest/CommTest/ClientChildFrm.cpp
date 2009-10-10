
// PingChildFrm.cpp : CClientChildFrame ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

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
//	cs.style  &= ~FWS_ADDTOTITLE ;
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

	m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CClientSendView), CSize (0, rectClient.Height() / 6), pContext);
	m_wndSplitter.CreateView (1, 0, RUNTIME_CLASS (CClientRecvView), CSize (0, rectClient.Height () / 2), pContext);

	m_wndSplitter.SetColumnInfo (0, rectClient.Height () / 6, 30);
	m_wndSplitter.SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (), SWP_NOZORDER | SWP_NOREDRAW);


	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}
