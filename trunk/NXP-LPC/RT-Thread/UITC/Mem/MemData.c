/******************************************************************************
ģ����      :  
�ļ���      :   
����ļ�    :
ʵ�ֹ���    : �Ĵ����Ķ�д�����ӿ�
�޸ļ�¼    : Ŀǰֻ������һ���ָ����ϵĶ���
              ��Ҫ����״̬���е�λ�Ļ�ȡ���޸Ľӿ�ʵ��
------------------------------------------------------------------------------
����        �޸���      �޸�����
2007/9/16
******************************************************************************/

#include <string.h>       // Keil: Line added	 
#include "MemData.h" 
#include "Func.h"

static 	MEMDB g_MemData; 

/*********************************************************************************************************
** ��������: SetPIBit
** ��������: SetPIBit
**
** ���������� ���뿪���� ��bit��ʽ���� nIdx ��0��ʼ
**
** �䡡��:  INT8U Val
** �䡡��:  INT16U nIdx
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��6��13��
** ��  ע:  
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetPIBit(INT8U Val, INT16U nIdx )
{
	INT16U  no, bias; 

	if (nIdx < MAX_I_CNT)
	{
		no= nIdx/8; 
		bias=nIdx%8;

		g_MemData.IData.RawData[no] = ( ( g_MemData.IData.RawData[no] & (ClrBit(bias)) ) | ((!!Val)<<bias)  ); 	
 	}
}

/*********************************************************************************************************
** ��������: SetPIW
** ��������: SetPIW
**
** ���������� 
**
** �䡡��:  INT16U Val
** �䡡��:  INT16U nIdx
**          
** �䡡��:  void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��4��
** ��  ע:  ���ж����棬��Ӳ�����������
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void SetPIW( INT16U Val,INT16U nIdx)
{
	if (nIdx<MAX_AI_CNT)
	{
		g_MemData.AIData.RawData[nIdx] = Val;
	}
}

INT8U GetIVal(INT16U OccNo)
{
	return	( !!( g_MemData.IData.State[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
}

INT8U GetIForceMark(INT16U OccNo )
{
	return	( !!( g_MemData.IData.ForceMark[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
}


//ǿ��I�Ĵ���
INT8U ForceI( INT16U OccNo, INT16U value ) 
{ 
	INT16U  no, bias; 
	if( OccNo<=MAX_I_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
		g_MemData.IData.State[no]=( ( g_MemData.IData.State[no] & (ClrBit(bias)) ) | ((!!value)<<bias) ); 
		g_MemData.IData.ForceMark[no] = g_MemData.IData.ForceMark[no] | OrBit(bias); 
//		Ram.CurrentMeasure.Stu.udigital_in = Ram.CurrentMeasure.Stu.udigital_in | ((!!value)<<(OccNo-1));
		return TRUE;
	}  
	return FALSE;
}

//���ǿ��
INT8U UnForceI( INT16U OccNo )
{ 
	INT16U  no, bias; 
	if( OccNo<=MAX_I_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
		g_MemData.IData.State[no]=(  ( g_MemData.IData.State[no] & (ClrBit(bias)) ) | ( g_MemData.IData.RawData[no] & OrBit(bias) ) ); 
		g_MemData.IData.ForceMark[no] = g_MemData.IData.ForceMark[no] & (ClrBit(bias)); 
		return TRUE;
	} 
	return FALSE;
}

//��ǿ�Ʊ�־
INT8U SetIForceMark( INT16U OccNo, INT16U value )
{ 
	INT16U  no, bias; 
	if( OccNo<=MAX_I_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
		g_MemData.IData.ForceMark[no]=( (g_MemData.IData.ForceMark[no] & (ClrBit(bias)) ) | ((!!value)<<bias) );
		return TRUE;
	} 
	return FALSE;
}

/* -------------------------------  Q  -----------------------------------------
///////////////////////////////////////////////////////////////
Input :
occno : 1 -- MAX_Q
///////////////////////////////////////////////////////////////
----------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
** ��������:  GetQVal
** ��������:  ȡ����ֵ�����߼�ɨ������ͨѶ�������
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U GetQVal(INT16U OccNo )
{
	return	( !!( g_MemData.QData.State[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );	 
}

/*-------------------------------------------------------------------------
** ��������: SetPulseQValue
** ��������:  �������  �ṩ��ͨѶ���߼���ģ���õ�
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U SetPulseQValue( INT16U OccNo, INT8U Val,INT16U PulseTime )
{
	INT16U  no, bias; 

	if( OccNo<=MAX_Q_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8;
		bias=(OccNo-1)%8;
		if(!(g_MemData.QData.ForceMark[no]&OrBit(bias))) 
		{ //set val
			if(Val==0 && PulseTime!=HOLD_TYPE && PulseTime!=HOLD_TYPE1 ) 
				return FALSE;
			g_MemData.QData.Output[no]=(  ( g_MemData.QData.Output[no] & (ClrBit(bias)) ) | ((!!Val)<<bias)  ); 
			/*overwrite State Right now*/
			//g_MemReg.QData.State[no]=(  ( g_MemReg.QData.State[no] & (ClrBit(bias)) ) | ((!!Val)<<bias)  ); 
			if( PulseTime==HOLD_TYPE || PulseTime==HOLD_TYPE1 )
				g_MemData.QData.PulseTime[OccNo-1]=0; 
			else
			{
				g_MemData.QData.PulseTime[OccNo-1]=PulseTime; 
			}

			//g_MemReg.QData.OutputEna[no] =g_MemReg.QData.OutputEna[no] | OrBit(bias); 
			//if(PulseTime==HOLD_TYPE)
			//	g_MemReg.QData.CheckEna [no] =  g_MemReg.QData.CheckEna[no] | OrBit(bias); 
			//else
			//    g_MemReg.QData.CheckEna [no] = g_MemReg.QData.CheckEna [no] & (ClrBit(bias)); 
			//return TRUE;
		} 
		return TRUE;
	} 
	return FALSE;
}
/*-------------------------------------------------------------------------
** ��������: ForceQValue
** ��������:  ����ǿ�ƣ��ɵ������ʹ��
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U ForceQ(INT16U OccNo, INT16U Val)
{
	INT16U  no, bit; 
	if( OccNo<=MAX_Q_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bit=(OccNo-1)%8;

		g_MemData.QData.ForceMark[no] = g_MemData.QData.ForceMark[no] | OrBit(bit); 
		g_MemData.QData.Output[no]=(  ( g_MemData.QData.Output[no] & (ClrBit(bit)) ) | ((!!Val)<<bit)  ); 
		/*overwrite State Right now*/
		//g_MemReg.QData.State[no]= (  ( g_MemReg.QData.State[no] & (ClrBit(bit)) ) | ((!!Val)<<bit)  ); 
		g_MemData.QData.PulseTime[OccNo-1]=HOLD_TYPE; 
		//  g_MemReg.QData.OutputEna[no] = g_MemReg.QData.OutputEna[no] | OrBit(bit); 
		//  g_MemReg.QData.CheckEna [no] = g_MemReg.QData.CheckEna [no] | OrBit(bit); 
		return TRUE;
	}
	return FALSE;
}
/*-------------------------------------------------------------------------
** ��������: UnForceQ
** ��������:  ȡ������ǿ�ƣ��ɵ������ʹ��
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U UnForceQ( INT16U OccNo )
{ 
	INT16U  no, bit; 
	if( OccNo<=MAX_Q_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bit=(OccNo-1)%8;
		if(g_MemData.QData.ForceMark[no] & OrBit(bit) )
		{
			//	g_MemReg.QData.OutputEna[no] = g_MemReg.QData.OutputEna[no] & (ClrBit(bit)); 
			//	g_MemReg.QData.CheckEna [no] = g_MemReg.QData.CheckEna [no] & (ClrBit(bit)); 
			g_MemData.QData.PulseTime[OccNo-1]=0; 
			g_MemData.QData.ForceMark[no] = g_MemData.QData.ForceMark[no] & (ClrBit(bit)); 
		}
		return TRUE;
	} 
	return FALSE;
}
/*-------------------------------------------------------------------------
** ��������: SetForceMarkQ
** ��������:  ���ÿ���ǿ�Ʊ�־���ɵ������ʹ��
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U SetQForceMark( INT16U OccNo, INT16U value )
{ 
	INT16U  no, bias; 
	if( OccNo<=MAX_Q_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
		g_MemData.QData.ForceMark[no]=( ( g_MemData.QData.ForceMark[no] & (ClrBit(bias)) ) | ((!!value)<<bias) );
		return TRUE;
	} 
	return FALSE;
}
/*-------------------------------------------------------------------------
** ��������:  GetQForceMark
** ��������:  ȡ����ǿ�Ʊ�־���ɵ������ʹ��
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U GetQForceMark( INT16U OccNo)
{
	return ( !!( g_MemData.QData.ForceMark[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) ) ;
}

/*********************************************************************************************************
** ��������:  CheckPulseQ
** ��������:   ��������Ϳ������ȵ�����ʱ�䵽���Զ���output��0 �ú�����10ms����һ�Σ����
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: ��
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��7��26��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#define  MS_1TICK 20
void CheckPulseQ( INT16U OccNo, INT32U TickSum )
{
	if (OccNo>0 && OccNo<=MAX_Q_CNT)
	{
		if( g_MemData.QData.PulseTime[OccNo] && (g_MemData.QData.Output[OccNo/8] & OrBit(OccNo%8)) ) 
		{
			if(g_MemData.QData.PulseTime[OccNo] >= (MS_1TICK*TickSum))
				g_MemData.QData.PulseTime[OccNo] -= (MS_1TICK*TickSum); 
//			if(g_MemReg.QData.PulseTime[OccNo] >= TickSum)
//				g_MemReg.QData.PulseTime[OccNo] -= TickSum; 
			else
				g_MemData.QData.PulseTime[OccNo] = 0;

			if(g_MemData.QData.PulseTime[OccNo]==0)
			{
				g_MemData.QData.Output[OccNo/8] = (g_MemData.QData.Output[OccNo/8] & ClrBit(OccNo%8) ); 
			} 
		}	
	}
	return ;
}
 
/*-------------------------------------------------------------------------
** ��������:  
** ��������:   
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: Ram
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��8��7��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT8U SetMWVal( INT16U OccNo, INT16U Val ) 
{
	if( OccNo<=MAX_MW_CNT && OccNo>0 ) 
	{
		g_MemData.MData.m_pMW[OccNo-1] = Val; 
		return TRUE;
	}
	return FALSE;
}

INT16U GetMWVal( INT16U occno ) 
{ 
	if( occno<=MAX_MW_CNT && occno>0)
		return ( (g_MemData.MData.m_pMW[occno-1]) ); 
	return 0;
}
/*********************************************************************************************************
** ��������: GetMWBitVal
** ��������: GetMWBitVal
**
** ���������� 
**
** �䡡��:  INT16U occno
** �䡡��:  INT16U bit ��1��ʼ
**          
** �䡡��:  INT8U
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��9��7��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
INT8U GetMWBitVal( INT16U occno, INT16U bit ) 
{ 
	if( occno<=MAX_MW_CNT && occno>0 && bit>0 && bit<=16 ) 
		return ( (g_MemData.MData.m_pMW[occno-1] >>(bit-1)) & 0x01 ); 
	return 0;
}

INT8U SetMWBitVal(INT16U OccNo,INT16U bit ,INT8U Val)
{
	if( OccNo<=MAX_MW_CNT && OccNo>0 && bit>0 && bit<=16 ) 
	{
//		g_MemData.MData.m_pMW[OccNo-1] = g_MemData.MData.m_pMW[OccNo-1]   ; 
		return TRUE;
	}
	return FALSE;
}


INT8U SetMDVal( INT16U OccNo, INT32U Val ) 
{
	if( OccNo<=MAX_MD_CNT && OccNo>0 ) 
	{
		g_MemData.MData.m_pMD[OccNo-1] =  Val; 
		return TRUE;
	}
	return FALSE;
}

INT32U GetMDVal( INT16U occno ) 
{ 
	if( occno<=MAX_MD_CNT && occno>0)
		return ( (g_MemData.MData.m_pMD[occno-1]) ); 
	return 0;
}

INT8U GetMDBitVal( INT16U occno, INT16U bit ) 
{ 
	if( occno<=MAX_MD_CNT && occno>0 && bit>0 && bit<=32 ) 
		return ( (g_MemData.MData.m_pMD[occno-1] >>(bit-1)) & 0x01 ); 
	return 0;
}

/*-------------------------------------------------------------------------
** ��������:  GetAIVal
** ��������:  ȡģ�����Ĳ�ֵ
**
** �䡡��: ��
**
** �䡡��: ��
**         
** ȫ�ֱ���: g_MemReg
** ����ģ��: ��
**
** ������:  LiJin
** �ա���: 2007��8��7��
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
**------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------*/
INT16U GetAIVal( INT16U OccNo )
{
	return ( g_MemData.AIData.Value[OccNo - 1] );
}

INT8U GetAIForceMark(INT16U OccNo )
{
	return	( !!( g_MemData.AIData.ForceMark[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
}

INT8U ForceAI(INT16U OccNo, INT16U Val)
{
	INT16U bias; 

	if(Val != 0 && Val < 4000)
		Val = 4000;
	else if(Val > 20000)
		Val = 20000;

	if( OccNo<=MAX_AI_CNT && OccNo>0 ) 
	{ 
		bias=(OccNo-1)%8;
		g_MemData.AIData.Value[OccNo-1] = Val; 
		g_MemData.AIData.ForceMark[(OccNo-1)/8] = g_MemData.AIData.ForceMark[(OccNo-1)/8] | OrBit(bias);
		return TRUE;
	}  
	return FALSE;
}

INT8U UnForceAI(INT16U OccNo)
{
	INT16U bit; 
	if( OccNo<=MAX_AI_CNT && OccNo>0 ) 
	{ 
		bit=(OccNo-1)%8;
		if((g_MemData.AIData.ForceMark[(OccNo-1)/8] & OrBit(bit)))
		{
			g_MemData.AIData.ForceMark[(OccNo-1)/8] = g_MemData.AIData.ForceMark[(OccNo-1)/8] & (ClrBit(bit)); 
			g_MemData.AIData.Value[OccNo-1] = g_MemData.AIData.RawData[OccNo-1];
		}
		return TRUE;
	} 
	return FALSE;
}

INT8U SetAIForceMark( INT16U OccNo, INT16U value )
{ 
	INT16U  bias; 
	if( OccNo<=MAX_AI_CNT && OccNo>0 ) 
	{ 
		bias=(OccNo-1)%8;
		g_MemData.AIData.ForceMark[(OccNo-1)/8] =( ( g_MemData.AIData.ForceMark[(OccNo-1)/8] & (ClrBit(bias)) ) | ((!!value)<<bias) );
		return TRUE;
	} 
	return FALSE;
}
/* -------------------------------  AQ  --------------------------------------
///////////////////////////////////////////////////////////////
Input :
occno : 1 -- MAX_AQ
///////////////////////////////////////////////////////////////
----------------------------------------------------------------------------*/
INT16U GetAQVal( INT16U OccNo )
{
	//	return	g_MemReg.AQData.Value[OccNo - 1];
	return	g_MemData.AQData.Output[OccNo - 1];
}

INT8U GetAQForceMark(INT16U OccNo )
{
	return	( !!( g_MemData.AQData.ForceMark[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
}

INT8U SetAQVal( INT16U OccNo, INT16U Val )
{
	if(Val < 4000)
		Val = 4000;
	else if(Val > 20000)
		Val = 20000;

	if( OccNo<=MAX_AQ_CNT && OccNo>0 )
	{
		//		g_MemReg.AQData.Output[OccNo - 1] = Val;
		g_MemData.AQData.Value[OccNo - 1] = Val;
		return TRUE;
	}
	return 0;
}

INT8U ForceAQ(INT16U OccNo, INT16U Val)
{
	INT16U no, bias;

	if(Val < 4000)
		Val = 4000;
	else if(Val > 20000)
		Val = 20000;

	if( OccNo<=MAX_AQ_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8;
		bias=(OccNo-1)%8;
		g_MemData.AQData.Value[OccNo-1] = Val;
		g_MemData.AQData.Output[OccNo-1] = Val;
		g_MemData.AQData.ForceMark[(OccNo-1)/8] = g_MemData.AQData.ForceMark[(OccNo-1)/8] | OrBit(bias);

		return TRUE;
	}  
	return FALSE;
}

INT8U UnForceAQ(INT16U OccNo)
{
	INT16U  bit; 
	if( OccNo<=MAX_AQ_CNT && OccNo>0 ) 
	{  
		bit=(OccNo-1)%8;
		if((g_MemData.AQData.ForceMark[(OccNo-1)/8] & OrBit(bit)) )
		{
			g_MemData.AQData.ForceMark[(OccNo-1)/8] = g_MemData.AQData.ForceMark[(OccNo-1)/8] & (ClrBit(bit)); 
		}
		return TRUE;
	} 
	return FALSE;
}

INT8U SetAQForceMark( INT16U OccNo, INT16U value )
{ 
	INT16U  bias; 
	if( OccNo<=MAX_AQ_CNT && OccNo>0 ) 
	{ 
		bias=(OccNo-1)%8;
		g_MemData.AQData.ForceMark[(OccNo-1)/8] =( ( g_MemData.AQData.ForceMark[(OccNo-1)/8] & (ClrBit(bias)) ) | ((!!value)<<bias) );
		return TRUE;
	} 
	return FALSE;
}

/* -------------------------------  M  -----------------------------------------
///////////////////////////////////////////////////////////////
Input :
occno : 1 -- MAX_M
///////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------*/
// INT8U GetMVal( INT16U OccNo)
// {
// 	return	( !!( g_MemData.MData.State[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
// }
// 
// INT8U SetMVal( INT16U occno, INT16U value, INT32U pulseTime )
// { 
// 	INT16U  no, bias; 
// 	if( occno<=MAX_MB_CNT && occno>0 ) 
// 	{ 
// 		no= (occno-1)/8; 
// 		bias=(occno-1)%8;
// 
// 		g_MemData.MData.State[no]=(  ( g_MemReg.MData.State[no] & (ClrBit(bias)) ) | ((!!value)<<bias)  ); 
// 		if((pulseTime!=HOLD_TYPE) && (pulseTime!=HOLD_TYPE1) ) 
// 		{ 
// 			if(value)
// 			{
// 				g_MemReg.MData.PulseTime[occno-1]=pulseTime; 
// 				g_MemReg.MData.OutputEna[no] = g_MemReg.MData.OutputEna[no] | OrBit(bias); 
// 				g_MemReg.MData.State[no]=(  ( g_MemReg.MData.State[no] & (ClrBit(bias)) ) | ((!!value)<<bias)  ); 
// 			}
// 			//else
// 			//{
// 			//	return FALSE;
// 			//}
// 		} 
// 		else 
// 		{ 
// 			g_MemReg.MData.PulseTime[occno-1]=0; 
// 			g_MemReg.MData.OutputEna[no] = g_MemReg.MData.OutputEna[no] & (ClrBit(bias)); 
// 			g_MemReg.MData.State[no]=(  ( g_MemReg.MData.State[no] & (ClrBit(bias)) ) | ((!!value)<<bias)  ); 
// 		} 
// 		return TRUE;
// 	} 
// 	return FALSE;
// }
 
INT8U GetSVal(INT16U OccNo )
{
	return	( !!( g_MemData.SData.m_pS[(OccNo-1)/8] & OrBit((OccNo-1)%8) ) );
}

INT8U SetSVal( INT16U OccNo, INT8U Val )
{
	INT16U  no, bias; 
	if( OccNo<=MAX_S_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8;
		bias=(OccNo-1)%8;

		g_MemData.SData.m_pS[no]=( ( g_MemData.SData.m_pS[no] & (ClrBit(bias)) ) | ((!!Val)<<bias) );

		return TRUE;
	}

	return FALSE;
}
 
INT16U GetSWVal( INT16U OccNo )
{
	return	g_MemData.SData.m_pSW[OccNo - 1];
}

INT8U SetSWValue( INT16U OccNo, INT16U state )
{
	if( OccNo<=MAX_SW_CNT && OccNo>0 ) 
	{
		g_MemData.SData.m_pSW[OccNo-1] = (INT16U)state; 
		return TRUE;
	}
	return FALSE;
} 

void ScanAQ( INT16U OccNo, INT16U num )
{
	INT16U  bias, i; 

	for(i=OccNo;i<(OccNo+num);i++)
	{
		if( i<=MAX_AQ_CNT && i>0 )
		{ 
			bias=(i-1)%8;
			if(g_MemData.AQData.ForceMark[(OccNo-1)/8] & OrBit(bias)) 
				continue;
			g_MemData.AQData.Output[i-1] = g_MemData.AQData.Value[i-1]; 
		} 
		else
			return;
	}
	return;
}


/*********************************************************************************************************
** ��������: InitMemData
** ��������: InitMemData
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
** �ա���:  2008��9��19��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
void InitMemData( )
{
	//���
	memset( &g_MemData,0,sizeof(MEMDB));
	//ϵͳ�Ĵ�����ʼ��

}


//���ÿ���ֵ���������߼��������⿪��
INT8U SetIVal( INT16U OccNo, INT16U value ) 
{ 
	INT16U  no, bias; 
	if( OccNo<=MAX_I_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
		if(!(g_MemData.IData.ForceMark[no]&OrBit(bias))) 
		{ 
			g_MemData.IData.State[no]=( ( g_MemData.IData.State[no] & (ClrBit(bias)) ) | ((!!value)<<bias)  ); 
		}
		return TRUE;
	}  
	return FALSE;
}

INT8U SetQValue( INT16U OccNo, INT8U Val)
{
	INT16U  no, bias; 

	if( OccNo<=MAX_Q_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8;
		bias=(OccNo-1)%8;
		if(!(g_MemData.QData.ForceMark[no]&OrBit(bias))) 
		{ //set val
		 	g_MemData.QData.Output[no]=(  ( g_MemData.QData.Output[no] & (ClrBit(bias)) ) | ((!!Val)<<bias)  ); 
			/*overwrite State Right now*/
			//g_MemReg.QData.State[no]=(  ( g_MemReg.QData.State[no] & (ClrBit(bias)) ) | ((!!Val)<<bias)  ); 
				return TRUE;
		 }
	}	 
	return FALSE;
}

extern INT8U SetMBValue( INT16U OccNo, INT16U Value )
{
	INT16U  no, bias; 
	if( OccNo<=MAX_MB_CNT && OccNo>0 ) 
	{ 
		no= (OccNo-1)/8; 
		bias=(OccNo-1)%8;
	 	  
		g_MemData.MData.m_pMB[no]=( ( g_MemData.MData.m_pMB[no] & (ClrBit(bias)) ) | ((!!Value)<<bias)  ); 
		 
		return TRUE;
	}  
	return FALSE;
}

/*********************************************************************************************************
** ��������: TestMemData
** ��������: TestMemData
**
** ���������� ���Խӿ�
**
**          
** �䡡��:  extern void
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
extern void TestMemData()
{
	static INT16U IOccNo = 1;
	static INT16U QOccNo = 1;

	static INT16U AIOccNo = 1;
	static INT16U AQOccNo = 1;
	
	static INT16U MBOccNo = 1;
	static INT16U MWOccNo = 1;

	INT8U  Val = 0;
 	 
	INT16U WVal = 0;

 
	SetIVal(IOccNo,0);
	IOccNo ++;

	if (IOccNo <= MAX_I_CNT)
	{
		Val = GetIVal(IOccNo);
		if (Val==0)
		{
			SetIVal(IOccNo,1);
		}	
	} 
	else
	{
		IOccNo = 1;
	}

	SetQValue(QOccNo,0);
	QOccNo ++;

	if (QOccNo <= MAX_Q_CNT)
	{
		Val = GetQVal(QOccNo);
		if (Val==0)
		{
			SetQValue(QOccNo,1);
		}	
	} 
	else
	{
		QOccNo = 1;
	}

	SetMBValue(MBOccNo,0);
	MBOccNo ++;
	if (MBOccNo <= MAX_MB_CNT)
	{
		Val = GetQVal(MBOccNo);
		if (Val==0)
		{
			SetQValue(MBOccNo,1);
		}	
	} 
	else
	{
		MBOccNo = 1;
	} 


	if (AQOccNo <= MAX_AQ_CNT)
	{
		WVal = GetAQVal(AQOccNo);		 
		SetAQVal(AQOccNo,++WVal);	
	} 
	else
	{
		AQOccNo = 1;
	}
	AQOccNo ++;
 
	if (MWOccNo <= MAX_MW_CNT)
	{
		WVal = GetMWVal(MWOccNo);		 
		SetMWVal(MWOccNo,++WVal);	
	} 
	else
	{
		MWOccNo = 1;
	}
	MWOccNo ++;
}

extern  M_DEF * GetMDataPtr( void )
{
	return &g_MemData.MData;
}
