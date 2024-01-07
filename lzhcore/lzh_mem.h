#ifndef __LZH_MEM_H__
#define __LZH_MEM_H__

#include <stddef.h>
#include <stdlib.h>

/*===========================================================================*/
/* 内存追踪 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 内存追踪通用宏 */
#ifdef LZH_MEMORY_DEBUG
    #define LZH_MEM_START create_res()
    #define LZH_MEM_END clear_res()

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

#define LZH_MEM_CLEAR(p, len) mem_clear((p), (len))
#define LZH_MEM_CLEAR_FREE(p, len) (LZH_MEM_CLEAR((p), (len)), LZH_FREE((p)))

/* 初始化内存资源 */
void create_res();

/* 销毁内存资源 */
void clear_res();

/* 通用内存管理函数 */
void *mem_malloc(size_t len);
void *mem_realloc(void *ptr, size_t len);
void  mem_free(void *ptr);

/* 携带调试的内存管理函数 */
void *mem_dbg_malloc(size_t len, const char *func, const char *file, int line);
void *mem_dbg_realloc(void *ptr, size_t len, const char *func, const char *file, int line);
void  mem_dbg_free(void *ptr);

/* 内存擦除 */
void mem_clear(void *ptr, size_t len);

/* 打印内存信息 */
void mem_print_info();
void mem_dbg_print_info();

/* 打印内存块信息 */
void mem_print_block_list(size_t len);
void mem_dbg_print_block_list(size_t len);

/* 打印泄漏信息 */
void mem_print_leak_info();
void mem_dbg_print_leak_info();

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*===========================================================================*/

#endif /* __LZH_MEM_H__ */
