// PingTestDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "SvrCommDoc.h"


// CSvrCommDoc

IMPLEMENT_DYNCREATE(CSvrCommDoc, CDocument)

CSvrCommDoc::CSvrCommDoc()
{
 
}

BOOL CSvrCommDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSvrCommDoc::~CSvrCommDoc()
{
}


BEGIN_MESSAGE_MAP(CSvrCommDoc, CDocument)
END_MESSAGE_MAP()


// CSvrCommDoc ���

#ifdef _DEBUG
void CSvrCommDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSvrCommDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSvrCommDoc ���л�

void CSvrCommDoc::Serialize(CArchive& ar)
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
#endif


// CSvrCommDoc ����
 void CSvrCommDoc::StartTask( )
{
	 
}

void CSvrCommDoc::StopTask( )
{
	 
}


void CSvrCommDoc::OnCloseDocument()
{
	// TODO: �ڴ����ר�ô����/����û���
	StopTask();

	CDocument::OnCloseDocument();
}
