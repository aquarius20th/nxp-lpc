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
**��        ��:    ����
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

#include "stdafx.h"
#include "Packet.h"
#include <algorithm>
#include  "boost/memory.hpp"

boost::auto_alloc g_packet_alloc; 

CPacket::CPacket()
{
	m_pPacketData = NULL;
	m_nLen = 0;;
	m_nId = 0;
}

CPacket::~CPacket()
{

}

CPacket::CPacket( unsigned char *pData,unsigned int nLen )
{
	m_pPacketData = NULL;
	m_nLen = 0;;
	m_nId = 0;

	ASSERT( pData );
	ASSERT(nLen >0  && nLen <= MAX_PACKET_LEN);
	if (pData == NULL || nLen == 0 || nLen > MAX_PACKET_LEN)
		return;
	GetLocalTime(&m_stBuild);

	m_pPacketData = BOOST_MEMORY_ALLOC_ARRAY(g_packet_alloc, unsigned char, nLen); 
	m_nLen = nLen;
	memcpy_s(m_pPacketData,m_nLen,pData,nLen);
}

void CPacket::SetPacket( unsigned char *pData,unsigned int nLen)
{
	ASSERT( pData );
	ASSERT(nLen >0  && nLen <= MAX_PACKET_LEN);
	if (pData == NULL || nLen == 0 || nLen > MAX_PACKET_LEN)
		return;
	GetLocalTime(&m_stBuild);

	m_pPacketData = BOOST_MEMORY_ALLOC_ARRAY(g_packet_alloc, unsigned char, nLen); 
	m_nLen = nLen;
	memcpy_s(m_pPacketData,m_nLen,pData,nLen);
}

unsigned int CPacket::GetPacket(CString &szPacket)
{
	if (m_nLen >0 && m_nLen <MAX_PACKET_LEN)
	{
//		char szMsgB[512] = {0};
//		sprintf(szMsgB,"%02X ",pMsg->pData[0]);
		unsigned int nLen =  m_nLen;
		unsigned int i = 1;
		TCHAR temp[10] = {0};
		
	//	_stprintf_s(temp,"%02X ",m_pPacketData[0]);
		szPacket.Format(_T("%02X "),m_pPacketData[0]);
		if (nLen >= 32)
		{
			nLen = 32;
			for (i = 1; i<nLen; i++)
			{
				_stprintf_s(temp,6,_T("%02X "), m_pPacketData[i] );
				szPacket += temp;
			}
			szPacket.Delete(szPacket.GetLength()-1);
			szPacket += _T("...");
		}
		else
		{
			if (nLen>1)
			{
				for (i = 1; i<nLen; i++)
				{
					_stprintf_s(temp,6,_T("%02X "), m_pPacketData[i] );
					szPacket += temp;
				}
			}			
			szPacket.Delete(szPacket.GetLength()-1);			  
		}
	}
	return m_nLen;
}

unsigned char *CPacket::GetPacket(unsigned int &nLen)
{
	nLen = m_nLen;
	return m_pPacketData;
}

CPacketContainer::CPacketContainer()
{
	m_nCurId = 0;
}

CPacketContainer::~CPacketContainer()
{
	FreeMem( );
}
/*********************************************************************************************************
** ��������: PutData
** ��������: CPacketContainer::PutData
**
** ����������  
**
** �䡡��:  unsigned char * pData
** �䡡��:  unsigned int nLen
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��15��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void CPacketContainer::PutData( unsigned char *pData,unsigned int nLen  )
{
	ASSERT( pData );
	ASSERT(nLen >0  && nLen <= MAX_PACKET_LEN);
	if (pData == NULL || nLen == 0 || nLen > MAX_PACKET_LEN)
		return;

	CSingleLock lock( & m_Mutex);

	if (m_arrPingBuf.size() >= MAX_PACKET_CNT )
	{
		lock.Unlock();
		return;
	}

	CPacket *pPacket = BOOST_NEW(g_packet_alloc,CPacket);
	ASSERT(pPacket);
	if (pPacket)
	{
		pPacket->SetPacket(pData,nLen);
		pPacket->m_nId = ++m_nCurId;
		m_arrPingBuf.push_back(pPacket);
	}
	lock.Unlock();
	return;
}
/*********************************************************************************************************
** ��������: GetData
** ��������: CPacketContainer::GetData
**
** ����������  ��PING�����л�ȡ���ݣ����͵�pong������
**
** �䡡��:  CPacket * * ppPacket
**          
** �䡡��:   bool
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��15��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
bool  CPacketContainer::GetData( CPacket **ppPacket )
{
	if (ppPacket == NULL)
		return false;

	CSingleLock lock( & m_Mutex);
	if (m_arrPingBuf.empty() )
	{
		lock.Unlock();
		return false;
	}

	*ppPacket = m_arrPingBuf.front();
	m_arrPingBuf.pop_front();
	m_arrPongBuf.push_back(*ppPacket);

	return true;
}
/*********************************************************************************************************
** ��������: RemoveData
** ��������: CPacketContainer::RemoveData
**
** ����������  
**
** �䡡��:  CPacket * pPacket
**          
** �䡡��:   bool
**         
** ȫ�ֱ���:  
** ����ģ��: ����ͼ������
**
** ������:  LiJin
** �ա���:  2009��10��15��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
bool  CPacketContainer::RemoveData( CPacket *pPacket )
{
	ASSERT(pPacket);
	if (pPacket == NULL)
		return false;
	
	std::deque<CPacket *>::iterator iter;

	iter = std::find(m_arrPongBuf.begin(), m_arrPongBuf.end(),pPacket );
	if (iter != m_arrPongBuf.end())
	{
		ASSERT( (*iter)->m_nId == pPacket->m_nId );
		m_arrPongBuf.erase( iter);
		return true;
	}

//	CSingleLock lock( & m_Mutex);

	return false;
}

void CPacketContainer::FreeMem( )
{
	m_arrPongBuf.clear();
	m_arrPingBuf.clear();
}
