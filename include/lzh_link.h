#ifndef __LZH_LINK_H__
#define __LZH_LINK_H__

#include "lzh_mem.h"
#include <string.h>

/*===========================================================================*/
/* 双向链表模板 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lzh_link_st LZH_LINK;
typedef struct lzh_link_node_st LZH_LINK_NODE;

/* 双向链表主体结构 */
struct lzh_link_st {
    LZH_LINK_NODE *head; /* 头节点 */
    LZH_LINK_NODE *tail; /* 尾节点 */

    int count;       /* 节点总数 */
};

/* 链表节点 */
struct lzh_link_node_st {
    LZH_LINK_NODE *prev;
    LZH_LINK_NODE *next;
};

/* 链表还原 */
LZH_API void lzh_link_reset(LZH_LINK *link);

/* 将节点接入尾部 */
LZH_API LZH_BOOL lzh_link_push(LZH_LINK *link, LZH_LINK_NODE *node);

/* 按索引插入节点，如 0 则插在第一个，依次类推 */
LZH_API LZH_BOOL lzh_link_insert(LZH_LINK *link, int index, LZH_LINK_NODE *node);

/* 在目标节点之前插入节点, target 不能为空 */
LZH_API LZH_BOOL lzh_link_insert_before(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node);

/* 在目标节点之后插入节点, target 不能为空 */
LZH_API LZH_BOOL lzh_link_insert_after(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node);

/* 移除尾部节点，同时返回节点地址 */
LZH_API LZH_LINK_NODE *lzh_link_pop(LZH_LINK *link);

/* 根据索引移除节点 */
LZH_API LZH_LINK_NODE *lzh_link_remove(LZH_LINK *link, int index);

/* 移除目标节点, 移除成功返回该节点, 移除时会先查询节点是否存在 */
LZH_API LZH_LINK_NODE *lzh_link_remove_node(LZH_LINK *link, LZH_LINK_NODE *target);

/* 
 * 强制移除目标节点, 移除成功返回该节点, 移除时不检查节点是否存在
 */
LZH_API LZH_LINK_NODE *lzh_link_remove_force(LZH_LINK *link, LZH_LINK_NODE *target);

/*===========================================================================*/

/**
 * 链表模板，ns是命名空间，fns 是函数命名空间，keytype是索引类型，valuetype是元素类型。
 * 
 * 比较函数 RB_COMP 定义：
 *      若首个参数小于第二个，则返回负整数值，若首个参数大于第二个，
 * 则返回正整数值，若两参数等价，则返回零。
 * 
 * 迭代函数 RB_VISIT 定义：
 *      首个参数为当前节点，第二个参数为用户传入的参数。
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