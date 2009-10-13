

#include "stdafx.h"
#include "ClientComm.h"
#include "ClientCommDoc.h"

CClientSocket::CClientSocket( )
{
	m_pDocument = NULL;

	m_dwDestIp = 0;
	m_nDestPortNum = 0;
	m_nLocalPortNum = 0;

	m_pCommTsk = NULL;
	m_hTaskHandle = NULL;
	m_hStopEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
}

CClientSocket::~CClientSocket( )
{

}


/*********************************************************************************************************
** ��������: Connect
** ��������: CClientSocket::Connect
**
** ����������  tcp ����
**
** �䡡��:  DWORD dwTimeout
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��13��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CClientSocket::Connect ( DWORD dwTimeout )
{
	if (m_pDocument == NULL)
		return FALSE;

	m_dwDestIp = m_pDocument->m_dwDestIp;
	ASSERT(m_dwDestIp);
	if (m_dwDestIp == 0)
		return FALSE;	

	m_nDestPortNum = m_pDocument->m_nDestPort;
	if (m_nDestPortNum == 0)
		return FALSE;

	m_nLocalPortNum = m_pDocument->m_nLocalPort;

	if (m_nSocket != 0 && m_nSocket != INVALID_SOCKET)
	{
		CloseSocket(m_nSocket);
		m_nSocket = INVALID_SOCKET;
		return FALSE;
	}

	m_nSocket = CreateSocket( );

	if(m_nSocket != INVALID_SOCKET)
	{
		if( m_nLocalPortNum )
		{
			if (  BindSocketEx(m_nSocket,m_nLocalPortNum) != SOCKET_SUCCESS)
			{
				CloseSocket(m_nSocket);
				m_nSocket = INVALID_SOCKET;
				return FALSE;
			}			 
		}

		struct sockaddr_in dst_addr;		
		memset((void*)&dst_addr,0,sizeof(dst_addr));

		dst_addr.sin_family=AF_INET;
		dst_addr.sin_port=htons(m_nDestPortNum);
		dst_addr.sin_addr.s_addr=htonl( m_dwDestIp ); 

		if (dwTimeout <= 10)
			dwTimeout = CONNECT_TIMEOUT;
		int nRet = Connect_Event(m_nSocket,(struct sockaddr *)&dst_addr,sizeof(dst_addr),dwTimeout);
		if (nRet == SOCKET_SUCCESS)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//��ʼ�շ�
void CClientSocket::StartEngine( )
{
	StopEngine();
	if (m_pCommTsk == NULL)
	{
		m_pCommTsk = AfxBeginThread( EthCommTask, (LPVOID)(this));
		m_pCommTsk->m_bAutoDelete = FALSE;
		m_pCommTsk->ResumeThread();

		HANDLE pProcess = ::GetCurrentProcess();
		ASSERT(pProcess);
		//���������
		BOOL bRet = ::DuplicateHandle(pProcess,m_pCommTsk->m_hThread,pProcess,&m_hTaskHandle,DUPLICATE_SAME_ACCESS,true,DUPLICATE_SAME_ACCESS);
		//��֤�����Ƶľ��Ҫ��Ч
		ASSERT(bRet);
	}
	return ;
}
//ֹͣ�շ�
void CClientSocket::StopEngine( )
{

}
UINT  EthCommTask (LPVOID lpParam)
{

	return 0;
}