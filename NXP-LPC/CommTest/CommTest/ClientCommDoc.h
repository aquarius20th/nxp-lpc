
// CommTestDoc.h : CClientCommDoc ��Ľӿ�
//


#pragma once
#include "ClientComm.h"

const int MAX_SEND_LEN = 2048;

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

	CClientSocket  m_ClientSocket;

	CMutex  m_nSendTxtMutex;

	//ԭʼ�ģ�UNICODE����
	CString m_szRawSendTxt;

 

#ifdef UNICODE
	
#endif // UNICODE


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
};


