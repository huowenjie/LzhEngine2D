#include <string.h>
#include <stdlib.h>

#include "lzh_mem.h"
#include "lzh_mem_page.h"

/*===========================================================================*/

#if defined(_WINDOWS) 
#include <windows.h>
#else /* Linux */
#include <pthread.h>
#endif /* _WINDOWS & Linux */

#if defined(_WINDOWS)
typedef HANDLE MUTEX_HANDLE;
#else
typedef pthread_mutex_t MUTEX_HANDLE;
#endif /* _WINDOWS & Linux */

static int create_mutex(MUTEX_HANDLE *handle) 
{
#if defined(_WINDOWS)
    MUTEX_HANDLE mutex;

    if (!handle) {
        return MEM_FAILED;
    }

    /* ����һ�������� */
    mutex = CreateMutex(NULL, 0, NULL);
    if (!mutex) {
        return MEM_FAILED;
    }

    *handle = mutex;

#else /* Linux */
    if (!handle) {
        return MEM_FAILED;
    }

    if (pthread_mutex_init(handle, NULL)) {
        return MEM_FAILED;
    }
#endif /* _WINDOWS & Linux */
    return MEM_SUCCESS;
}

static int destroy_mutex(MUTEX_HANDLE *handle)
{
#if defined(_WINDOWS)
    if (!handle || !CloseHandle(*handle)) {
        return MEM_FAILED;
    }

    *handle = NULL;
#else /* Linux */
    if (!handle || pthread_mutex_destroy(handle)) {
        return MEM_FAILED;
    }
#endif /* _WINDOWS & Linux */
    return MEM_SUCCESS;
}

#if defined(_WINDOWS)
#define MEM_LOCK(lock) WaitForSingleObject((lock), INFINITE)
#define MEM_UNLOCK(lock) ReleaseMutex((lock))
#else
#define MEM_LOCK(lock) pthread_mutex_lock(&(lock))
#define MEM_UNLOCK(lock) pthread_mutex_unlock(&(lock))
#endif

/*===========================================================================*/

/* �ڴ滥���� */
static MUTEX_HANDLE mem_lock;

void mem_create_res() 
{
    create_mutex(&mem_lock);
}

void mem_clear_res()
{
    MEM_LOCK(mem_lock);
    clear_mem_pages();
    MEM_UNLOCK(mem_lock);

    destroy_mutex(&mem_lock);
}

void *mem_malloc(size_t len)
{
    unsigned char *ret = NULL;
    int index = get_page_index(len);

    MEM_LOCK(mem_lock);

    /* ��ȡ�����ڴ�ҳ��ַ */
    if (!usable_page_exist(index)) {
        /* �·���һ������ҳ */
        mem_page_malloc(index, 0);
    }

    /* ��ȡ�����ڴ�� */
    ret = alloc_block(len);

    MEM_UNLOCK(mem_lock);
    return ret;
}

void *mem_realloc(void *ptr, size_t len)
{
    int size  = 0;
    int index = 0;
    int index_new = 0;
    int dst_size  = 0;

    unsigned char *ret = NULL;

    if (!ptr) {
        return NULL;
    }

    size = get_addr_block_len(ptr, 0);
    index = get_page_index(size);
    index_new = get_page_index(len);

    if (size < (int)len || index > index_new) {
        MEM_LOCK(mem_lock);

        /* ����ڴ�ҳ */
        if (!usable_page_exist(index_new)) {
            /* �·���һ������ҳ */
            mem_page_malloc(index_new, 0);
        }

        /* ��ȡ�����ڴ�� */
        ret = alloc_block(len);
        dst_size = (int)((size < (int)len) ? size : len);

        if (ret) {
            /* �ڴ濽�� */
            memcpy(ret, ptr, dst_size);

            /* �ͷ�ԭʼ���ڴ�� */
            free_block(ptr, 0);
        }

        MEM_UNLOCK(mem_lock);
        return ret;
    }

    if (index == index_new) {
        return ptr;
    }

    return NULL;
}

void mem_free(void *ptr)
{
    if (!ptr) {
        return;
    }

    MEM_LOCK(mem_lock);
    free_block(ptr, 0);
    MEM_UNLOCK(mem_lock);
}

void *mem_dbg_malloc(size_t len, const char *func, const char *file, int line)
{
    unsigned char *ret  = NULL;
    int index = get_page_index(len);
    
    MEM_LOCK(mem_lock);

    /* ��ȡ�����ڴ�ҳ��ַ */
    if (!usable_page_exist(index)) {
        /* �·���һ������ҳ */
        mem_page_malloc(index, 1);
    }

    /* ��ȡ�����ڴ�� */
    ret = alloc_block_dbg(len, func, file, line);

    MEM_UNLOCK(mem_lock);
    return ret;
}

void *mem_dbg_realloc(void *ptr, size_t len, const char *func, const char *file, int line)
{
    int size  = 0;
    int index = 0;
    int index_new = 0;
    int dst_size  = 0;

    unsigned char *ret = NULL;

    if (!ptr) {
        return NULL;
    }

    size = get_addr_block_len(ptr, 1);
    index = get_page_index(size);
    index_new = get_page_index(len);

    if (size < (int)len || index > index_new) {
        MEM_LOCK(mem_lock);

        /* ����ڴ�ҳ */
        if (!usable_page_exist(index_new)) {
            /* �·���һ������ҳ */
            mem_page_malloc(index_new, 1);
        }

        /* ��ȡ�����ڴ�� */
        ret = alloc_block_dbg(len, func, file, line);

        dst_size = (int)((size < (int)len) ? size : len);

        if (ret) {
            /* �ڴ濽�� */
            memcpy(ret, ptr, dst_size);

            /* �ͷ�ԭʼ���ڴ�� */
            free_block(ptr, 1);
        }

        MEM_UNLOCK(mem_lock);
        return ret;
    }

    if (index == index_new) {
        return ptr;
    }

    return NULL;
}

void *mem_dbg_calloc(size_t num, size_t size, const char *func, const char *file, int line)
{
    size_t len = num * size;
    unsigned char *ret = NULL;
    int index = get_page_index(len);

    MEM_LOCK(mem_lock);

    /* ��ȡ�����ڴ�ҳ��ַ */
    if (!usable_page_exist(index)) {
        /* �·���һ������ҳ */
        mem_page_malloc(index, 1);
    }

    /* ��ȡ�����ڴ�� */
    ret = alloc_block_dbg(len, func, file, line);

    MEM_UNLOCK(mem_lock);
    return ret;
}

void mem_dbg_free(void *ptr)
{
    if (!ptr) {
        return;
    }

    MEM_LOCK(mem_lock);
    free_block(ptr, 1);
    MEM_UNLOCK(mem_lock);
}

void mem_clear(void *ptr, size_t len)
{
#ifdef _WINDOWS
    if (ptr) {
        SecureZeroMemory(ptr, len);
    }
#else /* Linux */
    volatile unsigned char *p =
        (volatile unsigned char *)ptr;

    if (p) {
        while (len-- > 0) {
            *p++ = 0;
        }
    }
#endif /* _WINDOWS & Linux */
}

void mem_print_info()
{
    page_print_basic_info(0);
}

void mem_dbg_print_info()
{
    page_print_basic_info(1);
}

void mem_print_block_list(size_t len)
{
    int index = get_page_index(len);
    page_print_block_list(index, 0);
}

void mem_dbg_print_block_list(size_t len)
{
    int index = get_page_index(len);
    page_print_block_list(index, 1);
}

void mem_print_leak_info()
{
    page_print_allocated_info(0);
}

void mem_dbg_print_leak_info()
{
    page_print_allocated_info(1);
}

/*===========================================================================*/
