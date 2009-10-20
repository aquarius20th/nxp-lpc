
// CommTestDoc.h : CClientCommDoc ��Ľӿ�
//


#pragma once
#include "ClientComm.h"
#include "Packet.h"

const int MAX_SEND_LEN = 2048;

const unsigned int UPDATA_VIEW_CLIENT_NORMAL = 1;
const unsigned int UPDATA_VIEW_CLIENT_PACKET = 2;

class CPacketDecodeFrm;
class CClientCommDoc : public CDocument
{
protected: // �������л�����
	CClientCommDoc();
	DECLARE_DYNCREATE(CClientCommDoc)

// ����
public:
	int  m_nProtocolType; //Э������ 0 TCP 1 UDP
	DWORD m_dwDestIp;
	unsigned int m_nDestPort;
	unsigned int m_nLocalPort; //0 ��ʾ����˿� ��0Ϊָ���˿�

	CClientComm  m_ClientComm;

	CPacketDecodeFrm    *m_pDecodeFrm;


	//ԭʼ�ģ�UNICODE����
	CString m_szRawSendTxt;

	BOOL Connect( );

	void  Disconnect( );


	BOOL m_bConnected;

	CPacketContainer m_PacketCtnr;

	unsigned int m_nPacketId;

	 
 
 

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CClientCommDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCloseDocument();
};


