


#include "stdafx.h"

#include "BDBWrapper.h"
 
 

CBDBWrapper::CBDBWrapper()
{
	m_pDB = NULL;					//���ݿ�
	m_pDbEnv = NULL;				//���ݿ⻷��
	m_pDbTxn = NULL;				//����������
}

CBDBWrapper::~CBDBWrapper( )
{

}