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
**����޸�����: 2 
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
#include "stdafx.h"
#include "SvrCommMsg.h"

CSvrCommPacket::CSvrCommPacket()
{
	Init();
}

CSvrCommPacket::~CSvrCommPacket()
{

}


void CSvrCommPacket::Init()
{
	m_nUsed=0;
	m_nOperation=-1;
 	ZeroMemory(&m_ol, sizeof(OVERLAPPED));
	ZeroMemory(&m_Buffer,sizeof(m_Buffer));
}
// Setup Setup the buffer for a Read. 
void CSvrCommPacket::SetupRead()
{
	if (m_nUsed == 0)
	{
		m_wsabuf.buf = reinterpret_cast<char*>(m_Buffer);
		m_wsabuf.len = MAX_PACKAGE_SIZE; 
	}
	else // We have received some of the data but not all .. 
	{
		m_wsabuf.buf = reinterpret_cast<char*>(m_Buffer) + m_nUsed;
		m_wsabuf.len = MAX_PACKAGE_SIZE - m_nUsed; 
	}
}

// Setup the buffer for a Write
void CSvrCommPacket::SetupWrite()
{
	m_wsabuf.buf = reinterpret_cast<char*>(m_Buffer);
	m_wsabuf.len = m_nUsed;
}

// cheks if the Buffer is valid. 
BOOL CSvrCommPacket::IsValid()
{
	return TRUE;
}

UINT CSvrCommPacket::GetUsed()
{
	return m_nUsed;
}

// Used to indicate that we did have  a successfull Receive 
UINT CSvrCommPacket::Use(UINT nSize)
{
	m_nUsed+=nSize;
	return m_nUsed;
}

// Empty A used structure. 
void CSvrCommPacket::EmptyUsed()
{
	m_nUsed=0;
}

/*********************************************************************************************************
** ��������: Flush
** ��������: CSvrCommPacket::Flush
**
** ���������� ����ɾ������������ 
**
** �䡡��:  UINT nBytesToRemove
**          
** �䡡��:   BOOL
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��10��26��
** ��  ע:  removes nSize byte from the Buffer. 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
BOOL CSvrCommPacket::Flush(UINT nBytesToRemove)
{
	if ((nBytesToRemove > MAX_PACKAGE_SIZE) || (nBytesToRemove > m_nUsed) ) 
	{
		TRACE("ERROR BOOL CSvrCommPacket::Flush(UINT nBytesToRemove)");
		return FALSE;
	}
	m_nUsed-=nBytesToRemove;
	memmove(m_Buffer, m_Buffer + nBytesToRemove, m_nUsed);
	return TRUE;
}


BOOL CSvrCommPacket::AddData(BYTE data)
{
	return AddData(&data, 1);
}

BOOL CSvrCommPacket::AddData(UINT data)
{
	return AddData(reinterpret_cast<const BYTE*>(&data), sizeof(UINT));
}

BOOL CSvrCommPacket::AddData(unsigned short data)
{
	return AddData(reinterpret_cast<const BYTE*>(&data), sizeof(unsigned short));
}

/*
* Adds a stream of char to the buffer. 
*/
BOOL CSvrCommPacket::AddData(const char *const pData, UINT nSize)
{ 
	return AddData(reinterpret_cast<const BYTE*>(pData),nSize);
}

/*
* Adds a stream of BYTES to the buffer. 
*/
BOOL CSvrCommPacket::AddData(const BYTE *const pData, UINT nSize)
{
	ASSERT(nSize+m_nUsed < MAX_PACKAGE_SIZE);
	if ( nSize > MAX_PACKAGE_SIZE-m_nUsed )
		return FALSE;
	else
	{
	//	memcpy(m_Buffer + m_nUsed, pData, nSize);
		memcpy_s(m_Buffer + m_nUsed, MAX_PACKAGE_SIZE-m_nUsed, pData, nSize);
		m_nUsed += nSize;
		return TRUE;
	}
}
// Setup the buffer for a ZeroByteRead. 
void CSvrCommPacket::SetupZeroByteRead()
{
	m_wsabuf.buf =(char*)m_Buffer;
	m_wsabuf.len = 0; 
}
