

#include "stdafx.h"
#include "SvrComm.h"

#include "Common.h"
#include "LogDataApi.h" 

#include  "boost/memory.hpp"

const int MAX_CLINENT_CNT = 128;

/*********************************************************************************************************
** ��������: CopyData
** ��������: CClientNode::CopyData
**
** ����������  �Ӹ��࿽�����ݳ���
**
** �䡡��:  ClientContext * pContext
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��31��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CClientNode::CopyData(ClientContext *pContext)
{
	ASSERT(pContext);
	if(pContext == NULL)
		return;

	ASSERT(this->m_nSocket == pContext->m_nSocket);
	this->m_nSocket = pContext->m_nSocket;
	memcpy_s( & (this->m_addr) ,sizeof(m_addr),& (pContext->m_addr),sizeof(m_addr));
	
	this->m_nSendCnt = pContext->m_nSendCnt; //����
	this->m_nRecvCnt = pContext->m_nRecvCnt;

	this->m_nTotalSendLen = pContext->m_nTotalSendLen; //�ֽڳ���
	this->m_nTotalRecvLen = pContext->m_nTotalRecvLen;

}

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

	//����ͻ����б���Ϣ
	FreeMem();
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
		(*iter)->CopyData(pcontext);		
		return;
	}

	CClientNode *pClient = new CClientNode;
	pClient->CopyData(pcontext);

	m_arrClientNode.push_back(pClient);
}

void CSvrComm::NotifyDisconnectedClient(ClientContext *pContext)
{

}

void CSvrComm::FreeMem()
{

}
