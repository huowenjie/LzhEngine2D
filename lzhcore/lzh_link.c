#include <stddef.h>
#include <lzh_link.h>

/*===========================================================================*/

void lzh_link_reset(LZH_LINK *link)
{
    if (!link) {
        return;
    }

    link->head  = NULL;
    link->tail  = NULL;
    link->count = 0;
}

/*-------------------------------------------------------*/

/* 在 target 之前插入节点 */
#define INSERT_BEFORE(target, node) \
    (target)->prev->next = (node); \
    (node)->prev = (target)->prev; \
    (node)->next = (target); \
    (target)->prev = (node);

/* 在 target 之后插入节点 */
#define INSERT_AFTER(target, node) \
    (target)->next->prev = (node); \
    (node)->prev = (target); \
    (node)->next = (target->next); \
    (target)->next = (node);

/* 移除 target */
#define REMOVE(target) \
    (target)->prev->next = (target)->next; \
    (target)->next->prev = (target)->prev;

/*-------------------------------------------------------*/

LZH_BOOL lzh_link_push(LZH_LINK *link, LZH_LINK_NODE *node)
{
    if (!link || !node) {
        return LZH_FALSE;
    }

    if (link->head) {
        INSERT_AFTER(link->tail, node);
        link->tail = node;
    } else {
        link->head = node;
        link->tail = node;

        node->next = node;
        node->prev = node;
    }

    link->count++;
    return LZH_TRUE;
}

LZH_BOOL lzh_link_insert(LZH_LINK *link, int index, LZH_LINK_NODE *node)
{
    int i;
    LZH_LINK_NODE *add_node = NULL;

    if (!link || !node) {
        return LZH_FALSE;
    }

    if (index > link->count) {
        return LZH_FALSE;
    }

    if (!link->count) {
        /* 链表为空 */
        link->head = node;
        link->tail = node;

        node->next = node;
        node->prev = node;
    } else if (!index) {
        /* 换掉头节点 */
        INSERT_BEFORE(link->head, node);
        link->head = node;
    } else if (index == link->count) {
        /* 换掉尾节点 */
        INSERT_AFTER(link->tail, node);
        link->tail = node;
    } else {
        add_node = link->head;

        /* 先定位到位置，然后插入节点 */
        for (i = 0; i < index; i++) {
            add_node = add_node->next;
        }

        INSERT_BEFORE(add_node, node);
    }

    link->count++;
    return LZH_TRUE;
}

LZH_BOOL lzh_link_insert_before(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node)
{
    if (!link || !target || !node) {
        return LZH_FALSE;
    }

    INSERT_BEFORE(target, node);
    if (target == link->head) {
        link->head = node;
    }

    return LZH_TRUE;
}

LZH_BOOL lzh_link_insert_after(LZH_LINK *link, LZH_LINK_NODE *target, LZH_LINK_NODE *node)
{
    if (!link || !target || !node) {
        return LZH_FALSE;
    }

    INSERT_AFTER(target, node);
    if (target == link->tail) {
        link->tail = node;
    }

    return LZH_TRUE;
}

LZH_LINK_NODE *lzh_link_pop(LZH_LINK *link)
{
    LZH_LINK_NODE *ret = NULL;

    if (!link) {
        return NULL;
    }

    ret = link->tail;

    if (ret) {
        if (link->head != ret) {
            REMOVE(ret);
            link->tail = ret->prev;
        } else {
            link->head = NULL;
            link->tail = NULL;
        }

        link->count--;
    }

    return ret;
}

LZH_LINK_NODE *lzh_link_remove(LZH_LINK *link, int index)
{
    int i;
    LZH_LINK_NODE *ret = NULL;

    if (!link) {
        return NULL;
    }

    if (index >= link->count || !link->count) {
        return NULL;
    }

    if (link->count == 1) {
        ret = link->head;

        link->head = NULL;
        link->tail = NULL;
    } else if (!index) {
        ret = link->head;

        REMOVE(link->head);
        link->head = ret->next;
    } else if (index == (link->count - 1)) {
        ret = link->tail;

        REMOVE(link->tail);
        link->tail = ret->prev;
    } else {
        ret = link->head;

        for (i = 0; i < index; i++) {
            ret = ret->next;
        }

        REMOVE(ret);
    }

    link->count--;
    return ret;
}

LZH_LINK_NODE *lzh_link_remove_node(LZH_LINK *link, LZH_LINK_NODE *target)
{
    int i;
    LZH_LINK_NODE *ret = NULL;

    if (!link || !target) {
        return NULL;
    }

    if (!link->count) {
        return NULL;
    }
    
    ret = target;

    if (link->count == 1) {
        REMOVE(ret);
        link->head = NULL;
        link->tail = NULL;
    } else if (link->head == target) {
        REMOVE(ret);
        link->head = ret->next;
    } else if (link->tail == target) {
        REMOVE(ret);
        link->tail = ret->prev;
    } else {
        ret = link->head;

        for (i = 0; i < link->count; i++) {
            if (ret == target) {
                REMOVE(ret);
                break;
            }

            ret = ret->next;
        }

        /* 找不到 target，则不予删除 */
        if (i == link->count) {
            return NULL;
        }
    }

    link->count--;
    return ret;
}

LZH_LINK_NODE *lzh_link_remove_force(LZH_LINK *link, LZH_LINK_NODE *target)
{
    LZH_LINK_NODE *ret = NULL;

    if (!link || !target) {
        return NULL;
    }

    if (!link->count) {
        return NULL;
    }

    ret = target;
    REMOVE(ret);

    if (link->count == 1) {
        link->head = NULL;
        link->tail = NULL;
    } else if (link->head == target) {
        link->head = ret->next;
    } else if (link->tail == target) {
        link->tail = ret->prev;
    }

    link->count--;
    return ret;
}

/*===========================================================================*/
