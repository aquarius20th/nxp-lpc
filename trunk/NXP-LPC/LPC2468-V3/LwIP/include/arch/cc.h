//*------------------------------------------------------------------------------------------------
//* �ļ���				: cc.h
//* ��������			: ��Ӳ��ƽ̨��صĻ����������������������ļ�
//* ����    			: ������
//* �汾				: 0.1
//* �������ڡ�ʱ��		: 2006/09/04 14:26
//* �޸����ڡ�ʱ��	    : 
//* �޸�ԭ��			: 
//*------------------------------------------------------------------------------------------------
#ifndef	__cc_h__
#define	__cc_h__

#include	"ucos_ii.h"
//*------------------------------- �����������Ͷ��� -----------------------------------------------
typedef unsigned char  u8_t;
typedef signed   char  s8_t;
typedef unsigned short u16_t;
typedef signed   short s16_t;
typedef unsigned int   u32_t;
typedef signed   int   s32_t;
typedef u32_t          mem_ptr_t;
typedef	OS_EVENT*	   HANDLER;
//*---------------------------------- ���ú궨�� -------------------------------------------------
//* �ٽ���뱣����
#define	SYS_ARCH_DECL_PROTECT(ulIntStatus)		u32_t  	ulIntStatus = 0;
#define	SYS_ARCH_PROTECT(ulIntStatus)			(ulIntStatus = OSCPUSaveSR());
#define	SYS_ARCH_UNPROTECT(ulIntStatus)			(OSCPURestoreSR(ulIntStatus));
					  

//* �������ݰ��ṹ���װ��
#define	PACK_STRUCT_FIELD(x)	__packed x
#define	PACK_STRUCT_STRUCT
#define	PACK_STRUCT_BEGIN		__packed
#define	PACK_STRUCT_END

#define	LWIP_PROVIDE_ERRNO

#define BYTE_ORDER LITTLE_ENDIAN

#define LWIP_PLATFORM_ASSERT(x) 
                                    


#endif
