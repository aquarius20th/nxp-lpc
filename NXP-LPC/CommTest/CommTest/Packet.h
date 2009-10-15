/****************************************Copyright (c)**************************************************
**                                 
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:  
**��   ��   ��:  
**����޸�����: 
**��        ��:    ����  ����PING PONG���й���
**
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:  
** ��  ��:  
** �ա���:  
** �衡��: 
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:
** �ա���:
** �衡��:
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#pragma once
#include <deque>


const unsigned int MAX_PACKET_LEN = 2048;
const unsigned int MAX_PACKET_CNT = 2048;

class CPacket
{
public:
	CPacket( );
	CPacket( unsigned char *pData,unsigned int nLen );
	~CPacket( );
public:
	void SetPacket( unsigned char *pData,unsigned int nLen);
	unsigned int m_nId;
	unsigned int GetPacket(CString &szPacket);
protected:
	unsigned char *m_pPacketData;
	unsigned int  m_nLen;
public:
	SYSTEMTIME m_stBuild; 
};


class CPacketContainer
{
public:
	CPacketContainer();
	~CPacketContainer();


public:
	 //task ��ping���������ݣ����ping���ˣ���ֹͣ����
	void PutData( unsigned char *pData,unsigned int nLen  );
	//view��ping��ȡ����
	bool GetData( CPacket ** ppPacket );

	//view����ɾ������
	bool RemoveData( CPacket *pPacket );

protected:
	void FreeMem( );

	CCriticalSection  m_Mutex;
	 //task ��ping���������ݣ����ping���ˣ���ֹͣ����
	std::deque  < CPacket * >   m_arrPingBuf; 

	//view��ping��ȡ���ݣ�Ȼ���Ƶ�pong�У����pong���ˣ���ʼɾ��pong��ͷ
	std::deque  < CPacket * >   m_arrPongBuf;
	unsigned int m_nCurId;
};