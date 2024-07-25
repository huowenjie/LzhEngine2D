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

/* �ļ��� */
LZH_API LZH_BOOL lzh_read_file(const char *file, LZH_DATA *data);

/* �ļ�д */
LZH_API LZH_BOOL lzh_write_file(const char *file, const LZH_DATA *data);

/* ��ȡ�ļ���С */
LZH_API LZH_UINT32 lzh_get_file_size(const char *file); 

/*-------------------------------------------------------*/
/* ���빤�� */

/* UTF8 ת��Ϊ UCS2 */
LZH_API LZH_BOOL lzh_utf8_to_ucs2(const LZH_DATA *utf8, LZH_DATA *ucs2);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SYSTOOL_H__ */