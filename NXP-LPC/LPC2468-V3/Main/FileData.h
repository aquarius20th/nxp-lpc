/****************************************Copyright (c)**************************************************
**                                �ļ�����ģ��
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
#ifndef _CFG_PARSER_H
#define	_CFG_PARSER_H


#define  MAX_CH_CNT   32    //ÿ��ģ������ͨ������
#define  MAX_MODULE_CNT  4  //��װ�����֧��4�����
#define  MAX_GATAGE_CNT 64  //64�β���
#define  FCB_FLAG   0x4C49



//ģ�����ź�����
#define MAI_420mA   1 // 4��20mA
#define MAI_020mA   2 // 0��20mA	
#define MAI_010mA   3 // 0��10mA
#define MAI_05V   4 // 0��5V	
#define MAI_15V   5 // 1��5V	
 


typedef enum ENCODER_TYPE
{
	INTERFACE_NONE			=0,	//û������
	INTERFACE_PARALLEL		=1,	//�����Ͳ��нӿ�
	INTERFACE_SSI			=2,	//������SSI�ӿ�
	INTERFACE_INCREMENTAL	=3	//������
	//	INTERFACE_AI			=4	//ģ��
}ENCODER_TYPE;


typedef enum GATAGE_UINT
{
	UNIT_MM = 0,   //����
	UNIT_CM = 1,    //����
	UNIT_DEGREE = 2  //��
}GATAGE_UINT;

 
typedef enum GATAGE_CALC
{
	CALC_BY_LINE = 0 ,  //���Լ���
	CALC_BY_TAB  = 1  //����ת����
}GATAGE_CALC;

//��ת����
typedef enum ENCODER_DIRECTION
{
	DIRE_CLOCKWISE =  0,      //˳ʱ�뷽��
	DIRE_ANTI_CLOCKWISE =  1  //��ʱ�뷽��
}ENCODER_DIRECTION;

//�����ͱ������ı�������
typedef enum CODE_TYPE
{
	CODE_GRAY		=0,	//������
	CODE_BCD		    =1,	//BCD��
	CODE_BINARY		=2	//��������
}CODE_TYPE;

typedef enum STOP_BIT
{
	ONE_STOPBIT = 0,
	ONEPOINTFILE_STOPBIT = 1,
	TWO_STOPBIT = 2
}STOP_BIT;

typedef enum PARITY_BIT
{
	NONE_PARITY = 0,  //��У��
	ODD_PARITY = 1,  //��У��
	EVEN_PARITY = 2  //żУ��  
}PARITY_BIT;

typedef struct DEVICE_TIME
{
	INT16U  wYear;
	INT8U	ucMonth;
	INT8U	ucDay;
	INT8U   ucHour;
	INT8U   ucMinute;
	INT16U  wSecond;
	INT16U wMilliseconds;
	INT16U wPad;
}DEVICE_TIME;


//�����ļ����ƿ�
typedef struct FCB 
{
	INT16U  wHeadFlag; //�ļ�ͷ��־ 0x4c 0x49

	//�汾�ţ�װ�ü����޸�����ʱ���Զ�����wBuild������ʱ������ʱ������Դ�ļ����ɣ�
	//�ϴ�ʱ�����˰汾�Ÿ��ǵ������ļ��İ汾����
	INT16U	wMajorVer; //���汾��  �磺1.00 :wMajorVer = 1 wMinorVer= 0��2.01 = wMajorVer = 2 wMinorVer= 1 ���汾�ź�Ӧ�ó����й� 
	INT16U  wMinorVer; //�Ӱ汾�ţ�
	INT16U  wBuild;    //���ļ�����ʱ������ÿ����һ�Σ��汾������1	

	INT16U  wBinBuild;    //��������޸����ã�ÿ�޸�һ�Σ��˰汾��׷��һ�� 	
	INT16U  wPad;

	//�ļ����ص�ʱ�䣬������ʱ����
	DEVICE_TIME            DownLoadTm;
	//ԭʼ�ļ���󱣴�ʱ��
	DEVICE_TIME            SaveTm;		

	//Դ�ļ��ĳ���  Դ�ļ��ǿ�ѡ��
	INT32U    nCfgFileLen;	
	//������ļ�����  BIN�ļ��Ǳ����
	INT32U    nBinLen;     
	//Դ�ļ���crcУ��
	INT16U  wConfCrc;

	INT16U  wBinCrc;

	//�ļ���Ϣ
	INT32U   nCtrlBit;       // bit 0  
	// bit 1	
	// bit 2

}FCB;

typedef struct  tagMB_PORT
{
	INT32U Baud;

	INT8U  StopBit;
	INT8U  DataBit;
	INT8U  ParityBit;

	INT8U  Addr;
} MB_PORT ;//Һ�����޸�

typedef struct tagD_CFG 
{
	INT16U StartAddr;//ӳ�����ʼ��ַ
	INT16U ChCnt;
}D_CFG;

typedef struct  tagA_CFG
{
	INT16U StartAddr;//ӳ�����ʼ��ַ
	INT16U ChCnt;
	INT8U SignalType[MAX_CH_CNT];  //ÿ��ͨ�����ź�����
}A_CFG;

typedef struct  tagIO
{
	INT16U SlotNo;     //��λ��
	INT16U ModuleType; //ģ������
	D_CFG    DiCfg;
	D_CFG    DoCfg;
	A_CFG    AiCfg;
	A_CFG    AoCfg;
}IO;

typedef struct  tagCPU
{
	MB_PORT   Port;
	INT32U    MWCnt;
	INT32U    MDCnt;
}CPU;

typedef struct HD_CFG 
{
	CPU CpuCfg;
	INT32U ModuleCnt;
	IO pIoCfg[MAX_MODULE_CNT];
}SEC_HD_CFG;

 //�ֶβ���
typedef struct GATAGE_PARA
{
	INT32U EncoderVal;
	FP64 Gatage;
}GATAGE_PARA;

typedef struct GATAGE_CFG
{
	FP64  MaxGatage;    //���բ�ſ���
	FP64  MinGatage;    //��Сբ�ſ���

	INT32U  MaxEncoderVal;    //���բ�ſ��ȶ�Ӧ�ı�����ֵ
	INT32U  MinEncoderVal;    //��Сբ�ſ���

	INT8U   UnitType;      //��λ
	INT8U	CalcMethod;    //���㷽ʽ
	INT8U   Direction;     //��ת����
	INT8U   EncodeType;    //�������ͣ�ֻ�Ծ��Ա�������Ч

	INT32U    ParaCnt;  //�ֶβ�������
	GATAGE_PARA  pGatageTab[MAX_GATAGE_CNT];
} SEC_GATAGE_CFG;

typedef struct  BIN_DATA
{
	SEC_HD_CFG HdCfg;
	SEC_GATAGE_CFG  GatageCfg;
}BIN_DATA;

//��flash����������Ϣ
INT32U LoadBinData(INT8U *pBuf,BIN_DATA *pBinData);
//�ڼ���flash�����������Ϣʧ��ʱ�����ô˽ӿ����Ĭ�ϵ�������Ϣ
void InitDefaultBinData(BIN_DATA *pBinData);



  
#endif
