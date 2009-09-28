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
#include "app_cfg.h"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (int)(-1)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR            (-1)
#endif


#define  MAX_CONN_CNT 3 //֧�����3·����
#define USERPORT  9002

#define  BUFF_LEN  512

struct client_node
{
	INT32S  sock_id;
	INT32U  second_cnt; //����������붨ʱ���в����ۼӣ�����յ����ݾ���0��30����һ�Σ��������ֵ>30�����ж�Ϊû�����ݣ��Ͽ�
	INT8U   send_buf[BUFF_LEN];
	INT8U   recv_buf[BUFF_LEN];
	INT16U  send_len;
	INT16U  recv_len;
};

static struct client_node g_Conn[MAX_CONN_CNT];
static  OS_STK          ListenTaskStk[LISTEN_TASK_STK_SIZE];
static  OS_STK          NetSvrTaskStk[NET_SVR_TASK_STK_SIZE][MAX_CONN_CNT];


static INT32S GetSocket( struct client_node *pClient)
{
#if OS_CRITICAL_METHOD == 3              
	OS_CPU_SR  cpu_sr = 0;
#endif
	INT32S socket_id = INVALID_SOCKET;

	if (pClient)
	{
		OS_ENTER_CRITICAL();
		socket_id = pClient->sock_id ;
		OS_EXIT_CRITICAL();
	}
	return socket_id;
}

static INT8U AddNode( INT32S nSocketId )
{
#if OS_CRITICAL_METHOD == 3              
	OS_CPU_SR  cpu_sr = 0;
#endif
	INT8U i  = 0;
	INT8U bFlag = OS_FALSE;

	if (nSocketId == 0 || nSocketId == INVALID_SOCKET)
		return OS_FALSE;

	OS_ENTER_CRITICAL();

	for (i  = 0; i < MAX_CONN_CNT ; i++)
	{
		if(g_Conn[i].sock_id == 0 || g_Conn[i].sock_id == INVALID_SOCKET )
		{
			bFlag = OS_TRUE;
			g_Conn[i].sock_id = nSocketId;
			g_Conn[i].recv_len = 0;
			g_Conn[i].send_len = 0;
			break;
//			if(g_Conn[i].sock_id )
		}		
	}
//	socket_id = pClient->sock_id ;
	OS_EXIT_CRITICAL();	
}

static void RemoveNode( struct client_node *pClient )
{
#if OS_CRITICAL_METHOD == 3              
	OS_CPU_SR  cpu_sr = 0;
#endif	 
	if (pClient)
	{
		OS_ENTER_CRITICAL();
		pClient->sock_id = INVALID_SOCKET;
		OS_EXIT_CRITICAL();
	} 
} 

static  void  ListenTask (void *p_arg)
{
	INT32S newsocket,server;
	struct sockaddr_in dst_addr,client_addr;
	int namelen = sizeof(client_addr);
	while(1)
	{
		server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if (server == INVALID_SOCKET)
		{
			OSTimeDlyHMSM(0,0,1,0);
			continue;
		}

		dst_addr.sin_family = AF_INET;
		dst_addr.sin_port = htons(USERPORT);
		dst_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		if (bind(server,(struct sockaddr *)&dst_addr,sizeof(dst_addr))==SOCKET_ERROR)
		{
			//	str_print("�������˿ڰ�ʧ�ܡ�����ȷ����IP��ַ����������",2);
			close(server);
			OSTimeDlyHMSM(0,0,1,0);

			continue; 
		}

		if (listen(server,5) == SOCKET_ERROR)
		{
			close(server);
			OSTimeDlyHMSM(0,0,1,0);
			continue;
		}

		while(1)
		{
			struct fd_set fdread;
			struct timeval tv;
			int ret = 0;

			OSTimeDlyHMSM(0,0,0,300);
	 		tv.tv_sec = 0;
			tv.tv_usec = 1;
			FD_ZERO(&fdread);
			FD_SET(server, &fdread);
			ret = select(0, &fdread, NULL, NULL, &tv);
			if (ret <= 0)
				continue;
			newsocket = accept(server,(struct sockaddr*)&client_addr,&namelen);
			if (newsocket == INVALID_SOCKET)
			{
				close(newsocket);
				OSTimeDlyHMSM(0,0,0,300);
				continue;
			}
			//���ӽ����ˣ������Ƿ����ظ��Ľڵ㣬Ȼ����ӽ���
			


		}
	}

}

static  void  ProcessTask (void *p_arg)
{
	INT32S sock;
	int ret = 0;
	struct client_node *pCilent = (struct client_node *)p_arg;

	if (p_arg == NULL)
		return;

	while(1)
	{
		sock = GetSocket( pCilent );
		if (sock == 0 || sock == INVALID_SOCKET)
		{
			OSTimeDlyHMSM(0,0,1,0);
			continue;
		}

	 	//�������ݣ�Ȼ��������
		ret = recv(sock, pCilent->recv_buf, BUFF_LEN, 0);

		if (ret>0 && ret <= BUFF_LEN)
		{//�������ݴ���

		}
		else if ( ret == 0)
		{// ���ӱ��ر���
			close( sock );
			RemoveNode(pCilent);
			continue;
		}
		else
		{
			continue;
		}
	}
}


void InitNetSvr( void )
{
	INT8U i = 0;

	for (i = 0 ; i < MAX_CONN_CNT; i++)
	{
		memset(&g_Conn[i],0,sizeof(struct client_node ));
	}

	//���������߳�
	OSTaskCreateExt(ListenTask,                               /* Create the start task                                    */
		(void *)0,
		(OS_STK *)&ListenTaskStk[LISTEN_TASK_STK_SIZE - 1],
		LISTEN_TASK_PRIO,
		LISTEN_TASK_PRIO,
		(OS_STK *)&ListenTaskStk[0],
		LISTEN_TASK_STK_SIZE,
		(void *)0,
		OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

 
	//���������շ��߳�
	for (i = 0 ; i < MAX_CONN_CNT; i++)
	{
		OSTaskCreateExt(ProcessTask,                               /* Create the start task                                    */
			(void *)(& g_Conn[i]),
			(OS_STK *)&NetSvrTaskStk[NET_SVR_TASK_STK_SIZE - 1][i],
			NET_SVR_TASK_PRIO_BASE+i,
			NET_SVR_TASK_PRIO_BASE+i,
			(OS_STK *)&(NetSvrTaskStk[0][i]),
			NET_SVR_TASK_STK_SIZE,
			(void *)0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	}
 
}