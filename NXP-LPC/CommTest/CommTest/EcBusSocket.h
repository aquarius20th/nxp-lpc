//��������:������SOCKETͨѶ�ۺ�ģ�ͣ�������ɺ󽫰�װ����SOCKET
//         ͨѶģʽ(����select,�첽����,�첽�¼�,�ص�I/O,���I/O)
//         ��.�����Ա�����ͨѶ���򷽱����.�����ǻ���SERVER/CLIENT
//         ��SERVER�������ߴ��������.���ʹ����Ҫ����ض���ͨѶ
//         ���ܿ��ԴӸ���̳У����Ӷ��̳߳ص�֧�ֹ��ܡ�

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <winsock2.h>

//��
#define Min(a, b)               (((a) < (b)) ? (a): (b))
#define Max(a, b)               (((a) > (b)) ? (a): (b))
#define INext(i, n)             ((((i) + 1) < (n)) ? ((i) + 1): 0)
#define IPrev(i, n)             (((i) > 0) ? ((i) - 1): ((n) - 1))

const int SOCKET_SUCCESS = 0;//��SOCKET_ERROR��Ӧ�ĳɹ���־
const DWORD	SHUTDOWN_RECV_TIMEOUT = 2*1000;  // �����ر�ʱ�ӳ�2��
const DWORD DEFAULT_TIMEOUT = 3*1000;// 3�� ȱʡ��ʱ
const int SOCKET_BUFFER_SIZE	= 5192;// ������ȱʡ��С
const DWORD CONNECT_TIMEOUT	= 3*1000;// 3�� ���ӳ�ʱ
const DWORD SEND_TIMEOUT		= 1*1000;// 1�� ���ͳ�ʱ
const DWORD RECV_TIMEOUT		= 2*1000;// 2�� ���ճ�ʱ 
const int _EOF						= 0x100;// ��Ч�����ַ�
const DWORD BLOCKED_SNDRCV_SLEEP	= 100; // 100����(��������ʱ�ȴ�[˯��]ʱ��)
const int SOCKET_MAJOR_VERSION 	= 2;
const int SOCKET_MINOR_VERSION	= 2;


static	void CleanupLibrary(void);
static int InitLibrary(void);

class CEcBusSocket  
{
public:
//���캯��
	CEcBusSocket();
	virtual ~CEcBusSocket();
private:
	int m_nErrorNo;
	CRITICAL_SECTION m_csErrorNo;

public:
	
private:
	int SetSocketOption(SOCKET hSocket);
	int BlockSocket(SOCKET hSocket, BOOL bBlock);
	//����һ�λ��������ݣ������п���û��ȫ������
	int Send_Event(SOCKET hSocket, char const * pszBuffer, int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);
	int SendTo_Event(SOCKET hSocket, const struct sockaddr * pTo,int nAddrLen,char const * pszBuffer, int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);
	int Send_Block(SOCKET hSocket,char const * pszBuffer, 	int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);

	int SendTo_Block(SOCKET hSocket, const struct sockaddr * pTo,int nAddrLen,char const * pszBuffer, int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);
protected:
	//�첽
	int RecvLL(SOCKET hSocket, char *pszBuffer, int nBufferSize);
	int SendLL(SOCKET hSocket, char const * pszBuffer, int nBufferSize);

	inline int GetLastError()//��ȡ���һ�β����Ĵ������
	{
		return (m_nErrorNo);
	};
	int BindSocket(SOCKET hSocket, struct sockaddr * pSocketAddress, int nAddrLen);
	int BindSocketEx(SOCKET hSocket,int nPort);
	int ListenSocket(SOCKET hSocket, int nConnections);
	SOCKET CreateSocket(int nAddressFamily= AF_INET, int nType=SOCK_STREAM,int nProtocol= 0);
	void CloseSocket(SOCKET hSocket, BOOL bHardClose=FALSE);
	DWORD GetIP(const char* name,BOOL bFixNtDNS= FALSE);

	//(����ģ��)
	SOCKET Accept_Block(SOCKET hSocket, struct sockaddr * pSocketAddress,int *nAddrLen);
	int Connect_Block(SOCKET hSocket, const struct sockaddr * pSocketAddress, int nAddrLen);
	//����ȫ�����������ݣ�ֱ����ʱ�������
	int SendData_Block(SOCKET hSocket,char const * pszBuffer, int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);
	//�����������ݣ��ú���ֹͣ���ڸö˿ڱ��ر�(���ճ���Ϊ0)����������ʱ��
	int RecvData_Block(SOCKET hSocket, char *pszBuffer, int nBufferSize, DWORD dwTimeout= RECV_TIMEOUT);
	int RecvDataFrom_Block( SOCKET hSocket, struct sockaddr * pFrom,  int nAddrlen,char *pszBuffer, int nBufferSize, DWORD dwTimeout=RECV_TIMEOUT);

	//(�¼�ģ��)һ���̵߳ȴ�һ���¼�
	int Connect_Event(SOCKET hSocket, const struct sockaddr * pSocketAddress, int nAddrLen,DWORD dwTimeout=CONNECT_TIMEOUT);
	//TCP
	int RecvData_Event(SOCKET hSocket, char *pszBuffer, int nBufferSize, DWORD dwTimeout= RECV_TIMEOUT);
	//UDP
	int RecvDataFrom_Event( SOCKET hSocket, struct sockaddr * pFrom, int nAddrlen,char *pszBuffer, int nBufferSize,   DWORD dwTimeout=RECV_TIMEOUT);
	//�����������ݻ�ʱ
	int SendData_Event(SOCKET hSocket, char const * pszBuffer, int nBufferSize, DWORD dwTimeout=SEND_TIMEOUT);
	//���ô������
	inline void SetLastError(int iErrorCode)
	{
		::EnterCriticalSection(&m_csErrorNo);
		m_nErrorNo = iErrorCode;
		::LeaveCriticalSection(&m_csErrorNo);
	};	
};
