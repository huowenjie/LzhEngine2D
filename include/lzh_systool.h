#ifndef __LZH_SYSTOOL_H__
#define __LZH_SYSTOOL_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 系统工具 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 定义进程 ID */
typedef unsigned long LZH_PROCESS_ID;

/* 定义线程 ID */
typedef unsigned long LZH_THREAD_ID;

/*-------------------------------------------------------*/

/* 获取可执行程序目录，成功返回 LZH_TRUE；失败返回 LZH_FALSE */
LZH_API LZH_BOOL lzh_get_exe_path(char *buff, int *len);

/* 获取随机数 */
LZH_API int lzh_random_int(int min, int max);
LZH_API float lzh_random_float(float min, float max);

/* 获取进程 ID */
LZH_API LZH_PROCESS_ID lzh_getpid();

/* 获取线程 ID */
LZH_API LZH_THREAD_ID lzh_gettid();

/* 获取当前时间文本 */
LZH_API LZH_BOOL lzh_get_curtime(const char *format, char *buf, int len);

/* 根据文本生成 hash code */
LZH_API LZH_HASH_CODE lzh_gen_hash_code(const char *src);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SYSTOOL_H__ */