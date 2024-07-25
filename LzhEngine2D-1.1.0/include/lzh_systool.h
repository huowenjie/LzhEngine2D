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

/* 文件读 */
LZH_API LZH_BOOL lzh_read_file(const char *file, LZH_DATA *data);

/* 文件写 */
LZH_API LZH_BOOL lzh_write_file(const char *file, const LZH_DATA *data);

/* 获取文件大小 */
LZH_API LZH_UINT32 lzh_get_file_size(const char *file); 

/*-------------------------------------------------------*/
/* 编码工具 */

/* UTF8 转换为 UCS2 */
LZH_API LZH_BOOL lzh_utf8_to_ucs2(const LZH_DATA *utf8, LZH_DATA *ucs2);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SYSTOOL_H__ */