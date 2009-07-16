//*------------------------------------------------------------------------------------------------
//* �ļ���				: sys_arch.c
//* ��������			: ����ϵͳģ���ӿں���ʵ���ļ�
//* ����    			: ������
//* �汾				: 0.1
//* �������ڡ�ʱ��		: 2006/09/04 10:50
//* �޸����ڡ�ʱ��	    : 
//* �޸�ԭ��			: 
//*------------------------------------------------------------------------------------------------
//*------------------------------------------ ͷ�ļ� -----------------------------------------------
#include <stdlib.h>
#include <string.h>
#include	"../include/lwip/sys.h"
#include	"../include/arch/cc.h"
#include	"../include/arch/sys_arch.h"
//*------------------------------------- �������������� -------------------------------------------
static ST_LWIP_MBOX __staLwIPMBoxs[MBOX_NB];
PST_LWIP_MBOX pstCurFreeMBox;

//* LwIP�߳�ʹ�õĶ�ջ
OS_STK T_LWIP_THREAD_STK[T_LWIP_THREAD_MAX_NB][T_LWIP_THREAD_STKSIZE];

//* sys_timeouts���飬���ڱ���timeouts������׵�ַ
static struct sys_timeouts __staSysTimeouts[T_LWIP_THREAD_MAX_NB + 1];
//*================================================================================================
//*����������������������������������������������������
//*================================================================================================
//*------------------------------------------------------------------------------------------------
//* �������� : sys_sem_new
//* �������� : ����������һ���µ��ź���
//* ��ڲ��� : <count>[in] ָ���ź����ĳ�ʼ״̬
//* ���ڲ��� : �����µ��ź���
//*------------------------------------------------------------------------------------------------
sys_sem_t sys_sem_new(u8_t count)
{
	return OSSemCreate(count);
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_sem_signal
//* �������� : �����ź�
//* ��ڲ��� : <sem>[in] semָ��Ҫ���͵��ź�
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void sys_sem_signal(sys_sem_t sem)
{
	OSSemPost(sem);
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_sem_free
//* �������� : �ͷ��ź���
//* ��ڲ��� : <sem>[in] ָ��Ҫ�ͷŵ��ź���
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void sys_sem_free(sys_sem_t sem)
{
	INT8U	__u8Err;
	
	while(NULL != OSSemDel(sem, OS_DEL_ALWAYS, &__u8Err))
		OSTimeDlyHMSM(0, 0, 0, 100);
}
//*------------------------------------------------------------------------------------------------
//* �������� : __MSToOSTicks
//* �������� : ������ת���ʱ�ӽ���
//* ��ڲ��� : <u16MS>[in] ������
//* ���ڲ��� : ������
//*------------------------------------------------------------------------------------------------
static INT16U __MSToOSTicks(INT16U u16MS)
{
	INT16U	__u16DelayTicks;
	
	if(u16MS != 0)
	{
		__u16DelayTicks = (u16MS * OS_TICKS_PER_SEC)/1000;
		if(__u16DelayTicks < 1)
			__u16DelayTicks = 1;
		else if(__u16DelayTicks > 65535)
			__u16DelayTicks = 65535;
		else;
	}
	else
		__u16DelayTicks = 0;		
		
	return __u16DelayTicks;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_arch_sem_wait
//* �������� : �ȴ��ɲ���semָ�����źŲ������߳�
//* ��ڲ��� :     <sem>[in] semָ��Ҫ���͵��ź�
//*          : <timeout>[in] ָ���ȴ����ʱ�䣨��λΪ���룩��Ϊ0���̻߳�һֱ������ֱ���յ�ָ�����źţ���0��ָ����
//*          :               ����ȴ�ʱ��
//* ���ڲ��� : -                0: ��ָ��ʱ���ڵȵ�ָ���ź�
//*          : - SYS_ARCH_TIMEOUT: ��ָ��ʱ����û�еȵ�ָ���ź�
//*------------------------------------------------------------------------------------------------
u32_t sys_arch_sem_wait(sys_sem_t sem, u32_t timeout)
{	
	INT8U	__u8RtnVal;	
		
	OSSemPend(sem, __MSToOSTicks(timeout), &__u8RtnVal);

	if(__u8RtnVal == OS_NO_ERR)
		return 0;
	else
		return SYS_ARCH_TIMEOUT;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_init
//* �������� : ����sys_arch.txt�ļ�����������Ϊ��ʼ��sys_arch��
//* ��ڲ��� : ��
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void sys_init(void)
{
	INT8U i;
	
	//* �Ȱ�������0
	memset(__staLwIPMBoxs, 0, sizeof(__staLwIPMBoxs));
	
	//* �������������
	for(i=0; i<(MBOX_NB-1); i++)
	{
		//* �������еĸ���Ա������һ��
		__staLwIPMBoxs[i].pstNext = &__staLwIPMBoxs[i+1];
				
		//* �������䣬ϵͳ���뱣֤�����ܹ�˳��������������ִ������ǳ���BUG��Ӧ���ڵ��Խ׶��ų�
		__staLwIPMBoxs[i].hMBox = OSQCreate(__staLwIPMBoxs[i].pvaMsgs, MBOX_SIZE);
	}
	
	//* ���������������һ��Ԫ�أ�����û�н���������
	__staLwIPMBoxs[MBOX_NB-1].hMBox = OSQCreate(__staLwIPMBoxs[MBOX_NB-1].pvaMsgs, MBOX_SIZE);
	
	//* ���������׵�ַ
	pstCurFreeMBox = __staLwIPMBoxs;
	
	//* ��ʼ��sys_timeouts���飬��ÿ�������Ա����������ַ����ΪNULL
	for(i=0; i<(T_LWIP_THREAD_MAX_NB + 1); i++)
		__staSysTimeouts[i].next = NULL;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_mbox_new
//* �������� : ����һ���յ�����
//* ��ڲ��� : ��
//* ���ڲ��� : - != SYS_MBOX_NULL : ��������ɹ�������һ��ָ�����������ָ��
//*          : - = SYS_MBOX_NULL  : ����û������ɹ�
//*------------------------------------------------------------------------------------------------
sys_mbox_t sys_mbox_new(int size)
{
#if OS_CRITICAL_METHOD == 3                     
    OS_CPU_SR  		cpu_sr = 0;
#endif	

	PST_LWIP_MBOX	__pstMBox = SYS_MBOX_NULL;
   	
	OS_ENTER_CRITICAL()		;

		if(pstCurFreeMBox != NULL)
		{
			__pstMBox = pstCurFreeMBox;
			pstCurFreeMBox = __pstMBox->pstNext;
		}
 
	OS_EXIT_CRITICAL()	 ;
	
	return __pstMBox;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_mbox_free
//* �������� : �ͷ����䣬������黹������
//* ��ڲ��� : <mbox>[in] Ҫ�黹������
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void sys_mbox_free(sys_mbox_t mbox)
{	
#if OS_CRITICAL_METHOD == 3                     
    OS_CPU_SR  		cpu_sr = 0;
#endif	
	
	//* Ϊ�˷�ֹ����������������������һ������
	OSQFlush(mbox->hMBox);

	OS_ENTER_CRITICAL()	  ;
	{
		mbox->pstNext = pstCurFreeMBox;
		pstCurFreeMBox = mbox;
	}
	OS_EXIT_CRITICAL() ;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_mbox_post
//* �������� : ����ϢͶ�ݵ�ָ��������
//* ��ڲ��� : <mbox>[in] ָ��ҪͶ�ݵ�����
//*          :  <msg>[in] ָ��ҪͶ�ݵ���Ϣ
//* ���ڲ��� : ��
//*------------------------------------------------------------------------------------------------
void sys_mbox_post(sys_mbox_t mbox, void *msg)
{
	while(OSQPost(mbox->hMBox, msg) == OS_Q_FULL)
		OSTimeDlyHMSM(0, 0, 0, 100);
}

err_t sys_mbox_trypost(sys_mbox_t q, void *msg)
{
  u32_t new_head;
  u32_t ret;
  SYS_ARCH_DECL_PROTECT(lev);

  /* parameter check */
//  LWIP_ASSERT("sys_mbox_free ", q != SYS_MBOX_NULL );
//  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
//  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  SYS_ARCH_PROTECT(lev);

 #if 0
  new_head = q->head + 1;
  if (new_head >= MAX_QUEUE_ENTRIES) {
    new_head = 0;
  }
  if (new_head == q->tail) {
    SYS_ARCH_UNPROTECT(lev);
    return ERR_MEM;
  }
 

  q->q_mem[q->head] = msg;
  q->head = new_head;
  LWIP_ASSERT("mbox is full!", q->head != q->tail);
  ret = ReleaseSemaphore(q->sem, 1, 0);
  LWIP_ASSERT("Error releasing sem", ret != 0);
#endif

  SYS_ARCH_UNPROTECT(lev);
  return ERR_OK;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t q, void **msg)
{
  u32_t ret;
  SYS_ARCH_DECL_PROTECT(lev);
#if 0
  /* parameter check */
  LWIP_ASSERT("sys_mbox_free ", q != SYS_MBOX_NULL );
  LWIP_ASSERT("q->sem != NULL", q->sem != NULL);
  LWIP_ASSERT("q->sem != INVALID_HANDLE_VALUE", q->sem != INVALID_HANDLE_VALUE);

  if ((ret = WaitForSingleObject(q->sem, 0)) == WAIT_OBJECT_0) {
    SYS_ARCH_PROTECT(lev);
    if(msg != NULL) {
      *msg  = q->q_mem[q->tail];
    }

    (q->tail)++;
    if (q->tail >= MAX_QUEUE_ENTRIES) {
      q->tail = 0;
    }
    SYS_ARCH_UNPROTECT(lev);
    return 0;
  }
  else
  {
    LWIP_ASSERT("Error waiting for sem", ret == WAIT_TIMEOUT);
    if(msg != NULL) {
      *msg  = NULL;
    }

    return SYS_ARCH_TIMEOUT;
  }
  #endif 
   return SYS_ARCH_TIMEOUT;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_arch_mbox_fetch
//* �������� : ��ָ�������������Ϣ���ú����������߳�ֱ����ʱ�������������յ�һ����Ϣ
//* ��ڲ��� :    <mbox>[in]  ָ��������Ϣ������
//*          :     <msg>[out] ���������������յ�����Ϣָ��
//*          : <timeout>[in]  ָ���ȴ����յ��ʱ�䣬Ϊ0����һֱ�ȴ�ֱ�����յ���Ϣ����λΪ����
//* ���ڲ��� : -                0: ��ָ��ʱ�����յ���Ϣ
//*          : - SYS_ARCH_TIMEOUT: ��ָ��ʱ����û���յ���Ϣ
//*------------------------------------------------------------------------------------------------
u32_t sys_arch_mbox_fetch(sys_mbox_t mbox, void **msg, u32_t timeout)
{
	INT8U	__u8RtnVal;
	
	if(msg != NULL)
		*msg = OSQPend(mbox->hMBox, __MSToOSTicks(timeout), &__u8RtnVal);
	else 
		OSQPend(mbox->hMBox, __MSToOSTicks(timeout), &__u8RtnVal);

	if(__u8RtnVal == OS_NO_ERR)
		return 0;
	else
		return SYS_ARCH_TIMEOUT;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_thread_new
//* �������� : ����һ�����߳�
//* ��ڲ��� : <thread>[in] ���̵߳���ڵ�ַ
//*          :    <arg>[in] ���ݸ����̵߳Ĳ���
//*          :   <prio>[in] ��LwIPָ�������߳����ȼ���������ȼ���1��ʼ
//* ���ڲ��� : �����߳����ȼ���ע������prio��ͬ�����ֵʵ�ʵ���T_LWIP_THREAD_START_PRIO + prio��
//*          : ����������ɹ��򷵻�0
//*------------------------------------------------------------------------------------------------
//sys_thread_t sys_thread_new(void(*thread)(void *arg), void *arg, int prio)
sys_thread_t sys_thread_new(char *name, void (* thread)(void *arg), void *arg, int stacksize, int prio)
{
	INT8U __u8Prio = 0;
	
	//* ������ȼ�����û�г���ϵͳ����ķ�Χ
	if(prio > 0 && prio <= T_LWIP_THREAD_MAX_NB)
	{
		__u8Prio = T_LWIP_THREAD_START_PRIO + (prio - 1);
	
		if(OS_NO_ERR == OSTaskCreate(thread, arg, &T_LWIP_THREAD_STK[prio-1][T_LWIP_THREAD_STKSIZE-1], __u8Prio))
			return __u8Prio;
		else
            return 0;
	}
	else	
		return 0;
}
//*------------------------------------------------------------------------------------------------
//* �������� : sys_arch_timeouts
//* �������� : ��ȡ��ǰ�߳�ʹ�õ�sys_timeouts�ṹ��ָ��
//* ��ڲ��� : ��
//* ���ڲ��� : ����һ��ָ��ǰ�߳�ʹ�õ�sys_timeouts�ṹ��ָ��
//*------------------------------------------------------------------------------------------------
struct sys_timeouts *sys_arch_timeouts(void)
{
	INT8S __s8Idx;
	
	//* ��ȥ��ʼ�����ƫ������Ҳ����LwIP�ڲ������ȼ�����
	__s8Idx = OSTCBCur->OSTCBPrio - T_LWIP_THREAD_START_PRIO;
	
	//* ��ǰ�߳���ָ����LwIP�߳����ȼ��ŷ�Χ֮��
	if(__s8Idx >= 0 && __s8Idx < T_LWIP_THREAD_MAX_NB)
		return &__staSysTimeouts[__s8Idx];
	
	//* ������������������ǰ�̲߳�����ָ����LwIP�߳����ȼ���Դ֮�ڣ��򷵻�__staSysTimeouts��������һ����Ա
	return &__staSysTimeouts[T_LWIP_THREAD_MAX_NB];
}
