

#include "db_cxx.h"
class CBDBWrapper
{
public:
	CBDBWrapper( );
	~CBDBWrapper( );
public:
protected:
	Db	   *m_pDB;					//���ݿ�
	DbEnv  *m_pDbEnv;				//���ݿ⻷��
	DbTxn  *m_pDbTxn;				//����������


};