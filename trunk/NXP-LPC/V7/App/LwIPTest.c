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
**��        ��:   
**��        ע :   
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
#include <stdlib.h>
#include "includes.h"  
#include "bsp.h"
#include "api.h"
#include "sockets.h"

#define  MAX_CONN_CNT 3 //֧�����3·����

struct client_node
{
	struct netconn *conn;
	INT32U second_cnt; //����������붨ʱ���в����ۼӣ�����յ����ݾ���0��30����һ�Σ��������ֵ>30�����ж�Ϊû�����ݣ��Ͽ�
};

struct netconn *g_Conn[MAX_CONN_CNT] ; 

void InitServer( )
{
	INT8U i = 0;

	for (i = 0 ; i < MAX_CONN_CNT; i++)
	{
		g_Conn[i] = NULL;
	}

}

void MainLwIpListen( )
{
	struct netconn *conn = NULL, *newconn = NULL;
	struct sockaddr_in sin;
	struct ip_addr naddr;
	/* ����һ�����ӽṹ */
	conn = netconn_new(NETCONN_TCP);
	/* �����Ӱ󶨵�һ����������IP��ַ��2000�˿��� */
	netconn_bind(conn, NULL, 2000);

	while(1)
	{
		/* ����ֱ���õ�һ����������� */
		newconn = netconn_accept(conn);
		if (newconn)
		{
			/* ��ȡԶ��������IP��ַ�Ͷ˿ں� */
			netconn_peer(conn,  &naddr, &sin.sin_port);
	//		sin.sin_port = htons(sin.sin_port);
	//		sin.sin_addr.s_addr = naddr.addr;
			//����Ƿ�Ϸ�


			//֪ͨ������һ������
		}

		OSTimeDly(1000);
	}
}

void ClientMgr( )
{

}

void ConnHandler( struct netconn *conn )
{
	struct netbuf *buf = NULL;
	if (conn == NULL)
		return ;
	
	/* ��������ֱ�����������ر����� */
	buf = netconn_recv(conn);
	if (buf)
	{
		//��������Ӵ��ʱ����������ʱ��û�������շ�����ô��Ҫǿ�ƹر�

		//��������

	}
	else
	{
		netconn_delete(conn);
	}
// 	while((buf = netconn_recv(conn)) != NULL)
// 	{
// //		do_something(buf);
// 	}
}

