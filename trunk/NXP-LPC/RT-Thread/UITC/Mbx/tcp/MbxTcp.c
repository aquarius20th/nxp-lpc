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
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>

#include <lwip/sys.h>
#include <lwip/api.h>
#include "lwip/ip_addr.h"

#include "applib.h"
#include "mb.h"
#include "MbxTcp.h"
#include "mbproto.h" 
#include "Func.h"


/* ----------------------- Defines ------------------------------------------*/

/* ----------------------- MBAP Header --------------------------------------*/
/*
 *
 * <------------------------ MODBUS TCP/IP ADU(1) ------------------------->
 *              <----------- MODBUS PDU (1') ---------------->
 *  +-----------+---------------+------------------------------------------+
 *  | TID | PID | Length | UID  |Code | Data                               |
 *  +-----------+---------------+------------------------------------------+
 *  |     |     |        |      |                                           
 * (2)   (3)   (4)      (5)    (6)                                          
 *
 * (2)  ... MB_TCP_TID          = 0 (Transaction Identifier - 2 Byte) 
 * (3)  ... MB_TCP_PID          = 2 (Protocol Identifier - 2 Byte)
 * (4)  ... MB_TCP_LEN          = 4 (Number of bytes - 2 Byte)
 * (5)  ... MB_TCP_UID          = 6 (Unit Identifier - 1 Byte)
 * (6)  ... MB_TCP_FUNC         = 7 (Modbus Function Code)
 *
 * (1)  ... Modbus TCP/IP Application Data Unit
 * (1') ... Modbus Protocol Data Unit
 */

#define MB_TCP_TID          0
#define MB_TCP_PID          2
#define MB_TCP_LEN          4
#define MB_TCP_UID          6
#define MB_TCP_FUNC         7

#define MB_TCP_PROTOCOL_ID  0   /* 0 = Modbus Protocol */

/* ----------------------- Defines ------------------------------------------*/
#define MB_TCP_PSEUDO_ADDRESS   255

#define MB_TCP_DEFAULT_PORT 502 /* TCP listening port. */


MBErrorCode MBTCPReceive( UCHAR * pucRcvAddress, UCHAR ** ppucFrame, USHORT * pusLength )
{
    MBErrorCode    eStatus = MB_EIO;
    UCHAR          *pucMBTCPFrame;
    USHORT          usLength;
    USHORT          usPID;

//    if( xMBTCPPortGetRequest( &pucMBTCPFrame, &usLength ) != FALSE )
	if(0)
    {
        usPID = pucMBTCPFrame[MB_TCP_PID] << 8U;
        usPID |= pucMBTCPFrame[MB_TCP_PID + 1];

        if( usPID == MB_TCP_PROTOCOL_ID )
        {
            *ppucFrame = &pucMBTCPFrame[MB_TCP_FUNC];
            *pusLength = usLength - MB_TCP_FUNC;
            eStatus = MB_ENOERR;

            /* Modbus TCP does not use any addresses. Fake the source address such
             * that the processing part deals with this frame.
             */
            *pucRcvAddress = MB_TCP_PSEUDO_ADDRESS;
        }
    }
    else
    {
        eStatus = MB_EIO;
    }
    return eStatus;
}

MBErrorCode MBTCPSend( UCHAR _unused, const UCHAR * pucFrame, USHORT usLength )
{
    MBErrorCode    eStatus = MB_ENOERR;
    UCHAR          *pucMBTCPFrame = ( UCHAR * ) pucFrame - MB_TCP_FUNC;
    USHORT          usTCPLength = usLength + MB_TCP_FUNC;

    /* The MBAP header is already initialized because the caller calls this
     * function with the buffer returned by the previous call. Therefore we 
     * only have to update the length in the header. Note that the length 
     * header includes the size of the Modbus PDU and the UID Byte. Therefore 
     * the length is usLength plus one.
     */
    pucMBTCPFrame[MB_TCP_LEN] = ( usLength + 1 ) >> 8U;
    pucMBTCPFrame[MB_TCP_LEN + 1] = ( usLength + 1 ) & 0xFF;
//    if( xMBTCPPortSendResponse( pucMBTCPFrame, usTCPLength ) == FALSE )
    {
        eStatus = MB_EIO;
    }
    return eStatus;
}

#define  MBX_TCP_TASK_STK_SIZE 512
#define  MBX_TCP_TASK_PRIO 18
//���֧��3·����
#define  MBX_TCP_CLIENT_CNT 3

struct MBX_TCP
{
	INT32U TaskStk[MBX_TCP_TASK_STK_SIZE];
	INT8U  Priority;
	INT8U  UsedFlag;

	//�Զ˵�IP��ַ�Լ��˿ں�
	struct ip_addr Addr;
	INT16U Port;

	struct netconn  *pConn;

};

typedef struct MBX_TCP CMbxTcp;

CMbxTcp g_arrMbxTcp[MBX_TCP_CLIENT_CNT];

/*********************************************************************************************************
** ��������: InitMbxTcp
** ��������: InitMbxTcp
**
** ����������  
**
** �䡡��:  void
**          
** �䡡��:   void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2009��11��20��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void InitMbxTcp( void )
{
	INT8U i = 0;
	for ( i = 0 ; i < MBX_TCP_CLIENT_CNT ; i++)
	{
		memset( &g_arrMbxTcp[i].TaskStk ,0,sizeof( g_arrMbxTcp[i].TaskStk ) );
	}


}

static INT8U AddNewClient( struct netconn  *pConn )
{

	return TRUE;
}

void MbxTcpListen(void *pData )
{
	struct netconn *conn = NULL, *newconn = NULL;
	INT16U sin_port = 0;
	struct ip_addr naddr;
	/* ����һ�����ӽṹ */
	conn = netconn_new(NETCONN_TCP);
	/* �����Ӱ󶨵�һ����������IP��ַ��2000�˿��� */
	netconn_bind(conn, NULL, MB_TCP_DEFAULT_PORT);
	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	while(1)
	{
		/* ����ֱ���õ�һ����������� */
		newconn = netconn_accept(conn);
		if (newconn)
		{
			/* ��ȡԶ��������IP��ַ�Ͷ˿ں� */
			netconn_peer(newconn,  &naddr, &sin_port);
			//		sin.sin_port = htons(sin.sin_port);
			//		sin.sin_addr.s_addr = naddr.addr;
			//����Ƿ�Ϸ�


			//֪ͨ������һ������
		}

	}
}


void InitMbxTcpTask( )
{

}