
// CommTestDoc.cpp : CCommTestDoc ���ʵ��
//

#include "stdafx.h"
#include "CommTest.h"

#include "CommTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCommTestDoc

IMPLEMENT_DYNCREATE(CCommTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommTestDoc, CDocument)
END_MESSAGE_MAP()


// CCommTestDoc ����/����

CCommTestDoc::CCommTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCommTestDoc::~CCommTestDoc()
{
}

BOOL CCommTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCommTestDoc ���л�

void CCommTestDoc::Serialize(CArchive& ar)
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


// CCommTestDoc ���

#ifdef _DEBUG
void CCommTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCommTestDoc ����
