///////////////////////////////////////////////////////////////
//	�� �� �� : ZikuL.h
//	�ļ����� : �ֿ�ͷ�ļ�
//	��    �� : ��ΰ
//	����ʱ�� : 2008-03-06 14:50:04
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#ifndef ZIKUL_H
#define ZIKUL_H

//�����Ҫ�Լ������ֿ�

typedef struct
{
   INT16U code;			//����
   INT8U m[32];			//����
}WORD_STOCK;

#define CN_WORD_NUM 253		//�ṩ�ĺ��ָ���

extern const WORD_STOCK g_WordStock[];

#define	NOFIND 0XFFFF       // û�ҵ�����
extern INT16U FindCnCharIndex(INT16U code);

#endif	//ZIKUL_H
