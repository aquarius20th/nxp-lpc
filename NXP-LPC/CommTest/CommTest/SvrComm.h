
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
	void CopyData(ClientContext *pContext);
	BOOL m_bOnline;
private:

	//����ʱ���ۼ�
//	COleDateTime m_dtLink;



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
	 virtual inline void NotifyReceivedPackage(CSvrCommPacket *pOverlapBuff,int nSize,ClientContext *pContext);

	 std::vector <CClientNode *> & GetClientNodeArr( ) 
	 {
		 CSingleLock lock(&m_Lock,TRUE);
		 return m_arrClientNode;
	 }

private:
	CCriticalSection m_Lock; 

	//������Ҫ����
	stdext::hash_map <ClientContext *, CClientNode *> m_mapClients;
	std::vector <CClientNode *> m_arrClientNode;
private:
	void FreeMem( );
};