// PacketDecodeFrm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h" 
#include "SvrCommFrm.h"
#include "SvrRecvView.h"
#include "SvrSendView.h"
#include "SvrCommDoc.h"
 


// CSvrCommFrm

IMPLEMENT_DYNCREATE(CSvrCommFrm, CBCGPMDIChildWnd)

CSvrCommFrm::CSvrCommFrm()
{

}

CSvrCommFrm::~CSvrCommFrm()
{
}


BEGIN_MESSAGE_MAP(CSvrCommFrm, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSvrCommFrm ��Ϣ�������

BOOL CSvrCommFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style &= ~WS_SYSMENU;
 	cs.style  &= ~FWS_ADDTOTITLE ;

	return CBCGPMDIChildWnd::PreCreateWindow(cs);
}

int CSvrCommFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	 
	return 0;
}

BOOL CSvrCommFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (!m_wndSplitter.CreateStatic (this, 2,1))
	{
		ASSERT(FALSE);
		return -1;
	}

	m_wndSplitter.ModifyStyle (WS_HSCROLL | WS_VSCROLL, 0);

	CRect rectClient;
	GetClientRect (rectClient);

	m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CSvrSendView), CSize (0, rectClient.Width() / 2), pContext);
	m_wndSplitter.CreateView (1,0, RUNTIME_CLASS (CSvrRecvView), CSize (0, rectClient.Width () / 2), pContext);
	m_wndSplitter.SetRowInfo(0, rectClient.Height () *2/5 , 40);
	m_wndSplitter.SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (), SWP_NOZORDER | SWP_NOREDRAW);
	m_wndSplitter.RecalcLayout();
	return TRUE;
//	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CSvrCommFrm::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDocument *pDoc = GetActiveDocument();
	if (pDoc->IsKindOf(RUNTIME_CLASS( CSvrCommDoc )))
	{
	 	((CSvrCommDoc*)pDoc)->CloseFrm(this);
		DestroyWindow();
		return;
	}
 

	CBCGPMDIChildWnd::OnClose();
}
