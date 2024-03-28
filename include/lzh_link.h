#ifndef __LZH_LINK_H__
#define __LZH_LINK_H__

#include "lzh_mem.h"
#include <string.h>

/*===========================================================================*/
/* ˫������ģ�� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lzh_link_st LZH_LINK;
typedef struct lzh_link_node_st LZH_LINK_NODE;

/* ˫����������ṹ */
struct lzh_link_st {
    LZH_LINK_NODE *head; /* ͷ�ڵ� */
    LZH_LINK_NODE *tail; /* β�ڵ� */

    int count;       /* �ڵ����� */
};

/* ����ڵ� */
struct lzh_link_node_st {
    LZH_LINK_NODE *prev;
    LZH_LINK_NODE *next;
};

/* ����ԭ */
LZH_API void lzh_link_reset(LZH_LINK *link);

/* ���ڵ����β�� */
LZH_API LZH_BOOL lzh_link_push(LZH_LINK *link, LZH_LINK_NODE *node);

/* ����������ڵ㣬�� 0 ����ڵ�һ������������ */
LZH_API LZH_BOOL lzh_link_insert(LZH_LINK *link, int index, LZH_LINK_NODE *node);

/* ��Ŀ��ڵ�֮ǰ����ڵ�, target ����Ϊ�� */
LZH_API LZH_BOOL lzh_link_insert_before(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node);

/* ��Ŀ��ڵ�֮�����ڵ�, target ����Ϊ�� */
LZH_API LZH_BOOL lzh_link_insert_after(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node);

/* �Ƴ�β���ڵ㣬ͬʱ���ؽڵ��ַ */
LZH_API LZH_LINK_NODE *lzh_link_pop(LZH_LINK *link);

/* ���������Ƴ��ڵ� */
LZH_API LZH_LINK_NODE *lzh_link_remove(LZH_LINK *link, int index);

/* �Ƴ�Ŀ��ڵ�, �Ƴ��ɹ����ظýڵ�, �Ƴ�ʱ���Ȳ�ѯ�ڵ��Ƿ���� */
LZH_API LZH_LINK_NODE *lzh_link_remove_node(LZH_LINK *link, LZH_LINK_NODE *target);

/* 
 * ǿ���Ƴ�Ŀ��ڵ�, �Ƴ��ɹ����ظýڵ�, �Ƴ�ʱ�����ڵ��Ƿ����
 */
LZH_API LZH_LINK_NODE *lzh_link_remove_force(LZH_LINK *link, LZH_LINK_NODE *target);

/*===========================================================================*/

/**
 * ����ģ�壬ns�������ռ䣬fns �Ǻ��������ռ䣬keytype���������ͣ�valuetype��Ԫ�����͡�
 * 
 * �ȽϺ��� RB_COMP ���壺
 *      ���׸�����С�ڵڶ������򷵻ظ�����ֵ�����׸��������ڵڶ�����
 * �򷵻�������ֵ�����������ȼۣ��򷵻��㡣
 * 
 * �������� RB_VISIT ���壺
 *      �׸�����Ϊ��ǰ�ڵ㣬�ڶ�������Ϊ�û�����Ĳ�����
 */
#define LINK_DECLARE(ns, fns, valuetype) \
    typedef struct ns##_LINK_NODE ns##_LINK_NODE; \
    typedef struct ns##_LINK ns##_LINK; \
    typedef int (*ns##_LINK_COMP)(const void *, const void *); \
    typedef void (*ns##_LINK_VISIT)(const ns##_LINK_NODE *, void *); \
    \
    struct ns##_LINK_NODE { \
        ns##_LINK_NODE *prev; \
        ns##_LINK_NODE *next; \
        valuetype value; \
    }; \
    \
    struct ns##_LINK { \
        ns##_LINK_NODE *head; \
        ns##_LINK_NODE *tail; \
        int count; \
        ns##_LINK_COMP comp; \
    }; \
    \
    ns##_LINK *fns##_link_create(ns##_LINK_COMP comp); \
    void fns##_link_destroy(ns##_LINK *link); \
    int fns##_link_count(ns##_LINK *link); \
    LZH_BOOL fns##_link_push(ns##_LINK *link, valuetype value); \
    LZH_BOOL fns##_link_pop(ns##_LINK *link, valuetype *value); \
    LZH_BOOL fns##_link_insert(ns##_LINK *link, int index, valuetype value); \
    LZH_BOOL fns##_link_remove(ns##_LINK *link, int index, valuetype *value); \
    LZH_BOOL fns##_link_remove_value(ns##_LINK *link, const valuetype value); \
    void fns##_link_clear(ns##_LINK *link, ns##_LINK_VISIT visit, void *args); \
    LZH_BOOL fns##_link_value(ns##_LINK *link, int index, valuetype *value); \
    LZH_BOOL fns##_link_exist(ns##_LINK *link, const valuetype value); \
    int fns##_link_index(ns##_LINK *link, const valuetype value);

#define LINK_IMPLEMENT(ns, fns, valuetype) \
    ns##_LINK *fns##_link_create(ns##_LINK_COMP comp) { \
        ns##_LINK *link = LZH_MALLOC(sizeof(ns##_LINK)); \
        if (!link) { \
            return NULL; \
        } \
        memset(link, 0, sizeof(sizeof(ns##_LINK))); \
        link->comp = comp; \
        return link; \
    } \
    void fns##_link_destroy(ns##_LINK *link) { \
        if (link) { \
            LZH_FREE(link); \
        } \
    } \
    int fns##_link_count(ns##_LINK *link) { \
        if (link) { \
            return link->count; \
        } \
        return 0; \
    } \
    LZH_BOOL fns##_link_push(ns##_LINK *link, valuetype value) { \
        ns##_LINK_NODE *node = NULL; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        node = LZH_MALLOC(sizeof(ns##_LINK_NODE)); \
        if (!node) { \
            return LZH_FALSE; \
        } \
        memset(node, 0, sizeof(sizeof(ns##_LINK_NODE))); \
        node->value = value; \
        return lzh_link_push((LZH_LINK *)link, (LZH_LINK_NODE *)node); \
    } \
    LZH_BOOL fns##_link_pop(ns##_LINK *link, valuetype *value) { \
        ns##_LINK_NODE *node = NULL; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        node = (ns##_LINK_NODE *)lzh_link_pop((LZH_LINK *)link); \
        if (!node) { \
            return LZH_FALSE; \
        } \
        if (value) { \
            *value = node->value; \
        } \
        LZH_FREE(node); \
        return LZH_TRUE; \
    } \
    LZH_BOOL fns##_link_insert(ns##_LINK *link, int index, valuetype value) { \
        ns##_LINK_NODE *node = NULL; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        node = LZH_MALLOC(sizeof(ns##_LINK_NODE)); \
        if (!node) { \
            return LZH_FALSE; \
        } \
        memset(node, 0, sizeof(sizeof(ns##_LINK_NODE))); \
        node->value = value; \
        return lzh_link_insert((LZH_LINK *)link, index, (LZH_LINK_NODE *)node); \
    } \
    LZH_BOOL fns##_link_remove(ns##_LINK *link, int index, valuetype *value) { \
        ns##_LINK_NODE *node = NULL; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        node = (ns##_LINK_NODE *)lzh_link_remove((LZH_LINK *)link, index); \
        if (!node) { \
            return LZH_FALSE; \
        } \
        if (value) { \
            *value = node->value; \
        } \
        LZH_FREE(node); \
        return LZH_TRUE; \
    } \
    LZH_BOOL fns##_link_remove_value(ns##_LINK *link, const valuetype value) { \
        ns##_LINK_NODE *node = NULL; \
        int index = 0; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        for (node = link->head; node != NULL && index < link->count; node = node->next) { \
            if (link->comp) { \
                ns##_LINK_COMP comp = link->comp; \
                if (!comp(&node->value, &value)) { \
                    lzh_link_remove_node((LZH_LINK *)link, (LZH_LINK_NODE *)node); \
                    LZH_FREE(node); \
                    return LZH_TRUE; \
                } \
            } else if (node->value == value) { \
                lzh_link_remove_node((LZH_LINK *)link, (LZH_LINK_NODE *)node); \
                LZH_FREE(node); \
                return LZH_TRUE; \
            } \
            index++; \
        } \
        return LZH_FALSE; \
    } \
    void fns##_link_clear(ns##_LINK *link, ns##_LINK_VISIT visit, void *args) { \
        ns##_LINK_NODE *node = NULL; \
        \
        if (!link) { \
            return; \
        } \
        \
        while ((node = (ns##_LINK_NODE *)lzh_link_pop((LZH_LINK *)link)) != NULL) { \
            if (visit) { \
                visit(node, args); \
            } \
            LZH_FREE(node); \
        } \
    } \
    LZH_BOOL fns##_link_value(ns##_LINK *link, int index, valuetype *value) { \
        ns##_LINK_NODE *node = NULL; \
        int i = 0; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        if (index < 0 || index >= link->count) { \
            return LZH_FALSE; \
        } \
        \
        if (!value) { \
            return LZH_FALSE; \
        } \
        \
        node = link->head; \
        while (i++ < index) { \
            node = node->next; \
        } \
        *value = node->value; \
        return LZH_TRUE; \
    } \
    LZH_BOOL fns##_link_exist(ns##_LINK *link, const valuetype value) { \
        ns##_LINK_NODE *node = NULL; \
        int index = 0; \
        \
        if (!link) { \
            return LZH_FALSE; \
        } \
        \
        for (node = link->head; node != NULL && index < link->count; node = node->next) { \
            if (link->comp) { \
                ns##_LINK_COMP comp = link->comp; \
                if (!comp(&node->value, &value)) { \
                    return LZH_TRUE; \
                } \
            } else if (node->value == value) { \
                return LZH_TRUE; \
            } \
            index++; \
        } \
        return LZH_FALSE; \
    } \
    int fns##_link_index(ns##_LINK *link, const valuetype value) { \
        ns##_LINK_NODE *node = NULL; \
        int index = 0; \
        \
        if (!link) { \
            return -1; \
        } \
        \
        for (node = link->head; node != NULL && index < link->count; node = node->next) { \
            if (link->comp) { \
                ns##_LINK_COMP comp = link->comp; \
                if (!comp(&node->value, &value)) { \
                    return index; \
                } \
            } else if (node->value == value) { \
                return index; \
            } \
            \
            index++; \
        } \
        return -1; \
    }

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_LINK_H__ */