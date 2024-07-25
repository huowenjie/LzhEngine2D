#ifndef __LZH_MEM_H__
#define __LZH_MEM_H__

#include "lzh_type.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*===========================================================================*/
/* �ڴ�׷�� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* �ڴ�׷��ͨ�ú� */
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

/* ��ʼ���ڴ���Դ */
LZH_API void mem_create_res();

/* �����ڴ���Դ */
LZH_API void mem_clear_res();

/* ͨ���ڴ������ */
LZH_API void *mem_malloc(size_t len);
LZH_API void *mem_realloc(void *ptr, size_t len);
LZH_API void  mem_free(void *ptr);

/* Я�����Ե��ڴ������ */
LZH_API void *mem_dbg_malloc(size_t len, const char *func, const char *file, int line);
LZH_API void *mem_dbg_realloc(void *ptr, size_t len, const char *func, const char *file, int line);
LZH_API void  mem_dbg_free(void *ptr);

/* �ڴ���� */
LZH_API void mem_clear(void *ptr, size_t len);

/* ��ӡ�ڴ���Ϣ */
LZH_API void mem_print_info();
LZH_API void mem_dbg_print_info();

/* ��ӡ�ڴ����Ϣ */
LZH_API void mem_print_block_list(size_t len);
LZH_API void mem_dbg_print_block_list(size_t len);

/* ��ӡй©��Ϣ */
LZH_API void mem_print_leak_info();
LZH_API void mem_dbg_print_leak_info();

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*===========================================================================*/

#endif /* __LZH_MEM_H__ */
