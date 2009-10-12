 

#include "stdafx.h"
#include "EcBusSocket.h"



//ע��WINSOCK2.2DLL
int  InitLibrary(void)
{
	WSADATA         WSD;
	WORD wVersionRequired = MAKEWORD( SOCKET_MAJOR_VERSION, SOCKET_MINOR_VERSION );
	ZeroMemory(&WSD,sizeof(WSADATA));
	int nErrorNo = WSAStartup(wVersionRequired, &WSD);
	if ( SOCKET_SUCCESS != nErrorNo )
	{
		//SetLastError( nErrorNo );
		return ( SOCKET_ERROR );
	}
	if ( LOBYTE( WSD.wVersion ) != SOCKET_MINOR_VERSION || HIBYTE( WSD.wVersion ) != SOCKET_MAJOR_VERSION ) 
	{
		WSACleanup( );
		//	SetLastError( WSAVERNOTSUPPORTED );
		return (SOCKET_ERROR); 
	}
	//�ɹ���ʼ��
	return (SOCKET_SUCCESS);
}
//�ͷ�Winsock2��̬���ӿ�
void  CleanupLibrary(void)
{
	WSACleanup();
}

CEcBusSocket::CEcBusSocket()
{
	::InitializeCriticalSection(&m_csErrorNo);
}

CEcBusSocket::~CEcBusSocket()
{
	::DeleteCriticalSection(&m_csErrorNo);
}

// �����׽����Ƿ�Ϊ������
//���:�׽���,�Ƿ���Ҫ������
//����:�����ȷ��ô����0�����󷵻�-1
int CEcBusSocket::BlockSocket(SOCKET hSocket, BOOL bBlock/*FALSE*/)
{
	u_long IoctlLong = (bBlock) ? 0 : 1;
	if (ioctlsocket(hSocket, FIONBIO, &IoctlLong) == SOCKET_ERROR)
	{
		SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
    }
	return (SOCKET_SUCCESS);
}

//�����׽�������
//���:�׽���
//����:�����ȷ��ô����0�����󷵻�-1
int CEcBusSocket::SetSocketOption(SOCKET hSocket)
{
    int nActivate = 1;
	//�����ַ����
    if (setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &nActivate,sizeof(nActivate)) == SOCKET_ERROR )
    {
        SetLastError( WSAGetLastError() );
        return (SOCKET_ERROR);//return (-1)
    }
	return (SOCKET_SUCCESS);
}

//�����������ݣ�ע���������������֮ǰ����ȷ���Ƿ��н�����Ϣ����
//���:�׽���,���ݻ�����,��������С
//����:�����ȷ��ô���ؽ��յ��ֽ����������󷵻ش������
int CEcBusSocket::RecvLL(SOCKET hSocket, char *pszBuffer, int nBufferSize)
{
	DWORD		dwRtxBytes = 0,
				dwRtxFlags = 0;
	WSABUF		WSABuff;

	//��ջ���
	ZeroMemory(&WSABuff,sizeof(WSABUF));

	WSABuff.len = nBufferSize;
	WSABuff.buf = pszBuffer;
	//�����ȷ�ͷ��ر��ν��յ��ֽڸ�����������󷵻ش������(����)
	return ((WSARecv(hSocket, &WSABuff, 1, &dwRtxBytes, &dwRtxFlags,NULL, NULL) == SOCKET_SUCCESS) ? (int) dwRtxBytes : -WSAGetLastError());
}


int CEcBusSocket::RecvData_Block(SOCKET hSocket, char *pszBuffer, int nBufferSize, 	DWORD dwTimeout)
{
	ASSERT(hSocket != NULL);
	if(hSocket==NULL)
		return ( SOCKET_ERROR );
	FD_SET fd = {1, hSocket};
	TIMEVAL tv = {dwTimeout, 0};
	int nBytesReceived=0;
	if(select(0, &fd, NULL, NULL, &tv) == 0) 
		goto CLEAR;
	if((nBytesReceived = recv(hSocket, pszBuffer, nBufferSize, 0)) == SOCKET_ERROR)
		goto CLEAR;
	return nBytesReceived;

CLEAR:
	SetLastError(WSAGetLastError());//��ʱ
	return(SOCKET_ERROR);
}

// ��������(����ֱ���յ�����Ϊֹ)
int CEcBusSocket::RecvData_Event(SOCKET hSocket, char *pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	HANDLE hReadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hReadEvent == NULL)
	{
		SetLastError( (int)GetLastError() );
		return ( SOCKET_ERROR );
	}

	int		nRecvBytes = 0;
	DWORD	dwWaitResult ;
	for (;;)
	{
		// ע��FD_READ | FD_CLOSE �¼� 
		// (��Ϊ�����ڵȴ�FD_READ�¼��У��Է��ر��׽��֣�����Ҫ��עFD_CLOSE)
		if( WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, FD_READ | FD_CLOSE) == SOCKET_ERROR)
		{
			CloseHandle(hReadEvent);
			SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
	
		// �ȵ�FD_READ | FD_CLOSE�¼��ķ���
		dwWaitResult = WSAWaitForMultipleEvents(1, &hReadEvent, TRUE,dwTimeout, TRUE);

		if (dwWaitResult != WSA_WAIT_EVENT_0)
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		
		////////////////////////////////////////////////////////////// 
		///	ע�⣺��ʹ dwWaitResult == WSA_WAIT_EVENT0 ��ҲӦ�� 
		///			��һ����������Ƿ�������
		///////////////////////////////////////////////////////////////
		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hReadEvent,&NetEvent) == SOCKET_ERROR)
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		//�жϷ�����ʲô�¼� FD_READ �� FD_CLOSE	
		if( ( NetEvent.lNetworkEvents == FD_CLOSE ) ||
			 ( NetEvent.lNetworkEvents	== FD_READ && 
			   NetEvent.iErrorCode[FD_READ_BIT] !=0 ) )	// ��������
		{
			// ����¼�
			WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
			CloseHandle(hReadEvent);
			SetLastError(WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ����¼�
		WSAEventSelect(hSocket, (WSAEVENT) hReadEvent, 0);
	
		// ��������
		if ((nRecvBytes = RecvLL(hSocket, pszBuffer, nBufferSize)) >= 0)
			break;	// ����ѭ��

		//Recv���ص��Ǵ������ĸ�����������Ҫ��ת����
		int nErrorCode = -nRecvBytes;

		if ( nErrorCode != WSAEWOULDBLOCK )	//̫���δ����ص�����
		{
			CloseHandle(hReadEvent);
			SetLastError( nErrorCode );
			return (SOCKET_ERROR);
		}
		//����ס��
		Sleep(BLOCKED_SNDRCV_SLEEP);
    }
    CloseHandle(hReadEvent);
    return (nRecvBytes);
}


//�������ݣ�����
//���:�׽��֣����͵��ִ�,�ִ����ȣ���ʱֵ
int CEcBusSocket::Send_Block(SOCKET hSocket,char const * pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	ASSERT(hSocket!=NULL);
	if(hSocket==NULL||pszBuffer==NULL)
		return (SOCKET_ERROR);
	FD_SET fd = {1, hSocket};
	TIMEVAL tv = {dwTimeout, 0};
	int nBytesSent=0;
	if(select(0, NULL, &fd, NULL, &tv) == 0)
		goto CLEAR;//ѡ���ͳ�ʱ
	if((nBytesSent = send(hSocket, pszBuffer, nBufferSize, 0)) == SOCKET_ERROR) 
		goto CLEAR;//���ͳ�����
	return nBytesSent;

CLEAR:
	SetLastError(WSAGetLastError());//��ʱ
	return(SOCKET_ERROR);
}

//����ȫ�������������ݣ�����
//���:�׽��֣����͵��ִ�,�ִ����ȣ���ʱֵ
//����:��ȷ���ط��͵��ֽ����������󷵻�SOCKET_ERROR
int CEcBusSocket::SendData_Block(SOCKET hSocket,char const * pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	if(hSocket==NULL)
		return(SOCKET_ERROR);
	int nBytesSent = 0;
	int nBytesThisTime;
	const char* pszTemp = pszBuffer;
	do 
	{
		nBytesThisTime = Send_Block(hSocket,pszTemp, nBufferSize-nBytesSent, dwTimeout);
		if(nBytesThisTime<0)
			return(SOCKET_ERROR);
		//���һ��û�з��ͳɹ�
		nBytesSent += nBytesThisTime;
		//�ı䵱ǰ�ַ�ָ��
		pszTemp += nBytesThisTime;
	} while(nBytesSent < nBufferSize);
	return nBytesSent;
}

//���:�׽��֣����͵��ִ�,�ִ����ȣ���ʱֵ
//����:��ȷ���ط��͵��ֽ����������󷵻�SOCKET_ERROR
int CEcBusSocket::SendData_Event(SOCKET hSocket,char const * pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	if(hSocket==NULL)
		return(SOCKET_ERROR);
	int nBytesSent = 0;
	int nBytesThisTime;
	const char* pszTemp = pszBuffer;
	do 
	{
		nBytesThisTime = Send_Event(hSocket,pszTemp, nBufferSize-nBytesSent, dwTimeout);
		if(nBytesThisTime<0)
			return(SOCKET_ERROR);
		//���һ��û�з��ͳɹ�
		nBytesSent += nBytesThisTime;
		//�ı䵱ǰ�ַ�ָ��
		pszTemp += nBytesThisTime;
	} while(nBytesSent < nBufferSize);
	return nBytesSent;
}
//һ�η������ݣ�����һ��ȫ��������
//���:�׽��֣����շ���ַ��Ϣ,��ַ�ṹ���ṹ���ȣ������������������ȣ���ʱ
//����:��ȷ���ط����ֽ����������󷵻�SOCKET_ERROR
int CEcBusSocket::SendTo_Block(SOCKET hSocket, const struct sockaddr * pTo,	int nAddrLen,char const * pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	if(hSocket==NULL||pszBuffer==NULL)
		return SOCKET_ERROR;
	FD_SET fd = {1, hSocket};
	TIMEVAL tv = {dwTimeout, 0};
	int nBytesSent=0;
	if(select(0, NULL, &fd, NULL, &tv) == 0) 
		goto CLEAR;
	nBytesSent = sendto(hSocket, pszBuffer, nBufferSize, 0, pTo, nAddrLen);
	if(nBytesSent == SOCKET_ERROR)
		goto CLEAR;
	return nBytesSent;

CLEAR:
	SetLastError(WSAGetLastError());//��ʱ
	return(SOCKET_ERROR);
}

// ���ݱ��������ݱ�
int CEcBusSocket::SendTo_Event(SOCKET hSocket, const struct sockaddr * pTo,
								 int nAddrLen,char const * pszBuffer, int nBufferSize, DWORD dwTimeout)
{
	HANDLE hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
	{
		SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}

	DWORD	dwRtxBytes = 0,
            dwRtxFlags = 0;
	WSABUF	WSABuff;

	ZeroMemory(&WSABuff,sizeof(WSABUF));
	WSABuff.len = nBufferSize;
	WSABuff.buf = (char *) pszBuffer;

	for (;;)
	{
		if (WSASendTo( hSocket, &WSABuff, 1, &dwRtxBytes, dwRtxFlags,
			pTo, nAddrLen, NULL, NULL) == SOCKET_SUCCESS)
			break;

		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		//////////////////////////////////////////////////////////////////////////
		//	˯��һ��ʱ��
		/////////////////////////////////////////////////////////////////////////
		Sleep(BLOCKED_SNDRCV_SLEEP);

		// ע��FD_WRITE�¼�  
		if( WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, FD_WRITE) 
			== SOCKET_ERROR)
		{
			CloseHandle(hWriteEvent);
			SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		DWORD dwWaitResult = WSAWaitForMultipleEvents
			(1, &hWriteEvent, TRUE,dwTimeout, TRUE);
		
		if( dwWaitResult != WSA_WAIT_EVENT_0 )
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hWriteEvent,&NetEvent) 
			== SOCKET_ERROR)
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		if(NetEvent.iErrorCode[FD_WRITE_BIT] !=0 )	// ��������
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(NetEvent.iErrorCode[FD_WRITE_BIT]);
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ע���¼�
		WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
	}

	CloseHandle(hWriteEvent);
	return ((int) dwRtxBytes);
}

int  CEcBusSocket::Send_Event(SOCKET hSocket, char const * pszBuffer, int nBufferSize, DWORD dwTimeout/*=SEND_TIMEOUT*/)
{
	HANDLE hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hWriteEvent == NULL)
	{
		SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}

	DWORD	dwRtxBytes = 0, dwRtxFlags = 0;
	WSABUF	WSABuff;

	ZeroMemory(&WSABuff,sizeof(WSABUF));
	WSABuff.len = nBufferSize;
	WSABuff.buf = (char *) pszBuffer;

	for (;;)
	{
		if (WSASend( hSocket, &WSABuff, 1, &dwRtxBytes, dwRtxFlags, NULL, NULL) == SOCKET_SUCCESS)
			break;

		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		Sleep(BLOCKED_SNDRCV_SLEEP);
		// ע��FD_WRITE�¼�  
		if( WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, FD_WRITE) == SOCKET_ERROR)
		{
			CloseHandle(hWriteEvent);
			SetLastError( WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hWriteEvent, TRUE,dwTimeout, TRUE);

		if( dwWaitResult != WSA_WAIT_EVENT_0 )
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}

		WSANETWORKEVENTS NetEvent;
		if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hWriteEvent,&NetEvent) == SOCKET_ERROR)
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(  WSAGetLastError() );
			return (SOCKET_ERROR);
		}
		if(NetEvent.iErrorCode[FD_WRITE_BIT] !=0 )	// ��������
		{
			// ע���¼�
			WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
			CloseHandle(hWriteEvent);
			SetLastError(NetEvent.iErrorCode[FD_WRITE_BIT]);
			return (SOCKET_ERROR);
		}
		////////////////////////////////////////////////////////////////
		// ע���¼�
		WSAEventSelect(hSocket, (WSAEVENT) hWriteEvent, 0);
	}

	CloseHandle(hWriteEvent);
	return ((int) dwRtxBytes);
}
 
//�ر��׽���
//���:�׽���,�Ƿ�ǿ�йر�(���bHardClose==FALSE,��ô����ʣ������ݺ�ر�����)
void CEcBusSocket::CloseSocket(SOCKET hSocket, BOOL bHardClose)
{
	// ����Ҫ�������
	if (bHardClose == FALSE) // ���Źر� Graceful close
	{
		// ���ٷ������ݣ�����TCP�׽��֣������е����ݶ��������֮��
		// ������һ�� FIN ��֪ͨ���շ����������Ѿ�������ϡ�
		shutdown(hSocket, SD_SEND);

		// ���ջ������п��ܻ���δ���յ����ݣ��ڹر��׽���֮ǰӦ����
		// ��ȡ���������ݡ�
		int		nRecvResult;
		HANDLE	hSocketEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		//Ϊ���������ṩ�Ļ�����
		char	szBuffer[256];
		do
		{
			if (hSocketEvent != NULL)
			{
				//ע�������¼�
				WSAEventSelect(hSocket,(WSAEVENT) hSocketEvent, FD_READ | FD_CLOSE);
				WSAWaitForMultipleEvents(1,&hSocketEvent, TRUE,SHUTDOWN_RECV_TIMEOUT, TRUE);
				//��������¼�
				WSAEventSelect(hSocket, (WSAEVENT) hSocketEvent, 0);
			}
			ZeroMemory(szBuffer,256);
			//���ղ�������
			nRecvResult = RecvLL(hSocket, szBuffer, sizeof(szBuffer));
		} while (nRecvResult > 0);

		if (hSocketEvent != NULL)
			CloseHandle(hSocketEvent);
		//����������պͷ���
		shutdown(hSocket, SD_BOTH);
	}
	else
		shutdown(hSocket, SD_BOTH);
	// �ر��׽���
	closesocket(hSocket);
}

//����ACCEPT��û����Ӧ������
//���:�׽��֣�������ַ������
//����:��ȷ���ض˿ںţ����򷵻�INVALID_SOCKET
SOCKET CEcBusSocket::Accept_Block(SOCKET hSocket, struct sockaddr * pSocketAddress,int *nAddrLen)
{
	ASSERT(hSocket!=NULL);
	//int nLengthAddr = sizeof(SOCKADDR);
	SOCKET hAccept = accept(hSocket, pSocketAddress, nAddrLen);
	//����ö˿ڴ���
	if(hAccept == INVALID_SOCKET)
	{
		SetLastError(WSAGetLastError());
	}
	return hAccept;
}

// ���׽���
//���:�׽���,�󶨵ĵ�ַ��Ϣ,����
//����:��ȷ0������-1
int CEcBusSocket::BindSocket(SOCKET hSocket, struct sockaddr * pSocketAddress, int nAddrLen)
{
	if (bind(hSocket, pSocketAddress, nAddrLen) == SOCKET_ERROR)
	{
		SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}
	return (SOCKET_SUCCESS);
}

// ���׽���
//���:�׽���,�˿ں�
//����:��ȷ0,����-1
int CEcBusSocket::BindSocketEx(SOCKET hSocket,int nPort)
{
	SOCKADDR_IN sockAddr;
	ZeroMemory(&sockAddr,sizeof(sockAddr));

	sockAddr.sin_family			= AF_INET;
	sockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	sockAddr.sin_port			= htons((u_short)nPort);

	return BindSocket(hSocket,(SOCKADDR *)&sockAddr, sizeof(sockAddr));
}

// ��������
//���:�׽���,��ַ�ṹ,�ṹ����,��ʱ
//����:SOCKET_SUCCESS/SOCKET_ERROR
int CEcBusSocket::Connect_Event(SOCKET hSocket, const struct sockaddr * pSocketAddress, int nAddrLen,DWORD dwTimeout)
{
	HANDLE hConnectEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hConnectEvent == NULL)
	{
		SetLastError( (int)GetLastError() );
		return (SOCKET_ERROR);
	}
	// ע��FD_CONNECT�¼�
	if( WSAEventSelect(hSocket, (WSAEVENT) hConnectEvent, FD_CONNECT) == SOCKET_ERROR)
	{
		CloseHandle(hConnectEvent);
		SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}
	int	nConnectResult = WSAConnect(hSocket, pSocketAddress, nAddrLen, NULL, NULL, NULL, NULL);
	int	nConnectError  = WSAGetLastError();
	
	if((nConnectResult==SOCKET_ERROR) && (nConnectError == WSAEWOULDBLOCK))
	{
		DWORD dwWaitResult = WSAWaitForMultipleEvents(1, &hConnectEvent, TRUE,dwTimeout, TRUE);
		if (dwWaitResult != WSA_WAIT_EVENT_0)
		{
			SetLastError( WSAGetLastError() );
			nConnectResult = SOCKET_ERROR;
		}
		else
		{
			WSANETWORKEVENTS NetEvent;
			if(WSAEnumNetworkEvents(hSocket,(WSAEVENT)hConnectEvent,&NetEvent) == SOCKET_ERROR)
			{
				SetLastError( WSAGetLastError() );
				nConnectResult = SOCKET_ERROR;
			}
			else if(NetEvent.iErrorCode[FD_CONNECT_BIT] !=0 )	// ��������
			{
				SetLastError( NetEvent.iErrorCode[FD_CONNECT_BIT] );
				nConnectResult = SOCKET_ERROR;
			}
			else
				nConnectResult = SOCKET_SUCCESS;
			////////////////////////////////////////////////////////////////
		}
	}

	// ע�������¼�
	WSAEventSelect(hSocket, (WSAEVENT) hConnectEvent, 0);
	CloseHandle(hConnectEvent);
	return (nConnectResult);
}

int CEcBusSocket::Connect_Block(SOCKET hSocket, const struct sockaddr * pSocketAddress, int nAddrLen)
{
	ASSERT(hSocket!=NULL);
	if(hSocket==NULL)
		return SOCKET_ERROR;
	if(connect(hSocket, pSocketAddress, nAddrLen) == SOCKET_ERROR) 
		return SOCKET_ERROR;
	return SOCKET_SUCCESS;
}

//���������ص�IO�������׽���
//���:Э�飬Э������(TCP/U),Э��
//����:���ش������ص�IO SOCKET
//ע��:ʹ��SOCKET()�����������׽���Ĭ�Ͼ����ص�IO����
SOCKET CEcBusSocket::CreateSocket(int nAddressFamily /*= AF_INET*/, int nType/*= SOCK_STREAM*/, int nProtocol/*= 0*/)
{
	SOCKET hSocket = WSASocket(nAddressFamily, nType, nProtocol, NULL,0,WSA_FLAG_OVERLAPPED);	
	if ( hSocket == INVALID_SOCKET )
	{
		SetLastError( WSAGetLastError() );
		return (INVALID_SOCKET);
	}

	//�����׽���ѡ��
	if ( SOCKET_ERROR == SetSocketOption(hSocket) )	//��������ʧ��
	{
		CloseSocket(hSocket, TRUE);
		return (INVALID_SOCKET);
	}
	return (hSocket);
}
// �����׽���
//���:�׽���,����ĵȴ����г���
//����:SOCKET_ERROR/SOCKET_SUCCESS
int CEcBusSocket::ListenSocket(SOCKET hSocket, int nConnections)
{
	if(listen(hSocket, nConnections) == SOCKET_ERROR)
	{
		SetLastError( WSAGetLastError() );
		return (SOCKET_ERROR);
	}
	return (SOCKET_SUCCESS);
}
