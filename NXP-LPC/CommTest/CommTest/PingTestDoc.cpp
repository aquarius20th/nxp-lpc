// PingTestDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CommTest.h"
#include "PingTestDoc.h"


// CPingTestDoc

IMPLEMENT_DYNCREATE(CPingTestDoc, CDocument)

CPingTestDoc::CPingTestDoc()
{
	m_dwDestIp = 0;
}

BOOL CPingTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CPingTestDoc::~CPingTestDoc()
{
}


BEGIN_MESSAGE_MAP(CPingTestDoc, CDocument)
END_MESSAGE_MAP()


// CPingTestDoc ���

#ifdef _DEBUG
void CPingTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CPingTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CPingTestDoc ���л�

void CPingTestDoc::Serialize(CArchive& ar)
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


// CPingTestDoc ����
