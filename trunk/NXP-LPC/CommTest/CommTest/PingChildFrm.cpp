
// PingChildFrm.cpp : CPingChildFrame ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "PingChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPingChildFrame

IMPLEMENT_DYNCREATE(CPingChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CPingChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CPingChildFrame ����/����

CPingChildFrame::CPingChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CPingChildFrame::~CPingChildFrame()
{
}


BOOL CPingChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.style &= ~WS_SYSMENU;
//	cs.style  &= ~FWS_ADDTOTITLE ;
	return TRUE;
}

// CPingChildFrame ���

#ifdef _DEBUG
void CPingChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CPingChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

void CPingChildFrame::ActivateFrame(int nCmdShow)
{
	CBCGPMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

// CPingChildFrame ��Ϣ�������

int CPingChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

//	SetTitle(_T("xxxxxx"));
// 	SetWindowText(_T("xxxxxx"));
// 	CDocument *pDoc = GetActiveDocument();
	

	return 0;
}
