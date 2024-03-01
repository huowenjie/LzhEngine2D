#ifndef __LZH_SYSTOOL_H__
#define __LZH_SYSTOOL_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 系统工具 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 获取可执行程序目录，成功返回 LZH_TRUE；失败返回 LZH_FALSE */
LZH_API LZH_BOOL lzh_get_exe_path(char *buff, int *len);

/* 获取随机数 */
LZH_API int lzh_random_int(int min, int max);
LZH_API float lzh_random_float(float min, float max);

#ifdef __cplusplus
}
#endif

#endif /* __LZH_SYSTOOL_H__ */