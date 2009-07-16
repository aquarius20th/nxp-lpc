//*------------------------------------------------------------------------------------------------
//* �ļ���				: LwIPEntry.c
//* ��������			: LwIP��ں�����
//* ����    			: ������
//* �汾				: 0.1
//* �������ڡ�ʱ��		: 2007/06/24
//* �޸����ڡ�ʱ��	    : 
//* �޸�ԭ��			: 
//*------------------------------------------------------------------------------------------------
//*------------------------------------------ ͷ�ļ� ----------------------------------------------
#include <stdlib.h>
#include	"ucos_ii.h"
#include	"../include/lwip/netif.h"
#include	"../include/lwip/tcpip.h"
//*------------------------------------ �������������ͺ궨�� --------------------------------------
//* IP��ַ
#define 	IP_ADDR_0			192
#define 	IP_ADDR_1			168
#define 	IP_ADDR_2			10
#define 	IP_ADDR_3			72

//* ���ص�ַ
#define		GATEWAY_ADDR_0 		192
#define		GATEWAY_ADDR_1 		168
#define		GATEWAY_ADDR_2 		10	   
#define		GATEWAY_ADDR_3 		1

//* �����ַ
#define		NET_MASK_0			255
#define		NET_MASK_1			255
#define		NET_MASK_2			255
#define		NET_MASK_3			0
//*================================================================================================
//*����������������������������������������������������
//*================================================================================================
//*------------------------------------------------------------------------------------------------
//* �������� : __ilvInitLwIP
//* �������� : ���LwIP������ĳ�ʼ������
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
__inline void __ilvInitLwIP(void)
{
	sys_init();
	
	mem_init();
	
	memp_init();
	
	pbuf_init();
	
//	raw_init();
	
	tcpip_init(NULL, NULL);
}
//*------------------------------------------------------------------------------------------------
//* �������� : __ilvSetLwIP
//* �������� : ����LwIP�����������������ӿڡ�������������ȹ���
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
__inline void __ilvSetLwIP(void)
{
	extern err_t ethernetif_init(struct netif *stNetif);

	struct ip_addr __stIpAddr, __stNetMask, __stGateway;
	static struct netif __stEMACNetif;
	
	//* ��ʼ��ȱʡ����ӿ�(��ϰ�������ϵ�����)������ӿ�����(��netif�ṹ������)������
	//* ����˵�������������ȱ�����
	netif_init();
	
	//* ����������EMAC�ӿ�
	IP4_ADDR(&__stIpAddr, IP_ADDR_0, IP_ADDR_1, IP_ADDR_2, IP_ADDR_3);
			
	IP4_ADDR(&__stNetMask, NET_MASK_0, NET_MASK_1, NET_MASK_2, NET_MASK_3);
	IP4_ADDR(&__stGateway, GATEWAY_ADDR_0, GATEWAY_ADDR_1, GATEWAY_ADDR_2, GATEWAY_ADDR_3);
	
	netif_add(&__stEMACNetif, &__stIpAddr, &__stNetMask, &__stGateway, NULL, ethernetif_init, tcpip_input);
	
	netif_set_default(&__stEMACNetif);
	netif_set_up(&__stEMACNetif);
}
//*------------------------------------------------------------------------------------------------
//* �������� : T_LwIPEntry
//* �������� : LwIP�������
//* ��ڲ��� : <pvArg>[in/out] ��������
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void T_LwIPEntry(void * pvArg)
{
	struct netconn  *__pstConn, *__pstNewConn;
	struct netbuf	*__pstNetbuf;

	//* ��ʼ��LwIP
	__ilvInitLwIP();
	
	//* ����LwIP�����������������ӿڡ�������������ȹ���
	__ilvSetLwIP();
	
	__pstConn = netconn_new(NETCONN_TCP);
	netconn_bind(__pstConn, NULL, 80);
	netconn_listen(__pstConn);
	
	while(OS_TRUE)
	{
		__pstNewConn = netconn_accept(__pstConn);
		
		if(__pstNewConn != NULL)
		{			
			__pstNetbuf = netconn_recv(__pstNewConn);
			if(__pstNetbuf != NULL)
			{
				netconn_write(__pstNewConn, "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n", 44, NETCONN_COPY);
				netconn_write(__pstNewConn, "<body><h1>����LWIP TCP���ԣ�</h1></body>", 40, NETCONN_COPY);
				
				netbuf_delete(__pstNetbuf);	
			}
			
			netconn_close(__pstNewConn);
			while(netconn_delete(__pstNewConn) != ERR_OK)
				OSTimeDlyHMSM(0, 0, 1, 0);
		}
	}
}