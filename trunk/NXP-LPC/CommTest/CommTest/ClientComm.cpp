

#include "stdafx.h"
#include "ClientComm.h"
#include "ClientCommDoc.h"
#include "Common.h"
#include "LogDataApi.h"

CClientComm::CClientComm( )
{
	m_pDocument = NULL;

	m_dwDestIp = 0;
	m_nDestPortNum = 0;
	m_nLocalPortNum = 0;

	m_nSocket = INVALID_SOCKET;

	m_pCommTsk = NULL;
	m_hTaskHandle = NULL;
	m_hStopEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	m_pRawBuf = new unsigned char [MAX_DATA_LEN];
}

CClientComm::~CClientComm( )
{
	if(m_pRawBuf)
	{
		delete [] m_pRawBuf;
		m_pRawBuf = NULL;
	}
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
BOOL CClientComm::Connect ( DWORD dwTimeout )
{
	ASSERT(m_pDocument);
	if (m_pDocument == NULL)
		return FALSE;

	StopTask();

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
	//	return FALSE;
	}

	m_nSocket = CreateSocket( );

	CString szLog;

	if(m_nSocket != INVALID_SOCKET)
	{
		if( m_nLocalPortNum )
		{
			if (  BindSocketEx(m_nSocket,m_nLocalPortNum) != SOCKET_SUCCESS)
			{
				CloseSocket(m_nSocket);
				m_nSocket = INVALID_SOCKET;

				szLog.Format(_T("�󶨱��ض˿�%dʧ�ܣ������Ƕ˿��ѱ�ռ�ã�"),m_nLocalPortNum );
				LogString(szLog.GetBuffer(szLog.GetLength()),ERR_STR );
				szLog.ReleaseBuffer();

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
			szLog.Format(_T("����%d.%d.%d.%d:%d�ɹ���"),dst_addr.sin_addr.s_net ,dst_addr.sin_addr.s_host ,
				dst_addr.sin_addr.s_lh ,dst_addr.sin_addr.s_impno,m_nDestPortNum);
			LogString(szLog.GetBuffer(szLog.GetLength()),NORMAL_STR );
			szLog.ReleaseBuffer();

			StartTask();
			return TRUE;
		}
		else
		{//���Ӳ��ɹ���ǿ�ƹر�
			szLog.Format(_T("����%d.%d.%d.%d:%dʧ�ܣ�"),dst_addr.sin_addr.s_net ,dst_addr.sin_addr.s_host ,
				dst_addr.sin_addr.s_lh ,dst_addr.sin_addr.s_impno,m_nDestPortNum );
			LogString(szLog.GetBuffer(szLog.GetLength()),ERR_STR );
			szLog.ReleaseBuffer();

			CloseSocket(m_nSocket,TRUE);
			m_nSocket = INVALID_SOCKET;
			return FALSE;
		}
	}
	return FALSE;
} 
/*********************************************************************************************************
** ��������: StartTask
** ��������: CClientComm::StartTask
**
** ���������� �����̣߳���������ʱ�����߳� 
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��14��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CClientComm::StartTask( )
{
	StopTask();
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
void CClientComm::StopTask( )
{
	if( m_hStopEvent )
		SetEvent( m_hStopEvent );

	//�ȴ��߳��˳�
	if ( m_pCommTsk != NULL && m_hTaskHandle)
	{
		Common::WaitForThreadToTerminate(m_hTaskHandle);
		CloseHandle(m_hTaskHandle);
		delete m_pCommTsk;
		m_pCommTsk = NULL;

		OutputDebugString(_T("�ļ������߳��˳� \n"));
	}
}

void CClientComm::ExecMsgCmd( CCommMsg & msg  )
{
	if (msg.m_nMsgType == MSG_SEND_DATA)
	{
		if (m_nSocket == 0 || m_nSocket == INVALID_SOCKET )	
		{
			return;
		}

		unsigned int nLen = m_SendBuf.GetData(m_pRawBuf);
		int nRetLen = 0;

		if (nLen>0)
		{
			nRetLen = SendData_Event(m_nSocket,(const char *)m_pRawBuf,nLen);
			if ( nRetLen == nLen )
			{//���ͳɹ�

			}
			else 
			{//
				if (m_nSocket != 0 && m_nSocket != INVALID_SOCKET)
				{
					if (nRetLen == SOCKET_ERROR)
					{//Ӳ�ر�
						CloseSocket(m_nSocket,TRUE);
						m_nSocket= INVALID_SOCKET;
					}
					else
					{//���ݹر�
						CloseSocket(m_nSocket);
						m_nSocket= INVALID_SOCKET;

					}
					// ֪ͨ����
				}
			}				 
		}
	}
}
/*********************************************************************************************************
** ��������: Engine
** ��������: CClientComm::Engine
**
** ���������� �շ����� 
**
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��14��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 	//3.����շ������з���socket�ѱ��Զ˹رյ�,��֪ͨ����
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CClientComm::Engine( )
{
	//1.�ȿ����Ƿ���Ҫ�з��ͣ�����з��ͣ���������
	CCommMsg msg;
	if(m_CommMsg.GetCommMsg(msg))
	{
		ExecMsgCmd(msg);
		Sleep(50);
	}
	//2.�������ݣ������͵�����
	int nRet = RecvData_Event(m_nSocket,(char*)m_pRawBuf,MAX_DATA_LEN);

	if (nRet == SOCKET_ERROR)
	{

	}
	else
	{
	
	}


}



UINT  EthCommTask (LPVOID lpParam)
{	
	CClientComm *pComm = (CClientComm *)lpParam;
	ASSERT(pComm);
	if (pComm == NULL)
		return 0x88;

	CString szLog;
	struct sockaddr_in dst_addr;		
	memset((void*)&dst_addr,0,sizeof(dst_addr));
 	dst_addr.sin_addr.s_addr=htonl( pComm->m_dwDestIp ); 
	szLog.Format(_T("%d.%d.%d.%d:%d�շ��߳�������"),dst_addr.sin_addr.s_net ,dst_addr.sin_addr.s_host ,
		dst_addr.sin_addr.s_lh ,dst_addr.sin_addr.s_impno,pComm->m_nDestPortNum );

 	LogString(szLog.GetBuffer(szLog.GetLength()),ERR_STR );
	szLog.ReleaseBuffer();

	Sleep(1000);

	ResetEvent(pComm->m_hStopEvent);
 
	
	while(1)
	{
		DWORD dwRtn = WaitForSingleObject(pComm->m_hStopEvent, 0);
		if ( dwRtn == WAIT_OBJECT_0)
		{   //	szLog = "�˳�����..................\n";
			OutputDebugString(_T("�˳����ߺ���..................\n"));
			return 0x88;
		}	

		pComm->Engine();
	}

	return 0;
}