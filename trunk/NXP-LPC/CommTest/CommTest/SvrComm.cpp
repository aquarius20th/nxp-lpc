

#include "stdafx.h"
#include "SvrComm.h"

#include "Common.h"
#include "LogDataApi.h" 

#include  "boost/memory.hpp"

const int MAX_CLINENT_CNT = 128;

CSvrComm::CSvrComm( )
{
	m_bStart = FALSE;
}

CSvrComm::~CSvrComm( )
{
	FreeMem();
}

BOOL CSvrComm::StartTask( )
{
	return Start();
}

void CSvrComm::StopTask( )
{
	ShutDown();
 
}

/*********************************************************************************************************
** ��������: NotifyNewConnection
** ��������: CSvrComm::NotifyNewConnection
**
** ����������  
**
** �䡡��:  ClientContext * pcontext
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��30��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CSvrComm::NotifyNewConnection(ClientContext *pcontext)
{
	ASSERT(pcontext);
	if (pcontext == NULL)
		return;

	ASSERT(pcontext->m_nSocket != 0 && pcontext->m_nSocket != INVALID_SOCKET);
	ASSERT(pcontext->m_nID != 0 && pcontext->m_nID != INVALID_SOCKET);

	int nSize = m_arrClientNode.size();
	if (nSize >= MAX_CLINENT_CNT)
		return;

	std::vector <CClientNode *>::iterator iter = m_arrClientNode.begin();
	bool bFind = false;

	//�����Ƿ����ظ�
	for ( ;  iter != m_arrClientNode.end() ; ++ iter)
	{
		if ((*iter)->m_nSocket == pcontext->m_nSocket)
		{
			bFind = true;
			break;
		}
	}

	if (bFind)
	{//�ҵ��ˣ�����֮
		ASSERT(FALSE);

		
		return;
	}

	CClientNode *pClient = new CClientNode;




	m_arrClientNode.push_back(pClient);
}

void CSvrComm::NotifyDisconnectedClient(ClientContext *pContext)
{

}

void CSvrComm::FreeMem()
{

}
