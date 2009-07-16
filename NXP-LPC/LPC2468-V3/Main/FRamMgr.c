/****************************************Copyright (c)**************************************************
**                                �����Ա���ģ��
**     ����洢ǰ����Ҫ��һ�����ƿ�ṹ�����ڱ����־λ������Ĵ����ĸ���������MD��MW�ı������ֿ�                          
**     ��������������󣬿���Ԥ�����ֿռ����ڴ洢¼������                                  
**
**     ʱ�䱣�洦��������      ���ʱ������������2468ƽ̨���ԡ�2468��I2C��Ҫ���ӿ����֡�                
**     �����ҪԤ�����ӿ�����¼������
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
 
#include "MemData.h" 
#include "FRamMgr.h"
#include "TaskDef.h"
#include "hd_Init.h"
#include "I2c.h" 
#include "ram.h"
#include "TimerMgr.h"
#include "vicControl.h"


#define  FRAM3164   0xA0     //����������ַ

#define  FRAMCB_FLAG   0x4C49


// ���ƿ�
typedef struct FRAMCB 
{
	INT16U  wHeadFlag; //�ļ�ͷ��־ 0x4c 0x49
	//��һ�α����ʱ��
	DEVICE_TIME   SaveTm;			 
	INT16U     nMWCount;	 
	INT16U     nMDCount; 
}FRAMCB;


#define MW_FRAM_ADDR sizeof(FRAMCB)+10
#define MD_FRAM_ADDR MW_FRAM_ADDR+2*MAX_MW_CNT +10


static FRAMCB  FRamCB;
static OS_STK  FRamWRTaskStk [FRAMWR_TASK_STK_SIZE];
/*-------------------------------------------------------*/
// �������ƣ�FRam_SaveValue
// ���������INT8U uID:Ҫ���õ�ID�ţ����ڴ��д洢�ṹ����IDΪ׼;
//				Val:���õ�ֵ
// �����������
// �����������޸�FRAM�е�������Ϣ
/*-------------------------------------------------------*/
static void FRamSaveValue(INT16U nMWCnt,INT16U nMDCnt,M_DEF *pMemData )
{
	INT16U i = 0;
	INT16U Addr = 0;

	Addr = MW_FRAM_ADDR;

	for (i = 0; i < nMWCnt; i++)
	{
		if (pMemData->m_pMW[i] != pMemData->m_pMWLast[i])
		{//д������
			Addr += i*2;
			i2cWrite(1, FRAM3164, (INT8U *) & pMemData->m_pMW[i] ,  Addr,  1, sizeof(INT16U));
			while (i2cGetFlag(1) == I2C_BUSY);  
		}
	}

	Addr = MD_FRAM_ADDR;

	for (i = 0; i < nMDCnt; i++)
	{
		if (pMemData->m_pMD[i] != pMemData->m_pMDLast[i])
		{//д������
			Addr += i*4;
			i2cWrite(1, FRAM3164, (INT8U *) & pMemData->m_pMW[i] ,  Addr,  1, sizeof(INT32U));
			while (i2cGetFlag(1) == I2C_BUSY);  
		}
	}
	//����FRAMCB��ֵ

}
/*********************************************************************************************************
** ��������: FRamSave_Task
** ��������: FRamSave_Task
**
** ���������� ��ʱ�洢����
**
** �䡡��:  void * pdata
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
void FRamSave_Task(void *pdata)
{
	INT16U nTimerId = 2;
	INT8U bRet = FALSE;

	pdata = pdata;

	//1.��FRAM�����ȡFRAMCB
	i2cRead( 1,	FRAM3164,(INT8U *) & FRamCB,0, 1,sizeof(FRAMCB));    
    // �ȴ�I2C���߲�������        
 	while (i2cGetFlag(1) == I2C_BUSY);                                

	//2.�жϵ���ǰ�ı����MW MD�������Ƿ������ڵ�һ��
	if (FRamCB.wHeadFlag == FRAMCB_FLAG)
	{//�����������Ŀ��ƿ���Ч
		if (FRamCB.nMWCount && FRamCB.nMDCount && FRamCB.nMWCount <= MAX_MW_CNT && FRamCB.nMDCount <= MAX_MD_CNT)
		{//�����ǺϷ���
			if (GetFRamMWCnt() && GetFRamMDCnt() && GetFRamMWCnt() <= MAX_MW_CNT && GetFRamMDCnt() <= MAX_MD_CNT)
			{ 
				//��ֹ�����������������
				if ( GetFRamMWCnt()<= FRamCB.nMWCount )
				{//��

				}
				else
				{//�������洢�ĸ�������Ԥ�ڣ���ֻ�������ò��֣�ʣ�µĲ����򲻹ܣ��ȴ���һ�ε�д��

				}
				if (GetFRamMDCnt() <= FRamCB.nMDCount)
				{

				}
			}
		}
	}
	else
	{//д����ƿ�
		FRamCB.wHeadFlag = FRAMCB_FLAG;
		FRamCB.nMDCount = GetFRamMDCnt();
		FRamCB.nMWCount = GetFRamMWCnt( );
		//ʱ��


		i2cWrite(1, FRAM3164, (INT8U *) & FRamCB,  0,  1, sizeof(FRAMCB));
		while (i2cGetFlag(1) == I2C_BUSY);                              
	}

	if (GetFRamMWCnt() && GetFRamMDCnt() && GetFRamMWCnt() <= MAX_MW_CNT && GetFRamMDCnt() <= MAX_MD_CNT)
	{
		//500ms����һ��
		SetTimer(nTimerId,500,NULL,NULL);
		while(1)
		{
			if (GetFRamMWCnt() && GetFRamMDCnt() && GetFRamMWCnt() <= MAX_MW_CNT && GetFRamMDCnt() <= MAX_MD_CNT)
			{
				bRet = IsTimeTo(nTimerId);
				if (bRet)
				{
					FRamSaveValue( GetFRamMWCnt(),GetFRamMDCnt() , GetMDataPtr()  );
				}
			}
		    OSTimeDlyHMSM(0,0,0,100);		 
		}
	}
	else
	{
	    OSTimeDlyHMSM(0,0,0,200);		
	}	
}
/*********************************************************************************************************
** ��������: InitFRamWR
** ��������: InitFRamWR
**
** ���������� ϵͳ��ʼ��ʱ����Ҫ����FRAM�����Ƿ��д洢���������ݣ�����У�����ƥ�䣬�����
**
**          
** �䡡��:  INT8U
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
extern INT8U  InitFRamMgrTsk( void )
{
	//0.����Ӳ������
	//I2C�ж�����                
	SetVICIRQ(VIC_I2C2, 6, (int)i2c1IRQ);                                      
    //��ʼ��I2C0      
	I2CInit(1, 100000,NULL);                                  

	 //������ʱд����		 
	OSTaskCreate (FRamSave_Task, (void *)0, &FRamWRTaskStk[FRAMWR_TASK_STK_SIZE-1], PRIO_FRAM_SAVE);
	 
	return TRUE;
}
