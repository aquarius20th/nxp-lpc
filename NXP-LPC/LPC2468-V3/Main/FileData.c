/****************************************Copyright (c)**************************************************
**                                �ļ�����ģ�� [Ŀǰ�������ù����У�δ��������Ч�Խ��м��]
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
**��        ע: 
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
#include "includes.h"
#include "FileData.h"
#include "modbus.h"



/*********************************************************************************************************
** ��������: LoadHdCfg
** ��������: LoadHdCfg
**
** ��������������Ӳ��������Ϣ
**
** �䡡��:  INT8U * pBuf
** �䡡��:  SEC_HD_CFG * pCfg
**          
** �䡡��:  INT32U
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
static INT32U LoadHdCfg(INT8U *pBuf,SEC_HD_CFG *pCfg)
{
	INT32U nBufPos = 0;
	INT32U i = 0;

	if (pBuf == NULL)
		return nBufPos;
	if (pCfg == NULL)
		return nBufPos;

	memcpy(& pCfg->CpuCfg, &pBuf[nBufPos],sizeof(CPU)); 
	nBufPos += sizeof(CPU);

	memcpy(& pCfg->ModuleCnt, &pBuf[nBufPos],sizeof(INT32U)); 
	nBufPos += sizeof(INT32U);

	memset(& pCfg->pIoCfg,0,sizeof(IO)*MAX_MODULE_CNT);
	if (pCfg->ModuleCnt >0 && pCfg->ModuleCnt <= MAX_MODULE_CNT)
	{
		for (i = 0; i < pCfg->ModuleCnt; i++)
		{
			memcpy(& pCfg->pIoCfg[i], &pBuf[nBufPos],sizeof(IO)); 
			nBufPos += sizeof(IO);
		}
	}

	return nBufPos;
}
/*********************************************************************************************************
** ��������: LoadGatageCfg
** ��������: LoadGatageCfg
**
** ���������� ����բ�ŷֶβ�����
**
** �䡡��:  INT8U * pBuf
** �䡡��:  SEC_GATAGE_CFG * pCfg
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��1��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT32U LoadGatageCfg(INT8U *pBuf,SEC_GATAGE_CFG *pCfg)
{
	INT32U nBufPos = 0;
	INT32U i = 0;

 	if (pBuf == NULL)
		return nBufPos;
	if (pCfg == NULL)
		return nBufPos;

	memcpy(& pCfg->MaxGatage, &pBuf[nBufPos],sizeof(FP64)); 
	nBufPos += sizeof(FP64);

	memcpy(& pCfg->MinGatage, &pBuf[nBufPos],sizeof(FP64)); 
	nBufPos += sizeof(FP64);

	memcpy(& pCfg->MaxEncoderVal, &pBuf[nBufPos],sizeof(INT32U)); 
	nBufPos += sizeof(INT32U);

	memcpy(& pCfg->MinEncoderVal, &pBuf[nBufPos],sizeof(INT32U)); 
	nBufPos += sizeof(INT32U);

	memcpy(& pCfg->UnitType, &pBuf[nBufPos],sizeof(INT8U)); 
	nBufPos += sizeof(INT8U);

	memcpy(& pCfg->CalcMethod, &pBuf[nBufPos],sizeof(INT8U)); 
	nBufPos += sizeof(INT8U);

	memcpy(& pCfg->Direction, &pBuf[nBufPos],sizeof(INT8U)); 
	nBufPos += sizeof(INT8U);

	memcpy(& pCfg->EncodeType, &pBuf[nBufPos],sizeof(INT8U)); 
	nBufPos += sizeof(INT8U);

	memcpy(& pCfg->ParaCnt, &pBuf[nBufPos],sizeof(INT32U)); 
	nBufPos += sizeof(INT32U);

	memset(  pCfg->pGatageTab,0,sizeof(GATAGE_PARA) *MAX_GATAGE_CNT );

	if (pCfg->ParaCnt >0 && pCfg->ParaCnt <= MAX_GATAGE_CNT)
	{
		for (i = 0; i < pCfg->ParaCnt; i++)
		{
			memcpy(& pCfg->pGatageTab[i], &pBuf[nBufPos],sizeof(GATAGE_PARA)); 
			nBufPos += sizeof(GATAGE_PARA);
		}
	}

	return nBufPos;
}
/*********************************************************************************************************
** ��������: LoadBinData
** ��������: LoadBinData
**
** �����������������ļ�����ȡ������Ϣ
**
** �䡡��: INT8U �ڴ���
**          
** �䡡��: INT8U ���󷵻�FALSE����ȷ����TURE
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  
** �ա���:  
** ��  ע: �ȴ�flash�м������ݵ�ram��Ȼ�����ram������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT32U LoadBinData(INT8U *pBuf,BIN_DATA *pBinData)
{
	INT32U nBufPos = 0;
	INT32U nLen = 0;

	//1.����Ӳ��������Ϣ
	nLen = LoadHdCfg(&pBuf[nBufPos], &pBinData->HdCfg);
	if (nLen == FALSE)
		return FALSE;
	nBufPos += nLen;

	//2.����բ��������Ϣ
	nLen = LoadGatageCfg(&pBuf[nBufPos], &pBinData->GatageCfg);
	if (nLen == FALSE)
		return FALSE;
	nBufPos += nLen;

	return nBufPos;
}

/*********************************************************************************************************
** ��������: InitDefaultHdCfg
** ��������: InitDefaultHdCfg
**
** ���������� Ĭ�ϵ�������Ϣ
**
** �䡡��:  SEC_HD_CFG * pHdCfg
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��19��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void InitDefaultHdCfg(SEC_HD_CFG *pHdCfg)
{
	if (pHdCfg == NULL)
		return;

	pHdCfg->CpuCfg.MDCnt = 0;
	pHdCfg->CpuCfg.MWCnt = 0;

	pHdCfg->CpuCfg.Port.Addr = MAX_MB_ADDR;
	pHdCfg->CpuCfg.Port.Baud = 9600;

	pHdCfg->CpuCfg.Port.StopBit = ONE_STOPBIT;
	pHdCfg->CpuCfg.Port.DataBit = 8;
 	pHdCfg->CpuCfg.Port.ParityBit = NONE_PARITY;

	pHdCfg->ModuleCnt = 0;
	memset(pHdCfg->pIoCfg,0,sizeof(IO)*MAX_MODULE_CNT);	
}
static void InitDefaultGatageCfg(SEC_GATAGE_CFG *pGatageCfg)
{
	if (pGatageCfg == NULL)
		return;

	pGatageCfg->MaxGatage = 10*100;    //���բ�ſ��� 10��
	pGatageCfg->MinGatage = 0;    //��Сբ�ſ��� 0��

	pGatageCfg->MaxEncoderVal = 4096;    //���բ�ſ��ȶ�Ӧ�ı�����ֵ
	pGatageCfg->MinEncoderVal = 96;    //��Сբ�ſ���

	pGatageCfg->UnitType  = UNIT_CM;      //��λ
	pGatageCfg->CalcMethod = CALC_BY_LINE;    //���㷽ʽ
	pGatageCfg->Direction = DIRE_CLOCKWISE;     //��ת����
	pGatageCfg->EncodeType = CODE_GRAY;    //�������ͣ�ֻ�Ծ��Ա�������Ч

	pGatageCfg->ParaCnt = 0;  //�ֶβ�������
	memset( pGatageCfg->pGatageTab,0,sizeof(GATAGE_PARA)*MAX_GATAGE_CNT );
}

void InitDefaultBinData(BIN_DATA *pBinData)
{
	InitDefaultHdCfg(& pBinData->HdCfg);
	InitDefaultGatageCfg( & pBinData->GatageCfg );
}
/*********************************************************************************************************
** ��������: InitDefaultFcb
** ��������: InitDefaultFcb
**
** ���������� 
**
**          
** �䡡��:  void
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
void InitDefaultFcb( FCB *pFcb)
{
	if (pFcb == NULL)
		return;

	pFcb->wHeadFlag = FCB_FLAG;

	pFcb->wMajorVer = 1; //���汾��  �磺1.00 :wMajorVer = 1 wMinorVer= 0��2.01 = wMajorVer = 2 wMinorVer= 1 ���汾�ź�Ӧ�ó����й� 
	pFcb->wMinorVer = 0; //�Ӱ汾�ţ�
	pFcb->wBuild = 0;    //���ļ�����ʱ������ÿ����һ�Σ��汾������1	

	pFcb->wBinBuild = 0;    //��������޸����ã�ÿ�޸�һ�Σ��˰汾��׷��һ�� 	

	pFcb->DownLoadTm.wYear = 2008;
	pFcb->DownLoadTm.ucMonth = 8;
	pFcb->DownLoadTm.ucDay = 8;
	pFcb->DownLoadTm.ucHour = 8;
	pFcb->DownLoadTm.ucMinute = 8;
	pFcb->DownLoadTm.wSecond = 8;
	pFcb->DownLoadTm.wMilliseconds = 8;

	pFcb->SaveTm.wYear = 2008; 
	pFcb->SaveTm.ucMonth = 8; 		
	pFcb->SaveTm.ucDay = 8; 		
	pFcb->SaveTm.ucHour = 8; 		
	pFcb->SaveTm.ucMinute = 8; 		
	pFcb->SaveTm.wSecond = 8; 	
	pFcb->SaveTm.wMilliseconds = 8 ;		

	//Դ�ļ��ĳ���
	pFcb->nCfgFileLen = 0;
	//Դ�ļ���crcУ��
	pFcb->wConfCrc = 0xffff;

	//������ļ�����
	pFcb->nBinLen = 0;     
	pFcb->wBinCrc = 0xffff;

	pFcb->nCtrlBit = 0;       // bit 0  
}
