#ifndef __LZH_RB_TREE_H__
#define __LZH_RB_TREE_H__

#include "lzh_mem.h"
#include "lzh_stack.h"

#include <string.h>

/*===========================================================================*/
/* ����� */
/*===========================================================================*/

/**
 * �������ÿ�����������һ���洢��Ԫ����ʾ�ڵ����ɫ�������� RED ���� BLACK,
 * ͨ�����κ�һ���Ӹ���Ҷ�ӵļ�·���ϸ���������ɫ����Լ���������ȷ��û��
 * һ��·���������·�������������������ƽ�⡣
 * 
 * һ�ź����������һ�Ŷ�������ͬʱ�����������ʣ�
 * 1.ÿ������Ǻ�ɫ�Ļ����Ǻ�ɫ�ģ�
 * 2.���ڵ��Ǻ�ɫ�ģ�
 * 3.ÿ��Ҷ�ӽ���Ǻ�ɫ�ģ�
 * 4.���һ������Ǻ�ɫ�ģ������������ӽ�㶼�Ǻ�ɫ�ģ�
 * 5.����ÿ����㣬�Ӹý�㵽�����к����Ҷ�ӽ��ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ��㡣
 */

#define RBTREE_COLOR_RED   0x00000000      /* �����ɫ */
#define RBTREE_COLOR_BLACK 0x00000001      /* �����ɫ */
#define RBTREE_COLOR_MASK  0x0000FFFF      /* ��ɫ���� */
#define RBTREE_NIL_NODE    0x00010000      /* �ڱ��ڵ� */

typedef struct RB_NODE RB_NODE;
typedef struct RB_TREE RB_TREE;

/* �������� */
struct RB_NODE
{
    unsigned int flag;

    RB_NODE *parent;
    RB_NODE *left;
    RB_NODE *right;
};

/* ����� */
struct RB_TREE
{
    RB_NODE *root;
    RB_NODE *nil;

    int count;
};

/*===========================================================================*/

/* �Խ�� node ��������ת */
LZH_API int rb_left_rotate(RB_TREE *tree, RB_NODE *node);

/* �Խ�� node ��������ת */
LZH_API int rb_right_rotate(RB_TREE *tree, RB_NODE *node);

/* ������ʱ��������� */
LZH_API int rb_insert_fixup_tree(RB_TREE *tree, RB_NODE *node);

/* ɾ���ڵ�ʱ��������� */
LZH_API int rb_delete_fixup_tree(RB_TREE *tree, RB_NODE *node);

/* �ڵ��ƶ� */
LZH_API int rb_node_transplant(RB_TREE *tree, RB_NODE *dest, RB_NODE *src);

/* ��ȡ�ڵ�߶� */
LZH_API int rb_node_height(const RB_NODE *node);

/* ������ɫ */
LZH_API void rb_node_set_color(RB_NODE *node, unsigned int color);

/* ��ȡ��ɫ */
LZH_API unsigned int rb_node_get_color(RB_NODE *node);

/* �Ƿ�Ϊ�ڱ��ڵ㣬����ڱ��ڵ���߿սڵ㣬���� 1�����򷵻� 0 */
LZH_API int rb_node_is_nil(RB_NODE *node);

/**
 * �����ģ�壬ns�������ռ䣬fns �Ǻ��������ռ䣬keytype���������ͣ�valuetype��Ԫ�����͡�
 * 
 * �ȽϺ��� RB_COMP ���壺
 *      ���׸�����С�ڵڶ������򷵻ظ�����ֵ�����׸��������ڵڶ�����
 * �򷵻�������ֵ�����������ȼۣ��򷵻��㡣
 * 
 * �������� RB_VISIT ���壺
 *      �׸�����Ϊ��ǰ key���ڶ�������Ϊֵ value�����һ������Ϊ�û�����Ĳ���
 */
#define RBTREE_DECLARE(ns, fns, keytype, valuetype) \
    typedef struct ns##_RB_NODE ns##_RB_NODE; \
    typedef struct ns##_RB_TREE ns##_RB_TREE; \
    typedef int (*ns##_RB_COMP)(const void *, const void *); \
    typedef void (*ns##_RB_VISIT)(const ns##_RB_NODE *, void *); \
    STACK_DEFINE(fns, ns##_RB, ns##_RB_NODE *); \
    \
    struct ns##_RB_NODE { \
        unsigned int flag; \
        ns##_RB_NODE *parent; \
        ns##_RB_NODE *left; \
        ns##_RB_NODE *right; \
        keytype key; \
        valuetype value; \
    }; \
    \
    struct ns##_RB_TREE { \
        ns##_RB_NODE *root; \
        ns##_RB_NODE *nil; \
        ns##_RB_COMP comp; \
        int count; \
    }; \
    \
    ns##_RB_TREE *fns##_rb_create(ns##_RB_COMP comp); \
    void fns##_rb_destroy(ns##_RB_TREE *tree, ns##_RB_VISIT visit, void *args); \
    int fns##_rb_insert(ns##_RB_TREE *tree, keytype key, valuetype value); \
    int fns##_rb_delete(ns##_RB_TREE *tree, keytype key); \
    int fns##_rb_find(ns##_RB_TREE *tree, keytype key, valuetype *value); \
    int fns##_rb_iterate(ns##_RB_TREE *tree, ns##_RB_VISIT visit, void *args);

#define RBTREE_IMPLEMENT(ns, fns, keytype, valuetype) \
    STACK_IMPLEMENT(fns, ns##_RB, ns##_RB_NODE *); \
    ns##_RB_TREE *fns##_rb_create(ns##_RB_COMP comp) { \
        ns##_RB_NODE *nil = NULL; \
        ns##_RB_TREE *tree = LZH_MALLOC(sizeof(ns##_RB_TREE)); \
        memset(tree, 0, sizeof(sizeof(ns##_RB_TREE))); \
        \
        nil = LZH_MALLOC(sizeof(ns##_RB_NODE)); \
        memset(nil, 0, sizeof(ns##_RB_NODE)); \
        nil->flag = RBTREE_COLOR_BLACK | RBTREE_NIL_NODE; \
        \
        tree->root = NULL; \
        tree->count = 0; \
        tree->nil = nil; \
        tree->comp = comp; \
        \
        return tree; \
    } \
    void fns##_rb_destroy(ns##_RB_TREE *tree, ns##_RB_VISIT visit, void *args) { \
        if (tree) { \
            ns##_RB_STACK stack; \
            ns##_RB_STACK tmp; \
            \
            ns##_RB_NODE **buf = NULL; \
            ns##_RB_NODE *node = NULL; \
            \
            int count = tree->count; \
            if (count <= 0) { \
                return; \
            } \
            \
            buf = LZH_MALLOC(2 * count * sizeof(ns##_RB_NODE *)); \
            memset(buf, 0, 2 * count * sizeof(ns##_RB_NODE *)); \
            \
            stack.elems = buf; \
            stack.num = 0; \
            stack.size = count; \
            \
            tmp.elems = buf + count; \
            tmp.num = 0; \
            tmp.size = count; \
            \
            node = tree->root; \
            \
            while ((node && !rb_node_is_nil((RB_NODE *)node)) || tmp.num > 0) { \
                while (node && !rb_node_is_nil((RB_NODE *)node)) { \
                    fns##_stack_push(&stack, node); \
                    fns##_stack_push(&tmp, node); \
                    node = node->right; \
                } \
                \
                if (tmp.num > 0) { \
                    fns##_stack_pop(&tmp, &node); \
                    node = node->left; \
                } \
            } \
            \
            while (stack.num > 0) { \
                fns##_stack_pop(&stack, &node); \
                if (visit) { \
                    visit(node, args); \
                } \
                LZH_FREE(node); \
            } \
            LZH_FREE(buf); \
            LZH_FREE(tree->nil); \
            LZH_FREE(tree); \
        } \
    } \
    int fns##_rb_insert(ns##_RB_TREE *tree, keytype key, valuetype value) { \
        ns##_RB_NODE *node = NULL; \
        ns##_RB_NODE *target = NULL; \
        ns##_RB_NODE *add = NULL; \
        ns##_RB_COMP comp = NULL; \
        \
        int cmp = 0; \
        \
        if (!tree) { \
            return -1; \
        } \
        \
        node = tree->root; \
        comp = tree->comp; \
        if (!comp) { \
            return -1; \
        } \
        \
        while (node && !rb_node_is_nil((RB_NODE *)node)) { \
            target = node; \
            cmp = comp(&key, &node->key); \
            \
            if (!cmp) { \
                return -1; \
            } \
            \
            if (cmp < 0) { \
                node = node->left; \
            } else { \
                node = node->right; \
            } \
        } \
        \
        add = LZH_MALLOC(sizeof(ns##_RB_NODE)); \
        memset(add, 0, sizeof(ns##_RB_NODE)); \
        \
        add->flag = RBTREE_COLOR_RED; \
        add->parent = NULL; \
        add->left = tree->nil; \
        add->right = tree->nil; \
        add->key = key; \
        add->value = value; \
        \
        if (!target) { \
            tree->root = add; \
        } else if (cmp < 0) { \
            target->left = add; \
        } else { \
            target->right = add; \
        } \
        \
        add->parent = target; \
        \
        if (rb_insert_fixup_tree((RB_TREE *)tree, (RB_NODE *)add)) { \
            return -1; \
        } \
        \
        tree->count++; \
        return 0; \
    } \
    int fns##_rb_delete(ns##_RB_TREE *tree, keytype key) { \
        ns##_RB_NODE *target = NULL; \
        ns##_RB_NODE *tmp = NULL; \
        ns##_RB_COMP comp = NULL; \
        unsigned int color = RBTREE_COLOR_RED; \
        \
        if (!tree) { \
            return -1; \
        } \
        \
        target = tree->root; \
        comp = tree->comp; \
        if (!comp) { \
            return -1; \
        } \
        \
        while (target && !rb_node_is_nil((RB_NODE *)target)) { \
            int cmp = comp(&key, &target->key); \
            if (!cmp) { \
                break; \
            } \
            if (cmp < 0) { \
                target = target->left; \
            } else { \
                target = target->right; \
            } \
        } \
        \
        if (!target || rb_node_is_nil((RB_NODE *)target)) { \
            return -1; \
        } \
        \
        color = rb_node_get_color((RB_NODE *)target); \
        \
        if (rb_node_is_nil((RB_NODE *)target->left)) { \
            tmp = target->right; \
            rb_node_transplant((RB_TREE *)tree, (RB_NODE *)target, (RB_NODE *)tmp); \
        } else if (rb_node_is_nil((RB_NODE *)target->right)) { \
            tmp = target->left; \
            rb_node_transplant((RB_TREE *)tree, (RB_NODE *)target, (RB_NODE *)tmp); \
        } else { \
            ns##_RB_NODE *mini = target->right; \
            \
            while (!rb_node_is_nil((RB_NODE *)mini->left)) { \
                mini = mini->left; \
            } \
            \
            color = rb_node_get_color((RB_NODE *)mini); \
            tmp = mini->right; \
            \
            if (mini->parent == target) { \
                tmp->parent = mini; \
            } else { \
                rb_node_transplant((RB_TREE *)tree, (RB_NODE *)mini, (RB_NODE *)tmp); \
                mini->right = target->right; \
                mini->right->parent = mini; \
            } \
            \
            rb_node_transplant((RB_TREE *)tree, (RB_NODE *)target, (RB_NODE *)mini); \
            mini->left = target->left; \
            mini->left->parent = mini; \
            rb_node_set_color((RB_NODE *)mini, target->flag & RBTREE_COLOR_MASK); \
        } \
        \
        if (color == RBTREE_COLOR_BLACK) { \
            rb_delete_fixup_tree((RB_TREE *)tree, (RB_NODE *)tmp); \
        } \
        \
        tree->count--; \
        LZH_FREE(target); \
        return 0; \
    } \
    int fns##_rb_find(ns##_RB_TREE *tree, keytype key, valuetype *value) { \
        ns##_RB_NODE *target = NULL; \
        ns##_RB_COMP comp = NULL; \
        \
        if (!tree) { \
            return -1; \
        } \
        \
        target = tree->root; \
        comp = tree->comp; \
        if (!comp) { \
            return -1; \
        } \
        \
        while (target && !rb_node_is_nil((RB_NODE *)target)) { \
            int cmp = comp(&key, &target->key); \
            \
            if (!cmp) { \
                break; \
            } \
            \
            if (cmp < 0) { \
                target = target->left; \
            } else { \
                target = target->right; \
            } \
        } \
        \
        if (!target || rb_node_is_nil((RB_NODE *)target)) { \
            return -1; \
        } \
        \
        if (value) { \
            *value = target->value; \
        } \
        return 0; \
    } \
    int fns##_rb_iterate(ns##_RB_TREE *tree, ns##_RB_VISIT visit, void *args) { \
        ns##_RB_STACK stack; \
        ns##_RB_NODE **nodes = NULL; \
        ns##_RB_NODE *node = NULL; \
        int count = 0; \
        \
        if (!tree || !visit) { \
            return -1; \
        } \
        \
        count = tree->count; \
        if (count <= 0) { \
            return -1; \
        } \
        \
        nodes = LZH_MALLOC(count * sizeof(ns##_RB_NODE *)); \
        memset(nodes, 0, count * sizeof(ns##_RB_NODE *)); \
        \
        stack.elems = nodes; \
        stack.num = 0; \
        stack.size = count; \
        node = tree->root; \
        \
        while ((node && !rb_node_is_nil((RB_NODE *)node)) || stack.num > 0) { \
            while (node && !rb_node_is_nil((RB_NODE *)node)) { \
                fns##_stack_push(&stack, node); \
                node = node->left; \
            } \
            \
            if (stack.num > 0) { \
                fns##_stack_pop(&stack, &node); \
                visit(node, args); \
                \
                node = node->right; \
            } \
        } \
        \
        LZH_FREE(nodes); \
        return 0; \
    } \

/*===========================================================================*/

#endif /* __LZH_RB_TREE_H__ */
