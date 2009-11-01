

#include "stdafx.h"
#include "SvrComm.h"

#include "Common.h"
#include "LogDataApi.h" 
#include <utility>

#include  "boost/memory.hpp"

const int MAX_CLINENT_CNT = 1024;

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

//	ASSERT(this->m_nSocket == pContext->m_nSocket);
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
	CSingleLock lock(&m_Lock,TRUE);

	//����ͻ����б���Ϣ
	FreeMem();
	lock.Unlock();
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
	bool bFind = false;
	std::vector <CClientNode *>::iterator iter ;
	stdext::hash_map <ClientContext *, CClientNode *>::iterator it_map;

	CSingleLock lock(&m_Lock,TRUE);
	int nSize = m_arrClientNode.size();
	if (nSize >= MAX_CLINENT_CNT)
	{
		lock.Unlock();
		return;
	}

	//�����Ƿ����ظ� ��IP��ַ�Ͷ˿ں����Ƚ�
	for (iter = m_arrClientNode.begin();  iter != m_arrClientNode.end() ; ++ iter)
	{
// 		if ((*iter)->m_nSocket == pcontext->m_nSocket)
// 		{
// 			bFind = true;
// 			break;
// 		}
		if (0 == memcmp( &((*iter)->m_addr ),&(pcontext->m_addr),sizeof(pcontext->m_addr)))
		{
			bFind = true;
			break;
		}
	}

	if (bFind)
	{//�ҵ��ˣ�����֮ ͬһ����Դ�ĶϿ���������
		(*iter)->CopyData(pcontext);	
		(*iter)->m_bOnline = TRUE;

		it_map = m_mapClients.find( pcontext );
		if (it_map != m_mapClients.end())
		{
			ASSERT(FALSE);
			it_map->second = (*iter);
		}
		else
		{
			m_mapClients.insert(std::make_pair(pcontext,(*iter)));
		} 

		lock.Unlock();
		return;
	}

	CClientNode *pClient = new CClientNode;
	pClient->CopyData(pcontext);
	pClient->m_bOnline = TRUE;

	m_arrClientNode.push_back(pClient);

	it_map = m_mapClients.find( pcontext );
	if (it_map != m_mapClients.end())
	{
		ASSERT(FALSE);
		it_map->second = pClient;
	}
	else
	{
		m_mapClients.insert(std::make_pair(pcontext,pClient));
	}

	lock.Unlock();
}

void CSvrComm::NotifyDisconnectedClient(ClientContext *pContext)
{
	CClientNode *pClient = NULL;
	stdext::hash_map <ClientContext *, CClientNode *>::iterator it_map;

	CSingleLock lock(&m_Lock,TRUE);

	it_map = m_mapClients.find( pContext );
	if (it_map != m_mapClients.end())
	{
		it_map->second->m_bOnline = FALSE;
		m_mapClients.erase(it_map);
	}
	else
	{
	//	ASSERT(FALSE);
		OutputDebugString(_T("xxxxxxx\r\n"));
	}
	lock.Unlock();
}

/*********************************************************************************************************
** ��������: NotifyReceivedPackage
** ��������: CSvrComm::NotifyReceivedPackage
**
** ����������  
**
** �䡡��:  CSvrCommPacket * pOverlapBuff
** �䡡��:  int nSize
** �䡡��:  ClientContext * pContext
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��1��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CSvrComm::NotifyReceivedPackage(CSvrCommPacket *pOverlapBuff,int nSize,ClientContext *pContext)
{
	ASSERT(pContext);
	ASSERT(nSize >= 0 && nSize <= MAX_PACKAGE_SIZE);
	ASSERT(pOverlapBuff);

	if(pOverlapBuff == NULL || pContext == NULL || nSize <= 0 || nSize >= MAX_PACKAGE_SIZE)
		return;

	CClientNode *pClient = NULL;
	stdext::hash_map <ClientContext *, CClientNode *>::iterator it_map;

	CSingleLock lock(&m_Lock,TRUE);

	it_map = m_mapClients.find( pContext );
	if (it_map != m_mapClients.end())
	{
		pClient = it_map->second ;
	}
	else
	{
		ASSERT(FALSE);
	}
	ASSERT(pClient);
	if (pClient==NULL)
	{
		lock.Unlock();
		return;
	}
	pClient->m_nRecvCnt ++;
	pClient->m_nTotalRecvLen += nSize;
	lock.Unlock();
	return;
}

void CSvrComm::FreeMem()
{
	std::vector <CClientNode *>::iterator iter ;

	for (iter = m_arrClientNode.begin();  iter != m_arrClientNode.end() ; ++ iter)
	{
		delete (*iter);		 
	}
	m_arrClientNode.clear();
	m_mapClients.clear();
}
