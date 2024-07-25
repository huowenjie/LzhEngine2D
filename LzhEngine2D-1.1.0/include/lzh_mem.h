#ifndef __LZH_MEM_H__
#define __LZH_MEM_H__

#include "lzh_type.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*===========================================================================*/
/* 内存追踪 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 内存追踪通用宏 */
#ifdef LZH_MEMORY_DEBUG
    #define LZH_MEM_START mem_create_res()
    #define LZH_MEM_END mem_clear_res()

    #define LZH_MALLOC(len) mem_dbg_malloc((len), __FUNCTION__, __FILE__, __LINE__)
    #define LZH_REALLOC(p, len) mem_dbg_realloc((p), (len), __FUNCTION__, __FILE__, __LINE__)
    #define LZH_FREE(p) mem_dbg_free(p)

    #define LZH_PRINT_MEM_INFO mem_dbg_print_info(0)
    #define LZH_PRINT_BLOCK_LIST(len) mem_dbg_print_block_list(0, (len))
    #define LZH_PRINT_LEAK_INFO mem_dbg_print_leak_info(0)
#else
    #define LZH_MEM_START
    #define LZH_MEM_END

    #define LZH_MALLOC(len) malloc(len)
    #define LZH_REALLOC(p, len) realloc((p), (len))
    #define LZH_FREE(p) free(p)

    #define LZH_PRINT_MEM_INFO
    #define LZH_PRINT_BLOCK_LIST
    #define LZH_PRINT_LEAK_INFO
#endif /* USE_MEMORY */

#define LZH_DATA_INIT(data) (data)->value = NULL; (data)->size = 0
#define LZH_DATA_SET(data, val, len) (data)->value = (LZH_BYTE *)(val); (data)->size = (LZH_UINT32)(len)
#define LZH_DATA_MALLOC(data, len) \
    do { \
        (data)->value = LZH_MALLOC((size_t)(len)); \
        (data)->size = (LZH_UINT32)(len); \
        memset((data)->value, 0, (len)); \
    } while (0)

#define LZH_DATA_FREE(data) \
    do { \
        if ((data)->value) { \
            LZH_FREE((data)->value); \
            LZH_DATA_INIT(data); \
        } \
    } while (0)

#define LZH_MEM_CLEAR(p, len) mem_clear((p), (len))
#define LZH_MEM_CLEAR_FREE(p, len) (LZH_MEM_CLEAR((p), (len)), LZH_FREE((p)))

/* 初始化内存资源 */
LZH_API void mem_create_res();

/* 销毁内存资源 */
LZH_API void mem_clear_res();

/* 通用内存管理函数 */
LZH_API void *mem_malloc(size_t len);
LZH_API void *mem_realloc(void *ptr, size_t len);
LZH_API void  mem_free(void *ptr);

/* 携带调试的内存管理函数 */
LZH_API void *mem_dbg_malloc(size_t len, const char *func, const char *file, int line);
LZH_API void *mem_dbg_realloc(void *ptr, size_t len, const char *func, const char *file, int line);
LZH_API void  mem_dbg_free(void *ptr);

/* 内存擦除 */
LZH_API void mem_clear(void *ptr, size_t len);

/* 打印内存信息 */
LZH_API void mem_print_info();
LZH_API void mem_dbg_print_info();

/* 打印内存块信息 */
LZH_API void mem_print_block_list(size_t len);
LZH_API void mem_dbg_print_block_list(size_t len);

/* 打印泄漏信息 */
LZH_API void mem_print_leak_info();
LZH_API void mem_dbg_print_leak_info();

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*===========================================================================*/

#endif /* __LZH_MEM_H__ */
