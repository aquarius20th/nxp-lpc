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
	if (CBCGPTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	 
//	CFrameWnd *pFrame = (CFrameWnd*)theApp.m_pMainWnd;
	//	ASSERT(pFrame);
	CClientCommDoc* pDoc = (CClientCommDoc*)GetDocument ();
	ASSERT(pDoc);

	// TODO:  �ڴ������ר�õĴ�������
  	CCreateContext context;
 	memset(&context,0,sizeof(CCreateContext));	
  	context.m_pCurrentDoc = pDoc;	
//	AddView(_T("������Ϣ"),RUNTIME_CLASS(CClientRecvView),pDoc);
//	AddView(_T("ͳ����Ϣ"),RUNTIME_CLASS(CClientStatisView),pDoc);
	AddView(RUNTIME_CLASS(CClientRecvView),_T("������Ϣ"),-1,&context);
	AddView(RUNTIME_CLASS(CClientStatisView),_T("ͳ����Ϣ"),-1,&context);

	return 0;
}

void CClientTabView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPTabView::OnSize(nType, cx, cy);

	 
	// TODO: �ڴ˴������Ϣ����������
}
