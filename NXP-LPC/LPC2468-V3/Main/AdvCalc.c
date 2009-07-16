/****************************************Copyright (c)**************************************************
**                                       �߼���������
**                                      
**          ͨ���ɼ���ǰ�ı����������ֵ������բ�ŵ����ͣ������բ�ŵĶ�Ӧ����                            
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
#include "includes.h"
#include "FileData.h"
#include "AdvCalc.h"
#include "MemData.h"
#include "TimerMgr.h"
 
#include "IoAdapter.h"
#include "FileData.h"
#include "Ram.h"
#include "IoAdapter.h"
#include "TaskDef.h"


//բ�ſ��ȼ������
typedef struct GATAGE_CALC_PARA
{
	FP64	k;				//ƽ����(ֱ����)б��
	FP64	b;				//����ֵ
	GATAGE_PARA  	*pArcPoint;
	INT32U  slopcnt;
	FP64	slop[MAX_GATAGE_CNT-1];		//�����ŷֶμ������б��
}GATAGE_CALC_PARA;


static GATAGE_CALC_PARA  GatagePara;
static OS_STK	AdvCalcTaskStk  [ADVCALC_TASK_STK_SIZE];

/***********************************************************************************
**����ԭ�ͣ�INT16U GraytoBinary(INT16U x)
**��ڲ���:	INT16U	x:16λ������ֵ
**���ڲ���:	INT16U	y:16λ������ֵ
**�� �� ֵ��		
**˵    ����������ת��Ϊ��������
************************************************************************************/
static INT32U GraytoBinary(INT32U x_INT32U)
{
    INT32U y = 0;
    y = x_INT32U;
    while(x_INT32U>>=1)
         y ^= x_INT32U;
    return y;
}   
/*********************************************************************************************************
** ��������: GetParameter
** ��������: GetParameter �����⿪�ţ�ֻ�ڱ�ģ��ʹ��
**
** ���������� ����բ�ſ�����ز�����б�ʵ�
**
** �䡡��:  CGatagePara * pPara
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��1��
** ��  ע:  ϵͳ��ʼ��ʱ���������������صĲ�����������ʱ�������������㡣
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U InitGatagePara (GATAGE_CALC_PARA *pPara,SEC_GATAGE_CFG *pGatage)
{
	INT8U	i = 0;
	INT32U	calcdata = 0;	
	INT8U  CalcMethod = 0;
	
	if (pPara == NULL)
		return FALSE;
	if (pGatage == NULL)
		return FALSE;

	CalcMethod = GetGatageCalcMethod( ) ;
	
	if ( CalcMethod == CALC_BY_LINE)
	{//��������Լ���
		calcdata = pGatage->MaxEncoderVal - pGatage->MinEncoderVal;
		if (calcdata == 0)
			return FALSE;

		pPara->k = (pGatage->MaxGatage - pGatage->MinGatage)/calcdata;
		pPara->b = (pGatage->MinGatage * pGatage->MaxEncoderVal - pGatage->MaxGatage* pGatage->MinEncoderVal ) /calcdata;
		return TRUE;
	}
	else if ( CalcMethod == CALC_BY_TAB )
	{
		if (pGatage->ParaCnt<=3 || pGatage->ParaCnt > MAX_GATAGE_CNT || pGatage->pGatageTab == NULL)
		{
			return FALSE;
		}
		pPara->pArcPoint = pGatage->pGatageTab;
		pPara->slopcnt = pGatage->ParaCnt-1;

		for ( i = 0; i < pGatage->ParaCnt-1; i++)
		{
			calcdata = pGatage->pGatageTab[i+1].EncoderVal - pGatage->pGatageTab[i].EncoderVal;
			if(calcdata == 0)
				return FALSE;
			pPara->slop[i] = (FP32)(pPara->pArcPoint[i+1].Gatage - pPara->pArcPoint[i].Gatage) / calcdata;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
} 
/*********************************************************************************************************
** ��������: CalcGatage
** ��������: �����⿪�ţ�ֻ�ڱ�ģ��ʹ��
**
** ���������� ����բ�ſ���ֵ
**
** �䡡��:  INT32U EncoderVal
** �䡡��:  GATAGE_CALC_PARA * pPara
** �������:  fp32 * pfGatageVal �����բ�ſ���
**          
** �䡡��:  INT8U �����Ƿ�ɹ�
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��2��
** ��  ע:  �ٶ���Ϊ��ʱ����ı���ֵ��Ч������ֵ�ĺϷ����������ĵط���У��
            ��������Ŀ���ֵ�Ƿ���ȷ��Ҳ���ڴ˴�У��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static INT8U CalcGatage(INT32U EncoderVal,GATAGE_CALC_PARA *pPara,FP32 *pfGatageVal)
{
	INT8U  CalcMethod = 0;
	INT8U  i = 0;
 	INT8U  Direction ;

	if (pPara == NULL)
		return FALSE;
	if (pfGatageVal == NULL)
		return FALSE;

	CalcMethod = GetGatageCalcMethod() ;

	if ( CalcMethod == CALC_BY_LINE)
	{//��������Լ���
		*pfGatageVal = (FP32)(pPara->k * EncoderVal) + pPara->b;
		return TRUE;
	}
	else if ( CalcMethod == CALC_BY_TAB)
	{
		if (pPara->pArcPoint == NULL)
			return FALSE;

		Direction = GetEncoderDirection();

		if (Direction == DIRE_CLOCKWISE)  //˳ʱ�뷽��
		{
			if (EncoderVal >=pPara->pArcPoint[0].EncoderVal && EncoderVal < pPara->pArcPoint[pPara->slopcnt].EncoderVal )
			{//�ڷ�Χ��
				for (i = 0; i < pPara->slopcnt-1; i++)
				{//�ҳ�����������
					if (EncoderVal >=pPara->pArcPoint[i].EncoderVal && EncoderVal < pPara->pArcPoint[i+1].EncoderVal)
					{
						*pfGatageVal = pPara->pArcPoint[i].Gatage + pPara->slop[i]*(EncoderVal-pPara->pArcPoint[i].EncoderVal);
						return TRUE;
					}
				}
			}
			else if (EncoderVal < pPara->pArcPoint[0].EncoderVal )
			{//��������£�Ϊ��ֵ
				*pfGatageVal = pPara->pArcPoint[0].Gatage + pPara->slop[0]*(EncoderVal-pPara->pArcPoint[0].EncoderVal);
				return TRUE;
			}
			else if (EncoderVal >= pPara->pArcPoint[pPara->slopcnt].EncoderVal )
			{//�������޷�Χ
				*pfGatageVal = pPara->pArcPoint[pPara->slopcnt].Gatage;
				return TRUE;
			}			 		
		}
		else if ( Direction == DIRE_ANTI_CLOCKWISE ) //��ʱ�뷽��
		{//���ֵ������ֵ
			if (EncoderVal <= pPara->pArcPoint[0].EncoderVal && EncoderVal >pPara->pArcPoint[pPara->slopcnt].EncoderVal )
			{//�ڷ�Χ��
				for (i = 0; i < pPara->slopcnt-1; i++)
				{//�ҳ�����������
					if (EncoderVal <=pPara->pArcPoint[i].EncoderVal && EncoderVal > pPara->pArcPoint[i+1].EncoderVal)
					{
						*pfGatageVal = pPara->pArcPoint[i+1].Gatage + pPara->slop[i]*(EncoderVal-pPara->pArcPoint[i+1].EncoderVal);
						return TRUE;
					}
				}
			}
			else if (EncoderVal > pPara->pArcPoint[0].EncoderVal )
			{//��������£�Ϊ��ֵ
				*pfGatageVal = pPara->pArcPoint[0].Gatage + pPara->slop[0]*(EncoderVal-pPara->pArcPoint[0].EncoderVal);
				return TRUE;
			}
			else if (EncoderVal <= pPara->pArcPoint[pPara->slopcnt].EncoderVal )
			{//�������޷�Χ
				*pfGatageVal = pPara->pArcPoint[pPara->slopcnt].Gatage;
				return TRUE;
			}		
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
} 
/*********************************************************************************************************
** ��������: AdvCalcTask
** ��������: AdvCalcTask
**
** ���������� �߼���������Ŀǰֻ���㿪�ȣ������԰���������Ҳ�ϲ�����
**
** �䡡��:  void * pdata
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��22��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: Ŀǰ��ʱ��֧�ִ�ģ�������룬��ʱֻ����MD�ɼ����������ź�
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
static void AdvCalcTask(void *pdata)
{
	FP32 fValue = 0.0f;
	INT16U nTimerId = 3;
	INT8U bRet = FALSE;
	INT32U EncoderVal = 0;
	INT32U LastEncoderVal = 0xff;
	INT8U bTimeTo = FALSE;

	pdata = pdata;

	//1000ms����һ��
	SetTimer(nTimerId,1000,NULL,NULL);
 
	while(1)
	{
		bTimeTo = IsTimeTo(nTimerId);
		if (bTimeTo)
		{
			//����ֵ�̶������%MD0001
			EncoderVal = GetMDVal(0);
			if (LastEncoderVal != EncoderVal)
			{
				LastEncoderVal = EncoderVal;
				bRet = CalcGatage(EncoderVal,&GatagePara ,&fValue);
				if (bRet == FALSE)
				{//��ϵͳ����λ					

				}
				else
				{//��ϵͳ����λ

				}
			}
		}	 
		OSTimeDlyHMSM(0,0,0,300);
	}
}

/*********************************************************************************************************
** ��������: InitGatageTsk
** ��������: InitGatageTsk
**
** ���������� 
**
** �䡡��:  void
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��24��
** ��  ע: ����Ǻϲ�������������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U InitGatageTsk( void )
{
	INT8U bRet = FALSE;

	bRet = InitGatagePara(&GatagePara,&Ram.BinData.GatageCfg);
	if (bRet == FALSE)
	{
		SetLed(LED_FAULT,TRUE);
		return FALSE;
	}

	//��������
	OSTaskCreate (AdvCalcTask, (void *)0, 	&AdvCalcTaskStk[ADVCALC_TASK_STK_SIZE-1], GATAGECALC_TASK_PRIO);
	return bRet;
}
