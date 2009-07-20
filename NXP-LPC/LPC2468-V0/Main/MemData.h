/******************************************************************************
ģ����      :  
�ļ���      :  .h
����ļ�    :
ʵ�ֹ���    : �Ĵ����Ķ�д�����ӿ�
�޸ļ�¼    : Ŀǰֻ������һ���ָ����ϵĶ���
------------------------------------------------------------------------------
����        �޸���      �޸�����
2007/9/16
******************************************************************************/


#if !defined(MEM_DATA_DEF_H)
#define MEM_DATA_DEF_H

#include "MemCNST.h" 

//��λ����
typedef struct I_DEF
{   
	INT8U   LastState[MAX_I_CNT/8];   //��ǰ״̬λ      
	INT8U   State[MAX_I_CNT/8];       //��ǰֵ
	INT8U   RawData[MAX_I_CNT/8];     //����ӳ����
	INT8U   ForceMark[MAX_I_CNT/8];   //ǿ��λ 
} I_DEF;

typedef struct AI_DEF
{    
	INT16U   Value[MAX_AI_CNT];       
	INT16U   RawData[MAX_AI_CNT];     
	INT8U  ForceMark[MAX_AI_CNT/8];  
} AI_DEF;

//DO
#define HOLD_TYPE   0
#define HOLD_TYPE1  0xFFFFFFFF
#define MAX_PULSE   600000
typedef struct Q_DEF
{
	INT8U   State[MAX_Q_CNT/8];      /* DO value, occno--occno+7: State.0--State.7 */
//	INT8U   RawState[MAX_Q_CNT/8];   /* DO value, occno--occno+7: State.0--State.7 */
	INT8U   ForceMark[MAX_Q_CNT/8];  /* DO Force mark, occno--occno+7: ForceMark.0--ForceMark.7 */
	INT8U   Output[MAX_Q_CNT/8];     /* DO Output Image, occno--occno+7: Output.0--Output.7 */
//	INT8U   OutputEna[MAX_Q_CNT/8];  /* DO Output Enable, occno--occno+7: OutputEna.0--OutputEna.7 */
	INT8U   CheckEna[MAX_Q_CNT/8];   /* DO Chena Enable, occno--occno+7: OutputEna.0--OutputEna.7 */
	INT32U    PulseTime[MAX_Q_CNT];    /* DO Output Pulse Time in Ticks (10ms), 0xFFFF is HOLD_TYPE, others mean PULSE_TYPE. */
} Q_DEF;

//AO
typedef struct AQ_DEF
{
	INT16U  Value[MAX_AQ_CNT];      /* AO value */
	INT8U   ForceMark[MAX_AQ_CNT/8];			/* AO Force mark, occno--occno+7: ForceMark.0--ForceMark.7 */
	INT16U  Output[MAX_AQ_CNT];     /* AO Output Image */
} AQ_DEF;

//M�Ĵ���
typedef struct M_DEF
{
 	INT8U  m_pMB[MAX_MB_CNT/8];  //λ�Ĵ���
	INT16U m_pMW[MAX_MW_CNT];  //�ּĴ���
	INT32U m_pMD[MAX_MD_CNT];  //˫�ּĴ���

	//���ڵ��籣��
	INT16U m_pMWLast[MAX_MW_CNT]; //���ڵ��籣�棬��һ�ε�ֵ
	INT32U m_pMDLast[MAX_MD_CNT];  //˫�ּĴ���
}M_DEF;

//ϵͳ�Ĵ���
typedef struct S_DEF
{
	INT8U m_pS[MAX_S_CNT/8];  //λ�Ĵ���
	INT16U m_pSW[MAX_SW_CNT];  //�ּĴ��� 
}S_DEF;


typedef struct MEMDB
{	 	 
	I_DEF   IData;            
 	Q_DEF   QData;            
	AI_DEF  AIData;          
  	AQ_DEF  AQData;       
 	M_DEF   MData;        
  	S_DEF   SData;
// 	TM_DEF      pTmData[MAX_TM_CNT];
} MEMDB;
 

//P���Ĳ����ӿ� ��Ӳ���������������

//���뿪���� ��bit��ʽ���� nIdx ��0��ʼ
extern void SetPIBit(INT8U Val, INT16U nIdx );
//���뿪���� ���ֽڷ�ʽ����
extern void SetPIB( void );
//����ģ���� ���ַ�ʽ����
extern void SetPIW( INT16U Val,INT16U nIdx);

//����������ı���ֵ ��˫�ַ�ʽ����
extern void SetPID( INT32U Val, INT16U nIdx );

 
//��ʼ�����б������ýӿ���ϵͳ��ʼ��ʱ����
void InitMemData( void );




//�ⲿ�ֽӿ���Ҫ���߼���ͨ�ŵ��ϲ�Ӧ�õ���
INT8U GetIVal(INT16U OccNo );
INT8U GetIForceMark(INT16U OccNo );
INT8U SetIVal( INT16U OccNo, INT16U value );
INT8U ForceI( INT16U occno, INT16U value );
INT8U UnForceI( INT16U OccNo );
INT8U SetIForceMark( INT16U OccNo, INT16U value );

INT8U GetQVal(INT16U OccNo );
INT8U GetQForceMark(INT16U OccNo );
INT8U SetQForceMark( INT16U OccNo, INT16U value );
INT8U ForceQ( INT16U occno, INT16U value );
INT8U UnForceQ( INT16U OccNo );
INT8U SetPulseQValue( INT16U OccNo, INT8U Val,INT16U PulseTime );

INT16U GetAIVal( INT16U OccNo );
INT8U  GetAIForceMark(INT16U OccNo );
INT8U ForceAI(INT16U OccNo, INT16U Val);
INT8U UnForceAI(INT16U OccNo);
INT8U SetAIForceMark( INT16U OccNo, INT16U value );

INT16U GetAQVal( INT16U OccNo );
INT8U GetAQForceMark(INT16U OccNo );
INT8U ForceAQ(INT16U OccNo, INT16U Val);
INT8U UnForceAQ(INT16U OccNo);
INT8U SetAQVal( INT16U OccNo, INT16U Val);
INT8U SetAQForceMark( INT16U OccNo, INT16U value );
void ScanAQ( INT16U OccNo, INT16U num );

INT8U GetMBVal( INT16U OccNo);
extern INT8U SetMBPluseVal( INT16U occno, INT16U value, INT32U pulseTime );
extern INT8U SetMBValue( INT16U occno, INT16U Value );

INT16U GetMWVal( INT16U occno );
INT8U SetMWVal( INT16U OccNo, INT16U Val );
INT8U GetMWBitVal( INT16U occno, INT16U bit );
INT8U SetMWBitVal(INT16U OccNo,INT16U bit ,INT8U Val);

INT32U GetMDVal( INT16U occno );
INT8U SetMDVal( INT16U OccNo, INT32U Val );
INT8U GetMDBitVal( INT16U occno, INT16U bit );


INT8U GetSVal(INT16U OccNo );
INT8U SetSVal( INT16U OccNo, INT8U Val );

INT16U GetSWVal( INT16U OccNo );
INT8U SetSWValue( INT16U OccNo, INT16U Val );

extern void TestMemData(void );

extern M_DEF * GetMDataPtr( void );

#endif
