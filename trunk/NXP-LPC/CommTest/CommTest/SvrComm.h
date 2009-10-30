
#pragma  once 

#include "UEServer.h"

class CSvrCommFrm;
class CClientNode : public ClientContext
{
public: 
	CClientNode( )
	{
		m_pFrm = NULL;

	}
	~CClientNode( )
	{

	}
public:
	CSvrCommFrm   *m_pFrm;

};

class CSvrComm :public CUEServer
{
 public:
	 CSvrComm( );
	 ~CSvrComm( );
 public:
	 BOOL m_bStart;
	 //��ʼ�շ�
	 BOOL StartTask( );
	 //ֹͣ�շ�
	 void StopTask( );

	 // Called when a new connection have been established.. 
	 virtual void NotifyNewConnection(ClientContext *pcontext);
	 virtual void NotifyDisconnectedClient(ClientContext *pContext);

public:
	 std::vector <CClientNode *> m_arrClientNode;
private:
	void FreeMem( );
};