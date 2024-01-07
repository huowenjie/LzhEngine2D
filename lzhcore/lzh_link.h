#ifndef __LZH_LINK_H__
#define __LZH_LINK_H__

/*===========================================================================*/
/* ����˫������ */
/*===========================================================================*/

#define LINK_SUCCESS 0
#define LINK_FAILED -1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct link_st LINK;
typedef struct link_node_st LINK_NODE;

/* ˫����������ṹ */
struct link_st {
    LINK_NODE *head; /* ͷ�ڵ� */
    LINK_NODE *tail; /* β�ڵ� */

    int count;       /* �ڵ����� */
};

/* ����ڵ� */
struct link_node_st {
    LINK_NODE *prev;
    LINK_NODE *next;
};

/* ����ԭ */
void link_reset(LINK *link);

/* ���ڵ����β�� */
int link_push(LINK *link, LINK_NODE *node);

/* ����������ڵ㣬�� 0 ����ڵ�һ�����������ƣ���ѯ�ڵ㸴�Ӷ�Ϊ O(n) */
int link_insert(LINK *link, int index, LINK_NODE *node);

/* ��Ŀ��ڵ�֮ǰ����ڵ�, target ����Ϊ�� */
int link_insert_before(LINK *link, LINK_NODE *target, LINK_NODE *node);

/* ��Ŀ��ڵ�֮�����ڵ�, target ����Ϊ�� */
int link_insert_after(LINK *link, LINK_NODE *target, LINK_NODE *node);

/* �Ƴ�β���ڵ㣬ͬʱ���ؽڵ��ַ */
LINK_NODE *link_pop(LINK *link);

/* ���������Ƴ��ڵ㣬��ѯ�ڵ㸴�Ӷ�Ϊ O(n) */
LINK_NODE *link_remove(LINK *link, int index);

/* �Ƴ�Ŀ��ڵ�, �Ƴ��ɹ����ظýڵ�, �Ƴ�ʱ���Ȳ�ѯ�ڵ��Ƿ���� */
LINK_NODE *link_remove_node(LINK *link, LINK_NODE *target);

/* 
 * ǿ���Ƴ�Ŀ��ڵ�, �Ƴ��ɹ����ظýڵ�, �Ƴ�ʱ�����ڵ��Ƿ���ڣ�
 * �㷨���Ӷ�Ϊ O(1) ��
 *
 * ���ñ�������Ҫ���С�ģ�ȷ�� target ���� link��
 */
LINK_NODE *link_remove_force(LINK *link, LINK_NODE *target);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*===========================================================================*/

#endif /* __LZH_LINK_H__ */
