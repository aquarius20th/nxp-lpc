// PacketDecodeFrm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PacketDecodeFrm.h" 
#include "PacketTreeView.h"
#include "PacketHexView.h"

#include "ClientCommDoc.h"
//#include "PingTestDoc.h"


// CPacketDecodeFrm

IMPLEMENT_DYNCREATE(CPacketDecodeFrm, CBCGPMDIChildWnd)

CPacketDecodeFrm::CPacketDecodeFrm()
{

}

CPacketDecodeFrm::~CPacketDecodeFrm()
{
}


BEGIN_MESSAGE_MAP(CPacketDecodeFrm, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPacketDecodeFrm ��Ϣ�������

BOOL CPacketDecodeFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style &= ~WS_SYSMENU;
 	cs.style  &= ~FWS_ADDTOTITLE ;

	return CBCGPMDIChildWnd::PreCreateWindow(cs);
}

int CPacketDecodeFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	 
	return 0;
}

BOOL CPacketDecodeFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
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

	m_wndSplitter.CreateView (0, 0, RUNTIME_CLASS (CPacketTreeView), CSize (0, rectClient.Width() / 2), pContext);
	m_wndSplitter.CreateView (1,0, RUNTIME_CLASS (CPacketHexView), CSize (0, rectClient.Width () / 2), pContext);

	return TRUE;
//	return CBCGPMDIChildWnd::OnCreateClient(lpcs, pContext);
}

void CPacketDecodeFrm::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDocument *pDoc = GetActiveDocument();
	if (pDoc->IsKindOf(RUNTIME_CLASS( CClientCommDoc )))
	{
		((CClientCommDoc*)pDoc)->m_pDecodeFrm = NULL;
		DestroyWindow();
		return;
	}
//	else


	CBCGPMDIChildWnd::OnClose();
}
