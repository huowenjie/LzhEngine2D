#ifndef __LZH_MEM_PAGE_H__
#define __LZH_MEM_PAGE_H__

#include <stddef.h>

/*===========================================================================*/
/* �ڴ�ҳ */
/*===========================================================================*/

#define MEM_SUCCESS 0
#define MEM_FAILED -1

/* �ڴ�ҳ��� */
#define MEM_PAGE_TYPE_ZERO          0    /* ����������Ϊ 0k �ڴ����ڴ�ҳ */
#define MEM_PAGE_TYPE_1K            1    /* ����������Ϊ 1k �ڴ����ڴ�ҳ */
#define MEM_PAGE_TYPE_2K            2    /* ����������Ϊ 2k �ڴ����ڴ�ҳ */
#define MEM_PAGE_TYPE_4K            3    /* ����������Ϊ 4k �ڴ����ڴ�ҳ */
#define MEM_PAGE_TYPE_LARGE         4    /* �������ڴ��ϴ�ĵ��ڴ�ҳ */

/* �ڴ�ҳ״̬ */
#define MEM_PAGE_STATUS_IDLE        0    /* �ڴ�ҳ��ȫ���� */
#define MEM_PAGE_STATUS_USING       1    /* �ڴ�ҳ����ʹ�� */
#define MEM_PAGE_STATUS_FULL        2    /* �ڴ�ҳ���� */

/* �ڴ��״̬ */
#define MEM_BLOCK_STATUS_IDLE       0    /* �ڴ����� */
#define MEM_BLOCK_STATUS_USING      1    /* �ڴ�鱻ռ�� */

typedef struct mem_page_st          MEM_PAGE;
typedef struct mem_block_st         MEM_BLOCK;
typedef struct mem_block_dbg_st     MEM_BLOCK_DBG;
typedef struct mem_page_link_st     MEM_PAGE_LINK;

/*-------------------------------------------------------*/

/* ��ȡ��ҳ���� */
int get_page_index(size_t len);

/* ͨ���ڴ�ҳ��ȡ���� */
int get_page_index_ex(MEM_PAGE *page);

/* �Ƿ���ڿ���ҳ�� */
int usable_page_exist(int index);

/* ����һ���ڴ�ҳ */
int mem_page_malloc(int index, int dbg);

/* �ͷ�һ���ڴ�ҳ������ڴ�����û�� idle ״̬���ڴ�ҳ��������Ӧ�Ĵ����� */
int mem_page_free(MEM_PAGE *page);

/* �����ڴ�ҳ */
void clear_mem_pages();

/* ���ڴ�ҳ����һ�������ڴ�� */
void *alloc_block(size_t len);
void *alloc_block_dbg(size_t len, const char *func, const char *file, int line);

/* �ͷ��ڴ�� */
void free_block(void *address, int dbg);

/* ��ӡ�����ڴ���Ϣ */
void page_print_basic_info(int dbg);

/* ��ӡ�ڴ���б� */
void page_print_block_list(int index, int dbg);

/* ��ӡ�ѷ�����ڴ���Ϣ */
void page_print_allocated_info(int dbg);

/*-------------------------------------------------------*/
/* �ڴ�ṹ��Ϣ */

/* ��ȡ������ַ�ڴ��ĳ���, ����ͷ�� */
int get_addr_block_len(void *ptr, int dbg);

/*===========================================================================*/

#endif /* __LZH_MEM_PAGE_H__ */
