//*------------------------------------------------------------------------------------------------
//* �ļ���		   : sys_arch.h
//* ��������       : ����ϵͳģ���ӿں���ʵ���ļ���ͷ�ļ�
//* ����    	   : ������
//* �汾		   : 0.1
//* �������ڡ�ʱ�� : 2006/09/04 11:33
//* �޸����ڡ�ʱ�� : 
//* �޸�ԭ��       : 
//*------------------------------------------------------------------------------------------------
#ifndef	__sys_arch_h__
#define	__sys_arch_h__

//*--------------------------------------  �궨�� ------------------------------------------------
#define	MBOX_SIZE					16		//* ָ�������ܹ����յ���Ϣ����
#define	MBOX_NB						8		//* ָ�����������Ҳ����������

#define T_LWIP_THREAD_START_PRIO	7		//* LwIP�߳���ʼ���ȼ���
#define	T_LWIP_THREAD_MAX_NB		1		//* ���������һ���߳�
#define	T_LWIP_THREAD_STKSIZE		512 	//* LwIP�̵߳Ķ�ջ��С

#define	SYS_MBOX_NULL				((void *)0)
#define	SYS_SEM_NULL				(void *)0
//*-------------------------------------- �ṹ���� ------------------------------------------------
/* LwIP����ṹ */
typedef struct stLwIPMBox{
	struct stLwIPMBox 	*pstNext;
	HANDLER 			hMBox;
	void 				*pvaMsgs[MBOX_SIZE];
} ST_LWIP_MBOX, *PST_LWIP_MBOX;
//*------------------------------- һЩ�Զ������������ -------------------------------------------
typedef HANDLER 		sys_sem_t;
typedef PST_LWIP_MBOX 	sys_mbox_t;		//* LwIP����
typedef u8_t			sys_thread_t;	//* LwIP�߳�ID
#endif
