///////////////////////////////////////////////////////////////
//	�� �� �� : ZikuL.h
//	�ļ����� : �ֿ�ͷ�ļ�
//	��    �� :  
//	����ʱ�� : 2008-03-06 14:50:04
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#pragma  once
//�����Ҫ�Լ������ֿ�

typedef struct CN_FONTS_LIB
{
   INT16U code;			//����
   INT8U m[32];			//����
}CN_FONTS_LIB;

#define CN_WORD_NUM 87		//�ṩ�ĺ��ָ���

extern const CN_FONTS_LIB g_WordStock[];

#define	NOFIND 0XFFFF       // û�ҵ�����
extern INT16U FindCnCharIndex(INT16U code);

 
