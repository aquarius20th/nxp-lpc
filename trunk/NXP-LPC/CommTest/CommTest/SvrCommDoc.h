#pragma once

#include <vector> 

// CSvrCommDoc �ĵ�
//const unsigned int UPDATA_VIEW_PING_NORMAL = 1;
//const unsigned int UPDATA_VIEW_CLIENT_PACKET = 2;

class CSvrCommDoc : public CDocument
{
	DECLARE_DYNCREATE(CSvrCommDoc)

public:
	CSvrCommDoc();
	virtual ~CSvrCommDoc();

public:
 
	//��ʼ�շ�
	void StartTask( );
	//ֹͣ�շ�
	void StopTask( );
private:



#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnCloseDocument();
};
