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
	m_bPinging = FALSE;
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

void CPingTestDoc::FreeMem()
{
	std::vector <CPingTask *>::iterator it = m_arrTask.begin();

	for (; it != m_arrTask.end() ; ++it)
	{
		delete (*it);
	}

	m_arrTask.clear();
}

void CPingTestDoc::StartTask( )
{
	if (m_nTaskCnt >0 && m_nTaskCnt <= 16)
	{
		unsigned int i = 0;
		CPingTask *pTask = NULL;
		for ( i= 0; i < m_nTaskCnt; i++)
		{
			pTask =  new CPingTask(this);
			ASSERT(pTask);
			pTask->m_nID = i+1;
			m_arrTask.push_back(pTask);
			pTask->StartTask();
		}				
	}
}

void CPingTestDoc::StopTask( )
{
	std::vector <CPingTask *>::iterator it = m_arrTask.begin();

	for (; it != m_arrTask.end() ; ++it)
	{
		 (*it)->StopTask();
	}
	FreeMem();
}


void CPingTestDoc::OnCloseDocument()
{
	// TODO: �ڴ����ר�ô����/����û���
	StopTask();

	CDocument::OnCloseDocument();
}
