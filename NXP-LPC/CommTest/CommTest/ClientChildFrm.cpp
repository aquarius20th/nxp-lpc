
// PingChildFrm.cpp : CClientChildFrame ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "ClientChildFrm.h"

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

//	SetTitle(_T("xxxxxx"));
// 	SetWindowText(_T("xxxxxx"));
// 	CDocument *pDoc = GetActiveDocument();
	

	return 0;
}
