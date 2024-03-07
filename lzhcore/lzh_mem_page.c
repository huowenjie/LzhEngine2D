#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "lzh_mem.h"
#include "lzh_link.h"
#include "lzh_mem_page.h"

/*===========================================================================*/

#if defined(_WINDOWS)
#include <windows.h>
#else  /* Linux */
#include <pthread.h>
#endif /* WIN32 & Linux */

/* ��ȡ�߳� ID */
#if defined(WIN32)
#define THREAD_SELF GetCurrentThreadId()
#else /* Linux */
#define THREAD_SELF pthread_self()
#endif /* WIN32 & Linux */

/*===========================================================================*/

#if defined(WIN32)
typedef uintptr_t MEM_UINTPTR;
#else  /* Linux */
typedef unsigned long MEM_UINTPTR;
#endif /* WIN32 & Linux */

#if defined(WIN32)
#define CH_SEP  '\\'
#else /* Linux */
#define CH_SEP  '/'
#endif /* WIN32 & Linux */

/*===========================================================================*/

/* ��ʼ���ڴ�����ֵ */
#define INIT_BLOCK_PADDING 0x00

/* ���ݶ��� */
#define DATA_ALIGN(size, align) \
    (((size) + (align) - 1) & (~((align) - 1)))

/* ��ǰ��Ͷ����ֽ��� */
#define BYTE_ALIGN_COUNT 8

/* 64 λϵͳ�ϲ��� 8 �ֽڶ���ķ�ʽ */
#define INT_ALIGN(size) DATA_ALIGN(size, BYTE_ALIGN_COUNT)

/* ����Ѱַ, ������ɺ�תΪ type */
#define TYPE_OFFSET(type, ptr, offset) \
    ((type)((type)(ptr) + (MEM_UINTPTR)(offset)))

/* ����Ѱַ */
#define TYPE_REOFFSET(type, ptr, offset) \
    ((type)((type)(ptr) - (MEM_UINTPTR)(offset)))

/* �ֽ�ƫ�� */
#define BYTE_OFFSET(ptr, offset) TYPE_OFFSET(unsigned char *, ptr, offset)

/* �����ֽ�ƫ�� */
#define BYTE_REOFFSET(ptr, offset) TYPE_REOFFSET(unsigned char *, ptr, offset)

/* ȡ�������ڴ��еĵ�ַ */
#define MEM_TO_ADDR(ptr) \
    ((unsigned char *)((MEM_UINTPTR)(*((unsigned long long *)(ptr)))))

/* ����ַ addr ���浽��С�� 8 byte ���ڴ���, ���������׵�ַΪ ptr */
#define ADDR_TO_MEM(ptr, addr) \
    *((unsigned long long *)(ptr)) = (unsigned long long)(MEM_UINTPTR)(addr)

/*===========================================================================*/

/*
 * �ڴ����ڴ�ҳ
 *
 * һ���ڴ�ҳ���˰���ͷ�����ݣ����������ɸ��ڴ�飬�����ڴ�ҳ�Ĺ��Ϊ
 * 1k��ÿ���ڴ����� 8 byte ���ڴ棬��ô����ڴ�ҳ�ĽṹΪ��
 *
 * -- MEM_PAGE_HEADER --
 *      0   MEM_BLOCK
 *      1   MEM_BLOCK
 *      2   MEM_BLOCK
 *      3   MEM_BLOCK
 *            ...
 *      254 MEM_BLOCK
 *      255 MEM_BLOCK
 * ----------------------
 *
 * �ڴ�ҳ��Ĺ�����ѭ���·�ʽ��
 *
 * 1.�����ͬ�����ڴ�ҳ���һ���ڴ�ҳ��������ڴ�ҳ�������һ��
 * �ڴ�ҳӳ����ṹ������ʾ��
 * 
 * MEM_PAGE_LINK1 --- PAGE0 -- PAGE1 -- PAGE2 -- ... -- TAIL
 *        |
 * MEM_PAGE_LINK2 --- PAGE0 -- PAGE1 -- PAGE2 -- ... -- TAIL
 *        |
 * MEM_PAGE_LINK3 --- PAGE0 -- PAGE1 -- PAGE2 -- ... -- TAIL
 *        |
 *        .
 *        .
 *        |
 * MEM_PAGE_LINKn --- PAGE0 -- PAGE1 -- PAGE2 -- ... -- TAIL
 *
 * 2.�ڴ�ҳ����ļ�����ʽ��
 *        ��Ҫͨ���ڴ�ҳ��Ϣ������ mem_page_info_index �����ٻ�ȡӳ���
 * �����������������£�
 *        2.1 ���ȣ������ڴ�ҳ������ڴ��Ĵ�С��ȫ�����Ϊ 8 ������
 * ��������size = x * 8, x �ĵ�ֵΪ(0, 1, 2, ���� 128)��
 *        2.2 ����һ�� ���ڴ���Ϣ���������� x������������Ϊ�ñ�������
 * ��������ڴ��СΪ 8 �ֽڣ���Ӧ������Ϊ 1��������ڴ��СΪ 16 ��
 * �ڣ�������Ϊ 2���������Ϊ 128�����������ڴ�Ϊ 1024 �ֽڣ� ͬʱ��
 * ����ȷ������֮ǰ�������Ƚ��û�������ڴ�����ת��Ϊ 8 ��������ȷ��
 * ���Ծ�ȷ��ȡ����ֵ����ʽ���£�
 *        x = ALIGN(size) >> 3��
 *        2.3 �õ� x ֮��ֱ���� ���ڴ���Ϣ������ �в�ѯ���鵽��ֵΪ��
 * ����ƺõ� ���ڴ�������Ϣ�� ��������ͨ�����������Ի�ȡ����Ӧ�� 
 * x ���ڴ�ҳ��Ϣ��
 *        2.4 ����û�������ڴ���� 512����������ʱû���������һ����
 * λ���㷨������ͨ��һ���ж���ֱ�Ӷ�λ�� ���ڴ�������Ϣ�� �����
 * һ��Ԫ�أ���� get_page_index ����ʵ�֣�
 *        2.5 �ڵ����ڴ��ҳ���ʱӦֱ��������Ʊ�ṹ��������Ĵ��룻
 *
 * 3.�ڴ�ҳ����Ĺ���ʽ��
 *        ����ĵ�βָ������ָ���������ݣ�Ҳ���� status = MEM_PAGE_STATUS_FULL��
 * ���ڴ�ҳ��ͷָ����ָ������������ڴ���������ڴ�ҳ����������ڴ�ҳ
 * �ڵ����ȷ��ڵ�ǰ����ĵڶ����ڵ㣬���ǵ�ǰ�����ͷ���ҳ���� 
 * MEM_PAGE_STATUS_FULL ״̬���ߵ�ǰ����û���κ��ڴ�ҳ�� �����Ļ���֤��
 * �����ڴ�ʱ������ O(1) ��ʱ��ȡ����Ӧ���ڴ�ҳ��ͬʱ�����ͷ��ڴ�ʱ��
 * ������ڿ����ڴ�״̬���ڴ�ҳ����һ������ʱ����֮�ͷŽ�����ϵͳ��
 * ��Լ�ڴ棻
 *
 * 4.�ڴ�ҳ�Ĺ���ʽ��
 *        ��ʼ���ڴ�ҳʱ��ÿ���ڴ����¼��һ�������ڴ��ĵ�ַ��ͨ��
 * ����ֱַ��д���������ķ�ʽ�����ڴ�ҳ���¼��һ�������ڴ�飻�ͷ�
 * �ڴ��ʱ���ڴ�ҳ���¼��ǰ�ͷŵ��ڴ����׵�ַ��ͬʱ����ǰ��¼��
 * �����ڴ��ĵ�ַд��������ͷŵ��ڴ������������൱��һ�������
 * ��Ĳ��룩��������֤��һ�������ڴ��ʱ������� O(1) ��ʱ����ٶ�
 * λ�����ڴ�顣
 */
struct mem_page_st {
    MEM_PAGE *prev;             /* ��һҳ */
    MEM_PAGE *next;             /* ��һҳ */

    unsigned char type;         /* �ڴ�ҳ���� */
    unsigned char status;       /* �ڴ�ҳ״̬ */
    unsigned char using_count;  /* �ѷ�����ڴ������ */
    unsigned char block_num;    /* ��ǰ�ڴ�ҳ�ڴ������ */
    int block_head;             /* ��λ�ڴ��ͷ����С */
    int block_data;             /* ��λ�ڴ�����ݴ�С */
    int alloc_size;             /* ��ǰ��������ݿռ��С */

    MEM_BLOCK *idle;            /* ��ǰ���е��ڴ���ַ */
    MEM_PAGE *head_addr;        /* �ڴ�ҳ��ͷ����ַ */
};

/* �ڴ�� */
struct mem_block_st {
    MEM_PAGE *page;             /* ���� page */
    int status;                 /* �ڴ��״̬ */
};

#define DATE_INFO_LENGTH 32
#define FILE_INFO_LENGTH 64
#define FUNC_INFO_LENGTH 64

/* �����ڴ�� */
struct mem_block_dbg_st {
    MEM_PAGE *page;             /* �ڴ�ҳ�ĵ�ַ */
    int status;                 /* �ڴ��״̬ */
    int line;                   /* ���� malloc ������ */
    unsigned long long thread;  /* ���� malloc ���߳� */

    char date[DATE_INFO_LENGTH]; /* ����ʱ�䣬��ʽΪ yyyy-mm-dd hh:MM:ss */
    char file[FILE_INFO_LENGTH]; /* �����ļ� */
    char func[FUNC_INFO_LENGTH]; /* �������� */
};

/* �ڴ�ҳ�����̳��� LINK */
struct mem_page_link_st {
    MEM_PAGE *head;             /* ��ͷ */
    MEM_PAGE *tail;             /* ��β */

    int count;                  /* �ڵ����� */
    int idle_num;               /* �п����ڴ��Ľڵ����� */
};

/* �ڴ�ҳ��Ϣ */
typedef struct {
    int page_type;              /* �ڴ�ҳ���� */
    int block_size;             /* ��λ�ڴ��ߴ� */
    int total_size;             /* �����ڴ��Ĵ�С֮�� */
    int block_num;              /* ÿһҳ�ڴ������� */
} MEM_PAGE_INFO;

/*===========================================================================*/

#define MEM_PAGE_BLOCK_INFO_COUNT 15    /* �ڴ�ҳ��Ϣ������ */
#define MEM_PAGE_MAP_INDEX_COUNT 65     /* �ڴ�ҳӳ������������������� 0 �� ���ڴ� */
#define MEM_PAGE_MIN_BLOCK 0            /* �ڴ�ҳ�ɸ��õ���С�ڴ�������С */
#define MEM_PAGE_MAX_BLOCK 512          /* �ڴ�ҳ�ɸ��õ�����ڴ�������С */
#define MEM_PAGE_MAX_IDLE 2             /* ÿ������������ҳ���� */

/*===========================================================================*/

/*
 * �ڴ�ҳ��Ϣ���������ڿ��ٲ��Ҷ�Ӧ���ڴ�������Ϣ��������
 * ����Ϊ�����볤�ȣ�����֮�� / 8 ��ֵΪ mem_page_info_list ���
 * ������
 */
static const unsigned char mem_page_info_index[MEM_PAGE_MAP_INDEX_COUNT] = {
     0,
     1,  2,  3,  3,  4,  4,  4,  4,    /*   1 ~ 8   */
     5,  5,  5,  5,  6,  6,  6,  6,    /*   9 ~ 16  */    
     7,  7,  7,  7,  8,  8,  8,  8,    /*  17 ~ 24  */
     9,  9,  9,  9,  9,  9,  9,  9,    /*  25 ~ 32  */
    10, 10, 10, 10, 10, 10, 10, 10,    /*  33 ~ 40  */
    11, 11, 11, 11, 11, 11, 11, 11,    /*  41 ~ 48  */
    12, 12, 12, 12, 12, 12, 12, 12,    /*  49 ~ 56  */
    13, 13, 13, 13, 13, 13, 13, 13     /*  57 ~ 64  */
};

/* �ڴ�ҳ������Ϣ�� */
static const MEM_PAGE_INFO mem_page_info_list[MEM_PAGE_BLOCK_INFO_COUNT] = {
    /* �ڴ�ҳ����        ��λ�ڴ��ߴ�        �ڴ���ܴ�С    �ڴ������*/
    { MEM_PAGE_TYPE_ZERO,        8,                   8,              1    },    /* 0  */
    { MEM_PAGE_TYPE_1K,          8,                1024,            128    },    /* 1  */
    { MEM_PAGE_TYPE_1K,         16,                1024,             64    },    /* 2  */
    { MEM_PAGE_TYPE_1K,         32,                1024,             32    },    /* 3  */
    { MEM_PAGE_TYPE_1K,         64,                1024,             16    },    /* 4  */
    { MEM_PAGE_TYPE_1K,         96,                1024,             10    },    /* 5  */
    { MEM_PAGE_TYPE_1K,        128,                1024,              8    },    /* 6  */
    { MEM_PAGE_TYPE_2K,        160,                2048,             12    },    /* 7  */
    { MEM_PAGE_TYPE_2K,        192,                2048,             10    },    /* 8  */
    { MEM_PAGE_TYPE_2K,        256,                2048,              8    },    /* 9  */
    { MEM_PAGE_TYPE_4K,        320,                4096,             12    },    /* 10 */
    { MEM_PAGE_TYPE_4K,        384,                4096,             10    },    /* 11 */
    { MEM_PAGE_TYPE_4K,        448,                4096,              9    },    /* 12 */
    { MEM_PAGE_TYPE_4K,        512,                4096,              8    },    /* 13 */
    { MEM_PAGE_TYPE_LARGE,      8,                   8,               1    },    /* 14 */
};

/* �ڴ�ҳӳ��� */
static MEM_PAGE_LINK mem_page_map[MEM_PAGE_BLOCK_INFO_COUNT] = { { 0 } };

/*===========================================================================*/

/* ��ʼ���ڴ�ҳ */
static void mem_page_initialize(int index, MEM_PAGE *page, int dbg);
static void mem_page_terminate(MEM_PAGE *page);

/* ��ȡ�ڴ�� */
static MEM_BLOCK *get_block(void *address, int dbg);

/* ��� dbg �ڴ�� */
static void pad_dbg_block(
    MEM_BLOCK_DBG *block, const char *func, const char *file, int line);

/* ��ȡ�ڴ�ҳ����, ���ڴ�ӡ��Ϣ */
static const char *get_page_name(unsigned char type);
static const char *get_status_name(unsigned char status);
static const char *get_block_status_name(int status);

/* ��ӡй©��Ϣ */
static int print_leak_info(MEM_PAGE *page, int dbg, char *buff);

/* ��ӡ������Ϣ */
static void print_link_info(
    MEM_PAGE_LINK *link, int index, char *buff);

/* ��ӡ�ڴ�ҳ��Ϣ */
static void print_page_info(MEM_PAGE *page, char *buff);

/* ����ڴ���Ϣ */
static void output_mem_info_std(const char *info);

/* ��ȡ��ǰ��ʽ��ʱ�� */
int get_curtime(const char *format, char *buf, int len);

/*===========================================================================*/

int get_page_index(size_t len)
{
    /* ��Ϣ���������� */
    int index = 0;

    if (len > MEM_PAGE_MAX_BLOCK) {
        return MEM_PAGE_BLOCK_INFO_COUNT - 1;
    }

    index = ((int)INT_ALIGN(len) >> 3);

    /* �����ڴ��ֽ�����ȡ�ڴ���Ϣ������ */
    return mem_page_info_index[index];
}

int get_page_index_ex(MEM_PAGE *page)
{
    int index = 0;

    /* �ڴ�ҳΪ 0 �ڴ����ͻ��ߴ��ڴ����ͣ�index �ֶ�ָ�� */
    if (!page || page->type == MEM_PAGE_TYPE_ZERO) {
        index = 0;
    } else if (page->type == MEM_PAGE_TYPE_LARGE) {
        index = MEM_PAGE_BLOCK_INFO_COUNT - 1;
    } else {
        index = get_page_index(page->block_data);
    }

    return index;
}

int usable_page_exist(int index)
{
    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return 0;
    }

    if (!mem_page_map[index].count || 
        !mem_page_map[index].head) {
        return 0;
    }

    if ((mem_page_map[index].head)->status == MEM_PAGE_STATUS_FULL) {
        return 0;
    }

    return 1;
}

int mem_page_malloc(int index, int dbg)
{
    int ret = MEM_SUCCESS;
    int page_size = 0;
    int block_size = 0;

    MEM_PAGE_LINK *link = NULL;
    MEM_PAGE *idle_page = NULL;

    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return MEM_FAILED;
    }

    block_size = dbg ? sizeof(MEM_BLOCK_DBG) : sizeof(MEM_BLOCK);

    /* ��ȡ��Ӧ���ڴ�ҳ���� */
    link = mem_page_map + index;

    /* �ڴ�ҳ��С = �ڴ���ܴ�С + ÿ���ڴ��ͷ����С + �ڴ�ҳͷ����С */
    page_size = 
        mem_page_info_list[index].total_size + 
        block_size * mem_page_info_list[index].block_num +
        sizeof(MEM_PAGE);

    /* �����ڴ�ҳ */
    idle_page = (MEM_PAGE *)malloc(page_size);
    assert(idle_page);

    memset(idle_page, 0, page_size);
    mem_page_initialize(index, idle_page, dbg);

    /* 
     * ���´������ڴ�ҳ���ӵ�ͷ���֮���λ�ã��������û�нڵ㣬
     * ���߽ڵ�״̬��Ϊ FULL�������½ڵ���Ϊ����ͷ��㡣
     */
    if (!link->head || link->head->status == MEM_PAGE_STATUS_FULL) {
        ret = link_insert((LINK *)link, 0, (LINK_NODE *)idle_page);
    } else {
        ret = link_insert_after(
            (LINK *)link, (LINK_NODE *)link->head, (LINK_NODE *)idle_page);
    }

    if (ret == MEM_SUCCESS) {
        link->idle_num++;
    }

    return ret;
}

int mem_page_free(MEM_PAGE *page)
{
    int index = 0;
    MEM_PAGE_LINK *link = NULL;

    if (!page) {
        return MEM_FAILED;
    }

    index = get_page_index_ex(page);
    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return MEM_FAILED;
    }

    link = mem_page_map + index;
    link_remove_force(
            (LINK *)link, (LINK_NODE *)page);

    if (page->status == MEM_PAGE_STATUS_IDLE) {
        link->idle_num--;
    }

    mem_page_terminate(page);
    free(page);

    return MEM_SUCCESS;
}

void clear_mem_pages()
{
    int i;

    MEM_PAGE_LINK *link = NULL;
    unsigned char *tmp  = NULL;

    for (i = 0; i < MEM_PAGE_BLOCK_INFO_COUNT; i++) {
        link = mem_page_map + i;

        while (link->count > 0) {
            if (link->head->type == MEM_PAGE_TYPE_ZERO ||
                link->head->type == MEM_PAGE_TYPE_LARGE) {
                /* ָ��ƫ�����ڴ��������� */
                tmp = BYTE_OFFSET(link->head, sizeof(MEM_PAGE) + link->head->block_head);

                /* ��ȡ���ڴ�� 0 �ڴ�ĵ�ַ */
                tmp = MEM_TO_ADDR(tmp);
                if (tmp) {
                    tmp = BYTE_OFFSET(tmp, link->head->block_head);
                    free_block(tmp, link->head->block_head != sizeof(MEM_BLOCK));
                } 
            }

            mem_page_free(link->head);
        }

        link->idle_num = 0;
        link_reset((LINK *)link);
    }
}

void *alloc_block(size_t len)
{
    size_t size = 0;
    int index = 0;

    unsigned char *ret  = NULL;
    MEM_PAGE *page = NULL;
    MEM_PAGE_LINK *link = NULL;

    MEM_BLOCK_DBG *block_dbg  = NULL;
    MEM_BLOCK *block = NULL;

    index = get_page_index(len);
    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return NULL;
    }

    link = mem_page_map + index;

    if (!link->count || !link->head) {
        return NULL;
    }

    page = link->head;
    if (page->status == MEM_PAGE_STATUS_FULL) {
        return NULL;
    }

    /*
     * �����ǰҳ�����ڴ��ﵽ���ޣ��򽫵�ǰ���ڴ�ҳ
     * �����������β
     */
    if (page->using_count == (page->block_num - 1)) {
        if (link->count > 1 && link->tail != page) {
            link_remove_force((LINK *)link, (LINK_NODE *)page);
            link_push((LINK *)link, (LINK_NODE *)page);
        }

        page->status = MEM_PAGE_STATUS_FULL;
    }

    if (!page->using_count) {
        link->idle_num--;
        if (page->block_num > 1) {
            page->status = MEM_PAGE_STATUS_USING;
        }
    }

    page->using_count++;
    page->alloc_size += (page->block_data + page->block_head);

    /* ��λ�������ڴ�� */
    ret = (unsigned char *)page->idle;
    if (!ret) {
        return NULL;
    }

    /* �޸��ڴ���״̬ */
    block = (MEM_BLOCK *)ret;
    block->status = MEM_BLOCK_STATUS_USING;

    /* ��λ��������λ�� */
    ret = BYTE_OFFSET(ret, page->block_head);

    /*
     * ��ȡ��һ�������ڴ���ַ�����棺
     * �ڴ�ҳ����ʱ����������
     */
    if (page->status != MEM_PAGE_STATUS_FULL) {
        page->idle = (MEM_BLOCK *)MEM_TO_ADDR(ret);
    } else {
        page->idle = NULL;
    }

    /* 
     * ���� 0 �ڴ�ʹ��ڴ�Ĵ���ʽ��
     *
     * ֱ�ӷ���һ������ͷ���ڴ�飬��������ڴ��׵�ַ����
     * ���ڴ�ҳ�� 8 �ֽڵ��ڴ���С�
     */
    if (page->type == MEM_PAGE_TYPE_ZERO ||
        page->type == MEM_PAGE_TYPE_LARGE) {
        size = page->block_head + len;
        block = (MEM_BLOCK *)malloc(size);
        assert(block);

        block->page = page;
        block->status = MEM_BLOCK_STATUS_USING;

        /* ��� debug �ڴ�� */
        if (page->block_head == sizeof(MEM_BLOCK_DBG)) {
            block_dbg = (MEM_BLOCK_DBG *)block;
            pad_dbg_block(block_dbg, __FUNCTION__, __FILE__, __LINE__);
        }

        /* ���·�����ڴ��ַ���浽�ڴ�ҳ�� 8 �ֽ��ڴ���� */
        ADDR_TO_MEM(ret, block);

        /* �����ڴ�ҳ��Ϣ */
        page->alloc_size += ((int)size);

        /* ��ȡ���ڴ���������ַ */
        ret = (unsigned char *)block;
        ret = BYTE_OFFSET(ret, page->block_head);

        /* ��ʼ�������ڴ�� */
        memset(ret, INIT_BLOCK_PADDING, len);
    } else {
        /* ��ʼ�������ڴ�� */
        memset(ret, INIT_BLOCK_PADDING, (size_t)page->block_data);
    }

    return ret;
}

void *alloc_block_dbg(size_t len, const char *func, const char *file, int line)
{
    MEM_PAGE *page  = NULL;
    MEM_BLOCK_DBG *block = NULL;
    unsigned char *ret = alloc_block(len);

    if (!ret) {
        return NULL;
    }

    block = (MEM_BLOCK_DBG *)get_block(ret, 1);
    assert(block);

    page = block->page;
    assert(page == page->head_addr);

    if (page->type == MEM_PAGE_TYPE_ZERO ||
        page->type == MEM_PAGE_TYPE_LARGE) {
        block = (MEM_BLOCK_DBG *)BYTE_OFFSET(page, sizeof(MEM_PAGE));
    }

    pad_dbg_block(block, func, file, line);
    return ret;
}

void free_block(void *address, int dbg)
{
    int index = 0;

    MEM_UINTPTR idle = 0;
    MEM_PAGE *page = NULL;
    unsigned char *cursor = NULL;
    MEM_PAGE_LINK *link = NULL;

    MEM_BLOCK_DBG *block_dbg = NULL;
    MEM_BLOCK *block = NULL;

    if (!address) {
        return;
    }

    block = get_block(address, dbg);
    assert(block);

    cursor = (unsigned char *)block;
    page   = block->page;
    assert(page->head_addr == page);

    if (!page->using_count || !page->alloc_size) {
        return;
    }

    index = get_page_index_ex(page);
    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return;
    }

    link = mem_page_map + index;

    /* ���ڴ���� 0 �ڴ�ֱ���ͷ��ڴ棬ͬʱ��д���ڴ�ҳ���ڴ������ */
    if (page->type == MEM_PAGE_TYPE_ZERO ||
        page->type == MEM_PAGE_TYPE_LARGE) {
        free(cursor);

        /* ���¶�λ block λ�� */
        block  = (MEM_BLOCK *)BYTE_OFFSET(page, sizeof(MEM_PAGE));
        cursor = (unsigned char *)block;

        /* ��������£�����һ���ڴ�ҳֻ����һ���ڴ�飬���Կ���ֱ�Ӹ� 0 */
        page->alloc_size = 0;

        /* ָ��ƫ���������� */
        cursor = BYTE_OFFSET(cursor, page->block_head);

        /* ��д�û��ڴ����� */
        memset(cursor, INIT_BLOCK_PADDING, (size_t)page->block_data);
    } else {
        /* ָ��ƫ���������� */
        cursor = BYTE_OFFSET(cursor, page->block_head);

        /* ��д�û��ڴ����� */
        memset(cursor, INIT_BLOCK_PADDING, (size_t)page->block_data);

        /* 
         * ����һ������λ�ü�¼�ڵ�ǰ�ڴ����ڴ�����Ȼ��
         * ��ǰ�ڴ����Ϊ���п鸴��, ����ڴ�ҳ��������������
         */
        if (page->status != MEM_PAGE_STATUS_FULL) {
            idle = (MEM_UINTPTR)page->idle;
            ADDR_TO_MEM(cursor, idle);
        }

        page->alloc_size -= (page->block_data + page->block_head);        
    }

    /* ��ԭ�ڴ��״̬ */
    block->status = MEM_BLOCK_STATUS_IDLE;

    /* dbg ģʽ��ԭ�ڴ��ͷ����Ϣ���� */
    if (dbg) {
        block_dbg = (MEM_BLOCK_DBG *)block;
        pad_dbg_block(block_dbg, NULL, NULL, 0);
    }

    /* �����ڴ�ҳ��Ϣ */
    page->idle = block;
    page->using_count--;

    /*
     * ���۵�ǰ�ڴ�ҳ��ʲô״̬��ֱ�ӽ���ǰ�ڴ�ҳ����
     * �ڴ������ͷ��㡣
     */
    if (link->count > 1 && link->head != page) {
        link_remove_force((LINK *)link, (LINK_NODE *)page);
        link_insert((LINK *)link, 0, (LINK_NODE *)page);
    }

    /* �����ڴ�ҳ��״̬ */
    if (page->using_count == (page->block_num - 1)) {
        page->status = MEM_PAGE_STATUS_USING;
    }

    if (!page->using_count) {
        link->idle_num++;
        page->status = MEM_PAGE_STATUS_IDLE;

        /* ����һ������ҳ�����ͷű�ҳ���Խ�ʡ�ռ� */
        if (link->idle_num > MEM_PAGE_MAX_IDLE) {
            mem_page_free(page);
        }
    }
}

void page_print_basic_info(int dbg)
{
    int i;
    int j;

    char buff[128] = { 0 };

    MEM_PAGE_LINK *link = NULL;
    MEM_PAGE *page = NULL;

    output_mem_info_std("<============================basic check============================>\n");

    for (i = 0; i < MEM_PAGE_BLOCK_INFO_COUNT; i++) {
        link = mem_page_map + i;

        if(link->count > 0) {
            sprintf(buff, "<----------------------link %02d---------------------->\n", i);
            output_mem_info_std(buff);

            /* ��ӡ������Ϣ */
            print_link_info(link, i, buff);
            page = link->head;

            for (j = 0; j < link->count; j++) {
                if (!page) {
                    output_mem_info_std("page = null!!!\n");
                    break;
                }

                /* ��ӡ�ڴ�ҳ��Ϣ */
                output_mem_info_std("---------------------- page -----------------------\n");
                print_page_info(page, buff);

                /* ��ӡ�ڴ�й©��Ϣ */
                if (page->using_count > 0) {
                    print_leak_info(page, dbg, buff);
                }
                page = page->next;
            }

            page = NULL;
            sprintf(buff, "<----------------------link %02d---------------------->\n", i);
            output_mem_info_std(buff);
        }
    }

    output_mem_info_std("<============================basic check============================>\n");
}

void page_print_block_list(int index, int dbg)
{
    int i;
    int j;

    char buff[128] = { 0 };

    MEM_PAGE_LINK *link = NULL;
    MEM_PAGE *page = NULL;
    MEM_BLOCK *block = NULL;
    unsigned char *cursor = NULL;

    int size = 0;

    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return;
    }

    link = mem_page_map + index;
    page = link->head;

    /* ������Ϣ */
    sprintf(buff, "<----------------------link %02d---------------------->\n", index);
    output_mem_info_std(buff);

    print_link_info(link, index, buff);

    for (i = 0; i < link->count; i++) {
        if (!page) {
            output_mem_info_std("page = null!!!\n");
            break;
        }

        output_mem_info_std("---------------------- page -----------------------\n");
        print_page_info(page, buff);

        block = (MEM_BLOCK *)BYTE_OFFSET(page, sizeof(MEM_PAGE));

        output_mem_info_std("---------------------- block -----------------------\n");

        for (j = 0; j < page->block_num; j++) {
            sprintf(buff, "(%d) [%p] -- status = %s size = %d\n", 
                j, block, get_block_status_name(block->status), page->block_data);
            output_mem_info_std(buff);

            if (page->type == MEM_PAGE_TYPE_ZERO ||
                page->type == MEM_PAGE_TYPE_LARGE) {
                if (page->alloc_size) {
                    size = 
                        page->alloc_size -
                        page->block_head -
                        page->block_head -
                        page->block_data;

                    cursor = BYTE_OFFSET(block, page->block_head);
                    block = (MEM_BLOCK *)MEM_TO_ADDR(cursor);

                    sprintf(buff, "(%d) [%p] -- status = %s size = %d\n", 
                        j + 1, block, get_block_status_name(block->status), size);
                    output_mem_info_std(buff);
                }
            } else {
                block = (MEM_BLOCK *)BYTE_OFFSET(block, page->block_head + page->block_data);
            }
        }

        output_mem_info_std("---------------------- block -----------------------\n");
        page = page->next;
    }

    sprintf(buff, "<----------------------link %02d---------------------->\n", index);
    output_mem_info_std(buff);
}

void page_print_allocated_info(int dbg)
{
    int i;
    int j;
    int size = 0;

    char buff[128] = { 0 };

    MEM_PAGE_LINK *link = NULL;
    MEM_PAGE *page = NULL;

    output_mem_info_std("<============================alloc check============================>\n");

    /* �����ڴ����� */
    for (i = 0; i < MEM_PAGE_BLOCK_INFO_COUNT; i++) {
        link = mem_page_map + i;

        if(link->count > 0) {
            page = link->head;

            for (j = 0; j < link->count; j++) {
                if (!page) {
                    break;
                }

                /* ��ӡ�ڴ�й©��Ϣ */
                if (page->using_count > 0) {
                    /* ��ӡ�ڴ�ҳ��Ϣ */
                    print_page_info(page, buff);
                    size += print_leak_info(page, dbg, buff);
                }

                page = page->next;
            }

            page = NULL;
        }
    }

    if (!size) {
        output_mem_info_std("No leak!\n");
    }

    output_mem_info_std("<============================alloc check============================>\n");
}

int get_addr_block_len(void *ptr, int dbg)
{
    MEM_BLOCK *block = NULL;
    MEM_PAGE *page = NULL;
    int ret = 0;

    if (!ptr) {
        return 0;
    }
    
    block = get_block(ptr, dbg);
    if (!block) {
        return 0;
    }

    page = block->page;
    assert(page->head_addr == page);

    /* 
     * 0 �ڴ�ʹ��ڴ���ڴ�鷵��ʵ��������ڴ���С,
     * �����ܵ������С - �ڴ��ͷ����С
     */
    if (page->type == MEM_PAGE_TYPE_ZERO ||
        page->type == MEM_PAGE_TYPE_LARGE) {
        ret = 
            page->alloc_size -
            page->block_head -
            page->block_head -
            page->block_data;
    } else {
        ret = page->block_data;
    }

    return ret;
}

/*===========================================================================*/

void mem_page_initialize(int index, MEM_PAGE *page, int dbg)
{
    MEM_PAGE *head = NULL;
    MEM_BLOCK *block = NULL;
    unsigned char *cursor = NULL;

    int block_size = dbg ? sizeof(MEM_BLOCK_DBG) : sizeof(MEM_BLOCK);
    int page_size = sizeof(MEM_PAGE);
    int block_offset = 0;

    unsigned char i;

    if ((index > MEM_PAGE_BLOCK_INFO_COUNT - 1) || !page) {
        return;
    }

    head = page;

    head->prev = NULL;
    head->next = NULL;

    head->type = mem_page_info_list[index].page_type;
    head->status = MEM_PAGE_STATUS_IDLE;
    head->using_count = 0;
    head->block_num = mem_page_info_list[index].block_num;
    head->block_head = block_size;
    head->block_data = mem_page_info_list[index].block_size;
    head->alloc_size = 0;
    head->idle = (MEM_BLOCK *)BYTE_OFFSET(head, page_size);
    head->head_addr = head;

    cursor = BYTE_OFFSET(head, page_size);
    block_offset = head->block_head + head->block_data;

    /* 
     * ����ǰ n - 1 ���ڴ���ƫ��ֵ��ͬʱ��ÿ���ڴ���ǰ 8 ���ֽ�
     * ���Ϊ��һ���ڴ����׵�ַ�����һ���ڴ�鲻�����, ���еĵ�
     * ַ���� 64 λ�������档
     */
    for (i = 0; i < head->block_num - 1; i++) {
        block = (MEM_BLOCK *)cursor;
        block->page = page;
        block->status = MEM_BLOCK_STATUS_IDLE;

        ADDR_TO_MEM(cursor + block_size, cursor + block_offset);
        cursor = BYTE_OFFSET(cursor, block_offset);
    }

    /* �������һ���ڴ�� */
    block = (MEM_BLOCK *)cursor;
    block->page = page;
    block->status = MEM_BLOCK_STATUS_IDLE;
}

void mem_page_terminate(MEM_PAGE *page)
{
    unsigned char *pt = NULL;
    int size = 0;

    size = page->block_num * (page->block_data + page->block_head);
    pt = BYTE_OFFSET(page, sizeof(MEM_PAGE));

    /* ����ڴ�� */
    memset(pt, 0, size);

    /* ������ͷ�� */
    memset(page, 0, sizeof(MEM_PAGE));
}

MEM_BLOCK *get_block(void *address, int dbg)
{
    unsigned char *pt = NULL;
    MEM_BLOCK *ret = NULL;

    int block_size = dbg ? sizeof(MEM_BLOCK_DBG) : sizeof(MEM_BLOCK);

    if (!address) {
        return NULL;
    }

    pt = (unsigned char *)address;
    pt = BYTE_REOFFSET(pt, block_size);

    ret = (MEM_BLOCK *)pt;
    return ret;
}

void pad_dbg_block(MEM_BLOCK_DBG *block, const char *func, const char *file, int line)
{
    const char *str = NULL;

    if (!block) {
        return;
    }

    if (!func && !file && !line) {
        block->line = 0;
        block->thread = 0;

        memset(block->date, INIT_BLOCK_PADDING, DATE_INFO_LENGTH);
        memset(block->file, INIT_BLOCK_PADDING, FILE_INFO_LENGTH);
        memset(block->func, INIT_BLOCK_PADDING, FUNC_INFO_LENGTH);
    } else {
        block->line = line;
        block->thread = (unsigned long long)THREAD_SELF;

        get_curtime("%Y-%m-%d %H:%M:%S", block->date, DATE_INFO_LENGTH);

        if (file && file[0]) {
            str = strrchr(file, CH_SEP);
            str = str ? (str + 1) : file;

            strncpy(block->file, str, FILE_INFO_LENGTH);
        }

        if (func && func[0]) {
            strncpy(block->func, func, FUNC_INFO_LENGTH);
        }

        block->date[DATE_INFO_LENGTH - 1] = '\0';
        block->file[FILE_INFO_LENGTH - 1] = '\0';
        block->func[FUNC_INFO_LENGTH - 1] = '\0';
    }
}

const char *get_page_name(unsigned char type)
{
    static char buff[32] = { 0 };

    switch (type) {
    case MEM_PAGE_TYPE_ZERO:  strcpy(buff, "MEM_PAGE_TYPE_ZERO");  break;
    case MEM_PAGE_TYPE_1K:    strcpy(buff, "MEM_PAGE_TYPE_1K");    break;
    case MEM_PAGE_TYPE_2K:    strcpy(buff, "MEM_PAGE_TYPE_2K");    break;
    case MEM_PAGE_TYPE_4K:    strcpy(buff, "MEM_PAGE_TYPE_4K");    break;
    case MEM_PAGE_TYPE_LARGE: strcpy(buff, "MEM_PAGE_TYPE_LARGE"); break;
    }

    return buff;
}

const char *get_status_name(unsigned char status)
{
    static char buff[32] = { 0 };

    switch (status) {
    case MEM_PAGE_STATUS_IDLE:  strcpy(buff, "MEM_PAGE_STATUS_IDLE");  break;
    case MEM_PAGE_STATUS_USING: strcpy(buff, "MEM_PAGE_STATUS_USING"); break;
    case MEM_PAGE_STATUS_FULL:  strcpy(buff, "MEM_PAGE_STATUS_FULL");  break;
    }

    return buff;
}

const char *get_block_status_name(int status)
{
    static char buff[32] = { 0 };

    switch (status) {
    case MEM_BLOCK_STATUS_IDLE:  strcpy(buff, "MEM_BLOCK_STATUS_IDLE");  break;
    case MEM_BLOCK_STATUS_USING: strcpy(buff, "MEM_BLOCK_STATUS_USING"); break;
    }

    return buff;
}

int print_leak_info(MEM_PAGE *page, int dbg, char *buff)
{
    int i;

    unsigned char *cursor = NULL;
    MEM_BLOCK *block = NULL;
    MEM_BLOCK_DBG *block_dbg = NULL;
    int offset = 0;
    int count = 0;

    if (!page || !buff) {
        return 0;
    }

    count = page->block_num;
    block = (MEM_BLOCK *)((unsigned char *)page + sizeof(MEM_PAGE));
    offset = page->block_head + page->block_data; 
    cursor = (unsigned char *)block;

    sprintf(buff, "page %p:\n", page);
    output_mem_info_std(buff);

    if (dbg) {
        for (i = 0; i < count; i++) {
            block_dbg = (MEM_BLOCK_DBG *)cursor;

            if (block_dbg->status == MEM_BLOCK_STATUS_USING) {
                sprintf(buff, "--- block[%d] block size = %d ---\n", i, offset);
                output_mem_info_std(buff);

                sprintf(buff, "    time = %s\n",   block_dbg->date);
                output_mem_info_std(buff);

                sprintf(buff, "    file = %s\n",   block_dbg->file);
                output_mem_info_std(buff);

                sprintf(buff, "    line = %d\n",   block_dbg->line);
                output_mem_info_std(buff);

                sprintf(buff, "    func = %s\n",   block_dbg->func);
                output_mem_info_std(buff);

                sprintf(buff, "    tid  = 0x%llX\n", block_dbg->thread);
                output_mem_info_std(buff);
            }

            cursor += offset;
        }
    } else {
        for (i = 0; i < count; i++) {
            block = (MEM_BLOCK *)cursor;

            if (block->status == MEM_BLOCK_STATUS_USING) {
                sprintf(buff, "--- block[%d] block size = %d ---\n", i, offset);
                output_mem_info_std(buff);
            }

            cursor += offset;
        }
    }

    sprintf(buff, "--- allocated size = %d byte ---\n", page->alloc_size);
    output_mem_info_std(buff);

    return page->alloc_size;
}

void print_link_info(MEM_PAGE_LINK *link, int index, char *buff)
{
    if (!link || !buff) {
        return;
    }

    if (index > MEM_PAGE_BLOCK_INFO_COUNT - 1) {
        return;
    }

    sprintf(buff, "%s page link:\n", get_page_name(mem_page_info_list[index].page_type));
    output_mem_info_std(buff);

    sprintf(buff, "count      = %d\n", link->count);
    output_mem_info_std(buff);

    sprintf(buff, "ilde_num   = %d\n", link->idle_num);
    output_mem_info_std(buff);

    sprintf(buff, "heade      = %p\n", link->head);
    output_mem_info_std(buff);

    sprintf(buff, "tail       = %p\n", link->tail);
    output_mem_info_std(buff);
}

void print_page_info(MEM_PAGE *page, char *buff)
{
    if (!page || !buff) {
        return;
    }

    sprintf(buff, "page %p status      = %s\n", page, get_status_name(page->status));
    output_mem_info_std(buff);

    sprintf(buff, "page %p using_count = %d\n", page, (int)page->using_count);
    output_mem_info_std(buff);

    sprintf(buff, "page %p block_num   = %d\n", page, (int)page->block_num);
    output_mem_info_std(buff);

    sprintf(buff, "page %p block_head  = %d\n", page, (int)page->block_head);
    output_mem_info_std(buff);

    sprintf(buff, "page %p block_data  = %d\n", page, (int)page->block_data);
    output_mem_info_std(buff);

    sprintf(buff, "page %p alloc_size  = %d\n", page, (int)page->alloc_size);
    output_mem_info_std(buff);

    sprintf(buff, "page %p idle        = %p\n", page, page->idle);
    output_mem_info_std(buff);

    sprintf(buff, "page %p next_page   = %p\n", page, page->next);
    output_mem_info_std(buff);
}

void output_mem_info_std(const char *info)
{
    printf("%s", info);
}

const char *format_mem_info(char *buff, int size, const char *info, ...)
{
    va_list args;

    if (buff) {
        va_start(args, info);
        vsnprintf(buff, (int)size, info, args);
        va_end(args);
    }
    return buff;
}

int get_curtime(const char *format, char *buf, int len)
{
    time_t lc_time = 0;
    size_t ret = 0;
    struct tm *lctm = NULL;

    if (!format || !format[0]) {
        return MEM_FAILED;
    }

    if (!buf) {
        return MEM_FAILED;
    }

    if (len <= 0) {
        return MEM_FAILED;
    }

    memset(buf, 0, len);

    /* ��ȡ����ʱ�� */
    lc_time = time(NULL);
    lctm = localtime(&lc_time);

    if (!lctm) {
        return MEM_FAILED;
    }

    /* ת��ʱ����ϢΪ�ַ��� */
    ret = strftime(buf, len, format, lctm);
    return !ret ? MEM_FAILED : MEM_SUCCESS;
}
/*===========================================================================*/
