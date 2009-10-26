/****************************************Copyright (c)**************************************************
**                                江苏科技股份有限公司
**                                     事业部
**                                     服务端网络程序    
**
**                                 http://www.xxx.com.cn
**
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名:  
**创   建   人:  
**最后修改日期:  
**描        述:  
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人:  
** 版  本: v1.00
** 日　期:  
** 描　述: 原始版本
**
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人:  
** 日　期:  
** 描　述:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include "stdafx.h"
#include "UEServer.h"
#include <algorithm>

void WaitForThreadToTerminate(HANDLE hThread)
{
	CString szLog = _T("线程超时退出\n");

	DWORD dwRet = ::WaitForSingleObject( hThread,  2000);
	switch (dwRet)
	{
	case WAIT_OBJECT_0:
		//  The thread has terminated - do something
		break;

	case WAIT_TIMEOUT:
		//  The timeout has elapsed but the thread is still running
		//  do something appropriate for a timeout
		OutputDebugString(szLog);
		TerminateThread(hThread,0x88);
		break;
	default:
		ASSERT(false);
		break;
	}		 
}

CUEServer::CUEServer()
{
	m_pListenThread = NULL;
}

CUEServer::~CUEServer()
{
	ShutDown();

}
/*********************************************************************************************************
** 函数名称: CreateCompletionPort
** 函数名称: CUEServer::CreateCompletionPort
**
** 功能描述：  
**
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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
** 函数名称: SetupListner
** 函数名称: CUEServer::SetupListner
**
** 功能描述：  
**
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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
		closesocket(m_nListenSocket);
		return FALSE;
	}

	SOCKADDR_IN		saServer;	
	// Listen on our designated Port#
	saServer.sin_port = htons(m_nPortNumber);
	// Fill in the rest of the address structure
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;
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
	//将句柄复制
	BOOL bRet = ::DuplicateHandle(pProcess,m_pListenThread->m_hThread,pProcess,&m_hListenHandle,DUPLICATE_SAME_ACCESS,true,DUPLICATE_SAME_ACCESS);
	//保证所复制的句柄要有效
	ASSERT(bRet);

	return TRUE; 
}
/*********************************************************************************************************
** 函数名称: ListnerThreadProc
** 函数名称: CUEServer::ListnerThreadProc
**
** 功能描述： 监听线程
**
** 输　入:  LPVOID pParam
**          
** 输　出:   UINT
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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
		dwRet = WSAWaitForMultipleEvents(1, &pThis->m_hEvent,FALSE,	600,FALSE);	
  		if(pThis->m_bShutDown)
 			break;
		//超时,继续
		if (dwRet == WSA_WAIT_TIMEOUT)
			continue;
		WSANETWORKEVENTS events;
		int nRet = WSAEnumNetworkEvents(pThis->m_nListenSocket,	pThis->m_hEvent,&events);

		if (nRet == SOCKET_ERROR)
		{
			TRACE(_T("WSAEnumNetworkEvents error %ld\n"),WSAGetLastError());
			break;
		}
		if ( events.lNetworkEvents & FD_ACCEPT)
		{
		 	if ( events.iErrorCode[FD_ACCEPT_BIT] == 0&&pThis->m_bAcceptConnections&&!pThis->m_bShutDown)
		 	{
				//SOCKADDR_IN	SockAddr;
				SOCKET		clientSocket=INVALID_SOCKET;
				int			nRet=-1;
				int			nLen=-1;
				//
				// accept the new socket descriptor
				//
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
					 
					}
				}
				else
				 pThis->AssociateIncomingClientWithContext(clientSocket);
			}
			else
			{
				TRACE(_T("Unknown network event error %ld\n"),WSAGetLastError());
				break;
			}	
		}
	}

	TRACE("Listner Died!\r\n");
	return 0xdead;
} 
/*********************************************************************************************************
** 函数名称: IOWorkerThreadProc
** 函数名称: CUEServer::IOWorkerThreadProc
**
** 功能描述：  
**
** 输　入:  LPVOID pParam
**          
** 输　出:   UINT
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
UINT CUEServer::IOWorkerThreadProc(LPVOID pParam)
{
	CUEServer * pThis = reinterpret_cast<CUEServer*>(pParam);
	if (pThis == NULL)
		return 0;

	DWORD dwIoSize;
	ClientContext* lpClientContext = NULL; 
	CUEPacket *pOverlapBuff = NULL;

	bool bError=false;
	HANDLE hCompletionPort = pThis->m_hCompletionPort;
	LPOVERLAPPED lpOverlapped;
	while ( !bError )
	{
		pOverlapBuff=NULL;
		lpClientContext=NULL;

		// Get a completed IO request.
		BOOL bIORet = GetQueuedCompletionStatus(hCompletionPort,&dwIoSize,(LPDWORD) &lpClientContext,&lpOverlapped, INFINITE);
		// Simulate workload (for debugging, to find possible reordering)
		//Sleep(20);

		if (!bIORet)  
		{
			DWORD dwIOError = GetLastError();
			if(dwIOError != WAIT_TIMEOUT) // It was not an Time out event we wait for ever (INFINITE) 
			{

			}
		}

		if(bIORet && lpOverlapped && lpClientContext) 
		{
			pOverlapBuff=CONTAINING_RECORD(lpOverlapped, CUEPacket, m_ol);
	 		if(pOverlapBuff!=NULL)
				pThis->ProcessIOMessage(pOverlapBuff, lpClientContext, dwIoSize);
		}	

		if(lpClientContext==NULL&&pOverlapBuff==NULL&&pThis->m_bShutDown)
		{
			TRACE("lpClientContext==NULL \r\n"); 
			bError=true;
		}
	}

	return 0x88;
}
/*
* AssociateIncomingClientWithContext
* 
* This function do the Following: 
* 1) Does some simpleSecutity Stuff (e.g one connection per client, etc..)
* 2) Allocates an Context for the Socket. 
* 3) Configures the Socket. 
* 4) Associate the Socket and the context with the completion port. 
* 5) Fires an IOInitialize So the IOWORKERS Start to work on the connection. 
*/

BOOL CUEServer::AssociateIncomingClientWithContext(SOCKET clientSocket)
{	
	if (clientSocket == INVALID_SOCKET)
		return FALSE;

	if (m_bShutDown || !m_bAcceptConnections)
	{
		closesocket(clientSocket);
		return FALSE;
	} 	
	// Close connection if we have reached the maximum nr of connections... 	
	m_ContextMapLock.Lock(); // Mus lock the m_ContextMapLock Protect (m_NumberOfActiveConnections) ??
	if(m_NumberOfActiveConnections>=m_iMaxNumConnections)
	{//达到最大连接数
		// Disconnect. 	
		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( clientSocket, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct, sizeof(lingerStruct) );

		// Now close the socket handle. This will do an abortive or graceful close, as requested. 
		CancelIo((HANDLE) clientSocket);

		closesocket( clientSocket );
		clientSocket = INVALID_SOCKET;	
	}
	m_ContextMapLock.Unlock();

	if (clientSocket == INVALID_SOCKET)
		return FALSE; 
	// Create the Client context to be associated with the completion port
	ClientContext* pContext = AllocateContext();
	if(pContext!=NULL)
	{
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

		if(AddClientContext(pContext))
		{	
			// Associate the new socket with a completion port.
			if (!AssociateSocketWithCompletionPort(clientSocket, m_hCompletionPort, (DWORD) pContext))
			{
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return FALSE;
			}

			// Trigger first IO Completion Request
			// Otherwise the Worker thread will remain blocked waiting for GetQueuedCompletionStatus...
			// The first message that gets queued up is ClientIoInitializing - see ThreadPoolFunc and 
			// IO_MESSAGE_HANDLER

			// Important!! EnterIOLoop must notify that the socket and the structure  
			// pContext have an Pendling IO operation ant should not be deleted.
			// This is nessesary to avoid Access violation. 
			
			EnterIOLoop(pContext);
			CUEPacket *pOverlapBuff =AllocateBuffer(IOInitialize);
			if(pOverlapBuff!=NULL)
			{
				BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol);

				if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
				{            
					ReleaseBuffer(pOverlapBuff);
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
		{//添加到HASH表中失败
			return FALSE;
		}
	}
	else
	{
		closesocket(clientSocket);
		return FALSE;
	}
	return TRUE;
}

void CUEServer::ProcessIOMessage(CUEPacket *pOverlapBuff, ClientContext *pContext, DWORD dwSize)
{
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
** 函数名称: DisconnectClient
** 函数名称: CUEServer::DisconnectClient
**
** 功能描述：  
**
** 输　入:  ClientContext * pContext
** 输　入:  BOOL bGraceful
**          
** 输　出:   void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月19日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::DisconnectClient(ClientContext *pContext, BOOL bGraceful)
{	
	if(pContext!=NULL)
	{	
		pContext->m_ContextLock.Lock();
		BOOL bDisconnect=pContext->m_nSocket!=INVALID_SOCKET;
		pContext->m_ContextLock.Unlock();
		// If we have an active  socket close it. 
		if(bDisconnect)
		{			
			stdext::hash_map <SOCKET,ClientContext*>::iterator iter ;
			// Remove it From m_ContextMap. 
			m_ContextMapLock.Lock();
			//Remove it from the m_ContextMapLock,
			iter = m_ContextMap.find( pContext->m_nSocket  );
			if (iter != m_ContextMap.end())
			{//找到
				m_ContextMap.erase(iter);
				m_NumberOfActiveConnections--;
			}
			m_ContextMapLock.Unlock();
			TRACE("Client %i, Disconnected %x.\r\n",pContext->m_nSocket,pContext);

			pContext->m_ContextLock.Lock();
			// Notify that we are going to Disconnect A client. 
			NotifyDisconnectedClient(pContext);
			pContext->m_ContextLock.Unlock();

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
		pContext->m_ContextLock.Lock();
		pContext->m_nNumberOfPendlingIO++;
		pContext->m_ContextLock.Unlock();
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
		pContext->m_ContextLock.Lock();
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
		pContext->m_ContextLock.Unlock();

	}
	return nNumberOfPendlingIO; 
}

/*
* A workaround the WSAENOBUFS error problem. (For more info please see OnZeroBytesRead  
* Unlock the memory used by the OVELAPPED struktures. 
*/
BOOL CUEServer::AZeroByteRead(ClientContext *pContext, CUEPacket *pOverlapBuff)
{
	if (pContext == NULL)
		return FALSE;

	if(pContext->m_nSocket!=INVALID_SOCKET )
	{
		if(pOverlapBuff==NULL) 
			pOverlapBuff=AllocateBuffer(IOZeroByteRead);

		if(pOverlapBuff==NULL) 
		{			
		//	AppendLog("AllocateBuffer(IOZeroByteRead) == NULL.");
		//	ReleaseClientContext(pContext);
			return FALSE;
		}

		pOverlapBuff->SetOperation(IOZeroByteRead);

		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol); 	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
		 	DisconnectClient(pContext);
			TRACE(">OnZeroByteRead(%x)\r\n",pContext);
		 	ReleaseClientContext(pContext);
		
			return FALSE;
		}
	}
	else
	{
		TRACE(">OnZeroByteRead2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
	 	ReleaseClientContext(pContext);// Take care of it.
		return FALSE;
	}
	return TRUE;
}
/*
* Assumes that Packages arrive with A MINIMUMPACKAGESIZE header and builds Packages that  
* are noticed by the virtual function NotifyReceivedPackage 
*/
void CUEServer::ProcessPackage(ClientContext *pContext, DWORD dwIoSize, CUEPacket *pOverlapBuff)
{
 	// We may have Several Pending reads. And therefor we have to 
	// check and handle partial Messages.  	 
	// First handle partial packages.  
	CUEPacket *pBuffPartialMessage=NULL;
	pBuffPartialMessage=pContext->m_pBuffOverlappedPackage;
	// if we had a partial message in previous message process. 
	if ( pBuffPartialMessage!=NULL )
	{
		// Check how big the message is...
		UINT nUsedBuffer=pBuffPartialMessage->GetUsed();

		if ( nUsedBuffer < MIN_PACKAGE_SIZE )
		{
			//Header to small.. 
			UINT nHowMuchIsNeeded=MIN_PACKAGE_SIZE-nUsedBuffer;
			// too little Data to determine the size. 
			if ( nHowMuchIsNeeded > pOverlapBuff->GetUsed() )
			{
				AddAndFlush(pOverlapBuff,pBuffPartialMessage,pOverlapBuff->GetUsed());
				// Release the buffer if not used. 
				if ( pOverlapBuff!=NULL )
				{
					ReleaseBuffer(pOverlapBuff);
				}
				return; // wait for more data..
			}
			else
				AddAndFlush(pOverlapBuff,pBuffPartialMessage,nHowMuchIsNeeded);
		}
		// Check how big the message is...
		nUsedBuffer=pBuffPartialMessage->GetUsed();
		if ( nUsedBuffer >= MIN_PACKAGE_SIZE )
		{
			// Get The size.. 
			UINT nSize = 0;
			UINT nHowMuchIsNeeded=0;
			memmove(&nSize,pBuffPartialMessage->GetBuffer(),MIN_PACKAGE_SIZE);
			// The Overlapped Package is good. Never send packages bigger that the MAXIMUMPACKAGESIZE-MINIMUMPACKAGESIZE
			if ( nSize<=(MAX_PACKAGE_SIZE-MIN_PACKAGE_SIZE) )
			{
				nHowMuchIsNeeded=nSize-(nUsedBuffer-MIN_PACKAGE_SIZE);
				// If we need just a little data add it.. 
				if ( nHowMuchIsNeeded<=pOverlapBuff->GetUsed() )
				{
					// Add the remain into pBuffPartialMessage. 
					AddAndFlush(pOverlapBuff,pBuffPartialMessage,nHowMuchIsNeeded);
					NotifyReceivedPackage(pBuffPartialMessage,nSize,pContext);
					ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
					pContext->m_pBuffOverlappedPackage=NULL;
				}else
				{
					// Put everything in.. 
					AddAndFlush(pOverlapBuff,pBuffPartialMessage,pOverlapBuff->GetUsed());
				}
			}
			else
			{
				ReleaseBuffer(pOverlapBuff);
				pOverlapBuff=NULL;
				ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
				pContext->m_pBuffOverlappedPackage=NULL;
#ifdef SIMPLESECURITY
				AddToBanList(pContext->m_Socket);
#endif
				DisconnectClient(pContext);
				return;
			}
		}
	} 
	// Process the incoming byte stream in pOverlapBuff
	bool done;
	do 
	{
		UINT nUsedBuffer=pOverlapBuff->GetUsed();
		done=true;	
		if ( nUsedBuffer >= MIN_PACKAGE_SIZE )
		{
			UINT nSize = 0;
			memmove(&nSize,pOverlapBuff->GetBuffer(),MIN_PACKAGE_SIZE);
			// We Have a full Package..
			if ( nSize==nUsedBuffer-MIN_PACKAGE_SIZE )
			{
				NotifyReceivedPackage(pOverlapBuff,nSize,pContext);
				pOverlapBuff->EmptyUsed();
				done = true;
			}
			else if ( nUsedBuffer-MIN_PACKAGE_SIZE >nSize )
			{
				// We have more data 
				CUEPacket *pBuff=SplitBuffer(pOverlapBuff,nSize+MIN_PACKAGE_SIZE);
				NotifyReceivedPackage(pBuff,nSize,pContext);
				ReleaseBuffer(pBuff);
				// loop again, we may have another complete message in there...
				done = false;
			}
			else if ( nUsedBuffer-MIN_PACKAGE_SIZE<nSize && nSize<MAX_PACKAGE_SIZE)
			{
				//
				// The package is overlapped between this byte chunk stream and the next. 
				//
				pContext->m_pBuffOverlappedPackage=pOverlapBuff;
				pOverlapBuff=NULL;
				TRACE("new Partial Buffer >\r\n");
				done=true;
			}
			else if ( nSize>MAX_PACKAGE_SIZE )
			{			
				//pOverlapBuff->DUMP();
#ifdef SIMPLESECURITY
				AddToBanList(pContext->m_nSocket);
#endif
				ReleaseBuffer(pOverlapBuff);
				pOverlapBuff=NULL;
				DisconnectClient(pContext);
				break; 
			}
		}
		else if( nUsedBuffer>0 )
		{   //  Header  too small. 
			// nUsedBuffer < MINIMUMPACKAGESIZE
			// Add it to to the package overlapped buffer. 	
			// Let the remain be handled later. 
			pContext->m_pBuffOverlappedPackage=pOverlapBuff;
			pOverlapBuff=NULL;
			done=true;
		}
	} while ( !done );
	// Release the buffer if not used. 
	if ( pOverlapBuff!=NULL )
	{
		ReleaseBuffer(pOverlapBuff);
	}
}


void CUEServer::OnInitialize(ClientContext *pContext, DWORD dwIoSize,CUEPacket *pOverlapBuff)
{
	// Do some init here.. 

	// Notify new connection. 
	pContext->m_ContextLock.Lock();
	NotifyNewConnection(pContext);
	pContext->m_ContextLock.Unlock();
	/*
	Operations using the IO completion port will always complete in the order that they were submitted.
	Therefore we start A number of pendling read loops (R) and at last a Zero byte read to avoid the WSAENOBUFS problem.  	
	The number of m_iNumberOfPendlingReads should not be so big that we get the WSAENOBUFS problem. 
	*/
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

void CUEServer::OnRead(ClientContext *pContext,CUEPacket *pOverlapBuff)
{
	// issue a read request 
	if(pContext&&!m_bShutDown)
	{
		if(pOverlapBuff==NULL)
		{
			pOverlapBuff=AllocateBuffer(IOReadCompleted);
			if(pOverlapBuff==NULL)
			{ 
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return;
			}
		}
		if(pOverlapBuff!=NULL)
		{
			pOverlapBuff->SetOperation(IOReadCompleted);
			pOverlapBuff->SetupRead();
			if(m_bReadInOrder)
				MakeOrderdRead(pContext,pOverlapBuff);
			else
			{
				DWORD dwIoSize=0;
				ULONG			ulFlags = MSG_PARTIAL;
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
#endif
						{
						
						}
					}
					ReleaseBuffer(pOverlapBuff);
					TRACE(">OnRead(%x)\r\n",pContext);
					DisconnectClient(pContext);
					ReleaseClientContext(pContext);
				}
			}
		}
	}
}
void CUEServer::OnReadCompleted(ClientContext *pContext, DWORD dwIoSize,CUEPacket *pOverlapBuff)
{

	if (dwIoSize == 0||pOverlapBuff==NULL)
	{
		TRACE(">OnReadCompleted1(%x)\r\n",pContext);
		DisconnectClient(pContext);
		ReleaseClientContext(pContext);
		ReleaseBuffer(pOverlapBuff);
		return;
	}

	if(pContext)
	{		
		// Process The package assuming that it have a heap of size (MINIMUMPACKAGESIZE) 
		// That contains the size of the message. 
	 	/*
		* Lock the context so that no other thread enters 揚rocessPackage?function, 
		* this is necessary to process the package in order. (When IOCP is used with 
		* several working IO threads the packages can be processed in wrong order (even 
		* if the TCP protocol guarantees ordered stream) because of the operative 
		* system process scheduling.
		* Comment and source code Added 9/10/2005
		*/
		//pContext->m_ContextLock.Lock(); 
	
		// Insure That the Packages arrive in order. 
		
		if(m_bReadInOrder)
			pOverlapBuff=GetNextReadBuffer(pContext,pOverlapBuff);

		while(pOverlapBuff!=NULL)
		{
			//TRACE("R> %i\r\n",pOverlapBuff->GetSequenceNumber());
			// Mark that we are Using the buffer..
			pOverlapBuff->Use(dwIoSize);
#ifdef TRANSFERFILEFUNCTIONALITY
			if(!pContext->m_bFileReceivedMode)
#endif
				ProcessPackage(pContext,dwIoSize,pOverlapBuff);
#ifdef TRANSFERFILEFUNCTIONALITY
			else
				AddToFile(pContext,dwIoSize,pOverlapBuff);
#endif
			IncreaseReadSeqNum(pContext);
			pOverlapBuff=NULL;
			if(m_bReadInOrder)
				pOverlapBuff=GetNextReadBuffer(pContext);
		}
		ARead(pContext);
	}
}
void CUEServer::OnWrite(ClientContext *pContext, DWORD dwIoSize,CUEPacket *pOverlapBuff)
{
	if(pContext!=NULL&&pContext->m_nSocket!=INVALID_SOCKET)
	{	
		//pContext->m_ContextLock.Lock();
		if(m_bSendInOrder)
			pOverlapBuff=GetNextSendBuffer(pContext,pOverlapBuff);
#ifdef _DEBUG
		if(pOverlapBuff==NULL)
			TRACE("Write not in order (%x)\r\n",pContext);
#endif 		
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
			ULONG ulFlags = MSG_PARTIAL;
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
				if(m_bSendInOrder&&!m_bShutDown)
					pOverlapBuff=GetNextSendBuffer(pContext);
				TRACE(">OnWrite(%x)\r\n",pContext);
				ReleaseClientContext(pContext); 	// pContext may not exist after this call 	
				//break; // removed due to fix. 
			}
			else
			{
				IncreaseSendSeqNum(pContext);
				//TRACE("W> %i\r\n",pOverlapBuff->GetSequenceNumber());
				pOverlapBuff=NULL;
				if(m_bSendInOrder&&!m_bShutDown)
					pOverlapBuff=GetNextSendBuffer(pContext);
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

void CUEServer::OnWriteCompleted(ClientContext *pContext, DWORD dwIoSize,CUEPacket *pOverlapBuff)
{
	if(pContext!=NULL)
	{
		if (pOverlapBuff!=NULL)
		{
			if(pOverlapBuff->GetUsed()!=dwIoSize)
			{
			}
			else
			{
				pContext->m_ContextLock.Lock();
				NotifyWriteCompleted(pContext,dwIoSize,pOverlapBuff);
				pContext->m_ContextLock.Unlock();
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


void CUEServer::OnPostedPackage(ClientContext *pContext, CUEPacket *pOverlapBuff)
{
	ASSERT(pContext);
	if( pContext == NULL)
 		return; 

	if ( pOverlapBuff)
	{
		UINT nSize = 0;
		memmove(&nSize,pOverlapBuff->GetBuffer(),MIN_PACKAGE_SIZE);
		pContext->m_ContextLock.Lock();
		NotifyReceivedPackage(pOverlapBuff,nSize,pContext);
		pContext->m_ContextLock.Unlock();
		ReleaseBuffer(pOverlapBuff);
	}
	ReleaseClientContext(pContext);// Exit IOLoop	
}
/*
* Used to avoid in order packaging. 
* Returns The in order Buffer or NULL if not processed. 
* Same as GetReadBuffer
*/
CUEPacket * CUEServer::GetNextReadBuffer(ClientContext *pContext, CUEPacket *pBuff)
{
	ASSERT(pContext);
	// We must have a ClientContext to begin with. 
	if (pContext==NULL)
		return NULL;
	CUEPacket* pRetBuff=NULL;
	stdext::hash_map <unsigned int,CUEPacket*>::iterator iter;

	pContext->m_ContextLock.Lock();
	// We have a buffer
	if (pBuff!=NULL)
	{
		// Is the Buffer inorder ? 
		unsigned int iBufferSequenceNumber=pBuff->m_nSeqNum;
		if (iBufferSequenceNumber==pContext->m_nCurReadSeqNum)
		{
			//TRACE("GetNextReadBuffer()_1: m_ReadSequenceNumber= %i, m_CurrentReadSequenceNumber=%i\r\n",pContext->m_ReadSequenceNumber,pContext->m_CurrentReadSequenceNumber); 
			// Unlock the Context Lock. 
			pContext->m_ContextLock.Unlock();
			// return the Buffer to be processed. 
			return pBuff;
		}
		TRACE("OutOforderRead: SS: %i, CurrentS: %i, pkg: %i\r\n",pContext->m_nReadSeqNum,pContext->m_nCurReadSeqNum,iBufferSequenceNumber); 
		// Check if we already have a such key. 		 
		pRetBuff=NULL;
		iter = pContext->m_ReadBufferMap.find( iBufferSequenceNumber );
		if (iter != pContext->m_ReadBufferMap.end())
		{//找到了，重复
			pContext->m_ContextLock.Unlock();
			return NULL;
		}
		//没有重复	 
		// Add it to the Map. 
		// What if this fail?
		pContext->m_ReadBufferMap.insert(BUFFER_PAIR (iBufferSequenceNumber, pBuff) );
	}

	// return the Ordered Buffer. 
	pRetBuff=NULL;
	iter = pContext->m_ReadBufferMap.find( pContext->m_nCurReadSeqNum );
	if (iter != pContext->m_ReadBufferMap.end())
	{//找到
		pContext->m_ReadBufferMap.erase(iter);
		TRACE("GetNextReadBuffer()_2: m_ReadSequenceNumber= %i, m_CurrentReadSequenceNumber=%i\r\n",pContext->m_nReadSeqNum,pContext->m_nCurReadSeqNum); 
		pRetBuff = iter->second;
	}
	pContext->m_ContextLock.Unlock();
	return pRetBuff;
}
/*
* Used to avoid inorder packaging. 
* Returns The inorder Buffer or NULL if not processed. 
*/
CUEPacket* CUEServer::GetNextSendBuffer(ClientContext *pContext,CUEPacket *pBuff)
{
	ASSERT(pContext);
	// We must have a ClientContext to begin with. 
	if (pContext==NULL)
		return NULL;

	stdext::hash_map <unsigned int,CUEPacket*>::iterator iter;
	CUEPacket* pRetBuff=NULL;
	pContext->m_ContextLock.Lock();
	// We have a buffer
	if (pBuff!=NULL)
	{
		// Is the Buffer inorder ? 
		unsigned int iBufferSequenceNumber=pBuff->m_nSeqNum;
		if (iBufferSequenceNumber==pContext->m_nCurSendSeqNum)
		{
			//TRACE("GetNextSendBuffer()_1: m_SendSequenceNumber= %i, m_CurrentSendSequenceNumber=%i\r\n",pContext->m_SendSequenceNumber,pContext->m_CurrentSendSequenceNumber); 
			// Unlock the Context Lock. 
			pContext->m_ContextLock.Unlock();
			// return the Buffer to be processed. 
			return pBuff;
		}
		TRACE("OutOforder: SS: %i, CurrentS: %i, pkg: %i\r\n",pContext->m_nSendSeqNum,pContext->m_nCurSendSeqNum,iBufferSequenceNumber); 
		
		// Check if we already have a such key. 
		pRetBuff=NULL;

		iter = pContext->m_SendBufferMap.find( iBufferSequenceNumber );
		if (iter != pContext->m_SendBufferMap.end())
		{//找到了
			pContext->m_ContextLock.Unlock();
			return NULL;
		}	
		// Add it to the Map. 
		// What if this fail?
//		pContext->m_SendBufferMap[iBufferSequenceNumber]=pBuff;
		pContext->m_SendBufferMap.insert(BUFFER_PAIR(iBufferSequenceNumber,pBuff));
	}
	// return the Ordered Context. 
	pRetBuff=NULL;
	iter = pContext->m_SendBufferMap.find( pContext->m_nCurSendSeqNum );
	if (iter != pContext->m_SendBufferMap.end())
	{	//找到
		pContext->m_SendBufferMap.erase(iter);
		TRACE("GetNextSendBuffer()_2: m_SendSequenceNumber= %i, m_CurrentSendSequenceNumber=%i\r\n",pContext->m_nSendSeqNum,pContext->m_nCurSendSeqNum); 
	} 
	pContext->m_ContextLock.Unlock();
	return pRetBuff;
}
/*
* Sets the Sequence number to a Buffer and adds the sequence buffer. 
*/
void CUEServer::MakeOrderdRead(ClientContext *pContext, CUEPacket *pBuff)
{
	if (pContext!=NULL&&pBuff!=NULL)
	{
		//pContext->m_ContextLock.Lock();
		pBuff->m_nSeqNum = (pContext->m_nReadSeqNum);
		//TRACE("MakeOrderdRead> %i\r\n",pBuff->GetSequenceNumber());
		DWORD dwIoSize=0;
		ULONG ulFlags = MSG_PARTIAL;
		UINT nRetVal = WSARecv(pContext->m_nSocket, pBuff->GetWSABuffer(),1,&dwIoSize,&ulFlags,&pBuff->m_ol, NULL);

		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
		{
			if(WSAGetLastError()!=WSAENOTSOCK)
			{
			}
			//pContext->m_ContextLock.Unlock();
			ReleaseBuffer(pBuff);
			TRACE(">MakeOrderdRead(%x)\r\n",pContext);
			DisconnectClient(pContext);
			ReleaseClientContext(pContext);
		}
		else
		{
			pContext->m_nReadSeqNum=(pContext->m_nReadSeqNum+1)%MAX_SEQ_NUM;
			//pContext->m_ContextLock.Unlock();
		}
	}
}
/*********************************************************************************************************
** 函数名称: FreeBuffers
** 函数名称: CUEServer::FreeBuffers
**
** 功能描述：  
**
**          
** 输　出:   void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月19日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::FreeBuffers()
{
	//Free the buffer in the Free buffer list.. 
	CUEPacket *pBuff=NULL;
	std::deque <CUEPacket *> ::iterator iter;
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
** 函数名称: AllocateBuffer
** 函数名称: CUEServer::AllocateBuffer
**
** 功能描述：  
**
** 输　入:  int nType
**          
** 输　出:   CUEPacket*
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
CUEPacket* CUEServer::AllocateBuffer(int nType)
{
	CUEPacket *pMsg = NULL;
	int nCnt = 0;
	m_FreeBufferListLock.Lock();
	nCnt = m_arrFreeBuffer.size();
	if(!m_arrFreeBuffer.empty())
	{
	//	pMsg=(CUEPacket *)m_arrFreeBuffer.pop_front();
		pMsg= m_arrFreeBuffer.front();
		m_arrFreeBuffer.pop_front();
	}
	m_FreeBufferListLock.Unlock();

	if (pMsg == NULL)
	{//创建一个新的
		pMsg= new CUEPacket();
	}
	ASSERT(pMsg);
	if (pMsg == NULL)
		return NULL;

	pMsg->SetOperation(nType);

	m_BufferListLock.Lock();
	m_arrBuffer.push_front(pMsg);
	m_BufferListLock.Unlock();
	return pMsg;
}
/*********************************************************************************************************
** 函数名称: ReleaseBuffer
** 函数名称: CUEServer::ReleaseBuffer
**
** 功能描述：  释放
**
** 输　入:  CUEPacket * pBuff
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月17日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::ReleaseBuffer(CUEPacket *pBuff)
{
	ASSERT(pBuff);
	if(pBuff==NULL)
		return FALSE;
	std::deque<CUEPacket *>::iterator iter;

	m_BufferListLock.Lock();
	iter = std::find(m_arrBuffer.begin(), m_arrBuffer.end(),pBuff  );
	m_arrBuffer.erase( iter);
	m_BufferListLock.Unlock();
	//添加到空闲列表中
	m_FreeBufferListLock.Lock();
	if(m_iMaxNumberOfFreeBuffer==0|| m_arrFreeBuffer.size() <m_iMaxNumberOfFreeBuffer)
	{
// 		pos=m_FreeBufferList.AddHead((void*)pBuff);
// 		pBuff->SetPosition(NULL);
		m_arrFreeBuffer.push_front( pBuff );
	}
	else
	{
		// Delete the buffer. 
		if ( pBuff!=NULL )
			delete pBuff;
	}
	m_FreeBufferListLock.Unlock();
	pBuff=NULL;
#if 0
	// First Remove it from the BufferList. 
	m_BufferListLock.Lock();
	POSITION pos=pBuff->GetPosition();
	//TRACE("Buffer %i is going to be released.\n",pBuff);
	if(pos==NULL)
	{
	 	m_BufferListLock.Unlock();
		return FALSE;
	}

	m_BufferList.RemoveAt(pos);
	//TRACE("Buffer %i is released.\n",pBuff);
	m_BufferListLock.Unlock();

	// Add it to the FreeBufferList or delete it. 
	
	m_FreeBufferListLock.Lock();
	if(m_iMaxNumberOfFreeBuffer==0||m_FreeBufferList.GetCount()<m_iMaxNumberOfFreeBuffer)
	{
		pos=m_FreeBufferList.AddHead((void*)pBuff);
		pBuff->SetPosition(NULL);
	}
	else
	{
		// Delete the buffer. 
		if ( pBuff!=NULL )
			delete pBuff;
	}
	m_FreeBufferListLock.Unlock();
	pBuff=NULL;
#endif

	return TRUE;
}
/*********************************************************************************************************
** 函数名称: ASend
** 函数名称: CUEServer::ASend
**
** 功能描述：  异步发送
**
** 输　入:  ClientContext * pContext
** 输　入:  CUEPacket * pOverlapBuff
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月18日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::ASend(ClientContext *pContext,CUEPacket *pOverlapBuff)
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

/*
* Makes a asynchrony Read by posting a IORead message into completion port 
* who invoces a Onread.
*
* The read is not made directly to distribute CPU power fairly between the connections. 
*/
BOOL CUEServer::ARead(ClientContext *pContext,CUEPacket *pOverlapBuff)
{
	if (pContext == NULL)
		return FALSE;

	if(pContext->m_nSocket!=INVALID_SOCKET )
	{
		if(pOverlapBuff==NULL) 
			pOverlapBuff=AllocateBuffer(IORead);

		if(pOverlapBuff==NULL) 
		{			
			ReleaseClientContext(pContext);
			return FALSE;
		}

		pOverlapBuff->SetOperation(IORead);
		BOOL bSuccess = PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) pContext, &pOverlapBuff->m_ol);  	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			ReleaseBuffer(pOverlapBuff);
			TRACE(">ARead(%x)\r\n",pContext);
			ReleaseClientContext(pContext);
			return FALSE;
		}
	}
	else
	{
		TRACE(">ARead2(%x)\r\n",pContext);
		ReleaseBuffer(pOverlapBuff);
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
		if (iter->first >= 0)
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
		ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
#ifdef TRANSFERFILEFUNCTIONALITY		
		if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
		{

			pContext->m_File.Close();
		}
#endif
		ReleaseBufferMap(&pContext->m_ReadBufferMap);
		ReleaseBufferMap(&pContext->m_SendBufferMap);
		delete pContext;
	}
 
	m_ContextMap.clear();
	m_ContextMapLock.Unlock(); 
	 
	// Remove The stuff in FreeContext list
	m_bAcceptConnections=FALSE;
	std::vector <ClientContext *> ::iterator iter_free;
	m_FreeContextListLock.Lock(); 
	
	for (iter_free = m_arrFreeContext.begin(); iter_free != m_arrFreeContext.end();++ iter_free)
	{
		(*iter_free)->m_nSocket = INVALID_SOCKET;
		delete *iter_free;
	}
	m_arrFreeContext.clear();
	m_FreeContextListLock.Unlock();
}
/*********************************************************************************************************
** 函数名称: AllocateContext
** 函数名称: CUEServer::AllocateContext
**
** 功能描述：   AllocateContext. Creates a context in the heap with new or reuse context 
**             which is in the m_FreeContextList linked list. 
**          
** 输　出:   ClientContext*
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月18日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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
		//	pContext=(ClientContext *)m_FreeContextList.RemoveHead();
		}
		m_FreeContextListLock.Unlock();
	}
	ASSERT(pContext);

	pContext->m_ContextLock.Lock();
	pContext->m_nID=0;
	pContext->m_nSocket=INVALID_SOCKET;
	pContext->m_nNumberOfPendlingIO=0;
	pContext->m_nSendSeqNum=pContext->m_nReadSeqNum=0;
	pContext->m_nCurSendSeqNum=pContext->m_nCurReadSeqNum=0;
	pContext->m_pBuffOverlappedPackage=NULL;

	if ( !pContext->m_SendBufferMap.empty() )
		pContext->m_SendBufferMap.clear();

	if (!pContext->m_ReadBufferMap.empty() )
		pContext->m_ReadBufferMap.clear();

#ifdef TRANSFERFILEFUNCTIONALITY	
	pContext->m_bFileSendMode=FALSE;
	pContext->m_bFileReceivedMode=FALSE;
	pContext->m_iMaxFileBytes=-1;
	pContext->m_iFileBytes=-1;

	if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
		pContext->m_File.Close();
#endif	

	NotifyNewClientContext(pContext);
	pContext->m_ContextLock.Unlock();

	return pContext;
} 
/*********************************************************************************************************
** 函数名称: ReleaseClientContext
** 函数名称: CUEServer::ReleaseClientContext
**
** 功能描述：  Releases the Client Context. (put it into freeClientContext or delete it)
**
** 输　入:  ClientContext * pContext
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月18日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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

			pContext->m_ContextLock.Lock();
			NotifyContextRelease(pContext);
			ReleaseBuffer(pContext->m_pBuffOverlappedPackage);
#ifdef TRANSFERFILEFUNCTIONALITY		
			if (pContext->m_File.m_hFile != (unsigned int)INVALID_HANDLE_VALUE)
			{
				pContext->m_File.Close();
			}
			pContext->m_bFileSendMode=FALSE;
			pContext->m_bFileReceivedMode=FALSE;
			pContext->m_iMaxFileBytes=-1;
#endif
			ReleaseBufferMap(&pContext->m_ReadBufferMap);
			ReleaseBufferMap(&pContext->m_SendBufferMap);
			// Added. 
			pContext->m_nCurReadSeqNum=0;
			pContext->m_nSendSeqNum=0;
			pContext->m_nReadSeqNum=0;
			pContext->m_nCurSendSeqNum=0;
			pContext->m_ContextLock.Unlock();

			// Move the Context to the free context list (if Possible). 
			m_FreeContextListLock.Lock();	

			if(m_arrFreeContext.size()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
			{	
			//	bRet=m_arrFreeContext.AddHead((void*)pContext)!=NULL;
				m_arrFreeContext.insert( m_arrFreeContext.begin(), pContext );
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
/*
* Adds the A client context to the Context Map.
*/
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
	{//找到了，有重复
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
/*
* Same as Disconnect Client but we does not try to 
* remove the context from the Context Map m_ContextMap.
*/
void CUEServer::AbortiveClose(ClientContext *mp)
{
	// Notify that we are going to Disconnect A client. 
	NotifyDisconnectedClient(mp);
	// If we have an active  socket close it. 
	if(mp->m_nSocket>=0)
	{
		LINGER lingerStruct;
		lingerStruct.l_onoff = 1;
		lingerStruct.l_linger = 0;
		setsockopt( mp->m_nSocket, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct, sizeof(lingerStruct) );	
		//
		// Now close the socket handle.  This will do an abortive or  graceful close, as requested.  
		CancelIo((HANDLE) mp->m_nSocket);
		closesocket( mp->m_nSocket );
		mp->m_nSocket = INVALID_SOCKET;
	}

	// Move the Context to the free context list or kill it. 
	m_FreeContextListLock.Lock();
	if(m_arrFreeContext.size()<m_iMaxNumberOfFreeContext||m_iMaxNumberOfFreeContext==0)
		m_arrFreeContext.push_back(mp);
	else
	{
		if(mp)
			delete mp;
	}
	m_FreeContextListLock.Unlock();
}
/*********************************************************************************************************
** 函数名称: ReleaseBufferMap
** 函数名称: CUEServer::ReleaseBufferMap
**
** 功能描述：  
**
** 输　入:  BUFFER_MAP * pMap
**          
** 输　出:   void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年7月18日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ReleaseBufferMap(BUFFER_MAP *pMap)
{	
	ASSERT(pMap);
	if(pMap == NULL)
		return;
	stdext::hash_map<unsigned int,CUEPacket*>::iterator iter = pMap->begin();

	for (; iter != pMap->end(); ++iter)
	{
		ReleaseBuffer(iter->second);	 
	}
	pMap->clear();
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

void CUEServer::NotifyFileCompleted(ClientContext *pcontext)
{
	// pcontext is locked here. 
#ifdef TRANSFERFILEFUNCTIONALITY
	TRACE("FILE FINISHED"); 
	TRACE("%s> %d of %d.\r\n",pcontext->m_File.GetFileTitle(),pcontext->m_iFileBytes,pcontext->m_iMaxFileBytes);
#endif
}
/*
*	Called when a write is completed, this function is ofen used
*  for progressbars etc (e.g indicates how much is send in bytes) 
*/

void CUEServer::NotifyWriteCompleted(ClientContext *pContext, DWORD dwIoSize, CUEPacket *pOverlapBuff)
{
	// The pOverlapBuff Buffer are Successfully sended. 
}

/*
*	An package is received.. 
*/
void CUEServer::NotifyReceivedPackage(CUEPacket *pOverlapBuff,int nSize,ClientContext *pContext)
{

}




void CUEServer::OnZeroByteReadCompleted(ClientContext *pContext, DWORD dwIoSize,CUEPacket *pOverlapBuff)
{
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
void CUEServer::OnZeroByteRead(ClientContext *pContext,CUEPacket *pOverlapBuff)
{
	if(pContext)
	{
		// issue a Zeroread request 
		DWORD dwIoSize=0;
		ULONG  ulFlags = MSG_PARTIAL;
		if(pOverlapBuff==NULL)
		{
			pOverlapBuff=AllocateBuffer(IOZeroReadCompleted);
			if(pOverlapBuff==NULL)
			{
				DisconnectClient(pContext);
				ReleaseClientContext(pContext);
				return; 
			}
		}
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
		pContext->m_ContextLock.Lock();
		// increase or reset the sequence number 
		pContext->m_nCurReadSeqNum=(pContext->m_nCurReadSeqNum+1)%MAX_SEQ_NUM;
		pContext->m_ContextLock.Unlock();
	}
}


void CUEServer::IncreaseSendSeqNum(ClientContext *pContext)
{
	if (pContext!=NULL)
	{
		pContext->m_ContextLock.Lock();
		// increase or reset the sequence number 
		pContext->m_nCurSendSeqNum=(pContext->m_nCurSendSeqNum+1)%MAX_SEQ_NUM;
		pContext->m_ContextLock.Unlock();
	}
}
/*
* Move to CIOBUFFER ? 
*/
CUEPacket * CUEServer::SplitBuffer(CUEPacket *pBuff, UINT nSize)
{
	CUEPacket *pBuff2=NULL;
	pBuff2=AllocateBuffer(0);
	if(pBuff2==NULL)
		return NULL;
	pBuff2->m_nSeqNum = (pBuff->m_nSeqNum);

	if(!pBuff2->AddData(pBuff->GetBuffer(),nSize))
	{
		delete pBuff2;
		return NULL;
	}

	if(!pBuff->Flush(nSize))
	{
		delete pBuff2;
		return NULL;
	}

	return pBuff2;
}
/*
* Adds the nSize bytes from pFromBuff to pToBuff, and 
* removes the data from pFromBuff.  
*/
BOOL CUEServer::AddAndFlush(CUEPacket *pFromBuff, CUEPacket *pToBuff, UINT nSize)
{
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


/*
* Closes the Server and frees the memory. 
* We are leaking some small amount of memory (OVERLAPPEDSTRUKTUR)
*/

// Error in Disconnect.. (some how we have to wait until the Competionport is finished with the data). 

void CUEServer::ShutDown()
{
	CString msg;
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
//		AppendLog("Shutdown initialized.");
		m_bAcceptConnections=FALSE;
//		AppendLog("Sending shutdown signal to logical worker threads.");
//  	ShutDownWorkers();

		// We Let the IOWorker Take care of the last packets and die. 
//		AppendLog("Disconnecting all the Connections...");
//		DisconnectAll();

//		AppendLog("Sending shutdown signal to IO worker threads.");
		m_bShutDown=TRUE;
//		ShutDownIOWorkers();

//		AppendLog("Closing Completion port..");
		// Close the CompletionPort and stop any more requests (Stops the Listner) 
		CloseHandle(m_hCompletionPort);
		if(m_nPortNumber>0)
		{
//			AppendLog("Closing listner thread.");
			WSACloseEvent(m_hEvent);
			closesocket(m_nListenSocket);
		}
//		AppendLog("Deallocate memory used for Clients. ");
		FreeClientContext();
//		AppendLog("Deallocate memory used for Buffers. ");
		FreeBuffers();
		m_bServerStarted=FALSE;
	}
}
BOOL CUEServer::Start(int nPort,int iMaxNumConnections,int iMaxIOWorkers,int nOfWorkers,int iMaxNumberOfFreeBuffer,int iMaxNumberOfFreeContext, BOOL bOrderedSend, BOOL bOrderedRead, int iNumberOfPendlingReads)
{
	m_iMaxNumberOfFreeBuffer=iMaxNumberOfFreeBuffer;
	m_iMaxNumConnections=iMaxNumConnections;
	m_nPortNumber=nPort;
	m_iMaxIOWorkers=iMaxIOWorkers;
	m_nOfWorkers=nOfWorkers;
	m_iMaxNumberOfFreeContext=iMaxNumberOfFreeContext;
	m_bShutDown=FALSE;
	m_bReadInOrder=bOrderedRead;
	m_bSendInOrder=bOrderedSend;
	m_iNumberOfPendlingReads=iNumberOfPendlingReads;
	return Startup();
}
/*
* Starts the IOWorkers. 
*
*/
BOOL CUEServer::SetupIOWorkers()
{
	CWinThread* pWorkerThread=NULL;
	unsigned int i = 0;
	for( i=0; i<m_iMaxIOWorkers;i++)
	{
		pWorkerThread=AfxBeginThread(CUEServer::IOWorkerThreadProc, (void*)this,THREAD_PRIORITY_NORMAL);
		if(pWorkerThread)
			m_IOWorkerList.push_back(pWorkerThread);
			//m_IOWorkerList.AddHead((void*)pWorkerThread);
		else
		{
			CString msg;
		//	msg.Format("Error Couldnot start worker: %s",ErrorCode2Text(WSAGetLastError()));
		//	AppendLog(msg); 
			return FALSE;
		}
	}
	m_nIOWorkers=m_IOWorkerList.size();
	return TRUE; 
}
/*********************************************************************************************************
** 函数名称: ShutDownIOWorkers
** 函数名称: CUEServer::ShutDownIOWorkers
**
** 功能描述：  Shuttingdown the IOWOrkers..
**
**          
** 输　出:   void
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年10月25日
** 备  注:  We put a NULL in CompletionPort and set the m_bShutDown FLAG.Then we wait for the IOWorkes to 
            finish the works in the CompletionPort and exit. 
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CUEServer::ShutDownIOWorkers()
{
	DWORD dwExitCode;
	m_bShutDown=TRUE;
	// Should wait for All IOWorkers to Shutdown.. 
	BOOL bIOWorkersRunning=TRUE;
	CWinThread* pThread=NULL;
	while(bIOWorkersRunning)
	{
		// Send Empty Message into CompletionPort so that the threads die. 
		if(bIOWorkersRunning)
			PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) NULL, NULL);
		//	Sleep(60);
		// Check if the IOWorkers are terminated.. 	
// 		POSITION pos = m_IOWorkerList.GetHeadPosition ();
// 		while (pos != NULL) 
// 		{
// 			pThread = (CWinThread* )m_IOWorkerList.GetNext (pos);
// 			if(pThread)
// 			{
// 				if (::GetExitCodeThread (pThread->m_hThread, &dwExitCode)&&dwExitCode == STILL_ACTIVE) 
// 					bIOWorkersRunning=TRUE;
// 				else
// 					bIOWorkersRunning=FALSE;
// 			}
// 
// 		}

	}
	m_IOWorkerList.clear();
}
/*********************************************************************************************************
** 函数名称: Startup
** 函数名称: CUEServer::Startup
**
** 功能描述：  
**
**          
** 输　出:   BOOL
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年10月24日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CUEServer::Startup()
{
	// Some special cleanup 
#if defined SIMPLESECURITY	
	m_OneIPPerConnectionList.RemoveAll();
	m_BanIPList.RemoveAll();
#endif
	CString msg;
// 	AppendLog(m_sServerVersion);
// 	AppendLog("---------------------------------");
// 	AppendLog("Starting system.."); 
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

		msg.Format(_T("Maximum nr of simultaneous connections: %i"),m_iMaxNumConnections);
	//	AppendLog(msg);

		msg.Format(_T("Number of pendling asynchronous reads: %d"),m_iNumberOfPendlingReads);
   //	AppendLog(msg);

		// No need to make in order read or write
		if ( m_iMaxIOWorkers==1 )
		{
			m_bReadInOrder=FALSE;
			m_bSendInOrder=FALSE;
		}

		// If we have several Penling Reads and Several IO workers. We must read in order. 
		if ( m_iNumberOfPendlingReads>1&&m_iMaxIOWorkers>1 )
		{
			m_bReadInOrder=TRUE;
			m_bSendInOrder=TRUE;
		}

		if ( m_bSendInOrder )
	//		AppendLog("Send ordering initialized. (Decreases the performance by ~3%)");

		if ( m_bReadInOrder )
	//		AppendLog("Read ordering initialized.(Decreases the performance by ~3%)");

		// The map must be empty
// 		m_ContextMap.RemoveAll();
// 		m_ContextMap.InitHashTable(m_iMaxNumConnections);
		m_ContextMap.clear();

		// Create the CompletionPort used by IO Worker Threads.  
		bRet&=CreateCompletionPort();
		if( bRet)
		{
	//		AppendLog("Completionport successfully created.");		
		}
		// Config the Listner.. 
		if ( m_nPortNumber>0 )
		{
			bRet&=SetupListner();

			if( bRet )
			{
	//			AppendLog("Connection listner thread successfully started.");		
			}
		}
		// Setup the IOWorkers.. 
		bRet&=SetupIOWorkers();


		if ( bRet )
		{
			msg.Format(_T("Successfully started %i Input Output Worker thread(s)."),m_nIOWorkers );
		//	AppendLog(msg);
		}
		// Start the logical Workers. (SetWorkes can be callen in runtime..). 
// 		bRet&=SetWorkers(m_nOfWorkers);
// 		if ( bRet )
// 		{
// 			msg.Format("Successfully started %i logical Worker(s).",m_nOfWorkers);
// 			AppendLog(msg);
// 		}

		// Accept incoming Job. 
//		m_bAcceptJobs=TRUE;
		m_bServerStarted=TRUE;
	}

	if ( bRet )
	{
		if ( m_nPortNumber>0 )
		{
			msg.Format(_T("Server successfully started."));
		//	AppendLog(msg);
			msg.Format(_T("Waiting for clients on adress: %s, port:%i."),GetHostIP(),m_nPortNumber);
		//	AppendLog(msg);	
		}
		else 
		{
			msg.Format(_T("Client successfully started."));
		//	AppendLog(msg);	
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
** 函数名称: GetIpList
** 函数名称: CUEServer::GetIpList
**
** 功能描述： 获取本机所有IP地址 
**
** 输　入:  std::list<std::string> & r_iplist
**          
** 输　出:   bool
**         
** 全局变量:  
** 调用模块: 无
**
** 作　者:  LiJin
** 日　期:  2009年10月26日
** 备  注:  
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 备  注: 
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
