
// CommTestDoc.cpp : CClientCommDoc ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "ClientCommDoc.h"
#include "ClientSendView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientCommDoc

IMPLEMENT_DYNCREATE(CClientCommDoc, CDocument)

BEGIN_MESSAGE_MAP(CClientCommDoc, CDocument)
END_MESSAGE_MAP()


// CClientCommDoc ����/����

CClientCommDoc::CClientCommDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_bConnected = FALSE;
	m_ClientComm.m_pDocument = this;
}

CClientCommDoc::~CClientCommDoc()
{
}

BOOL CClientCommDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
 
	return TRUE;
}




// CClientCommDoc ���л�

void CClientCommDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CClientCommDoc ���

#ifdef _DEBUG
void CClientCommDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClientCommDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CClientCommDoc ����
BOOL CClientCommDoc::Connect( )
{
	BOOL bRet = m_ClientComm.Connect();

	//���ӳɹ��󣬸�����صĽ���
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		if (pView->IsKindOf( RUNTIME_CLASS(CClientSendView) ))
		{
		 	((CClientSendView*)pView)->OnConnected();
		}		 		 
	}

	return bRet;
}
void  CClientCommDoc::Disconnect( )
{
	m_ClientComm.StopTask();
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		ASSERT_VALID(pView);
		if (pView->IsKindOf( RUNTIME_CLASS(CClientSendView) ))
		{
			((CClientSendView*)pView)->OnDisconnected();
		}		 		 
	}
}

void CClientCommDoc::OnCloseDocument()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_ClientComm.StopTask();

	CDocument::OnCloseDocument();
}
