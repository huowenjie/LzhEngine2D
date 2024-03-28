#ifndef __LZH_SYSTOOL_H__
#define __LZH_SYSTOOL_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ϵͳ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ������� ID */
typedef unsigned long LZH_PROCESS_ID;

/* �����߳� ID */
typedef unsigned long LZH_THREAD_ID;

/*-------------------------------------------------------*/

/* ��ȡ��ִ�г���Ŀ¼���ɹ����� LZH_TRUE��ʧ�ܷ��� LZH_FALSE */
LZH_API LZH_BOOL lzh_get_exe_path(char *buff, int *len);

/* ��ȡ����� */
LZH_API int lzh_random_int(int min, int max);
LZH_API float lzh_random_float(float min, float max);

/* ��ȡ���� ID */
LZH_API LZH_PROCESS_ID lzh_getpid();

/* ��ȡ�߳� ID */
LZH_API LZH_THREAD_ID lzh_gettid();

/* ��ȡ��ǰʱ���ı� */
LZH_API LZH_BOOL lzh_get_curtime(const char *format, char *buf, int len);

/* �����ı����� hash code */
LZH_API LZH_HASH_CODE lzh_gen_hash_code(const char *src);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SYSTOOL_H__ */