/****************************************Copyright (c)**************************************************
**                                ���տƼ��ɷ����޹�˾
**                                     ��ҵ��
**                                         
**
**                                 http://www.xxx.com.cn
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:  
**��   ��   ��:  
**����޸�����: 
**��        ��:  
**              
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:  
** ��  ��: v1.00
** �ա���:  
** �衡��: ԭʼ�汾
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:  
** �ա���:  
** �衡��:  
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

#pragma  once
#include <deque>

// Determines the size of the first bytes who tells you how big the message are. (pakage heap)  
const int MAX_PACKAGE_SIZE = 1024;

class CSvrCommPacket
{
public:
	CSvrCommPacket( );
	~CSvrCommPacket( );
public:
	// Used with overlapped.. 
	OVERLAPPED			m_ol;

	int GetOperation()
	{
		return m_nOperation;
	}
	void SetOperation(int op)
	{
		m_nOperation = op;
	}
	// returns A pointer to the Buffer 
	unsigned char * GetBuffer()
	{
		return m_Buffer;
	}
	WSABUF * GetWSABuffer()
	{
		return  const_cast<WSABUF*>(&m_wsabuf);
	}
	// Setup Different Types in buffer. 
	void SetupWrite();
	void SetupRead();
	void SetupZeroByteRead();

	void EmptyUsed();
	UINT Use(UINT nSize);
	UINT GetUsed();
	//UINT GetSize();
	BOOL IsValid();

	BOOL Flush(UINT nBytesToRemove);

	// Write different types of variabels to the buffer
	BOOL AddData(const BYTE * pData,UINT nSize);
	BOOL AddData(const char * pData,UINT nSize);
	BOOL AddData(BYTE data);
	BOOL AddData(UINT data);
	BOOL AddData(unsigned short data);

	int m_nSeqNum;
protected:
	void Init();	


protected:
	// The Type of Operation. 
	int		m_nOperation;


	// number of bytes that are Used. 
	unsigned int    m_nUsed;
	// The buffer. 
	unsigned char  m_Buffer[MAX_PACKAGE_SIZE];
	//Holds the Buffer Used for send/receive
	WSABUF m_wsabuf;
};