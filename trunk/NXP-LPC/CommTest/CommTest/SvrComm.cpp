

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
		if (0 == memcmp( &((*iter)->m_addr ),&(pcontext->m_addr),sizeof(pcontext->m_addr) )
		{
			bFind = true;
			break;
		}
	}

	if (bFind)
	{//�ҵ��ˣ�����֮
		ASSERT(FALSE);
		(*iter)->CopyData(pcontext);		
		lock.Unlock();
		return;
	}

	CClientNode *pClient = new CClientNode;
	pClient->CopyData(pcontext);
	pClient->m_bOnline = TRUE;

	m_arrClientNode.push_back(pClient);
	lock.Unlock();
}

void CSvrComm::NotifyDisconnectedClient(ClientContext *pContext)
{

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


}

void CSvrComm::FreeMem()
{
	std::vector <CClientNode *>::iterator iter ;

	for (iter = m_arrClientNode.begin();  iter != m_arrClientNode.end() ; ++ iter)
	{
		delete (*iter);		 
	}
	m_arrClientNode.clear();
}
