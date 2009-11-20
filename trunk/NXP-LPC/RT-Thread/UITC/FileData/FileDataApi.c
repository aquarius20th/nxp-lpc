/****************************************Copyright (c)**************************************************
**                                       FLASH�ļ������ӿڵķ�װ
**                                      �ļ��ļ��ر�������˳����أ��ȼ���FCB��Ȼ����BIN SRC
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
#include "applib.h"
#include "IAP.h"

#include "FileDataDef.h"
#include "FileDataApi.h"
#include "Func.h"

//
 
#define  FCB_BLOCK_SIZE  4*1024  //0X16
#define  BIN_BLOCK_SIZE  4*1024  //0X17
#define  SRC_BLOCK_SIZE  4*1024  //0X18 

//FLASH�ĵ�ַ
 
#define	 FCB_BLOCK_DESTADDR 	0x00078000      //����0X16 
#define  BIN_BLOCK_DESTADDR 	0x00079000		//0X17
#define  SRC_BLOCK_DESTADDR 	0x0007A000		//0X18
 
//�洢������ָ��
static INT32U FcbBuffPtr = 0;
static INT32U BinBuffPtr = 0;
static INT32U SrcBuffPtr = 0;

//���ڴ洢FCB���ƿ�� �ڴ���ʱ��
__align(4) static INT8U FCB_BLOCK[FCB_BLOCK_SIZE];	
//BIN DATA
__align(4) 	static INT8U BIN_BLOCK[BIN_BLOCK_SIZE];	
//SRC DATA
__align(4) 	static INT8U SRC_BLOCK[SRC_BLOCK_SIZE];	

static FCB *g_spTmpFcb = NULL;

/*********************************************************************************************************
** ��������: WriteFcb
** ��������: WriteFcb
**
** ���������� д������Ϣ���ƿ�
**
** �䡡��:  FCB * pFcb
**          
** �䡡��:  INT16U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��6��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT16U WriteFcb( FCB *pFcb )
{

	return sizeof(FCB);
}

INT16U WriteBinData( BIN_DATA  *pBinDat, INT16U nLen)
{
	if (pBinDat == NULL || nLen == 0 || nLen >= BIN_BLOCK_SIZE)
		return 0;


	return 0;		
}

INT32U WriteSrcData( INT8U *pBuf,INT32U nLen)
{

	return 0;
}


INT8U  ErasureFlash( )
{
	return TRUE;
}

/*********************************************************************************************************
** ��������: ReadSrcData
** ��������: ReadSrcData
**
** ���������� 
**
** �䡡��:  INT32U nLen
** �䡡��:  INT16U wSrcCrc
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: ע�⣬�������̫�������ܵ���Ҫ��������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U ReadSrcData(INT32U nLen ,INT16U wSrcCrc)
{
	INT16U wCrc = 0;
	if (nLen>SRC_BLOCK_SIZE || wSrcCrc == 0)
		return FALSE;

	//��flash�ж�ȡ���ݵ��ڴ���
	FLASH_ReadByte(SRC_BLOCK_DESTADDR,SRC_BLOCK, nLen );
	//����һ��CRCֵ
	wCrc = GetCRC16(SRC_BLOCK,nLen);
	if (wCrc == wSrcCrc)	
		return TRUE;	

	return FALSE;
}
/*********************************************************************************************************
** ��������: ReadBinData
** ��������: ReadBinData
**
** ���������� ��flash�ж�ȡ������Ϣ
**
** �䡡��:  INT32U nLen ��Ҫ��ȡ�ĳ���
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע:  ע�⣬�������̫�������ܵ���Ҫ��������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U ReadBinData(INT32U nLen ,INT16U wBinCrc)
{
	INT16U wCrc = 0;
	if (nLen>BIN_BLOCK_SIZE || wBinCrc == 0)
		return FALSE;
	
	//��flash�ж�ȡ���ݵ��ڴ���
	FLASH_ReadByte(BIN_BLOCK_DESTADDR,BIN_BLOCK, nLen );
	//����һ��CRCֵ
	wCrc = GetCRC16(BIN_BLOCK,nLen);
	if (wCrc == wBinCrc)	
		return TRUE;	

	return FALSE;
}

extern INT8U  ReadSrcDataBuf(INT8U *pBuff, INT32U nFileOffset,INT8U nLen)
{
	if (pBuff == NULL)
		return FALSE;
	if (nFileOffset >= SRC_BLOCK_SIZE)
		return FALSE;
	if (nLen<=0)
		return FALSE;
	//��flash�ж�ȡ���ݵ��ڴ���
	return	FLASH_ReadByte(SRC_BLOCK_DESTADDR+nFileOffset,pBuff, nLen );
}


extern INT8U  ReadBinDataBuf(INT8U *pBuff, INT32U nFileOffset,INT8U nLen)
{
	if (pBuff == NULL)
		return FALSE;
	if (nFileOffset >= BIN_BLOCK_SIZE)
		return FALSE;
	if (nLen<=0)
		return FALSE;
	//��flash�ж�ȡ���ݵ��ڴ���
	return	FLASH_ReadByte(BIN_BLOCK_DESTADDR+nFileOffset,pBuff, nLen );
}

/*********************************************************************************************************
** ��������: ReadFcb
** ��������: ReadFcb
**
** ���������� ��flash�ж�ȡ���ݣ�
**
**          
** �䡡��:  INT16U ���������Ч�򷵻س��ȣ������Ч���򷵻�0
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT16U CheckFcb(FCB * pTmpFcb, INT8U *err )
{
	if(pTmpFcb == NULL)
	{
		return FALSE;
	}
	//����Ч�Լ��
	if (pTmpFcb->wHeadFlag != FCB_FLAG)
	{
		*err = FLASH_API_NO_FCB;
		return FALSE;
	}

	if ( pTmpFcb->nBinLen == 0  || pTmpFcb->nBinLen >BIN_BLOCK_SIZE )
	{
		*err = FLASH_API_NO_BINDATA;
		return FALSE;
	}

	if ( pTmpFcb->wBinCrc == 0)
	{
		*err = FLASH_API_BIN_CRC_ERR;
		return FALSE;
	}

	return sizeof(FCB);
}
/*********************************************************************************************************
** ��������: LoadFcb
** ��������: LoadFcb
**
** ����������  ��flash�ж�ȡ���ݣ���Ӧ��������Ϣ
**
** �䡡��:  FCB * pFcb
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: ϵͳ��ʼ��ʱ���øú���
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT16U LoadFcb(FCB *pFcb,INT8U *err)
{
	INT16U nRet = 0;

	FLASH_ReadByte(FCB_BLOCK_DESTADDR,FCB_BLOCK,FCB_BLOCK_SIZE );
	g_spTmpFcb = (FCB *) FCB_BLOCK ;

	nRet = CheckFcb( g_spTmpFcb,err );

	if (nRet&& pFcb!= NULL)
	{
		//�����Ч�������ص����ݴ�ŵ�RAM�Ķ�Ӧ�ṹ��
		memcpy(pFcb,g_spTmpFcb,sizeof(FCB));
		return sizeof(FCB);
	}
	return FALSE;
}
/*********************************************************************************************************
** ��������: GetFcbBuff
** ��������: GetFcbBuff
**
** ���������� ��ͨ��ģ���е��øú����������ϴ�����
**
** �䡡��:  INT8U * pBuff
** �䡡��:  INT16U nLen
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U  GetFcbBuff(INT8U **ppBuff,INT8U *pLen )
{
	INT8U err = 0;
	INT16U nRet = 0;
	 
	//��flash�ж�ȡ���ݵ��ڴ���
//	FLASH_ReadByte(FCB_BLOCK_DESTADDR,FCB_BLOCK,sizeof(FCB) );
//	g_spTmpFcb = (FCB *) FCB_BLOCK ;

	nRet = CheckFcb( g_spTmpFcb,&err );

	*ppBuff = &FCB_BLOCK[0];
//	*ppBuff =  FCB_BLOCK ;

	*pLen = sizeof(FCB);
	return nRet;
	 
}
/*********************************************************************************************************
** ��������: GetBinDataBuff
** ��������: GetBinDataBuff
**
** ���������� 
**
** �䡡��:  INT8U * pBuff
** �䡡��:  INT32U nLen
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��18��
** ��  ע:  BINDATA���ļ����ȣ�������ram�е�fcb������������flash�����������,
            �ڵ��ô˺���ǰ������� LoadFcb ��flash���ؿ�����Ϣ
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern INT8U  GetBinDataBuff(INT8U **ppBuff, INT32U *pLen )
{
	INT8U bRet = FALSE;
	INT16U nRet = 0;
	INT8U err = 0;

	//��ȡBIN����ǰ����Ҫ��ȡһ�¿��ƿ�
	nRet = CheckFcb( g_spTmpFcb,&err );
	if (nRet && g_spTmpFcb->nBinLen && g_spTmpFcb->nBinLen<= BIN_BLOCK_SIZE &&g_spTmpFcb->wBinCrc)
	{
		bRet = ReadBinData(g_spTmpFcb->nBinLen,g_spTmpFcb->wBinCrc);
		if (bRet)
		{
			*ppBuff = &BIN_BLOCK[0];
			*pLen = g_spTmpFcb->nBinLen;
			return TRUE;
		}
	}
	return FALSE;
}

extern INT8U  GetSrcDataBuff(INT8U **ppBuff, INT32U *pLen)
{
	INT8U bRet = FALSE;
	INT16U nRet = 0;
	INT8U err = 0;

	//��ȡBIN����ǰ����Ҫ��ȡһ�¿��ƿ�
	nRet = CheckFcb( g_spTmpFcb,&err );
	if (nRet && g_spTmpFcb->nCfgFileLen && g_spTmpFcb->nCfgFileLen<= SRC_BLOCK_SIZE &&g_spTmpFcb->wConfCrc)
	{
		bRet = ReadSrcData(g_spTmpFcb->nCfgFileLen,g_spTmpFcb->wConfCrc);
		if (bRet)
		{
			*ppBuff = SRC_BLOCK;
			*pLen = g_spTmpFcb->nCfgFileLen;
			return TRUE;
		}
	}
	return FALSE;
}
/*********************************************************************************************************
** ��������: LoadFlashData
** ��������: LoadFlashData
**
** ���������� ��FLASH�������ݵ�ram��
**
**          
** �䡡��:  extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��11��4��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U LoadFlashData( )
{
	//��flash�ж�ȡ���ݵ��ڴ���
	FLASH_ReadByte(FCB_BLOCK_DESTADDR,FCB_BLOCK,FCB_BLOCK_SIZE );
	FLASH_ReadByte(BIN_BLOCK_DESTADDR,BIN_BLOCK,BIN_BLOCK_SIZE );
	FLASH_ReadByte(SRC_BLOCK_DESTADDR,SRC_BLOCK,SRC_BLOCK_SIZE );

	g_spTmpFcb = (FCB *) FCB_BLOCK ;

	return TRUE;
}

/*********************************************************************************************************
** ��������: SelfCheckRam
** ��������: SelfCheckRam
**
** ���������� �ڴ��Լ�
**
** �䡡��:  void
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��24��
** ��  ע:   �ڴ��Լ� ����ڴ�������Ƭ�ڣ�Ƭ�⣿
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע:   
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U SelfCheckRam(void) 		 
{
	INT32U i = 0;
	INT8U chk = 0;

	//��ʼ�Լ�
	for (i=0;i<FCB_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
			case 0:
				chk=0xAA;
				break;
			case 1:
				chk=0x55;
				break;
			case 2:
				chk=0xFF;
				break;
			case 3:
				chk=0x00;
				break;
		}
		//д�ڴ�
		FCB_BLOCK[i] = chk;		
	}	
	for (i=0;i<BIN_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
		case 0:
			chk=0xAA;
			break;
		case 1:
			chk=0x55;
			break;
		case 2:
			chk=0xFF;
			break;
		case 3:
			chk=0x00;
			break;
		}
		//д�ڴ�
		BIN_BLOCK[i] = chk;		
	}
	for (i=0;i<SRC_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
		case 0:
			chk=0xAA;
			break;
		case 1:
			chk=0x55;
			break;
		case 2:
			chk=0xFF;
			break;
		case 3:
			chk=0x00;
			break;
		}
		//д�ڴ�
		SRC_BLOCK[i] = chk;		
	}
	for (i=0;i<FCB_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
		case 0:
			chk=0xAA;
			break;
		case 1:
			chk=0x55;
			break;
		case 2:
			chk=0xFF;
			break;
		case 3:
			chk=0x00;
			break;
		}
		//���ڴ棬У��
		if( FCB_BLOCK[i] !=chk)
		{
			return FALSE;
		}
	}	
	for (i=0;i<BIN_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
		case 0:
			chk=0xAA;
			break;
		case 1:
			chk=0x55;
			break;
		case 2:
			chk=0xFF;
			break;
		case 3:
			chk=0x00;
			break;
		}
		//���ڴ棬У��
		if( BIN_BLOCK[i] !=chk)
		{
			return FALSE;
		}
	}	
	for (i=0;i<SRC_BLOCK_SIZE;i++) 
	{
		switch(i%4) 
		{
		case 0:
			chk=0xAA;
			break;
		case 1:
			chk=0x55;
			break;
		case 2:
			chk=0xFF;
			break;
		case 3:
			chk=0x00;
			break;
		}
		//���ڴ棬У��
		if( SRC_BLOCK[i] !=chk)
		{
			return FALSE;
		}
	}
	return TRUE;
}
/*********************************************************************************************************
** ��������: PutFcbData
** ��������: PutFcbData
**
** ���������� ����ʱ������������
**
** �䡡��:  INT8U * pBuff
** �䡡��:  INT8U nLen
** �䡡��:  INT16U nPacketIdx ��1��ʼ
**          
** �䡡��:  extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��24��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U PutFcbData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx )
{
	if (nLen == 0 || pBuff == NULL || nPacketIdx == 0 || nPacketIdx > 256)
		return FALSE;

	if (nPacketIdx == 1)
	{//�յ���һ������ʱ�򣬸���ָ��
		FcbBuffPtr = 0;	
		BinBuffPtr = 0;
		SrcBuffPtr = 0;	
	}
	if (FcbBuffPtr+nLen >= FCB_BLOCK_SIZE)
	{//�������
		FcbBuffPtr = 0;	
		return FALSE;
	}

	memcpy( &FCB_BLOCK[FcbBuffPtr],pBuff,nLen);
	FcbBuffPtr += nLen;

	return TRUE;
}

INT8U PutBinData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx )
{
	if (nLen == 0 || pBuff == NULL || nPacketIdx == 0 || nPacketIdx > 512)
		return FALSE;

	if (BinBuffPtr+nLen >= BIN_BLOCK_SIZE)
	{//�������
		BinBuffPtr = 0;	
		return FALSE;
	}

	if (nPacketIdx == 1)
	{//��һ����
		BinBuffPtr = 0;
	}

	memcpy( &BIN_BLOCK[BinBuffPtr],pBuff,nLen);
	BinBuffPtr += nLen;

	return TRUE;
}

INT8U PutSrcData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx )
{
	if (nLen == 0 || pBuff == NULL || nPacketIdx == 0 || nPacketIdx > 512)
		return FALSE;

	if (SrcBuffPtr+nLen >= SRC_BLOCK_SIZE)
	{//�������
		SrcBuffPtr = 0;	
		return FALSE;
	}

	if (nPacketIdx == 1)
	{//��һ����
		SrcBuffPtr = 0;
	}

	memcpy( &SRC_BLOCK[SrcBuffPtr],pBuff,nLen);
	SrcBuffPtr += nLen;

	return TRUE;
}
/*********************************************************************************************************
** ��������: SaveData
** ��������: SaveData
**
** ���������� ��RAM�е���Ϣ�洢��FLASH��
**
**          
** �䡡��:  extern INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��24��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U SaveData( INT8U *err )
{                              
	OS_CPU_SR  cpu_sr;

	FCB *pTmpFcb = NULL;
	INT16U chkcrc = 0;
	INT32U i = 0;
	INT8U ByteValue = 0;
	INT8U nSector = 0;
	//0.���RAM��������ݳ�����FCB�Ƿ�һ��
	pTmpFcb = (FCB *)FCB_BLOCK;
	if (pTmpFcb->wHeadFlag != FCB_FLAG)
	{
		*err = FLASH_API_NO_FCB;
		return FALSE;
	}
	if (pTmpFcb->nBinLen == 0  || pTmpFcb->nBinLen >BIN_BLOCK_SIZE )
	{//BIN �����Ǳ������ص�
		*err = FLASH_API_NO_BINDATA;
		return FALSE;
	}

	if (pTmpFcb->nCfgFileLen > SRC_BLOCK_SIZE)
	{
		*err = FLASH_API_SRC_LEN_ERR;
		return FALSE;
	}
	if (pTmpFcb->nBinLen != BinBuffPtr)
	{//������Ȳ�һ��
		*err = FLASH_API_BIN_LEN_ERR;
		return FALSE;
	}
	if (pTmpFcb->nCfgFileLen && pTmpFcb->nCfgFileLen != SrcBuffPtr)
	{
		*err = FLASH_API_SRC_LEN_ERR;
		return FALSE;
	}

	//1.���RAM�е�����CRC�Ƿ���ȷ
	chkcrc = GetCRC16( BIN_BLOCK,BinBuffPtr);
	if (chkcrc != pTmpFcb->wBinCrc)
	{
		*err = FLASH_API_BIN_CRC_ERR;
		return FALSE;
	}

	if (pTmpFcb->nCfgFileLen)
	{
		chkcrc = GetCRC16( SRC_BLOCK,SrcBuffPtr);
		if (chkcrc != pTmpFcb->wConfCrc)
		{
			*err = FLASH_API_SRC_CRC_ERR;
			return FALSE;
		}
	}
	//2.�����������������ȳ������ܵ�Ҫ����������
	//3.��ʼдflash
	
	OS_ENTER_CRITICAL();	
	//2.0
	SelSector(0X16, 0X16);					// ѡ������
	EraseSector(0X16, 0X16);
	SelSector(0X16, 0X16);					// ѡ������
	RamToFlash(FCB_BLOCK_DESTADDR, (INT32U)FCB_BLOCK, FCB_BLOCK_SIZE);	// д��������FLASH	

	//2.1 BIN 
	SelSector(0X17, 0X17);					// ѡ������
	EraseSector(0X17, 0X17);
	SelSector(0X17, 0X17);					// ѡ������
	RamToFlash(BIN_BLOCK_DESTADDR, (INT32U)BIN_BLOCK, BIN_BLOCK_SIZE);	// д��������FLASH	

	if (pTmpFcb->nCfgFileLen)
	{
		//2.2 SRC 
		SelSector(0X18, 0X18);					// ѡ������
		EraseSector(0X18, 0X18);
		SelSector(0X18, 0X18);					// ѡ������
		RamToFlash(SRC_BLOCK_DESTADDR, (INT32U)SRC_BLOCK, SRC_BLOCK_SIZE);	// д��������FLASH		 
	}
	OS_EXIT_CRITICAL();	

	//4.��flash�������������Ƿ������ȷ�����������󣬵�������LED
	for (i = 0; i < FcbBuffPtr ; i++)
	{
		ByteValue = (*(volatile unsigned long *)(FCB_BLOCK_DESTADDR+i)); 
		if (ByteValue != FCB_BLOCK[i])
		{
			*err = FLASH_API_FCB_FLASH_ERR;
			return FALSE;
		}
	}

	for (i = 0; i < BinBuffPtr ; i++)
	{
		ByteValue = (*(volatile unsigned long *)(BIN_BLOCK_DESTADDR+i)); 
		if (ByteValue != BIN_BLOCK[i])
		{
			*err = FLASH_API_BIN_FLASH_ERR;
			return FALSE;
		}
	}

	if (pTmpFcb->nCfgFileLen)
	{
		for (i = 0; i < SrcBuffPtr ; i++)
		{
			ByteValue = (*(volatile unsigned long *)(SRC_BLOCK_DESTADDR+i)); 
			if (ByteValue != SRC_BLOCK[i])
			{
				*err = FLASH_API_SRC_FLASH_ERR;
				return FALSE;
			}
		}		 
	}
	//д�ɹ�,����ָ��
	FcbBuffPtr = 0;
	BinBuffPtr = 0;
	SrcBuffPtr = 0;
	return TRUE;
}

INT32U CheckRam(INT32U nStart,INT32U nEnd)
{
	INT32U i = 0;
	INT8U Val = 0;

	INT8U *pRam = (INT8U *)nStart;

	for ( ; ; )
	{
		if((INT32U)pRam >= nEnd)
			break;

		Val = *pRam;

		*pRam = 0xEA;
		__asm{NOP}   ;
		if ( *pRam != 0xEA )
		{
			*pRam = Val;
			return (INT32U)pRam;
		}
		*pRam = Val;
		pRam++;
	}
	return 0;
}