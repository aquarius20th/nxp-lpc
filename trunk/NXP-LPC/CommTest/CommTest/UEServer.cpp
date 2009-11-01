/****************************************Copyright (c)**************************************************
**                                ���տƼ��ɷ����޹�˾
**                                     ��ҵ��
**                                     ������������    
**
**                                 http://www.xxx.com.cn
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:  
**��   ��   ��:  
**����޸�����:  
**��        ��:  
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:  
** ��  ��: v1.00
** �ա���:  
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:  
** �ա���:  
** �衡��:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include "stdafx.h"
#include "UEServer.h"
#include <algorithm>
#include "LogDataApi.h"
#include "Common.h"

CUEServer::CUEServer()
{
	m_pListenThread = NULL;
	m_dwLocalIp = 0;
	m_bServerStarted = FALSE;
	m_nListenSocket=0;
 	m_iMaxNumberOfFreeContext=2;
	m_bAcceptConnections=TRUE;
	m_bServerStarted=FALSE;
	m_iMaxNumConnections=1201;
//	m_bAcceptJobs=TRUE;
	m_nOfWorkers=2;
	m_nPortNumber=999;
	m_NumberOfActiveConnections=0;
	m_iNumberOfPendlingReads=3;
}

CUEServer::~CUEServer()
{
	ShutDown();
}
/*********************************************************************************************************
** ��������: FreeBuffers
** ��������: CUEServer::FreeBuffers
**
** ���������� �˳�ǰ���������е��ڴ� 
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��19��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::FreeBuffers()
{
	OutputDebugString(_T("���ձ����ڴ�.... \n"));
	//Free the buffer in the Free buffer list.. 
	CSvrCommPacket *pBuff=NULL;
	std::list <CSvrCommPacket *> ::iterator iter;
	m_FreeBufferListLock.Lock();

	for (iter = m_arrFreeBuffer.begin();iter != m_arrFreeBuffer.end(); ++iter)
	{
		pBuff = *iter;
		delete pBuff;
		pBuff = NULL;
	}
	m_arrFreeBuffer.clear();
	m_FreeBufferListLock.Unlock();

	// Free the buffers in the Occupied buffer list (if any).  
	m_BufferListLock.Lock();
	for (iter = m_arrBuffer.begin();iter != m_arrBuffer.end(); ++iter)
	{
		pBuff = *iter;
		delete pBuff;
		pBuff = NULL;
	}
	m_arrBuffer.clear(); 
	m_BufferListLock.Unlock();
}
/*********************************************************************************************************
** ��������: AllocateBuffer
** ��������: CUEServer::AllocateBuffer
**
** ����������  ����һ��buf
**
** �䡡��:  int nType
**          
** �䡡��:   CUEPacket*
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CSvrCommPacket* CUEServer::AllocateBuffer(int nType)
{
	CSvrCommPacket *pMsg = NULL;
	int nCnt = 0;
	m_FreeBufferListLock.Lock();
	if(!m_arrFreeBuffer.empty())
	{ //��������б���Ϊ�յĻ�����ô��ͷ��ȡ��һ��
		pMsg= m_arrFreeBuffer.front();
		m_arrFreeBuffer.pop_front();
	}
	m_FreeBufferListLock.Unlock();

	if (pMsg == NULL)
	{//����һ���µ�
		pMsg= new CSvrCommPacket();
	}
	ASSERT(pMsg);
	if (pMsg == NULL)
		return NULL;

	pMsg->m_nSeqNum = 0;
	pMsg->EmptyUsed();
	pMsg->SetOperation(nType);

	m_BufferListLock.Lock();
	m_arrBuffer.push_front(pMsg); //����ͷ��
	m_BufferListLock.Unlock();
	return pMsg;
}
/*********************************************************************************************************
** ��������: ReleaseBuffer
** ��������: CUEServer::ReleaseBuffer
**
** ����������  �ͷ�
**
** �䡡��:  CUEPacket * pBuff
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::ReleaseBuffer(CSvrCommPacket *pBuff)
{
	ASSERT(pBuff);
	if(pBuff==NULL)
		return FALSE;
	std::list<CSvrCommPacket *>::iterator iter;

	m_BufferListLock.Lock();
// 	iter = std::find(m_arrBuffer.begin(), m_arrBuffer.end(),pBuff  );
// 	if (iter != m_arrBuffer.end())
// 	{
// 		m_arrBuffer.erase( iter);
// 	}
	m_arrBuffer.remove(pBuff);
	m_BufferListLock.Unlock();
	//��ӵ������б���
	m_FreeBufferListLock.Lock();
	if(m_iMaxNumberOfFreeBuffer==0|| m_arrFreeBuffer.size() <m_iMaxNumberOfFreeBuffer)
	{//����ͷ����β������ν
	//	m_arrFreeBuffer.push_front( pBuff );
		m_arrFreeBuffer.push_back( pBuff );
	}
	else
	{
		// Delete the buffer. 
		if ( pBuff!=NULL )
			delete pBuff;
	}
	m_FreeBufferListLock.Unlock();
	pBuff=NULL;
	return TRUE;
}
/*********************************************************************************************************
** ��������: CreateCompletionPort
** ��������: CUEServer::CreateCompletionPort
**
** ����������  
**
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::CreateCompletionPort()
{
	SOCKET s= INVALID_SOCKET ;	
	// First open a temporary socket that we will use to create the
	// completion port.  In NT 3.51 it will not be necessary to specify
	// the FileHandle parameter of CreateIoCompletionPort()--it will
	// be legal to specify FileHandle as NULL.  However, for NT 3.5
	// we need an overlapped file handle.
 	s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if ( s == INVALID_SOCKET ) 
	{	
		return FALSE;
	}

	// Create the completion port that will be used by all the workers
	// threads.
	m_hCompletionPort = CreateIoCompletionPort( (HANDLE)s, NULL, 0, 0 );
	if ( m_hCompletionPort == NULL ) 
	{	
		closesocket( s );
		return FALSE;
	}

	closesocket( s );
	return TRUE;
}
/*********************************************************************************************************
** ��������: SetupListner
** ��������: CUEServer::SetupListner
**
** ����������  ��������
**
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::SetupListner()
{
	m_nListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);	
	if ( m_nListenSocket == INVALID_SOCKET )
	{
		return FALSE;
	}
	// Event for handling Network IO
	m_hEvent = WSACreateEvent();
	if ( m_hEvent == WSA_INVALID_EVENT )
	{	
		closesocket(m_nListenSocket);
		return FALSE;
	}
	// The listener is ONLY interested in FD_ACCEPT
	// That is when a client connects to or IP/Port
	// Request async notification
	int nRet = WSAEventSelect(m_nListenSocket,m_hEvent,	FD_ACCEPT);

	if ( nRet == SOCKET_ERROR )
	{
		CloseHandle(m_hEvent);
		closesocket(m_nListenSocket);
		return FALSE;
	}

	SOCKADDR_IN		saServer;	
	// Listen on our designated Port#
	saServer.sin_port = htons(m_nPortNumber);
	// Fill in the rest of the address structure
	saServer.sin_family = AF_INET;
	if (m_dwLocalIp != 0 && m_dwLocalIp != INADDR_NONE)
	{
		saServer.sin_addr.s_addr =  htonl( m_dwLocalIp );
	}
	else
	{
		saServer.sin_addr.s_addr = INADDR_ANY;
	}
	// bind our name to the socket
	nRet = bind(m_nListenSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
	if ( nRet == SOCKET_ERROR )
	{
		closesocket(m_nListenSocket);
		return FALSE;
	}

	// Set the socket to listen
	//nRet = listen(m_socListen, nConnections);
	nRet=listen(m_nListenSocket, 5);
	if ( nRet == SOCKET_ERROR )
	{
 		closesocket(m_nListenSocket);
		return FALSE;
	}

  	m_bAcceptConnections=TRUE;
  	m_pListenThread = AfxBeginThread(CUEServer::ListnerThreadProc, (void*)this, THREAD_PRIORITY_NORMAL);
	m_pListenThread->m_bAutoDelete = FALSE;
	m_pListenThread->ResumeThread();

	HANDLE pProcess = ::GetCurrentProcess();
	ASSERT(pProcess);
	//���������
	BOOL bRet = ::DuplicateHandle(pProcess,m_pListenThread->m_hThread,pProcess,&m_hListenHandle,DUPLICATE_SAME_ACCESS,true,DUPLICATE_SAME_ACCESS);
	//��֤�����Ƶľ��Ҫ��Ч
	ASSERT(bRet);

	return TRUE; 
}
/*********************************************************************************************************
** ��������: ListnerThreadProc
** ��������: CUEServer::ListnerThreadProc
**
** ���������� �����߳�
**
** �䡡��:  LPVOID pParam
**          
** �䡡��:   UINT
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
UINT CUEServer::ListnerThreadProc(LPVOID pParam)
{
	ASSERT(pParam);
	CUEServer* pThis = reinterpret_cast<CUEServer*>(pParam);
	if(pThis == NULL)
		return 0;

	while( !pThis->m_bShutDown )
	{
		DWORD dwRet;
		dwRet = WSAWaitForMultipleEvents(1, &pThis->m_hEvent,FALSE,	500,FALSE);	
  		if(pThis->m_bShutDown)
 			break;
		//��ʱ,����
		if (dwRet == WSA_WAIT_TIMEOUT)
			continue;
		WSANETWORKEVENTS events;
		int nRet = WSAEnumNetworkEvents(pThis->m_nListenSocket,	pThis->m_hEvent,&events);

		if (nRet == SOCKET_ERROR)
		{
			TRACE(_T("WSAEnumNetworkEvents error %ld\n"),WSAGetLastError());
			// ע���¼�
			WSAEventSelect(pThis->m_nListenSocket, (WSAEVENT)pThis->m_hEvent, 0);
			CloseHandle(pThis->m_hEvent);

			break;
		}
		if ( events.lNetworkEvents & FD_ACCEPT)
		{
		 	if ( events.iErrorCode[FD_ACCEPT_BIT] == 0 && pThis->m_bAcceptConnections && !pThis->m_bShutDown)
		 	{
				//SOCKADDR_IN	SockAddr;
				SOCKET		clientSocket=INVALID_SOCKET;
				int			nRet=-1;
				int			nLen=-1;
				 
				// accept the new socket descriptor			 
				nLen = sizeof(SOCKADDR_IN);
#ifdef SIMPLESECURITY
				clientSocket = WSAAccept(pThis->m_nListenSocket, NULL, &nLen,ConnectAcceptCondition,(DWORD)pThis); 
#else
				clientSocket = WSAAccept(pThis->m_nListenSocket,NULL,&nLen,0,0); 
#endif
				if (clientSocket == SOCKET_ERROR)
				{
					nRet = WSAGetLastError();
					if (nRet != WSAEWOULDBLOCK)
					{							 
						// Just log the error and return					 
						CString szLog;
					 	szLog.Format(_T("Wsaaccept() error: %s"),pThis->ErrorCode2Text(WSAGetLastError()));
						pThis->LogString(szLog,ERR_STR);
					}
				}
				else
				{//�и��µ����ӽ�����
					pThis->AssociateIncomingClientWithContext(clientSocket);
				}
			}
			else
			{
				TRACE(_T("Unknown network event error %ld\n"),WSAGetLastError());
				// ע���¼�
				WSAEventSelect(pThis->m_nListenSocket, (WSAEVENT)pThis->m_hEvent, 0);
				CloseHandle(pThis->m_hEvent);

				break;
			}	
		}
	}

	TRACE("Listner Died!\r\n");
	return 0xdead;
} 
/*********************************************************************************************************
** ��������: IOWorkerThreadProc
** ��������: CUEServer::IOWorkerThreadProc
**
** ����������  
**
** �䡡��:  LPVOID pParam
**          
** �䡡��:   UINT
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��17��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
UINT CUEServer::IOWorkerThreadProc(LPVOID pParam)
{
	CUEServer * pThis = reinterpret_cast<CUEServer*>(pParam);
	if (pThis == NULL)
		return 0;

	DWORD dwIoSize;
	ClientContext* lpClientContext = NULL; 
	CSvrCommPacket *pPacket = NULL;

	bool bError=false;
	HANDLE hCompletionPort = pThis->m_hCompletionPort;
	LPOVERLAPPED lpOverlapped;
	while ( !bError )
	{
		pPacket=NULL;
		lpClientContext=NULL;

		// Get a completed IO request. ��Զ�ȴ�
		BOOL bIORet = GetQueuedCompletionStatus(hCompletionPort,&dwIoSize,(LPDWORD) &lpClientContext,&lpOverlapped, INFINITE);
		// Simulate workload (for debugging, to find possible reordering)
		//Sleep(20);

		if (!bIORet)  
		{	// If Something whent wrong.. ���ִ����ˣ�������
			DWORD dwIOError = GetLastError();
			if(dwIOError != WAIT_TIMEOUT) // It was not an Time out event we wait for ever (INFINITE) 
			{	
				TRACE(_T("GetQueuedCompletionStatus errorCode: %i, %s\n"),WSAGetLastError(),pThis->ErrorCode2Text(dwIOError));			

				if (lpClientContext!=NULL)
				{					 
					//	 ERROR_NETNAME_DELETED Happens when the communication socket
					//	 is cancelled and you have pendling WSASend/WSARead that are not finished. 
					//	 Then the Pendling I/O (WSASend/WSARead etc..) is cancelled and we return with 
					//	 ERROR_NETNAME_DELETED.. 
					if(dwIOError==ERROR_NETNAME_DELETED) 
					{
						//TRACE("ERROR_NETNAME_DELETED\r\n");
						pThis->DisconnectClient(lpClientContext); 
						TRACE(">IOWORKER1 (%x)\r\n",lpClientContext);
						pThis->ReleaseClientContext(lpClientContext); //Later Implementati
					}
					else
					{
						// Should not get here if we do: disconnect the client and cleanup & report. 
						pThis->LogString( pThis->ErrorCode2Text(dwIOError),ERR_STR );
						pThis->DisconnectClient(lpClientContext); 
						TRACE(">IOWORKER2 (%x)\r\n",lpClientContext);
						pThis->ReleaseClientContext(lpClientContext); //Should we do this ? 
					}
					// Clear the buffer if returned. 
					pPacket=NULL;
					if(lpOverlapped!=NULL)
						pPacket=CONTAINING_RECORD(lpOverlapped, CSvrCommPacket, m_ol);
					if(pPacket!=NULL)
						pThis->ReleaseBuffer(pPacket);			
					continue;
				}
				// We shall never come here  
				// anyway this was an error and we should exit the worker thread
				bError = true;
				CString szLog;
				szLog = pThis->ErrorCode2Text(dwIOError);
				pThis->LogString(szLog,ERR_STR ); 
				szLog = _T("IOWORKER KILLED BECAUSE OF ERROR IN GetQueuedCompletionStatus");
				pThis->LogString(szLog,ERR_STR );

				pPacket=NULL;
				if(lpOverlapped!=NULL)
					pPacket=CONTAINING_RECORD(lpOverlapped, CSvrCommPacket, m_ol);
				if(pPacket!=NULL)
					pThis->ReleaseBuffer(pPacket);
				continue;
			}
		}
		if(lpClientContext==NULL&&pPacket==NULL&&pThis->m_bShutDown)
		{
			TRACE("lpClientContext==NULL \r\n"); 
			bError=true;
			OutputDebugString(_T("IO�����߳��յ��ź�׼���˳� \n"));
			break;
		}
		if(bIORet && lpOverlapped && lpClientContext) 
		{
			pPacket=CONTAINING_RECORD(lpOverlapped, CSvrCommPacket, m_ol);
			ASSERT(pPacket);
	 		if(pPacket!=NULL)
				pThis->ProcessIOMessage(pPacket, lpClientContext, dwIoSize);
		}			
	}
	OutputDebugString(_T("IO�����߳��˳� \n"));
	return 0x1;
}
/*********************************************************************************************************
** ��������: AssociateIncomingClientWithContext
** ��������: CUEServer::AssociateIncomingClientWithContext
**
** ����������  �и��µ����ӽ���
**
** �䡡��:  SOCKET clientSocket
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  This function do the Following: 
             1) Does some simpleSecutity Stuff (e.g one connection per client, etc..)
			 2) Allocates an Context for the Socket. 
			 3) Configures the Socket. 
			 4) Associate the Socket and the context with the completion port. 
			 5) Fires an IOInitialize So the IOWORKERS Start to work on the connection. 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::AssociateIncomingClientWithContext(SOCKET clientSocket)
{	
	ASSERT(clientSocket != 0 && clientSocket != INVALID_SOCKET);
	if (clientSocket == INVALID_SOCKET)
		return FALSE;

	if (m_bShutDown || !m_bAcceptConnections)
	{
		closesocket(clientSocket);
		return FALSE;
	}

	struct sockaddr_in from_addr;
	memset((void*)&from_addr,0,sizeof(from_addr));
	int nLen = sizeof(from_addr); 

	CString szLog;

	int nRtn = getpeername(clientSocket,(SOCKADDR*)&from_addr,&nLen);
	if (nRtn != SOCKET_ERROR)
	{
		szLog.Format(_T("�յ�����%d.%d.%d.%d:%d�����ӡ�"),from_addr.sin_addr.s_net ,from_addr.sin_addr.s_host ,
  			from_addr.sin_addr.s_lh ,from_addr.sin_addr.s_impno, htons(from_addr.sin_port));
  		LogString(szLog,NORMAL_STR);
	}

	BOOL bConnLimit = FALSE;
	// Close connection if we have reached the maximum nr of connections... 	
	m_ContextMapLock.Lock(); // Mus lock the m_ContextMapLock Protect (m_NumberOfActiveConnections) ??
	if(m_NumberOfActiveConnections>=m_iMaxNumConnections)
	{//�ﵽ���������
		// Disconnect. 	
		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( clientSocket, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct, sizeof(lingerStruct) );
		// Now close the socket handle. This will do an abortive or graceful close, as requested. 
		CancelIo((HANDLE) clientSocket);

		closesocket( clientSocket );
		clientSocket = INVALID_SOCKET;	
		bConnLimit = TRUE;
	}
	m_ContextMapLock.Unlock();

	if (bConnLimit)
	{//�ﵽ������ӣ�����
		szLog.Format(_T("�ﵽ����������ƣ�����%d.%d.%d.%d:%d�����ӱ��رա�"),from_addr.sin_addr.s_net ,from_addr.sin_addr.s_host ,
			from_addr.sin_addr.s_lh ,from_addr.sin_addr.s_impno, htons(from_addr.sin_port));
		LogString(szLog,ERR_STR);
	}

	// Create the Client context to be associated with the completion port
	ClientContext* pContext = AllocateContext();
	ASSERT(pContext);
	if(pContext!=NULL)
	{
		CopyMemory(& pContext->m_addr,&from_addr,sizeof(from_addr));
		pContext->m_nSocket = clientSocket;
		// M_ID is Used for Delete(). Should we remove this soon ? 
		pContext->m_nID=clientSocket;
		/* 
		* TCP_NODELAY	BOOL=TRUE Disables the "nagle algorithm for send coalescing" which delays
		* short packets in the hope that the application will send more data and allow
		* it to combine them into a single one to improve network efficiency.
		*/
		const char chOpt = 1;
		int nErr = setsockopt(pContext->m_nSocket, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char));
		if (nErr == -1)
		{
			TRACE(">AcceptIncomingClient(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}
		//��ӵ�HASH����
		if(AddClientContext(pContext))
		{	
			// Associate the new socket with a completion port.
			if (!AssociateSocketWithCompletionPort(clientSocket, m_hCompletionPort, (DWORD) pContext))
			{
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return FALSE;
			}
			// ������һ��IO����
			// Otherwise the Worker thread will remain blocked waiting for GetQueuedCompletionStatus...
			// The first message that gets queued up is ClientIoInitializing - see ThreadPoolFunc and 
			// IO_MESSAGE_HANDLER

			// Important!! EnterIOLoop must notify that the socket and the structure  
			// pContext have an Pendling IO operation ant should not be deleted.
			// This is nessesary to avoid Access violation. 
			
			EnterIOLoop(pContext);
			CSvrCommPacket *pBuff =AllocateBuffer(IOInitialize);
			if(pBuff!=NULL)
			{
				BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pBuff->m_ol);

				if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
				{          
					ASSERT(pBuff);
					ReleaseBuffer(pBuff);
					DisconnectClient(pContext);
					TRACE(">IOInitialize AcceptIncomingClient(%x)\r\n",pContext);
					ReleaseClientContext(pContext);
					return FALSE;
				}
			}
			else
			{
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return FALSE;
			}
		}
		else
		{//��ӵ�HASH����ʧ��
			return FALSE;
		}
	}
	else
	{//����һ�������Ļ���ʧ��
		shutdown(clientSocket,2);
		closesocket(clientSocket);
		return FALSE;
	}

	return TRUE;
}

/*********************************************************************************************************
** ��������: ProcessIOMessage
** ��������: CUEServer::ProcessIOMessage
**
** ����������  
**
** �䡡��:  CSvrCommPacket * pOverlapBuff
** �䡡��:  ClientContext * pContext
** �䡡��:  DWORD dwSize
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��28��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ProcessIOMessage(CSvrCommPacket *pOverlapBuff, ClientContext *pContext, DWORD dwSize)
{
	ASSERT(pContext && pOverlapBuff);
	if(pOverlapBuff==NULL)
		return;

	//	Sleep(rand()%50);
	switch (pOverlapBuff->GetOperation())
	{
	case IOInitialize :
		OnInitialize(pContext,dwSize,pOverlapBuff);
		break;
	case IORead :
		OnRead(pContext,pOverlapBuff);
		break;	
	case IOReadCompleted :
 		OnReadCompleted(pContext,dwSize,pOverlapBuff);
		break;
	case IOWrite :
		OnWrite(pContext,dwSize,pOverlapBuff);
		break;
	case IOWriteCompleted :
		OnWriteCompleted(pContext,dwSize,pOverlapBuff);
		break;

	case IOZeroByteRead : //  Workaround the the WSAENOBUFS error problem..See OnZeroByteRead. 
		OnZeroByteRead(pContext,pOverlapBuff);
		break;

	case IOZeroReadCompleted : //  Workaround the the WSAENOBUFS error problem.. 
		OnZeroByteReadCompleted(pContext,dwSize,pOverlapBuff);
		break;
#if defined TRANSFERFILEFUNCTIONALITY
	case IOTransmitFileCompleted : //  Workaround the the WSAENOBUFS error problem.. 
		OnTransmitFileCompleted(pContext,pOverlapBuff);
		break;
#endif

	case IOPostedPackage : 
		OnPostedPackage(pContext,pOverlapBuff);
		break;
	default:
		ReleaseBuffer(pOverlapBuff);
		break;
	} 
}

void CUEServer::NotifyNewConnection(ClientContext *pcontext)
{

}
/*********************************************************************************************************
** ��������: DisconnectClient
** ��������: CUEServer::DisconnectClient
**
** ����������  
**
** �䡡��:  ClientContext * pContext
** �䡡��:  BOOL bGraceful
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��19��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::DisconnectClient(ClientContext *pContext, BOOL bGraceful/*=FALSE*/)
{	
	if(pContext!=NULL)
	{	
		pContext->m_Lock.Lock();
		BOOL bDisconnect=pContext->m_nSocket!=INVALID_SOCKET;
		pContext->m_Lock.Unlock();
		// If we have an active  socket close it. 
		if(bDisconnect)
		{	
			CONTEXT_ITER iter ;
		//	stdext::hash_map <SOCKET,ClientContext*>::iterator iter ;
			// Remove it From m_ContextMap. 
			m_ContextMapLock.Lock();
			//Remove it from the m_ContextMapLock,
			iter = m_ContextMap.find( pContext->m_nSocket  );
			if (iter != m_ContextMap.end())
			{//�ҵ�
				m_ContextMap.erase(iter);
				m_NumberOfActiveConnections--;
			}
			m_ContextMapLock.Unlock();
			TRACE("Client %i, Disconnected %x.\r\n",pContext->m_nSocket,pContext);

			pContext->m_Lock.Lock();
			// Notify that we are going to Disconnect A client. 
			NotifyDisconnectedClient(pContext);
			pContext->m_Lock.Unlock();

#ifdef SIMPLESECURITY
			if(m_bOneIPPerConnection)
			{		
				//  Remove the IP address from list.. 
				sockaddr_in sockAddr;
				memset(&sockAddr, 0, sizeof(sockAddr));
				int nSockAddrLen = sizeof(sockAddr);	
				int iResult = getpeername(pContext->m_nSocket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

				if (iResult != INVALID_SOCKET)
				{
					void* pVoid=(void*)sockAddr.sin_addr.S_un.S_addr; 
					m_OneIPPerConnectionLock.Lock();
					POSITION pos=m_OneIPPerConnectionList.Find(pVoid);
					if ( pos!=NULL )
					{
						m_OneIPPerConnectionList.RemoveAt(pos); 
					}
					m_OneIPPerConnectionLock.Unlock();	
				}
			}
#endif	
			// If we're supposed to abort the connection, set the linger value on the socket to 0.
			if ( !bGraceful ) 
			{
				LINGER lingerStruct;
				lingerStruct.l_onoff = 1;
				lingerStruct.l_linger = 0;
				setsockopt( pContext->m_nSocket, SOL_SOCKET, SO_LINGER,	(char *)&lingerStruct, sizeof(lingerStruct) );
			}		 
			// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
			CancelIo((HANDLE) pContext->m_nSocket);
			closesocket( pContext->m_nSocket );
			pContext->m_nSocket = INVALID_SOCKET;
		}
#ifdef _DEBUG 
		TRACE("Context %x is is disconnected but not removed from Context map \r\n",pContext);
#endif 
	}
}
/*
* Notifyes that this Client Context Strukture is currently in the 
* IOCompetetion lopp and are used by a another thread. 
* This funktion and ExitIOLoop is used to avoid possible Access Violation 
*/
void CUEServer::EnterIOLoop(ClientContext *pContext)
{
	if(pContext!=NULL)
	{
		pContext->m_Lock.Lock();
		pContext->m_nNumberOfPendlingIO++;
		pContext->m_Lock.Unlock();
	}
}

/*
* Notifies that the ClientContext is no longer in used by thread x, and 
* have been removed from the competition port. This function decreses the  
* m_nNumberOfPendlingIO and returns it. 
* 
* if it return zero (0) then it is safe to delete the structure from the heap. 
*/
int CUEServer::ExitIOLoop(ClientContext *pContext)
{
	int nNumberOfPendlingIO=0;
	if(pContext!=NULL)
	{
		pContext->m_Lock.Lock();
		pContext->m_nNumberOfPendlingIO--;
		nNumberOfPendlingIO=pContext->m_nNumberOfPendlingIO;
#ifdef _DEBUG
		if(nNumberOfPendlingIO<0)
		{
			TRACE("Strange nNumberOfPendlingIO ERROR\r\n");
		}
		if(pContext->m_nSocket==INVALID_SOCKET)
			TRACE("ExitIOLoop->nNumberOfPendlingIO %i, Socket: %i (%x)\r\n", pContext->m_nNumberOfPendlingIO,pContext->m_nSocket,pContext);
#endif
		pContext->m_Lock.Unlock();

	}
	return nNumberOfPendlingIO; 
}
/*********************************************************************************************************
** ��������: AZeroByteRead
** ��������: CUEServer::AZeroByteRead
**
** ����������  
**
** �䡡��:  ClientContext * pContext
** �䡡��:  CSvrCommPacket * pPacket
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��28��
** ��  ע:  A workaround the WSAENOBUFS error problem. (For more info please see OnZeroBytesRead  
           Unlock the memory used by the OVELAPPED struktures. 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::AZeroByteRead(ClientContext *pContext, CSvrCommPacket *pPacket)
{
	ASSERT(pContext && pPacket);
	if (pContext == NULL)
		return FALSE;

	ASSERT( pContext->m_nSocket!=INVALID_SOCKET && pContext->m_nSocket!= 0 );
	if(pContext->m_nSocket!=INVALID_SOCKET && pContext->m_nSocket!= 0)
	{
// 		if(pPacket==NULL) 
// 			pPacket=AllocateBuffer(IOZeroByteRead);
// 		if(pPacket==NULL) 
// 		{			
// 			CString szLog = _T("AllocateBuffer(IOZeroByteRead) == NULL.");
// 			LogString(szLog,ERR_STR);
// 		 	ReleaseClientContext(pContext);
// 			return FALSE;
// 		}

		pPacket->SetOperation(IOZeroByteRead);

		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pPacket->m_ol); 	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{          
			ReleaseBuffer(pPacket);
		 	DisconnectClient(pContext);
			TRACE(">OnZeroByteRead(%x)\r\n",pContext);
		 	ReleaseClientContext(pContext);
			CString szLog;
			szLog.Format(_T("Disconnect in AZeroByteRead Possible Socket Error: %s"),ErrorCode2Text(WSAGetLastError()));
			LogString(szLog,ERR_STR);
			return FALSE;
		}
	}
	else
	{
		TRACE(">OnZeroByteRead2(%x)\r\n",pContext);
		ReleaseBuffer(pPacket);
	 	ReleaseClientContext(pContext);// Take care of it.
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************
** ��������: ProcessPackage
** ��������: CUEServer::ProcessPackage
**
** ����������   �������յ��ı��Ľ�����������зְ�����������ϵ�һ��������
**
** �䡡��:  ClientContext * pContext
** �䡡��:  DWORD dwIoSize
** �䡡��:  CSvrCommPacket * pOverlapBuff
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  Assumes that Packages arrive with A MINIMUMPACKAGESIZE header and builds Packages that 
           are noticed by the virtual function NotifyReceivedPackage 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ProcessPackage(ClientContext *pContext, DWORD dwIoSize, CSvrCommPacket *pPacket)
{
	ASSERT(dwIoSize <= MAX_PACKAGE_SIZE);
 	// We may have Several Pending reads. And therefor we have to check and handle partial Messages.  	 
	// First handle partial packages.  
	CSvrCommPacket *pBuffPartialMessage=NULL;
	pBuffPartialMessage=pContext->m_pPacket;
 
	// Process the incoming byte stream in pPacket
	bool done = false;
	do 
	{
		UINT nUsedBuffer=pPacket->GetUsed();
		done=true;	
		if ( nUsedBuffer)
		{
			UINT nSize = dwIoSize;
			//memmove(&nSize,pPacket->GetBuffer(),MIN_PACKAGE_SIZE);
			// We Have a full Package..
			ASSERT(nSize == dwIoSize);
			if ( nSize==nUsedBuffer )
			{
				NotifyReceivedPackage(pPacket,nSize,pContext);
				pPacket->EmptyUsed();
				done = true;
			}		
			else 
			{//����ı���			
				//pPacket->DUMP();
#ifdef SIMPLESECURITY
				AddToBanList(pContext->m_nSocket);
#endif
				ReleaseBuffer(pPacket);
				pPacket=NULL;
				DisconnectClient(pContext);
				break; 
			}
		}
		else if( nUsedBuffer>0 )
		{   //  Header  too small. 
			// nUsedBuffer < MINIMUMPACKAGESIZE
			// Add it to to the package overlapped buffer. 	
			// Let the remain be handled later. 
			pContext->m_pPacket=pPacket;
			pPacket=NULL;
			done=true;
		}
	} while ( !done );
	// Release the buffer if not used. 
	if ( pPacket!=NULL )
	{
		ReleaseBuffer(pPacket);
	}
}


void CUEServer::OnInitialize(ClientContext *pContext, DWORD dwIoSize,CSvrCommPacket *pOverlapBuff)
{
	// Do some init here.. 

	// Notify new connection. 
	pContext->m_Lock.Lock();
	NotifyNewConnection(pContext);
	pContext->m_Lock.Unlock();
 
// 	Operations using the IO completion port will always complete in the order that they were submitted.
// 	Therefore we start A number of pendling read loops (R) and at last a Zero byte read to avoid the WSAENOBUFS problem.  	
// 	The number of m_iNumberOfPendlingReads should not be so big that we get the WSAENOBUFS problem. 
	 
	// A ZeroByteLoop. EnterIOLoop is not needed here. Already done in previus call.
	AZeroByteRead(pContext,pOverlapBuff);

	// m_iNumberOfPendlingReads=1 by default. 
	int i = 0;
	for( i=0;i<m_iNumberOfPendlingReads;i++)
 	{
		EnterIOLoop(pContext); // One for each Read Loop
 		ARead(pContext);
 	}
}
/*********************************************************************************************************
** ��������: OnRead
** ��������: CUEServer::OnRead
**
** ����������  
**
** �䡡��:  ClientContext * pContext
** �䡡��:  CSvrCommPacket * pPacket
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��28��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::OnRead(ClientContext *pContext,CSvrCommPacket *pPacket/*=NULL*/)
{
	// issue a read request 
	ASSERT(pContext && pPacket);
	if(pContext&&!m_bShutDown)
	{
// 		if(pPacket==NULL)
// 		{
// 			pPacket=AllocateBuffer(IOReadCompleted);
// 			if(pPacket==NULL)
// 			{ 
// 				DisconnectClient(pContext);
// 				ReleaseClientContext(pContext);
// 				return;
// 			}
// 		}
		if(pPacket!=NULL)
		{
			pPacket->SetOperation(IOReadCompleted);
			pPacket->SetupRead();
			pPacket->m_nSeqNum = pContext->m_nCurReadSeqNum;
// 			if(m_bReadInOrder)
// 				MakeOrderdRead(pContext,pPacket);
//			else
			{//����һ��IO����
				DWORD dwIoSize=0;
				ULONG ulFlags = 0;
				UINT nRetVal = WSARecv(pContext->m_nSocket, 
					pPacket->GetWSABuffer(),
					1,
					&dwIoSize, 
					&ulFlags,
					&pPacket->m_ol, 
					NULL);
				if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
				{
					if(WSAGetLastError()!=WSAENOTSOCK)
					{
#ifndef _DEBUG
						// Remove Unnecessary disconnect messages in release mode.. 
						if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
#endif
						{
						
						}
					}
					ReleaseBuffer(pPacket);
					TRACE(">OnRead(%x)\r\n",pContext);
					DisconnectClient(pContext);
					ReleaseClientContext(pContext);
				}
			}
		}
	}
}
/*********************************************************************************************************
** ��������: OnReadCompleted
** ��������: CUEServer::OnReadCompleted
**
** ����������  
**
** �䡡��:  ClientContext * pContext
** �䡡��:  DWORD dwIoSize
** �䡡��:  CSvrCommPacket * pPacket
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��28��
** ��  ע:  ��ʱ�Ѿ��յ�������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::OnReadCompleted(ClientContext *pContext, DWORD dwIoSize,CSvrCommPacket *pPacket/*=NULL*/)
{
	ASSERT(pContext && pPacket);

	if (dwIoSize == 0||pPacket==NULL)
	{//������
		TRACE(">OnReadCompleted1(%x)\r\n",pContext);
		DisconnectClient(pContext);
		ReleaseClientContext(pContext);
		ReleaseBuffer(pPacket);
		return;
	}
	if(pContext)
	{		
		// Process The package assuming that it have a heap of size (MINIMUMPACKAGESIZE) 
		// That contains the size of the message. 
	 	/*
		* Lock the context so that no other thread enters �ProcessPackage?function, 
		* this is necessary to process the package in order. (When IOCP is used with 
		* several working IO threads the packages can be processed in wrong order (even 
		* if the TCP protocol guarantees ordered stream) because of the operative 
		* system process scheduling.
		* Comment and source code Added 9/10/2005
		*/
	
		//�˴�������Ҫ������װһ�����ݣ�ȷ������˳��
		// Insure That the Packages arrive in order. 		
// 		if(m_bReadInOrder)
// 			pPacket=GetNextReadBuffer(pContext,pPacket);

		while(pPacket!=NULL)
		{
			//TRACE("R> %i\r\n",pPacket->GetSequenceNumber());
			// Mark that we are Using the buffer..
			pPacket->Use(dwIoSize);
#ifdef TRANSFERFILEFUNCTIONALITY
			if(!pContext->m_bFileReceivedMode)
#endif
				//�յ������ݽ��д��������
				ProcessPackage(pContext,dwIoSize,pPacket);
#ifdef TRANSFERFILEFUNCTIONALITY
			else
				AddToFile(pContext,dwIoSize,pPacket);
#endif
			IncreaseReadSeqNum(pContext);
			pPacket=NULL;
// 			if(m_bReadInOrder)
// 				pPacket=GetNextReadBuffer(pContext);
		}
		ARead(pContext);
	}
}
void CUEServer::OnWrite(ClientContext *pContext, DWORD dwIoSize,CSvrCommPacket *pOverlapBuff)
{
	if(pContext!=NULL&&pContext->m_nSocket!=INVALID_SOCKET)
	{	
		//pContext->m_Lock.Lock();
 
		while(pOverlapBuff!=NULL)
		{
			/*
			* Comments about bug in OnWrite() added 051227.. 
			* 
			* This BUG was difficult to find. The bug was found after  6 hours of 
			* extensive debugging  with several debug tools as Rational Test Suite, 
			* SoftICe , VC++ DEBUG, GLOWCODE, etc.  I Found that in some rarely bizarre 
			* cases  (when a client rapidly disconnect & reconnect, etc..)  we get an 
			* access violation , etc. First of all we had one ReleaseClientContext to many 
			* in OnWrite() which caused access violation. Second when I remove it, I found 
			* that sometimes the client specific data (e.g. ClientContext) does not removed/relesed 
			* from memory, even if the client is disconnected. The reason in not 
			* intuitive and do not ask me how I figured it out. The problem occurs 
			* when an send is not ordered (see http://www.codeproject.com/internet/iocp_server_client.asp, 
			* section "3.6.2 The package reordering problem" for more information ) and 
			* we call the function GetNextSendBuffer(pContext,pOverlapBuff); (above) in Onwrite(..), 
			* to get the correct buffer to process. At exactly this point the remote client disconnects
			* and this leads to the bug. Now I got tired of explaining this hassling stuff, so lets 
			* go to the business the fix is below.. 
			*/  
			pOverlapBuff->SetOperation(IOWriteCompleted);
			pOverlapBuff->SetupWrite();	
			ULONG ulFlags = 0;
			DWORD dwSendNumBytes = 0;

			int nRetVal = WSASend(pContext->m_nSocket, 
				pOverlapBuff->GetWSABuffer(),
				1,
				&dwSendNumBytes, 
				ulFlags,
				&pOverlapBuff->m_ol, 
				NULL);

			if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING ) 
			{
				if(WSAGetLastError()!=WSAENOTSOCK)
				{
#ifndef _DEBUG
					// Remove Unnecessary disconnect messages in release mode.. 
					if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
#endif	
					{						 
					}
				}
				ReleaseBuffer(pOverlapBuff);
				DisconnectClient(pContext);
				pOverlapBuff=NULL;
				/* "the bug fix 051227": Check if we need to go out of some more pending IO.
				(if our send is not processed in order) */ 	
				IncreaseSendSeqNum(pContext);
				TRACE(">OnWrite(%x)\r\n",pContext);
				ReleaseClientContext(pContext); 	// pContext may not exist after this call 	
				//break; // removed due to fix. 
			}
			else
			{
				IncreaseSendSeqNum(pContext);
				//TRACE("W> %i\r\n",pOverlapBuff->GetSequenceNumber());
				pOverlapBuff=NULL;
			}
		}
	}
	else
	{
		TRACE(">OnWrite2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
		ReleaseClientContext(pContext); //Later Implementation 
	}
}

void CUEServer::OnWriteCompleted(ClientContext *pContext, DWORD dwIoSize,CSvrCommPacket *pOverlapBuff)
{
	if(pContext!=NULL)
	{
		if (pOverlapBuff!=NULL)
		{
			if(pOverlapBuff->GetUsed()!=dwIoSize)
			{
				CString szLog;
				szLog.Format(_T("The whole message was not Sent.: %s"),ErrorCode2Text(WSAGetLastError()));
				ReleaseBuffer(pOverlapBuff);
				LogString(szLog,ERR_STR);
			}
			else
			{
				pContext->m_Lock.Lock();
				NotifyWriteCompleted(pContext,dwIoSize,pOverlapBuff);
				pContext->m_Lock.Unlock();
				ReleaseBuffer(pOverlapBuff);
			}
		}
		
		// We have finished a Complete LOOP, if no pending IO is in the competition port remove the client. 
		// We have always a Read request in the IO port if we have a Connection 
		
		//TRACE(">OnWriteCompleted()\r\n");
		//ExitIOLoop(pContext);
		ReleaseClientContext(pContext);
	}
}


void CUEServer::OnPostedPackage(ClientContext *pContext, CSvrCommPacket *pOverlapBuff)
{
	ASSERT(pContext);
	if( pContext == NULL)
 		return; 

	if ( pOverlapBuff)
	{
		UINT nSize = 0;
	//	memmove(&nSize,pOverlapBuff->GetBuffer(),MIN_PACKAGE_SIZE);
		pContext->m_Lock.Lock();
		NotifyReceivedPackage(pOverlapBuff,nSize,pContext);
		pContext->m_Lock.Unlock();
		ReleaseBuffer(pOverlapBuff);
	}
	ReleaseClientContext(pContext);// Exit IOLoop	
}
 
/*********************************************************************************************************
** ��������: ASend
** ��������: CUEServer::ASend
**
** ����������  �첽����
**
** �䡡��:  ClientContext * pContext
** �䡡��:  CUEPacket * pOverlapBuff
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��18��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::ASend(ClientContext *pContext,CSvrCommPacket *pOverlapBuff)
{
	if(pContext==NULL)
		return FALSE;
	// We must be safe before we start doing things. 
#ifdef TRANSFERFILEFUNCTIONALITY
	if(pContext->m_nSocket!=INVALID_SOCKET&&pOverlapBuff!=NULL&&!pContext->m_bFileSendMode)
#else
	if(pContext->m_nSocket!=INVALID_SOCKET&&pOverlapBuff!=NULL)
#endif
	{	 
		// Important!! Notifies that the socket and the structure  
		// pContext have an Pending IO operation ant should not be deleted.
		// This is necessary to avoid Access violation. 	 
		EnterIOLoop(pContext); 		 
		// If we are sending in order		 
	//	if(m_bSendInOrder)
	//		SetSendSequenceNumber(pContext,pOverlapBuff); 

		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, pOverlapBuff->GetUsed(), (DWORD) pContext, &pOverlapBuff->m_ol);
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			TRACE(">ASend(%x)\r\n",pContext);
		//	ReleaseClientContext(pContext); // Because of EnterIOLoop. 
			return FALSE;
		}
		return TRUE;
	}
	// Some Thing is Wrong Release the buffer and return. 
	ReleaseBuffer(pOverlapBuff);
	pOverlapBuff=NULL;
	return FALSE;
} 
/*********************************************************************************************************
** ��������: ARead
** ��������: CUEServer::ARead
**
** ���������� Makes a asynchrony Read by posting a IORead message into completion port who invoces a Onread.  
**
** �䡡��:  ClientContext * pContext
** �䡡��:  CSvrCommPacket * pPacket
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  The read is not made directly to distribute CPU power fairly between the connections. 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::ARead(ClientContext *pContext, CSvrCommPacket *pPacket /*=NULL*/)
{
	ASSERT(pContext);
	if (pContext == NULL)
		return FALSE;
	ASSERT(pContext->m_nSocket!=INVALID_SOCKET && pContext->m_nSocket!=0);
	if(pContext->m_nSocket!=INVALID_SOCKET && pContext->m_nSocket!=0)
	{//��ϵͳ����һ�� ���Ļ�������Ȼ��Ͷ�ݸ�IO�������߳�
		if(pPacket==NULL) 
			pPacket=AllocateBuffer(IORead);

		if(pPacket==NULL) 
		{			
			ReleaseClientContext(pContext);
			return FALSE;
		}

		pPacket->SetOperation(IORead);
		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pPacket->m_ol);  	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pPacket);
			TRACE(">ARead(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}
	}
	else
	{
		TRACE(">ARead2(%x)\r\n",pContext);
		ReleaseBuffer(pPacket);
		ReleaseClientContext(pContext);// Take care of it.
		return FALSE;
	}
	return TRUE;
}


/*
* Closes all the Sockets and removes all the buffer and ClientContext.  
*/ 
void CUEServer::FreeClientContext()
{	
	ClientContext *pContext=NULL;
	m_ContextMapLock.Lock();
	// First Delete all the objekts.
	CONTEXT_ITER iter = m_ContextMap.begin();
	for ( ; iter != m_ContextMap.end(); ++iter)
	{
		if (iter->first != 0 && iter->first != INVALID_SOCKET)
		{
			pContext = iter->second;
			LINGER lingerStruct;
			lingerStruct.l_onoff = 1;
			lingerStruct.l_linger = 0;
			setsockopt( pContext->m_nSocket, SOL_SOCKET, SO_LINGER,
				(char *)&lingerStruct, sizeof(lingerStruct) );
			// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
			CancelIo((HANDLE) pContext->m_nSocket);
			//while (!HasOverlappedIoCompleted((LPOVERLAPPED)pContext)) 
			//	Sleep(2);
			closesocket( pContext->m_nSocket );
		}
		pContext->m_nSocket = INVALID_SOCKET;
		ASSERT(pContext->m_pPacket);
		ReleaseBuffer(pContext->m_pPacket);
 
		delete pContext;
		pContext = NULL;
	}
 
	m_ContextMap.clear();
	m_ContextMapLock.Unlock(); 
	 
	// Remove The stuff in FreeContext list
	m_bAcceptConnections=FALSE;
	std::list <ClientContext *> ::iterator iter_free;
	m_FreeContextListLock.Lock(); 
	
	for (iter_free = m_arrFreeContext.begin(); iter_free != m_arrFreeContext.end();++ iter_free)
	{
	//	(*iter_free)->m_nSocket = INVALID_SOCKET;
		delete *iter_free;
	}
	m_arrFreeContext.clear();
	m_FreeContextListLock.Unlock();
}
/*********************************************************************************************************
** ��������: AllocateContext
** ��������: CUEServer::AllocateContext
**
** ����������   AllocateContext. Creates a context in the heap with new or reuse context 
**             which is in the m_FreeContextList linked list. 
**          
** �䡡��:   ClientContext*
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��18��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
ClientContext* CUEServer::AllocateContext()
{
	ClientContext* pContext = NULL;
	if ( !m_bShutDown )
	{
	 	m_FreeContextListLock.Lock();
	 
		if (  m_arrFreeContext.empty() )
		{
			pContext=new ClientContext();
		}
		else
		{
			pContext = m_arrFreeContext.back();
			m_arrFreeContext.pop_back();
		}
		m_FreeContextListLock.Unlock();
	}
	ASSERT(pContext);

	pContext->m_Lock.Lock();
	pContext->m_nID=0;
	pContext->m_nSocket=INVALID_SOCKET;
	pContext->m_nNumberOfPendlingIO=0;
 	pContext->m_nCurSendSeqNum=pContext->m_nCurReadSeqNum=1;
	pContext->m_pPacket=NULL; 

	NotifyNewClientContext(pContext);
	pContext->m_Lock.Unlock();

	return pContext;
} 
/*********************************************************************************************************
** ��������: ReleaseClientContext
** ��������: CUEServer::ReleaseClientContext
**
** ����������  Releases the Client Context. (put it into freeClientContext or delete it)
**
** �䡡��:  ClientContext * pContext
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��7��18��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
inline BOOL CUEServer::ReleaseClientContext(ClientContext *pContext)
{
	ASSERT(pContext);
	BOOL bRet=FALSE;	
	if(pContext!=NULL)
	{ 
		// We are removing this pContext from the penling IO port. 
		int nNumberOfPendlingIO=ExitIOLoop(pContext);
		// We Should not get an EnterIOLoopHere Because the client are disconnected. 
#ifdef _DEBUG		
		if(nNumberOfPendlingIO<0)
		{
			TRACE("FATAL ERROR AccessViolation possible\r\n");
			TRACE("Releasing %i(%x) nNumberOfPendlingIO=%i.\r\n",pContext->m_nSocket,pContext,nNumberOfPendlingIO);
		}
		ASSERT(nNumberOfPendlingIO>=0);
#endif
		// If no one else is using this pContext and we are the only owner. Delete it. 
		if(nNumberOfPendlingIO==0)
		{
			// Remove it From m_ContextMap. 

			pContext->m_Lock.Lock();
			NotifyContextRelease(pContext);
			if (pContext->m_pPacket)
			{
				ReleaseBuffer(pContext->m_pPacket);
			}			

		 	// Added. 
			pContext->m_nCurReadSeqNum=0;
		 	pContext->m_nCurSendSeqNum=0;
			pContext->m_Lock.Unlock();

			// Move the Context to the free context list (if Possible). 
			m_FreeContextListLock.Lock();	

			if(m_arrFreeContext.size()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
			{
				m_arrFreeContext.push_front(pContext);
			//	bRet=m_arrFreeContext.AddHead((void*)pContext)!=NULL;
			//	m_arrFreeContext.insert( m_arrFreeContext.begin(), pContext );
				TRACE("Putting (%x) in Freecontext list nNumberOfPendlingIO=%i.\r\n",pContext,nNumberOfPendlingIO);
			}
			else // Or just delete it. 
			{
				if(pContext)
				{
					TRACE("Context (%x) RIP\r\n",pContext);
					pContext->m_nSocket = INVALID_SOCKET;
					delete pContext;
					pContext=NULL;
				}
			}
			m_FreeContextListLock.Unlock();
			return TRUE; 	
		}
	}
	return FALSE; 
}
/*********************************************************************************************************
** ��������: AddClientContext
** ��������: CUEServer::AddClientContext
**
** ����������  ���һ���ͻ��˵������ĵ� HASH����
**
** �䡡��:  ClientContext * pContext
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::AddClientContext(ClientContext *pContext)
{
	ClientContext *pTempContext=NULL;
	CONTEXT_ITER iter ;
	unsigned int KeyID= 0;
	m_ContextMapLock.Lock();
	KeyID=pContext->m_nSocket;	 
	// Check if we already have a such key. 	 
	iter = m_ContextMap.find( KeyID );
	if (iter != m_ContextMap.end())
	{//�ҵ��ˣ����ظ�
		AbortiveClose(pContext);
		m_ContextMapLock.Unlock();
		return FALSE;
	}
	// Add it to the Map. 
	// What if this fail ? 
	pContext->m_nID=KeyID;
	m_ContextMap.insert(CONTEXT_PAIR(KeyID,pContext));	 
	m_NumberOfActiveConnections++;
	m_ContextMapLock.Unlock(); 
 	return TRUE;
}

BOOL CUEServer::AssociateSocketWithCompletionPort(SOCKET socket, HANDLE hCompletionPort, DWORD dwCompletionKey)
{
	HANDLE h = CreateIoCompletionPort((HANDLE) socket, hCompletionPort, dwCompletionKey, 0);
	return h == hCompletionPort;
}
/*********************************************************************************************************
** ��������: AbortiveClose
** ��������: CUEServer::AbortiveClose
**
** �����������쳣�ر�  
**
** �䡡��:  ClientContext * pContext
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��27��
** ��  ע:   Same as Disconnect Client but we does not try to remove the context from the Context Map 
             m_ContextMap.
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::AbortiveClose(ClientContext *pContext)
{
	// Notify that we are going to Disconnect A client. 
	NotifyDisconnectedClient(pContext);
	// If we have an active  socket close it. 
	if(pContext->m_nSocket!= INVALID_SOCKET && pContext->m_nSocket != 0 )
	{
		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( pContext->m_nSocket, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct, sizeof(lingerStruct) );	
		// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
		CancelIo((HANDLE) pContext->m_nSocket);
		closesocket( pContext->m_nSocket );
		pContext->m_nSocket = INVALID_SOCKET;
	}

	// Move the Context to the free context list or kill it. 
	m_FreeContextListLock.Lock();
	if(m_arrFreeContext.size()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
		m_arrFreeContext.push_back(pContext);
	else
	{
		if(pContext)
			delete pContext;
	}
	m_FreeContextListLock.Unlock();
}

void CUEServer::NotifyDisconnectedClient(ClientContext *pContext)
{

}


void CUEServer::NotifyNewClientContext(ClientContext *pContext)
{
	// Add some init here 	
}

void CUEServer::NotifyContextRelease(ClientContext *pContext)
{
	// add some extra clean up here. 
}
 
/*
*	Called when a write is completed, this function is ofen used
*  for progressbars etc (e.g indicates how much is send in bytes) 
*/

void CUEServer::NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize, CSvrCommPacket *pOverlapBuff)
{
	// The pOverlapBuff Buffer are Successfully sended. 
}

/*
*	An package is received.. 
*/
void CUEServer::NotifyReceivedPackage(CSvrCommPacket *pOverlapBuff,int nSize,ClientContext *pContext)
{
	if(pContext)
	{
		CString szLog;
		szLog.Format(_T("Recv %d - %d"),nSize,pOverlapBuff->m_nSeqNum);
		LogString(szLog,NORMAL_STR);
	}
}




void CUEServer::OnZeroByteReadCompleted(ClientContext *pContext, DWORD dwIoSize,CSvrCommPacket *pOverlapBuff/*=NULL*/)
{
	ASSERT(pContext && pOverlapBuff);
	if(pContext)
	{
		// Make a Loop. 
		AZeroByteRead(pContext,pOverlapBuff);	
	}
}

/* 
OnZeroByteRead(ClientContext *pContext) the workaround 
the WSAENOBUFS error problem.   

This Bugg was a very difficult one.. When I stresstested this server code the
server hung after a while. I first thougt that this was a memleak problem or 
deadlock problem. But after a some hours I found that it is because of the system 
WSAENOBUFS error. 

With every overlapped send or receive operation, it is probable that 
the data buffers submitted will be locked. When memory is locked, it 
cannot be paged out of physical memory. The operating system imposes 
a limit on the amount of memory that may be locked. When this limit 
is reached, overlapped operations will fail with the WSAENOBUFS error. 
If a server posts many overlapped receives on each connection, this 
limit will be reached as the number of connections grow. If a server a
nticipates handling a very high number of concurrent clients, the server 
can post a single zero byte receive on each connection. Because there is 
no buffer associated with the receive operation, no memory needs to be 
locked. With this approach, the per-socket receive buffer should be left 
intact because once the zero-byte receive operation completes, the server 
can simply perform a non-blocking receive to retrieve all the data buffered 
in the socket's receive buffer. There is no more data pending when the 
non-blocking receive fails with WSAEWOULDBLOCK. This design would be for 
servers that require the maximum possible concurrent connections while 
sacrificing the data throughput on each connection.
Of course, the more you are aware of how the clients will be interacting 
with the server, the better. In the previous example, a non-blocking receive 
is performed once the zero-byte receive completes to retrieve the buffered 
data. If the server knows that clients send data in bursts, then once the 
zero-byte receive completes, it may post one or more overlapped receives 
in case the client sends a substantial amount of data 
(greater than the per-socket receive buffer that is 8 KB by default). */
void CUEServer::OnZeroByteRead(ClientContext *pContext,CSvrCommPacket *pOverlapBuff/*=NULL*/)
{
	ASSERT(pContext && pOverlapBuff);
	if(pContext)
	{
		// issue a Zeroread request 
		DWORD dwIoSize=0;
		ULONG  ulFlags = 0;
// 		if(pOverlapBuff==NULL)
// 		{
// 			pOverlapBuff=AllocateBuffer(IOZeroReadCompleted);
// 			if(pOverlapBuff==NULL)
// 			{
// 				DisconnectClient(pContext);
// 				ReleaseClientContext(pContext);
// 				return; 
// 			}
// 		}
		pOverlapBuff->SetOperation(IOZeroReadCompleted);
		pOverlapBuff->SetupZeroByteRead(); 

		UINT nRetVal = WSARecv(pContext->m_nSocket, 
			pOverlapBuff->GetWSABuffer(),
			1,
			&dwIoSize, 
			&ulFlags,
			&pOverlapBuff->m_ol, 
			NULL);

		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
		{
			if(WSAGetLastError()!=WSAENOTSOCK)
			{
#ifndef _DEBUG
				// Remove Unnecessary disconnect messages in release mode.. 
				if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
				{
					;
				}
#endif	
			}
			ReleaseBuffer(pOverlapBuff);
			TRACE(">OnZeroByteRead(%x)\r\n",pContext);
			DisconnectClient(pContext);			
			ReleaseClientContext(pContext); //Later Implementation 
		}
	}
}
void CUEServer::IncreaseReadSeqNum(ClientContext *pContext)
{
	if (pContext!=NULL)
	{
		pContext->m_Lock.Lock();
		// increase or reset the sequence number 
		//pContext->m_nCurReadSeqNum=(pContext->m_nCurReadSeqNum+1)%MAX_SEQ_NUM;
		pContext->m_nCurReadSeqNum ++;
		if (pContext->m_nCurReadSeqNum >  MAX_SEQ_NUM)
		{
			pContext->m_nCurReadSeqNum = 1;
		}
		pContext->m_Lock.Unlock();
	}
}


void CUEServer::IncreaseSendSeqNum(ClientContext *pContext)
{
	if (pContext!=NULL)
	{
		pContext->m_Lock.Lock();
		// increase or reset the sequence number 
	//	pContext->m_nCurSendSeqNum=(pContext->m_nCurSendSeqNum+1)%MAX_SEQ_NUM;
		pContext->m_nCurSendSeqNum ++;
		if(pContext->m_nCurSendSeqNum >  MAX_SEQ_NUM)
		{
			pContext->m_nCurSendSeqNum = 1;
		}
		pContext->m_Lock.Unlock();
	}
}
/*
* Move to CIOBUFFER ? 
*/
CSvrCommPacket * CUEServer::SplitBuffer(CSvrCommPacket *pBuff, UINT nSize)
{
	ASSERT(pBuff && nSize >= 0 && nSize <= MAX_PACKAGE_SIZE);
	if(pBuff== NULL || nSize <= 0 || nSize > MAX_PACKAGE_SIZE)
		return NULL;

	CSvrCommPacket *pBuff2=NULL;
	pBuff2=AllocateBuffer(0);
	if(pBuff2==NULL)
		return NULL;
	pBuff2->m_nSeqNum = (pBuff->m_nSeqNum);

	if(!pBuff2->AddData(pBuff->GetBuffer(),nSize))
	{
		ReleaseBuffer(pBuff2);
	//	delete pBuff2;
		return NULL;
	}

	if(!pBuff->Flush(nSize))
	{
		ReleaseBuffer(pBuff2);
	//	delete pBuff2;
		return NULL;
	}

	return pBuff2;
} 
/*********************************************************************************************************
** ��������: AddAndFlush
** ��������: CUEServer::AddAndFlush
**
** ����������  ��From�ƶ����ݵ�To
**
** �䡡��:  CSvrCommPacket * pFromBuff
** �䡡��:  CSvrCommPacket * pToBuff
** �䡡��:  UINT nSize
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  Adds the nSize bytes from pFromBuff to pToBuff, and removes the data from pFromBuff.
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::AddAndFlush(CSvrCommPacket *pFromBuff, CSvrCommPacket *pToBuff, UINT nSize)
{
	ASSERT(pFromBuff && pToBuff && nSize);
	if(pFromBuff==NULL||pToBuff==NULL||nSize<=0)
		return FALSE;

	if(!pToBuff->AddData(pFromBuff->GetBuffer(),nSize))
	{
		return FALSE;
	}

	if(!pFromBuff->Flush(nSize))
	{
		return FALSE;
	}
	return TRUE;
}
/*********************************************************************************************************
** ��������: DisconnectAll
** ��������: CUEServer::DisconnectAll
**
** ����������  Just fakes that the client side have closed the connection.. 
**              We leave everyting to the IOWorkers to handle with Disconnectclient. 
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::DisconnectAll()
{
	std::list <ClientContext *> arrContex;
	std::list <ClientContext*>::iterator it_list;
	ClientContext *pClientContext = NULL;

	m_ContextMapLock.Lock();
	
	// First Delete all the objects.
	CONTEXT_ITER iter  = m_ContextMap.begin();
	for ( ; iter != m_ContextMap.end() ; ++iter)
	{
		ASSERT(  (iter)->second);
		if ( (iter)->second )
		{
			pClientContext = iter->second;
			arrContex.push_back( pClientContext );
		//	DisconnectClient((iter)->second);
		}
	} 
	for ( it_list = arrContex.begin(); it_list != arrContex.end(); ++it_list )
	{
		DisconnectClient(*it_list);
	}

	m_ContextMap.clear();
	arrContex.clear();
	 
	m_ContextMapLock.Unlock(); 

#ifdef _DEBUG
	m_BufferListLock.Lock();

	int nSize = m_arrBuffer.size();
	if (nSize >0)
	{
		TRACE("Warning Buffer is still in use even if all users are gone. %i Buffers are inuse state. \r\n",nSize);
		std::list <CSvrCommPacket *>::iterator iter = m_arrBuffer.begin();
		for ( ; iter != m_arrBuffer.end(); ++iter)
		{
			ASSERT(*iter);
			if (*iter)
			{
				TRACE("pPacket(%x)->GetOperation()=%i\r\n",*iter,(*iter)->GetOperation());
			}
		}	 
	}
	else
	{
		TRACE("BUFFER is now Empty\r\n");
	}
	m_BufferListLock.Unlock();
#endif
}  
/*********************************************************************************************************
** ��������: ShutDown
** ��������: CUEServer::ShutDown
**
** ����������  Closes the Server and frees the memory. 
**            We are leaking some small amount of memory (OVERLAPPEDSTRUKTUR)  
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��29��
** ��  ע:  
          Error in Disconnect.. (some how we have to wait until the Competionport is finished with the data). 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ShutDown()
{
	CString szLog;
	if(m_bServerStarted)
	{
#if defined SIMPLESECURITY	
		m_OneIPPerConnectionLock.Lock();
		if(!m_OneIPPerConnectionList.IsEmpty())
			m_OneIPPerConnectionList.RemoveAll();
		m_OneIPPerConnectionLock.Unlock();

		m_BanIPLock.Lock();
		m_BanIPList.RemoveAll();
		m_BanIPLock.Unlock();
#endif
		szLog = _T("Shutdown initialized."); 
		LogString(szLog,NORMAL_STR);
		m_bAcceptConnections=FALSE;
		szLog = _T("Sending shutdown signal to logical worker threads.");  
		LogString(szLog,NORMAL_STR);

		ShutDownListenProc( );

	  //	ShutDownWorkers();

		// We Let the IOWorker Take care of the last packets and die. 
		szLog = _T("Disconnecting all the Connections...");   
		LogString(szLog,NORMAL_STR);

 		DisconnectAll();

		szLog = _T("Sending shutdown signal to IO worker threads.");   
		LogString(szLog,NORMAL_STR);

		m_bShutDown=TRUE;
 		ShutDownIOWorkers();

		szLog = _T("Closing Completion port..");   
		LogString(szLog,NORMAL_STR);
 
		// Close the CompletionPort and stop any more requests (Stops the Listner) 
		CloseHandle(m_hCompletionPort);
		if(m_nPortNumber>0)
		{
 			szLog = _T("Closing listner thread.");   
			LogString(szLog,NORMAL_STR);

			WSACloseEvent(m_hEvent);
			closesocket(m_nListenSocket);
		}
		szLog = _T("Deallocate memory used for Clients. ");   
		LogString(szLog,NORMAL_STR);
 
		FreeClientContext();
		szLog = _T("Deallocate memory used for Buffers. ");   
		LogString(szLog,NORMAL_STR);
 
		FreeBuffers();
		m_bServerStarted=FALSE;
	}
}

BOOL CUEServer::Start(int nPort,int iMaxNumConnections, int nOfWorkers,int iMaxNumberOfFreeBuffer,int iMaxNumberOfFreeContext, BOOL bOrderedSend, BOOL bOrderedRead, int iNumberOfPendlingReads)
{
	m_iMaxNumberOfFreeBuffer=iMaxNumberOfFreeBuffer;
	
	m_iMaxNumConnections=iMaxNumConnections; //��������� 
	m_nPortNumber=nPort;                     //�������˿ں�

	m_nOfWorkers=nOfWorkers;

	m_iMaxNumberOfFreeContext=iMaxNumberOfFreeContext;
	m_bShutDown=FALSE;
// 	m_bReadInOrder=bOrderedRead;
// 	m_bSendInOrder=bOrderedSend;
	m_iNumberOfPendlingReads=iNumberOfPendlingReads;

	SYSTEM_INFO SystemInf;
	GetSystemInfo(&SystemInf);

	m_iMaxIOWorkers=SystemInf.dwNumberOfProcessors*2;

	return Startup();
}
/*********************************************************************************************************
** ��������: SetupIOWorkers
** ��������: CUEServer::SetupIOWorkers
**
** ����������  ����IO�����߳�
**
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  ��Ҫ�Ż���
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::SetupIOWorkers()
{
	CWinThread* pWorkerThread=NULL;
	unsigned int i = 0;
	CIOWorkTask *pTask = NULL;
	for( i=0; i<m_iMaxIOWorkers;i++)
	{
		pWorkerThread=AfxBeginThread(CUEServer::IOWorkerThreadProc, (void*)this,THREAD_PRIORITY_NORMAL);
		ASSERT(pWorkerThread);
		if(pWorkerThread)
		{
			pWorkerThread->m_bAutoDelete = FALSE;
			pWorkerThread->ResumeThread();

			pTask = new CIOWorkTask;
			pTask->m_nId = i+1;
			pTask->m_pThread = pWorkerThread;

			HANDLE pProcess = ::GetCurrentProcess();
			ASSERT(pProcess);
			//���������
			BOOL bRet = ::DuplicateHandle(pProcess,pWorkerThread->m_hThread,pProcess,& (pTask->m_hTask),DUPLICATE_SAME_ACCESS,true,DUPLICATE_SAME_ACCESS);
			//��֤�����Ƶľ��Ҫ��Ч
			ASSERT(bRet);

			m_IOWorkerList.push_back(pTask);
		}
		else
		{
			CString szLog;
		 	szLog.Format(_T("Error Couldnot start worker: %s"),ErrorCode2Text(WSAGetLastError()));
			LogString(szLog,ERR_STR);
 			return FALSE;
		}
	}
	m_nIOWorkers=m_IOWorkerList.size();
	return TRUE; 
}
/*********************************************************************************************************
** ��������: ShutDownIOWorkers
** ��������: CUEServer::ShutDownIOWorkers
**
** ����������  Shuttingdown the IOWOrkers..
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��25��
** ��  ע:  We put a NULL in CompletionPort and set the m_bShutDown FLAG.Then we wait for the IOWorkes to 
            finish the works in the CompletionPort and exit. 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ShutDownIOWorkers()
{
	m_bShutDown=TRUE;
	// Should wait for All IOWorkers to Shutdown.. 
	BOOL bIOWorkersRunning=TRUE;
	CWinThread* pThread=NULL;
 
	// Check if the IOWorkers are terminated.. 	
	std::vector <CIOWorkTask *>::iterator iter = m_IOWorkerList.begin();
	for ( ; iter != m_IOWorkerList.end(); ++iter)
	{
		// Send Empty Message into CompletionPort so that the threads die. 
		PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) NULL, NULL);
		Sleep(10);
	} 
 
	for ( iter = m_IOWorkerList.begin(); iter != m_IOWorkerList.end(); ++iter)
	{
	 //	 Send Empty Message into CompletionPort so that the threads die. 
	 //	PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) NULL, NULL);
	 //	Sleep(10);
	 	pThread = (*iter)->m_pThread;
		ASSERT(pThread && (*iter)->m_hTask);
		if(pThread && (*iter)->m_hTask )
		{
			Common::WaitForThreadToTerminate( (*iter)->m_hTask );
			delete pThread;
			pThread = NULL;
			delete (*iter);
		}
	}
	m_IOWorkerList.clear();
}
/*********************************************************************************************************
** ��������: ShutDownListenProc
** ��������: CUEServer::ShutDownListenProc
**
** ����������  �˳������߳�
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��27��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ShutDownListenProc( )
{
	if (m_pListenThread && m_hListenHandle )
	{
		Common::WaitForThreadToTerminate(m_hListenHandle);
		CloseHandle(m_hListenHandle);
		delete m_pListenThread;
		m_pListenThread = NULL;
		OutputDebugString(_T("�����߳��˳� \n"));
	}
}
/*********************************************************************************************************
** ��������: Startup
** ��������: CUEServer::Startup
**
** ����������  ��������
**
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��24��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::Startup()
{
	CString szLog; 

	m_NumberOfActiveConnections=0;   

	BOOL bRet=TRUE;
	m_bAcceptConnections=TRUE;

	if ( !m_bServerStarted )
	{
		m_bShutDown=FALSE;
		/*
		*	When using multiple pendling reads (eg m_iNumberOfPendlingReads>1) 
		*  with multiple IOworkers (eg m_iMaxIOWorkers>1), the order of the 
		*  packages are broken, because of IOCP internal design, Furthermore there is no 
		*  Performance gain to have multiple pendling reads if we use more than one IO-worker.
		*  The throughput is going upp because of serveral pendling reads, but is going down because of 
		*  the ordering part. 
		*/
		if ( m_iMaxIOWorkers>1 ) // we have some sort of bugg somewhere.. 
			m_iNumberOfPendlingReads=1;

		if(m_iNumberOfPendlingReads<=0)
			m_iNumberOfPendlingReads=1;

		szLog.Format(_T("֧�����%i·�������ӡ�"),m_iMaxNumConnections);
		LogString(szLog,NORMAL_STR);
		szLog.Format(_T("Number of pendling asynchronous reads: %d"),m_iNumberOfPendlingReads);
		LogString(szLog,NORMAL_STR);
// 		// ���ֻ��1��IO�����̣߳���ôû�б�Ҫ���а�˳���շ�
// 		if ( m_iMaxIOWorkers==1 )
// 		{
// 			m_bReadInOrder=FALSE;
// 			m_bSendInOrder=FALSE;
// 		}
// 
// 		// If we have several Penling Reads and Several IO workers. We must read in order. 
// 		if ( m_iNumberOfPendlingReads>1 && m_iMaxIOWorkers>1 )
// 		{
// 			m_bReadInOrder=TRUE;
// 			m_bSendInOrder=TRUE;
// 		}
// 
// 		if ( m_bSendInOrder )
// 		{
// 			szLog = _T("Send ordering initialized. (Decreases the performance by ~3%)");
// 			LogString(szLog,NORMAL_STR);
// 		}
//  
// 		if ( m_bReadInOrder )
// 		{
// 			szLog = _T("Read ordering initialized.(Decreases the performance by ~3%)");
// 			LogString(szLog,NORMAL_STR);
// 		}
 
		// The map must be empty 
		m_ContextMap.clear();

		// Create the CompletionPort used by IO Worker Threads.  
		bRet&=CreateCompletionPort();
		if( bRet)
		{
			szLog = _T("Completionport successfully created.");
			LogString(szLog,NORMAL_STR);
 		}
		// Config the Listner.. 
		if ( m_nPortNumber>0 )
		{
			bRet&=SetupListner();
			ASSERT(bRet);
			if( bRet )
			{
				szLog = _T("���������̳߳ɹ�");
				LogString(szLog,NORMAL_STR);
			}
		}
		// Setup the IOWorkers.. 
		bRet&=SetupIOWorkers();

		if ( bRet )
		{
		//	szLog.Format(_T("Successfully started %i Input Output Worker thread(s)."),m_nIOWorkers );
			szLog.Format(_T("����%i��IO�������̡߳�"),m_nIOWorkers );
			LogString(szLog,NORMAL_STR); 
		}
		// Start the logical Workers. (SetWorkes can be callen in runtime..). 
// 		bRet&=SetWorkers(m_nOfWorkers);
// 		if ( bRet )
// 		{
// 			szLog.Format("Successfully started %i logical Worker(s).",m_nOfWorkers);
// 			AppendLog(szLog);
// 		}

		// Accept incoming Job. 
//		m_bAcceptJobs=TRUE;
		m_bServerStarted=TRUE;
	}

	if ( bRet )
	{
		if ( m_nPortNumber>0 )
		{
			szLog.Format(_T("Server successfully started."));
			szLog = _T("���������ɹ�");
			LogString(szLog ,NORMAL_STR);
		//	AppendLog(szLog);
		//	szLog.Format(_T("Waiting for clients on adress: %s, port:%i."),GetHostIP(),m_nPortNumber);
		//	AppendLog(szLog);	
		}
		else 
		{
			szLog.Format(_T("Client successfully started."));
		//	AppendLog(szLog);	
		}
	}
	return bRet; 	
}
#if 0
UINT CUEServer::WorkerThreadProc(LPVOID pParam)
{
	CUEServer* pPoolServer= reinterpret_cast<CUEServer*>(pParam);
	CWinThread* pThis=NULL;
	if(pPoolServer)
		pThis=pPoolServer->GetWorker((WORD)::GetCurrentThreadId());

	if(pThis)
	{
		TRACE("Thread %i is alive.\r\n",::GetCurrentThreadId());
		JobItem *pJob=NULL;
		while(pThis->m_hThread!=INVALID_HANDLE_VALUE)	
		{
			pJob=NULL;	
			pJob=pPoolServer->GetJob();
			if(pJob) 
			{
				pPoolServer->ProcessJob(pJob,pPoolServer);
				pPoolServer->FreeJob(pJob);
			}
			else
				::SuspendThread(::GetCurrentThread());
		}


	}
	TRACE("Thread %i RIP.\r\n",::GetCurrentThreadId());
	return 0xdead;
}
#endif

#if 0
BOOL CUEServer::SetWorkers(int nThreads)
{
	int iNumberToKill=0;
	int iNumberToStart=0;

	m_WorkerThreadMapLock.Lock();
	int iNumberOfThreads=m_WorkerThreadMap.GetCount();
	m_WorkerThreadMapLock.Unlock();

	if(nThreads<iNumberOfThreads)
		iNumberToKill=iNumberOfThreads-nThreads;
	else
		iNumberToStart=nThreads-iNumberOfThreads;

	// No interference while admin the threads. 
	BOOL bAcceptJobs=m_bAcceptJobs;
	m_bAcceptJobs=FALSE;
	
	// if nThreads is bigger than our current thread count, remove all excess threads
	// Kill some of the workers. 
	m_WorkerThreadMapLock.Lock();
	POSITION pos = m_WorkerThreadMap.GetStartPosition ();
	while (pos != NULL&&iNumberToKill>0) 
	{
		WORD strKey;
		CWinThread* pThread=NULL;
		m_WorkerThreadMap.GetNextAssoc (pos, strKey,(void *&)pThread);
		if(pThread)
		{
			HANDLE hThread = pThread->m_hThread;
			// notify the thread that it should die. 
			pThread->m_hThread=INVALID_HANDLE_VALUE;  
			// now let the thread terminate itself

			//::GetExitCodeThread(hThread, &dwExit) && (dwExit != 0xdead)

			::ResumeThread(hThread);


			DWORD dwExit = NULL;
			while(::GetExitCodeThread(hThread, &dwExit) && (dwExit != 0xdead))
			{
				::Sleep(50);	// give it a chance to finish
			}
			::CloseHandle (hThread);
			iNumberToKill--;
			m_WorkerThreadMap.RemoveKey(strKey);
			delete[] pThread;
		}	
	}
	m_WorkerThreadMapLock.Unlock();
	 
	// Start some Workers.  
	m_WorkerThreadMapLock.Lock();
	while (iNumberToStart>0) 
	{
		CWinThread* pWorkerThread=AfxBeginThread(CUEServer::WorkerThreadProc, (void*)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);  
		pWorkerThread->m_bAutoDelete=FALSE;  
		if(pWorkerThread)
		{
			pWorkerThread->ResumeThread();
			m_WorkerThreadMap[(WORD)pWorkerThread->m_nThreadID]=(void*)pWorkerThread;
			iNumberToStart--;
		}else
			return FALSE;
	}

	m_WorkerThreadMapLock.Unlock();
	m_bAcceptJobs=bAcceptJobs;
	return TRUE;
}
#endif
CString CUEServer::GetHostIP()
{
	CString sRet=_T("");
	hostent* thisHost;
	char* ip;
	thisHost = gethostbyname( "" );
	ip = inet_ntoa (*(struct in_addr *)*thisHost->h_addr_list);
	sRet=ip;
	return (CString)ip; 
}
/*********************************************************************************************************
** ��������: GetIpList
** ��������: CUEServer::GetIpList
**
** ���������� ��ȡ��������IP��ַ 
**
** �䡡��:  std::list<std::string> & r_iplist
**          
** �䡡��:   bool
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
bool CUEServer::GetIpList( std::list<std::string> & r_iplist )
{
	char szhn[256] ={0};
	int nStatus = gethostname(szhn, sizeof(szhn));
	if (nStatus == SOCKET_ERROR )
	{
	//cout << "gethostname failed, Error code: " << WSAGetLastError() << endl; 
		return false;
	}
	HOSTENT *host = gethostbyname(szhn);
	if (host != NULL)
	{
		for ( int i=0; ; i++ )
		{
			r_iplist.push_back( inet_ntoa( *(IN_ADDR*)host->h_addr_list[i] ) ) ; 
			if ( host->h_addr_list[i] + host->h_length >= host->h_name ) 
				break;
		} 
	}
	return true; 
 } 

void  CUEServer::LogString(CString &szLog,int nStrType)
{
	::LogString(szLog.GetBuffer(szLog.GetLength()),nStrType);
	szLog.ReleaseBuffer();
}
CString CUEServer::ErrorCode2Text(DWORD dw)
{
	CString error= _T("");
	// Put your own common error text here (give more explaination etc..) 
	switch(dw)
	{
	case WSAEFAULT:
		error= _T("WSAEFAULT	The buf parameter is not completely contained in a valid part of the user address space.");
		break; 
	case WSAENOTCONN:
		error=_T("WSAENOTCONN	The socket is not connected."); 
		break;
	case WSAEINTR:
		error=_T("WSAEINTR	The (blocking) call was canceled through WSACancelBlockingCall.	"); 
		break;
	case WSAENOTSOCK:
		error=_T(" WSAENOTSOCK	The descriptor s is not a socket."); 
		break; 
	case WSANOTINITIALISED:
		error=_T("WSANOTINITIALISED: A successful WSAStartup call must occur before using this function.");
		break; 
	case WSAENETDOWN:
		error=_T("WSAENETDOWN	The network subsystem has failed."); 
		break;
	case WSAEINPROGRESS:
		error=_T("WSAEINPROGRESS	A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."); 
		break;
	case WSAENETRESET:
		error=_T(" WSAENETRESET	The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress."); 
		break; 
	case WSAEOPNOTSUPP:
		error=_T("WSAEOPNOTSUPP	MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations.	"); 
		break; 
	case WSAESHUTDOWN:
		error=_T("WSAESHUTDOWN	The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH."); 
		break;
	case WSAEWOULDBLOCK:
		error=_T(" WSAEWOULDBLOCK	The socket is marked as nonblocking and the receive operation would block.	"); 
		break; 
	case WSAEMSGSIZE:
		error=_T(" WSAENOTSOCK		The message was too large to fit into the specified buffer and was truncated."); 
		break;
	case WSAEINVAL:
		error=_T("WSAEINVAL	The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or (for byte stream sockets only) len was zero or negative.	"); 
	case WSAECONNABORTED:
		error=_T(" 	WSAECONNABORTED	The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable."); 
		break; 
	case WSAETIMEDOUT:
		error=_T("WSAETIMEDOUT	The connection has been dropped because of a network failure or because the peer system failed to respond.	"); 
		break; 
	case WSAECONNRESET:
		//error="WSAECONNRESET	The virtual circuit was reset by the remote side executing a hard or abortive close."; 
		error=_T("WSAECONNRESET Connection dropped..");
		break;

	default:
		error=_T("");  
		break;
	}

	// Use system format..  
	if(error.IsEmpty())
	{
		LPVOID lpMsgBuf;
		error=_T("");
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );
		error.Format(_T("%s"),lpMsgBuf);
		LocalFree(lpMsgBuf);
	}
	return error;
}


