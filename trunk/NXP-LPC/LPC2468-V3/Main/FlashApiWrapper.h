/****************************************Copyright (c)**************************************************
**                                       FLASH�ļ������ӿڵķ�װ
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
#ifndef FLASH_API_H
#define	FLASH_API_H 
#include "FileData.h"

typedef enum FAErrCode
{
	FLASH_API_NO_ERR = 0,   //û�д�
	FLASH_API_NO_FCB = 1,   //û��FCB���ƿ�
	FLASH_API_NO_BINDATA = 2, //û��bin�ļ�
	FLASH_API_BIN_CRC_ERR = 3,
	FLASH_API_SRC_CRC_ERR = 4,
	FLASH_API_BIN_LEN_ERR = 5 ,//BIN �ļ����ȴ��� 
	FLASH_API_SRC_LEN_ERR = 6 ,//SRC �ļ����ȴ��󣬳�������,���������صĳ��Ȳ�һ��
	FLASH_API_FCB_FLASH_ERR = 7 ,//��FLASH��������
	FLASH_API_BIN_FLASH_ERR = 8 ,//��FLASH��������
	FLASH_API_SRC_FLASH_ERR = 9  //��FLASH��������
}FAErrCode; 

typedef enum FLASH_DATA_TYPE
{
	FCB_DATA_TYPE = 1,
	BIN_DATA_TYPE = 2,
	SRC_DATA_TYPE = 3
}FLASH_DATA_TYPE;

//ͨ����Щд����������ͨ��ģ����õģ�������Һ�������������
//д���ƿ�
//INT16U WriteFcb(  FCB *pFcb  );
//дBIN
//INT16U WriteBinData( BIN_DATA  *pBinDat, INT16U nLen);
//дԴ�ļ�
INT32U WriteSrcData( INT8U *pBuf,INT32U nLen);

//����
extern INT8U  ErasureFlash( void ); 

extern INT8U LoadFlashData( );

//����������flash�ж�ȡ��Ӧ������
extern INT16U LoadFcb(FCB *pFcb,INT8U *err);
//��ͨ��ģ����û�����ϵͳ����ʱ��ʼ������
extern INT8U  ReadSrcDataBuf(INT8U *pBuff, INT32U nFileOffset,INT8U nLen);
extern INT8U  ReadBinDataBuf(INT8U *pBuff, INT32U nFileOffset,INT8U nLen);

extern INT8U  GetFcbBuff(INT8U **pBuff,INT8U *pLen );
extern INT8U  GetBinDataBuff(INT8U **ppBuff, INT32U *pLen);
extern INT8U  GetSrcDataBuff(INT8U **ppBuff, INT32U *pLen);

//��ͨ��ģ����ã�����ʱ��������д����
extern INT8U PutFcbData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx );
extern INT8U PutBinData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx );
extern INT8U PutSrcData(INT8U *pBuff, INT8U nLen,INT16U nPacketIdx );

extern INT8U SaveData(INT8U *err );


//�ڴ��Լ�
extern INT8U SelfCheckRam(void);		

 
#endif
