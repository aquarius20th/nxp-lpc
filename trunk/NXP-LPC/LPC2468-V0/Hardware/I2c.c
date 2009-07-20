/***********************************************Copyright (c)*********************************************
**                                Guangzou ZLG-MCU Development Co.,LTD.
**                                     
**                                       http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:			    IIC.c
** Last modified Date:      2007-10-15
** Last Version:		    1.0
** Descriptions:		    I2C����ʵ�֣������豸������������
**
**--------------------------------------------------------------------------------------------------------
** Created by:			    lixiaocheng
** Created date:		    2007-10-15
** Version:				    1.0
** Descriptions:		    ��
**
**--------------------------------------------------------------------------------------------------------
** Modified by:			    lixiaocheng
** Modified Date:		    2007-10-26
** Version:				    1.1
** Descriptions:		    ������I2C��UCOSII����ϵͳ�ļ���
**
*********************************************************************************************************/
#include <stdlib.h>
#include "includes.h"
#include "hd_init.h"
#include "I2cPrivate.h"
#include "I2c.h"                                                        
#include "I2cHook.h"


/*********************************************************************************************************
   �������I2C�����Ľṹ�壬�ж����������Ҫ��������ṹ��
*********************************************************************************************************/
static __I2C_INFO   __I2C0Data;
static __I2C_INFO   __I2C1Data;
static __I2C_INFO   __I2C2Data;

/*********************************************************************************************************
   �ǲ���ϵͳ�������ź���
*********************************************************************************************************/
OS_EVENT       *gpI2c0Sem;
OS_EVENT       *gpI2c1Sem;
OS_EVENT       *gpI2c2Sem;
OS_EVENT      **g_arrI2cTable[__IIC_MAX_NUM] = {&gpI2c0Sem, &gpI2c1Sem, &gpI2c2Sem};

/*********************************************************************************************************
   ����ʹ��ָ������������ṹ��ָ��,����Ը���������չ
*********************************************************************************************************/
const __PI2C_INFO   g_arrI2CInfoTab[__IIC_MAX_NUM] = {&__I2C0Data, &__I2C1Data, &__I2C2Data};

/*********************************************************************************************************
   ���涨����I2C0����ֵַ������ж��I2C���������ڸ�λ�������Ӧ�Ļ���ַ����
*********************************************************************************************************/
const INT32U        g_arrI2cBaseAddrTab[__IIC_MAX_NUM] = {I2C0_BASE_ADDR, I2C1_BASE_ADDR, I2C2_BASE_ADDR};

/*********************************************************************************************************
** Function name:           endBus
** Descriptions:            ���ߴ���������ߣ��ĺ�����__i2cISR����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __endBus (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
    
	pucAddrBase[__B_IIC_SET << uiOffBase] = 1 << 4;                     /*  ���߳�����������.STO      */
	pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x2C;                       /*  ���߳�������STA,SI,AA     */
	Parm->ucIICflag                       = I2C_ERR;
    __I2C_UNLOCK(*g_arrI2cTable[Parm->uiID]);                          /*  �ͷ��ź���                  */
}

/*********************************************************************************************************
** Function name:           AddrWrite
** Descriptions:            д��ӻ���ַ���ĺ�����__i2cISR����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __AddrWrite (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
	
    if (Parm->ucI2CSubAddrCtl == 1)
	{/*  ָ���ӵ�ַ��ʱ����д���ַ  */
		pucAddrBase[__B_IIC_DAT << uiOffBase] = (INT8U)((Parm->ucSLAddr)&0xFE);
	} 
	else
	{/*  ����ֱ�ӷ��ʹӻ���ַ        */
		pucAddrBase[__B_IIC_DAT << uiOffBase] = (Parm->ucSLAddr);
	}
	pucAddrBase[__B_IIC_CLR << uiOffBase]     = 0x28;                   /*  ����жϱ�־                */
}
/*********************************************************************************************************
** Function name:           dateWrite
** Descriptions:            д�����ݣ��ĺ�����__subAddrWrite����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __dateWrite (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
	
	if (Parm->usDataNum > 0) 
	{
		pucAddrBase[__B_IIC_DAT << uiOffBase] = *Parm->pucDataBuf++;
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;                   /*  ����SI��STA                 */
		Parm->usDataNum--;
	}
	else
	{
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x10;                   /*  �����ݷ��ͽ�������          */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
		Parm->ucIICflag = I2C_WRITE_END;						        /*  �������߽�����־            */
        __I2C_UNLOCK(*g_arrI2cTable[Parm->uiID]);                      /*  �ͷ��ź���                  */
	}
}
/*********************************************************************************************************
** Function name:           dateRead
** Descriptions:            ��ȡ���ݣ��ĺ�����__i2cISR����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __dateRead (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
	
	*(Parm->pucDataBuf++) = pucAddrBase[__B_IIC_DAT << uiOffBase];
	Parm->usDataNum--;
	
	switch ( Parm->usDataNum ) 
	{
	
	case 0:
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x10;                   /*  ��������                    */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
		Parm->ucIICflag = I2C_READ_END;                                 /*  ���ض�ȡ�ɹ�                */
        __I2C_UNLOCK(*g_arrI2cTable[Parm->uiID]);                       /*  �ͷ��ź���                  */
	break;
	
	case 1:                                                             /*  �������һ���ֽ�            */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x2C;                   /*  �ٽ��յ����ݷ��ط�Ӧ��λ    */
	break;
	
	default:
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;                   /*  ���յ����ݣ�����ACK         */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
	break;
	}
}
/*********************************************************************************************************
** Function name:           subAddrWrite
** Descriptions:            д��ӻ��ӵ�ַ��ַ���ĺ�����__i2cISR����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __subAddrWrite (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;

	if (Parm->ucI2CSubAddrCtl == __IIC_SUB_NONE)
	{/*  ���ӵ�ַ���ӵ�ַ�Ѵ���      */
	    __dateWrite( Parm );                                            /*  ֱ�ӷ�������                */
	                                                                
	} 
	else if (Parm->ucI2CSubAddrCtl == __IIC_SUB_R) 
	{                  /*  �����������ӵ�ַ            */
		if(Parm->ucSubAddrNum == 2) 
		{
			pucAddrBase[__B_IIC_DAT << uiOffBase] = (INT8U)((Parm->usSubAddr >> 8) & 0xff);	
			                                                            /*  ����һ���ֽڴӻ��ӵ�ַ      */
			                                                            /*  �ȷ��͸��ֽڵ�ַ            */
			                                                        
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
			Parm->ucSubAddrNum--;
		}
		else if (Parm->ucSubAddrNum == 1)
		{
			pucAddrBase[__B_IIC_DAT << uiOffBase] = (INT8U)((Parm->usSubAddr) & 0xff);
			                                                            /*  ���͵��ֽڵ�ַ���ֽڵ�ַ  */
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
			Parm->ucSubAddrNum--;
		} 
		else if (Parm->ucSubAddrNum == 0)
		{  /*  �������ӵ�ַ����������      */	
			pucAddrBase[__B_IIC_SET << uiOffBase] = 0x20;
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x18;
			Parm->ucI2CSubAddrCtl = __IIC_SUB_NONE;
		}
	} 
	else if (Parm->ucI2CSubAddrCtl == __IIC_SUB_W)
	{    /*  д���������ӵ�ַ            */
		if(Parm->ucSubAddrNum == 2) 
		{
			pucAddrBase[__B_IIC_DAT << uiOffBase] = (INT8U)((Parm->usSubAddr >> 8) & 0xff);	
			                                                            /*  ����һ���ֽڴӻ��ӵ�ַ      */
			                                                            /*  �ȷ��͸��ֽڵ�ַ            */
			                                                        
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
			Parm->ucSubAddrNum--;
		}
		else if ( Parm->ucSubAddrNum == 1 )
		{
			pucAddrBase[__B_IIC_DAT << uiOffBase] = (INT8U)(Parm->usSubAddr & 0xff);
			                                                            /*  ���͵��ֽڵ�ַ���ֽڵ�ַ  */
			                                                        
			pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;
			Parm->ucI2CSubAddrCtl                 = __IIC_SUB_NONE;     /*  �ӵ�ַ�Ѵ���                */
			Parm->ucSubAddrNum--;
		} 
		else if (Parm->ucSubAddrNum == 0)
		{   /*  д�������ӵ�ַ              */
		     __dateWrite( Parm );                                       /*  ֱ�ӷ�������                */
		     Parm->ucI2CSubAddrCtl                = __IIC_SUB_NONE;     /*  �ӵ�ַ�Ѵ���                */
		}
	}
}
/*********************************************************************************************************
** Function name:           hostRecvModeEntry
** Descriptions:            ����������ģʽ���ĺ�����__i2cISR����
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __hostRecvModeEntry (__PI2C_INFO Parm)
{
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
	
	if(Parm->usDataNum <= 1) 
	{
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x2c;                   /*  �����ֽ����ڵ���1��         */
		                                                                /*  ���յ��¸��ֽ�ʱ���ط�ACK   */
		                                                            
	}
	else 
	{
		pucAddrBase[__B_IIC_SET << uiOffBase] = 0x04;	                /*  �������ֽڶ���1��ʱ,��λAA  */
		pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x28;                   /*  ���յ��¸��ֽ�ʱ����ACK     */
	}
}
/*********************************************************************************************************
** Function name:           ISR_I2C
** Descriptions:            �жϷ������ײ���ã����жϷ�����û����ɴӻ�ģʽ
** Input parameters:        Parm--I2C�豸�������ṹ��ָ��
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __i2cISR (__PI2C_INFO Parm)
{
	            INT8U				ucSta;
	            INT32U				uiOffBase;
	volatile 	INT8U 	           *pucAddrBase;
	
	pucAddrBase	= Parm->pucAddrBase;
	uiOffBase   = Parm->uiOffBase;
	
	ucSta = pucAddrBase[__B_IIC_STAT << uiOffBase];                     /*  ��ȡI2C״̬��               */
	switch(ucSta & 0xF8) 
	{

	case __SEND_START:                                                  /*  �ѷ�����ʼ����,����д����   */
	case __SEND_RESTART:                                                /*  �����������ߺ󣬷��ʹӻ���ַ*/
        __AddrWrite( Parm );                                            /*  д��������ַ                */
		break;
		
	case __SEND_SLA_W_ACK:												/*  �ѷ���SLA+W���Ѿ�����Ӧ��    */
	case __SEND_DATA_ACK:                                               /*  �������ݣ��ѽ���Ӧ��         */
	                                                                    /*  �����������ʹ�����溯��     */
        __subAddrWrite( Parm );                                         /*  I2Cд���ݺ͵�ַ��һ��        */
		break;
		
	case __SEND_SLA_W_NOACK:                                            /*  ����SLA_W,�յ���Ӧ��         */
	case __SEND_DATA_NOACK:                                             /*  �������ݣ��յ���Ӧ��         */
	case __LOSS_BUS:                                                    /*  ��ʧ�ٲ�                     */
	case __SEND_SLA_R_NOACK:                                            /*  ����SLA+R ���շ�Ӧ��         */
	                                                                    /*  �������������Ҫ��������     */
	    __endBus( Parm );                                               /*  ��������                     */
		break;
		
	case __SEND_SLA_R_ACK:                                              /*  ����SLA+R,�յ�ACK            */
		__hostRecvModeEntry( Parm );                                    /*  ����������ģʽ               */
		break;
		
	case __RECV_DATA_ACK:                                               /*  ���������ݣ�����Ӧ��λ       */
	case __RECV_DATA_NOACK:                                             /*  �����������ֽ�,���ط�Ӧ��λ  */
	                                                                    /*  ������������������ö�����   */
		__dateRead( Parm );
		break;
		
	default:                                                            /*  ����״̬                     */
        __endBus( Parm );                                               /*  ��������                     */
		break;
	}
}
/*********************************************************************************************************
** Function name:           I2C0IRQ
** Descriptions:            �⺯��Ĭ�ϵ��жϷ�����������I2C�жϴ���,�ú����ҽ��˹��Ӻ����ɴ����û�����
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void i2c0IRQ ( void )
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
    __OS_ENTER_CIRCT();
	__i2cISR(g_arrI2CInfoTab[0]);
	i2c0Hook();
	VICVectAddr = 0x00;                                                 /*  ���VIC�ж�                 */
    __OS_EXIT_CIRCT();
}

/*********************************************************************************************************
** Function name:           I2C1IRQ
** Descriptions:            �⺯��Ĭ�ϵ��жϷ�����������I2C�жϴ���,�ú����ҽ��˹��Ӻ����ɴ����û�����
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void i2c1IRQ ( void )
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
    __OS_ENTER_CIRCT();
	__i2cISR(g_arrI2CInfoTab[1]);
	i2c1Hook();
	VICVectAddr = 0x00;                                                 /*  ���VIC�ж�                 */
    __OS_EXIT_CIRCT();
}

/*********************************************************************************************************
** Function name:           I2C2IRQ
** Descriptions:            �⺯��Ĭ�ϵ��жϷ�����������I2C�жϴ���,�ú����ҽ��˹��Ӻ����ɴ����û�����
** Input parameters:        NONE
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
void i2c2IRQ ( void )
{
#if OS_CRITICAL_METHOD == 3                                
	OS_CPU_SR  cpu_sr;
#endif
    __OS_ENTER_CIRCT();
	__i2cISR(g_arrI2CInfoTab[2]);
	i2c2Hook();
	VICVectAddr = 0x00;                                                 /*  ���VIC�ж�                 */
    __OS_EXIT_CIRCT();
}

/*********************************************************************************************************
** Function name:           I2CInit
** Descriptions:            I2c��ʼ������(���ַ�����)���ú�����Ҫ����װһ��ģ�������ò������ٶȳ���400K
**                          �����ñ�׼�ٶ�100K
** Input parameters:        ID              �������豸��
**                          Speed           I2CͨѶ�ٶ�
**                          Rsv             ��������
** Output parameters:       NONE
** Returned value:          PIN_ERR         �ܽ����ô���
**                          OPERATE_FAIL    ��ʼ��ʧ�ܣ�ID����
**                          OPERATE_SUCCESS ��ʼ���ɹ�
*********************************************************************************************************/
INT32U I2CInit ( INT32U ID, INT32U Speed,  void  *Rsv )
{
	volatile INT8U *pucAddrBase;
	volatile INT32U uiOffBase;
	
	Rsv = Rsv;                                                          /*  ��ֹ���뱨��                */
	/*  ��������,�ж� */
	if ( ID >= __IIC_MAX_NUM ) 
	{
	    return OPERATE_FAIL;
	}
	
	if ( Speed > 400000 )
	{
	    Speed = 100000;
	}
	
	/*  �����ź���������ϵͳ���� */
	*g_arrI2cTable[ID] = OSSemCreate(1);
	if(*g_arrI2cTable[ID] == (void *)NULL)
	{ /*  ��������ź���ʧ�ܷ��ش���  */
		return OPERATE_FAIL;
	}
 	 
	/*   ��ʼ��һЩ����  */
	g_arrI2CInfoTab[ID]->uiID          = ID;
	g_arrI2CInfoTab[ID]->pucAddrBase   = (INT8U*)g_arrI2cBaseAddrTab[ID];
	g_arrI2CInfoTab[ID]->uiOffBase     = 2;
	g_arrI2CInfoTab[ID]->ucIICflag     = I2C_IDLE;                     /*  ��ʶ���������ڿ���          */
	g_arrI2CInfoTab[ID]->ucSlave       = __IIC_MASTER;                 /*  ��ʶ������Ϊ����            */
	g_arrI2CInfoTab[ID]->usDataNum     = 0;
	
	pucAddrBase = g_arrI2CInfoTab[ID]->pucAddrBase;	                /*  ��ȡָ�����                */
	uiOffBase   = g_arrI2CInfoTab[ID]->uiOffBase;
	
	*(INT16U*)(pucAddrBase+(__B_IIC_SCLH << uiOffBase) ) = (INT16U)((Fpclk / Speed + 1) / 2);
	                                                                    /*  ����ʱ�Ӹߵ�ƽʱ��          */
	                                                                    
	*(INT16U*)(pucAddrBase+(__B_IIC_SCLL << uiOffBase) ) = (INT16U)((Fpclk / Speed) / 2);	
	                                                                    /*  ����ʱ�ӵ͵�ƽʱ��          */
                                                                    
    pucAddrBase[__B_IIC_CLR << uiOffBase]  = 0x2C;
    pucAddrBase[__B_IIC_SET << uiOffBase]  = 0x40;                      /*  ������ģʽ                  */
    
    return OPERATE_SUCCESS;
} 
/*********************************************************************************************************
** Function name:           i2cSetMode
** Descriptions:            ����I2C�ٶȣ���Ҫ���ڳ�ʼ�����û���ı�I2C��������ʱ�ú���ֻ���������ٶȡ�
**                          ���д���ٶȴ���400K�������ó�ϵͳĬ�ϵ�100K
** Input parameters:        ID   �������豸��,����ID=0,��ʾ�������豸��I2C0
**				            arg	 ���ò������ַ������ú�����ʱֻ����I2C�ٶ�
**				 	             ����Ҫ���õ��ٶ�Ϊ200K�����ַ���Ϊ"Speed=200000"
**				            Rsv	 ��������
** Output parameters:       NONE
** Returned value:          OPERATE_FAIL    ����ʧ��
**                          OPERATE_SUCCESS ���óɹ�
*********************************************************************************************************/
INT32U i2cSetMode (INT32U   ID,   INT32U Speed,  void   *Rsv)
{
	volatile INT8U     *pucAddrBase;
	volatile INT32U     uiOffBase;

	Rsv         = Rsv;
	pucAddrBase = g_arrI2CInfoTab[ID]->pucAddrBase;
	uiOffBase   = g_arrI2CInfoTab[ID]->uiOffBase;

	if (ID < __IIC_MAX_NUM) 
	{
		/*  �������� */
		if (Speed > 400000)
		{
		    Speed = 100000;
		}
		
    	__I2C_LOCK(*g_arrI2cTable[ID]);                                /*  ����I2C��Դ                 */
    	
		                                                                /*  �����ٶ�                    */
		*(INT16U*)(pucAddrBase + (__B_IIC_SCLH << uiOffBase)) = (INT16U)((Fpclk / Speed + 1) / 2);		
		*(INT16U*)(pucAddrBase + (__B_IIC_SCLL << uiOffBase)) = (INT16U)((Fpclk / Speed) / 2);
				
        __I2C_UNLOCK(*g_arrI2cTable[ID]);                              /*  �ͷ�I2C��Դ                 */  
            	
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

/*********************************************************************************************************
** Function name:           __i2cStart
** Descriptions:            ����I2C����
** Input parameters:        ID   �������豸��,����ID=0,��ʾ�������豸��I2C0
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
static void __i2cStart (INT32U ID)
{
	volatile INT8U     *pucAddrBase;
	volatile INT32U     uiOffBase;
	
	if (g_arrI2CInfoTab[ID]->ucSlave == __IIC_SLAVER) 
	{
	
        __I2C_UNLOCK(*g_arrI2cTable[ID]);                              /*  �ͷ�I2C��Դ                 */    	
	    return;                                                         /*  ����Ǵӻ��Ͳ���������      */
	 }
	 
	pucAddrBase = g_arrI2CInfoTab[ID]->pucAddrBase;
	uiOffBase   = g_arrI2CInfoTab[ID]->uiOffBase;
	
	g_arrI2CInfoTab[ID]->ucIICflag = I2C_BUSY;
	pucAddrBase[__B_IIC_CLR << uiOffBase] = 0x2C;                       /*  ��������,����Ϊ����         */
	pucAddrBase[__B_IIC_SET << uiOffBase] = 0x60;
}

/*********************************************************************************************************
** Function name:           i2cRead
** Descriptions:            I2c�����ݺ���
** Input parameters:        ID			   : I2C�豸��ʶ
**                          Addr		   : �ӻ���ַ
**                          Ret 		   : ָ�򷵻����ݴ洢λ�õ�ָ��	
**                          Sub_Addr	   : �ӻ��ڲ��ӵ�ַ
**                          Sub_Addr_NByte : �ӻ��ڲ��ӵ�ַ���� ---- 1: ���ֽڵ�ַ; 2: ˫�ֽڵ�ַ; 
**                          ReadNbyte      : ��Ҫ�����ݸ���
** Output parameters:       NONE
** Returned value:          �����ɹ�       : OPERATE_SUCCESS
**                          ����ʧ��       : OPERATE_FAIL
*********************************************************************************************************/
INT32U i2cRead (INT32U ID,
               INT8U  Addr, 
               INT8U *Ret, 
               INT16U Sub_Addr, 
               INT8U  Sub_Addr_NByte, 
               INT16U ReadNbyte)
{
	if (ReadNbyte == 0) 
	{
	    return OPERATE_FAIL;					                        /*  �������ȡ0���ֽ�           */
	}
		
	if (ID < __IIC_MAX_NUM) 
	{
         __I2C_LOCK(*g_arrI2cTable[ID]);                               /*  �����ź���                  */	
		if (g_arrI2CInfoTab[ID]->ucIICflag == I2C_BUSY)
		{		
		    __I2C_UNLOCK(*g_arrI2cTable[ID]);                          /*  �ͷ�I2C��Դ                 */
		    return OPERATE_FAIL;                                        /*  æ���ͷ��ش���              */
		}
		g_arrI2CInfoTab[ID]->ucSLAddr          = (INT8U)(Addr | 0x01); /*  �ӻ���ַ                    */
		g_arrI2CInfoTab[ID]->usSubAddr         = Sub_Addr;             /*  �ӻ���ַ�ӵ�ַ              */
		g_arrI2CInfoTab[ID]->ucSubAddrNum      = Sub_Addr_NByte;       /*  �ӻ��ӵ�ַ����              */
		g_arrI2CInfoTab[ID]->ucI2CSubAddrCtl   = __IIC_SUB_R;          /*  ����Ϊ������                */
		g_arrI2CInfoTab[ID]->pucDataBuf        = Ret;                  /*  �������ݵĻ�����            */
		g_arrI2CInfoTab[ID]->usDataNum         = ReadNbyte;            /*  Ҫ��ȡ�����ݸ���            */
		__i2cStart(ID);
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}

/*********************************************************************************************************
** Function name:           i2cWrite
** Descriptions:            I2cд���ݺ���
** Input parameters:        ID			   : I2C�豸��ʶ
**                          Addr		   : �ӻ���ַ
**                          Buf 		   : ָ��д�����ݴ洢λ�õ�ָ��	
**                          Sub_Addr	   : �ӻ��ڲ��ӵ�ַ
**                          Sub_Addr_NByte : �ӻ��ڲ��ӵ�ַ���� 
**                                              0: ���ڲ��ӵ�ַ��
**                                              1: ���ֽڵ�ַ; 
**                                              2: ˫�ֽڵ�ַ; 
**                          Nbyte          : д�����ݳ���
** Output parameters:       NONE
** Returned value:          �����ɹ�       : OPERATE_SUCCESS
**                          ����ʧ��       : OPERATE_FAIL
*********************************************************************************************************/
INT32U i2cWrite (INT32U  ID,
                INT8U   Addr, 
                INT8U  *Buf, 
                INT16U  Sub_Addr, 
                INT8U   Sub_Addr_NByte, 
                INT16U  Nbyte)
{
	if (Nbyte == 0) 
	{
	    return OPERATE_FAIL;					                        /*  ������д��0���ֽ�           */
	}
     	
	if (ID < __IIC_MAX_NUM)
	{
         __I2C_LOCK(*g_arrI2cTable[ID]);                               /*  �����ź���                  */
		if (g_arrI2CInfoTab[ID]->ucIICflag == I2C_BUSY) 
		{	
		     __I2C_UNLOCK(*g_arrI2cTable[ID]);                         /*  �ͷ�I2C��Դ                 */
		    return OPERATE_FAIL;
		}
    	
		g_arrI2CInfoTab[ID]->ucSLAddr        = (INT8U)(Addr & 0xfe);   /*  �ӻ���ַ                    */
		g_arrI2CInfoTab[ID]->usSubAddr       = Sub_Addr;               /*  �ӻ���ַ�ӵ�ַ              */
		g_arrI2CInfoTab[ID]->ucSubAddrNum    = Sub_Addr_NByte;         /*  �ӻ��ӵ�ַ����              */
		g_arrI2CInfoTab[ID]->ucI2CSubAddrCtl = __IIC_SUB_W;            /*  ����Ϊд����                */
		g_arrI2CInfoTab[ID]->pucDataBuf      = Buf;					/*  �������ݵĻ�����            */
		g_arrI2CInfoTab[ID]->usDataNum       = Nbyte;                  /*  Ҫд������ݸ���            */
		__i2cStart(ID);
		return OPERATE_SUCCESS;
	}
	return OPERATE_FAIL;
}
/*********************************************************************************************************
** Function name:           i2cGetFlag
** Descriptions:            ����I2C������ǰ״̬���ͨ��ʧ�ܣ����ʾ�ϴ����߲���ʧ�ܣ�
**                          ��������������Ȼ�ǿ��е�,���б�ʾ�ϴ�ͨ�ųɹ���û�н��й�ͨ��
**                          ���������ǿ��еģ�������������ͨ��
** Input parameters:        ID             : I2C�豸��ʶ
** Output parameters:       NONE
** Returned value:          �����ɹ�       : ���ص�ǰI2C����״̬
**                                           I2C_IDLE�� ��ʾ���߿���
**                                           I2C_WRITE_END����ʾд�����ɹ�
**                                           I2C_READ_END����ʾ�������ɹ�
**                                           I2C_ERR����ʾ���߲���ʧ��
**                                           I2C_BUSY����ʾ�������ڹ�����
**                          ����ʧ��       : OPERATE_FAIL
*********************************************************************************************************/
INT32U i2cGetFlag (INT8U ID)
{   
	if (ID < __IIC_MAX_NUM)
	{    
	    __I2C_LOCK(*g_arrI2cTable[ID]);                                /*  ��������Դ�����߲����Ƿ����*/ 
        __I2C_UNLOCK(*g_arrI2cTable[ID]);                              /*  �ͷ�I2C��Դ                 */    	
	    
		return g_arrI2CInfoTab[ID]->ucIICflag;
	}
	return OPERATE_FAIL;
}
/*********************************************************************************************************
** Function name:           i2cGetRemainBytes
** Descriptions:            ����I2C�������ж����ֽ�����û�з������
** Input parameters:        ID             : I2C�豸��ʶ
** Output parameters:       NONE
** Returned value:          �����ɹ�       : ���ص�ǰ��ʣû�з��͵��ֽ���
**                          ����ʧ��       : OPERATE_FAIL
*********************************************************************************************************/
INT32U i2cGetRemainBytes(INT8U ID)
{
	if (ID < __IIC_MAX_NUM) 
	{
		return g_arrI2CInfoTab[ID]->usDataNum;
	}
	return OPERATE_FAIL;
}
/*********************************************************************************************************
   END FILE
*********************************************************************************************************/

