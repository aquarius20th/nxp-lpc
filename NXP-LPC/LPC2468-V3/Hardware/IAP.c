
#include "includes.h"
#include "IAP.h" 

//#define		FLASHADDR			0x00050000				/*Ƭ��FLASH��ַ*/
#define  LPC_2468

#ifdef LPC_2468
#define		MAX_FLASH_ADDR		0x0007DFFF				/*�����ʵ�ַ����*/
#else
#define		MAX_FLASH_ADDR		0x0003FFFF				/*�����ʵ�ַ����*/
#endif // LPC_2468 

/* ����CCLKֵ��С����λΪKHz */
#define		IAP_FCCLK	48000

#define 	IAP_ENTER_ADR   0x7FFFFFF1              //  IAP��ڵ�ַ����

static INT32U	paramin[8];		                            // IAP��ڲ���������
static INT32U	paramout[8];	                            // IAP���ڲ���������

//__align(4) 	INT8U TempFile[MAX_FILE_LEN];		
//__align(4)	INT8U Sector_1_File[SECTOR_1_LEN];
//__align(4)	INT8U Sector_2_File[SECTOR_2_LEN];

/*********************************************************************************************************
**��������:  SelSector
**��������:  IAP����������ѡ�񣬴���Ϊ50
**��ڲ���:  sec1	��ʼ����
**			 sec2	��ֹ����
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	SelSector(INT8U	sec1,INT8U	sec2)
{
	paramin[0] = IAP_SELECTOR;	                    // ����������
	paramin[1] = sec1;			                    // ���ò���
	paramin[2] = sec2;
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	return(paramout[0]);	                        // ����״̬��
}
/*********************************************************************************************************
**��������:  RamToFlash
**��������:  ����RAM�����ݵ�FLASH���������51
**��ڲ���:  dst		Ŀ���ַ����FLASH��ʼ��ַ����256�ֽ�Ϊ�ֽ�
**			 src		Դ��ַ����RAM��ַ����ַ�����ֶ���
**			 no		    �����ֽڸ�����Ϊ256/512/1024/4096
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	RamToFlash(INT32U dst, INT32U src, INT32U  no)
{
	paramin[0] = IAP_RAMTOFLASH;	                // ����������
	paramin[1] = dst;				                // ���ò���
	paramin[2] = src;
	paramin[3] = no;
	paramin[4] = IAP_FCCLK;
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	return(paramout[0]);			                // ����״̬��
}
/*********************************************************************************************************
**�������ƣ�EraseSector
**�������ܣ������������������52
**��ڲ�����sec1	��ʼ����
**			sec2	��ֹ����
**���ڲ�����IAP ����״̬��
**			IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	EraseSector(INT32U sec1, INT32U sec2)
{
	paramin[0] = IAP_ERASESECTOR;	                // ����������
	paramin[1] = sec1;				                // ���ò���
	paramin[2] = sec2;
	paramin[3] = IAP_FCCLK;
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	return(paramout[0]);			                // ����״̬��
}
/*********************************************************************************************************
**��������:  BlankCHK
**��������:  ����������������53
**��ڲ���:  sec1	��ʼ����
**			 sec2	��ֹ����
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	BlankCHK(INT32U	sec1, INT32U  sec2)
{
	paramin[0] = IAP_BLANKCHK;	                    // ����������
	paramin[1] = sec1;				                // ���ò���
	paramin[2] = sec2;
	paramin[3] = IAP_FCCLK;
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	return(paramout[0]);			                // ����״̬��
}
/*********************************************************************************************************
**��������:  ReadParID
**��������:  ������ID���������54
**��ڲ���:  ����ID��ַָ��
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	ReadParID(INT32U *Device_ID)
{
	paramin[0] = IAP_READPARTID;	                // ����������
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	*Device_ID = paramout[1];
	return(paramout[0]);			                 // ����״̬��
}
/*********************************************************************************************************
**��������:  BootCodeID
**��������:  ��boot����ID���������55
**��ڲ���:  boot����ID��ַָ��
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	BootCodeID(INT32U *Boot_ID)	
{
	paramin[0] = IAP_BOOTCODEID;	                // ����������
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	*Boot_ID = paramout[1];
	
	return(paramout[0]);			                // ����״̬��
}
/*********************************************************************************************************
**��������:  Compare
**��������:  У�����ݣ��������56
**��ڲ���:  dst		Ŀ���ַ����RAM/FLASH��ʼ��ַ����ַ�����ֶ���
**			 src	 	Դ��ַ����RAM/RAM��ַ����ַ�����ֶ���
**			 no		    �Ƚ��ֽڸ����������ܱ�4����
**���ڲ���:  IAP ����״̬��
**			 IAP����ֵ��paramout��������
********************************************************************************************************/
INT32U	Compare(INT32U	dst, INT32U	src, INT32U	no)
{
	paramin[0] = IAP_COMPARE;	                    // ����������
	paramin[1] = dst;				                // ���ò���
	paramin[2] = src;
	paramin[3] = no;
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	// ����IAP�������
	return(paramout[0]);			                // ����״̬��
}
/*********************************************************************************************************
**��������:  Reinvoke_ISP
**��������:  ���µ���ISP���������57��
**��ڲ���:  ��
**���ڲ���:  ��
********************************************************************************************************/
void  Reinvoke_ISP(void)
{
	paramin[0] = IAP_REINVOKE_ISP;					//  ����������
	(*(void(*)())IAP_ENTER_ADR)(paramin,paramout);	//  ���µ���ISP
} 
/*********************************************************************************************************
**��������:  WriteFlash
**��������:  ��FLASH��д������
**��ڲ���:  dst		Ŀ���ַ����FLASH��ʼ��ַ����ַ������256�ֽڶ��룬����ַ�ĵ�8λ����Ϊ0
**			 src		Դ��ַ����RAM��ַ����ַ�����ֶ��룬����ַ�ĵ���λ����Ϊ0
**			 no		    д���ֽ���������Ϊ256/512/1024/4096
**���ڲ���:  Compare�ķ���ֵ�������ɹ���ȷ����0
********************************************************************************************************/
INT8U	WriteFlash(INT32U  dst, INT32U	src, INT32U	no)
{
	SelSector((dst/0x1000),(dst+no)/0x1000);	// ѡ������
	EraseSector((dst/0x1000),(dst+no)/0x1000);	// ��������
	BlankCHK((dst/0x1000),(dst+no)/0x1000);		// �������
	
	SelSector((dst/0x1000),(dst+no)/0x1000);	// ѡ������
	
	RamToFlash(dst,src,no);			            // д���ݵ�FLASH
	return(Compare(dst,src,no));	            // �Ƚ�����
}
/*
void IAP_WriteFlash(void)
{

	int i;
	for(i=0;i<256;i++)
	{
		SendData[i] = i;
	}
	SelSector(17, 17);					// ѡ������
	EraseSector(17, 17);				// ��������
	SelSector(17, 17);					// ѡ������
	RamToFlash(0x00050000, (INT32U)SendData, 1024);	// д���ݵ�FLASH
	
}
*/
/*-------------------------------------------------------*/
// �������ƣ�FLASH_WriteStr
// ���������INT16U StartAddr��FLASH�ڴ��ַ, 
//			 INT8U * buff���������ָ��, INT16U len�����ݳ���	
// ���������
// ����������д���ݵ�FLASH
/*-------------------------------------------------------*/
// INT8U FLASH_WriteStr(INT16U StartPos, INT8U * buff, INT16U len)
// {
// 	INT16U	i;	
// 	for(i=0;i<MAX_FILE_LEN;i++)			//��ȡԭ�洢���ļ�����
// 	{
// 		TempFile[i] = *(volatile unsigned long *)(FLASHADDR+i); 		
// 	}	
// 				for(i=0;i<len;i++)					//���¶�Ӧλ������
// 	{
// 		TempFile[StartPos+i] = buff[i];
// 	}
// 	
// 	for(i=0;i<SECTOR_1_LEN;i++)			//������1
// 	{
// 		Sector_1_File[i] = TempFile[i];
// 	}
// 		
// 	for(i=0;i<SECTOR_2_LEN;i++)			//������2
// 	{
// 		Sector_2_File[i] = TempFile[SECTOR_1_LEN+i];
// 	}
// 	
// 	OS_ENTER_CRITICAL();	
// 	SelSector(17, 17);					// ѡ������
// 	EraseSector(17, 17);
// 	SelSector(17, 17);					// ѡ������
// 	RamToFlash(SECTOR_1_DESTADDR, (INT32U)Sector_1_File, SECTOR_1_LEN);	// д������1��FLASH	
// 	RamToFlash(SECTOR_2_DESTADDR, (INT32U)Sector_2_File, SECTOR_2_LEN);	// д������2��FLASH	
// 	OS_EXIT_CRITICAL();		
// 	return	TRUE;
// }

/*-------------------------------------------------------*/
// �������ƣ�FLASH_ReadByte
// �������: INT16U StartAddr��FLASH�ڴ��ַ, 
//			void * buff���������ָ��, INT16U len�����ݳ���			
// ������������󷵻�FALSE����ȷ����TURE
// ������������FLASH��ȡһ������
/*-------------------------------------------------------*/
INT8U FLASH_ReadByte(INT32U StartPos, INT8U * buff, INT16U len)
{
	INT32U	i;
	if(StartPos+len>MAX_FLASH_ADDR)
	{
		return FALSE;
	}	 
	
	for(i=0;i<len;i++)
	{
		buff[i] = (*(volatile unsigned long *)(StartPos+i)); 
	}

	return	TRUE;
}
