
#pragma  once 


#include "EcBusSocket.h"

class CClientCommDoc;
class CClientSocket : public CEcBusSocket
{
	friend UINT  EthCommTask (LPVOID lpParam);		 
public:
	CClientSocket( );
	~CClientSocket( );
public:
	BOOL Connect ( DWORD dwTimeout = 2000);

	//��ʼ�շ�
	void StartEngine( );
	//ֹͣ�շ�
	void StopEngine( );

protected:
	SOCKET  m_nSocket;

	CClientCommDoc *m_pDocument;

	DWORD  m_dwDestIp;
	unsigned int m_nDestPortNum;
	unsigned int m_nLocalPortNum;

	CWinThread *m_pCommTsk;
	HANDLE      m_hStopEvent;
	HANDLE m_hTaskHandle;

};
