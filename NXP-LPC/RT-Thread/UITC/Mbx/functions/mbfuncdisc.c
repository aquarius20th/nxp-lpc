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
**   File: $Id: ,v 1.0 2009/11/15 15:27:16   $
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


/* ----------------------- System includes ----------------------------------*/
#include <stdlib.h>
#include <string.h>
 
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbframe.h"
#include "mbproto.h" 

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_DISCCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_DISCCNT_MAX        ( 0x07D0 )

/* ----------------------- Static functions ---------------------------------*/
MBException    MBError2Exception( MBErrorCode eErrorCode );

/* ----------------------- Start implementation -----------------------------*/

/*********************************************************************************************************
** ��������: MBFuncReadDiscreteInputs
** ��������: MBFuncReadDiscreteInputs
**
** ���������� ������
**
** �䡡��:  INT8U * pAduBuf
** �䡡��:  INT16U * usADULen
**          
** �䡡��:  MBException
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��28��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/ 
MBException MBFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen )
{
    USHORT          usRegAddress;
    USHORT          usDiscreteCnt;
    UCHAR           ucNBytes;
    UCHAR          *pucFrameCur;

    MBException    eStatus = MB_EX_NONE;
    MBErrorCode    eRegStatus;

    if( *usLen == ( MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN ) )
    {
        usRegAddress = ( USHORT )( pucFrame[MB_PDU_FUNC_READ_ADDR_OFF] << 8 );
        usRegAddress |= ( USHORT )( pucFrame[MB_PDU_FUNC_READ_ADDR_OFF + 1] );
        usRegAddress++;

        usDiscreteCnt = ( USHORT )( pucFrame[MB_PDU_FUNC_READ_DISCCNT_OFF] << 8 );
        usDiscreteCnt |= ( USHORT )( pucFrame[MB_PDU_FUNC_READ_DISCCNT_OFF + 1] );

        /* Check if the number of registers to read is valid. If not
         * return Modbus illegal data value exception. 
         */
        if( ( usDiscreteCnt >= 1 ) &&
            ( usDiscreteCnt < MB_PDU_FUNC_READ_DISCCNT_MAX ) )
        {
            /* Set the current PDU data pointer to the beginning. */
            pucFrameCur = &pucFrame[MB_PDU_FUNC_OFF];
            *usLen = MB_PDU_FUNC_OFF;

            /* First byte contains the function code. */
            *pucFrameCur++ = MB_FUNC_READ_DISCRETE_INPUTS;
            *usLen += 1;

            /* Test if the quantity of coils is a multiple of 8. If not last
             * byte is only partially field with unused coils set to zero. */
            if( ( usDiscreteCnt & 0x0007 ) != 0 )
            {
                ucNBytes = ( UCHAR ) ( usDiscreteCnt / 8 + 1 );
            }
            else
            {
                ucNBytes = ( UCHAR ) ( usDiscreteCnt / 8 );
            }
            *pucFrameCur++ = ucNBytes;
            *usLen += 1;

            eRegStatus =
                MBRegDiscreteCB( pucFrameCur, usRegAddress, usDiscreteCnt );

            /* If an error occured convert it into a Modbus exception. */
            if( eRegStatus != MB_ENOERR )
            {
                eStatus = MBError2Exception( eRegStatus );
            }
            else
            {
                /* The response contains the function code, the starting address
                 * and the quantity of registers. We reuse the old values in the 
                 * buffer because they are still valid. */
                *usLen += ucNBytes;;
            }
        }
        else
        {
            eStatus = MB_EX_ILLEGAL_DATA_VALUE;
        }
    }
    else
    {
        /* Can't be a valid read coil register request because the length
         * is incorrect. */
        eStatus = MB_EX_ILLEGAL_DATA_VALUE;
    }
    return eStatus;
}
 