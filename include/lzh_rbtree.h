#ifndef __LZH_RB_TREE_H__
#define __LZH_RB_TREE_H__

#include "lzh_mem.h"
#include "lzh_stack.h"

#include <string.h>

/*===========================================================================*/
/* 红黑树 */
/*===========================================================================*/

/**
 * 红黑树在每个结点上增加一个存储单元来表示节点的颜色，可以是 RED 或者 BLACK,
 * 通过对任何一条从根到叶子的简单路径上各个结点的颜色进行约束，红黑树确保没有
 * 一条路径会比其他路径长出两倍，因而近似平衡。
 * 
 * 一颗红黑树首先是一颗二叉树，同时满足以下性质：
 * 1.每个结点是红色的或者是黑色的；
 * 2.根节点是黑色的；
 * 3.每个叶子结点是黑色的；
 * 4.如果一个结点是红色的，则它的两个子结点都是黑色的；
 * 5.对于每个结点，从该结点到其所有后代的叶子结点的简单路径上，均包含相同数目的黑色结点。
 */

#define RBTREE_COLOR_RED   0x00000000      /* 定义红色 */
#define RBTREE_COLOR_BLACK 0x00000001      /* 定义黑色 */
#define RBTREE_COLOR_MASK  0x0000FFFF      /* 颜色掩码 */
#define RBTREE_NIL_NODE    0x00010000      /* 哨兵节点 */

typedef struct RB_NODE RB_NODE;
typedef struct RB_TREE RB_TREE;

/* 红黑树结点 */
struct RB_NODE
{
    unsigned int flag;

    RB_NODE *parent;
    RB_NODE *left;
    RB_NODE *right;
};

/* 红黑树 */
struct RB_TREE
{
    RB_NODE *root;
    RB_NODE *nil;

    int count;
};

/*===========================================================================*/

/* 对结点 node 进行左旋转 */
LZH_API int rb_left_rotate(RB_TREE *tree, RB_NODE *node);

/* 对结点 node 进行右旋转 */
LZH_API int rb_right_rotate(RB_TREE *tree, RB_NODE *node);

/* 插入结点时调整红黑树 */
LZH_API int rb_insert_fixup_tree(RB_TREE *tree, RB_NODE *node);

/* 删除节点时调整红黑树 */
LZH_API int rb_delete_fixup_tree(RB_TREE *tree, RB_NODE *node);

/* 节点移动 */
LZH_API int rb_node_transplant(RB_TREE *tree, RB_NODE *dest, RB_NODE *src);

/* 获取节点高度 */
LZH_API int rb_node_height(const RB_NODE *node);

/* 设置颜色 */
LZH_API void rb_node_set_color(RB_NODE *node, unsigned int color);

/* 获取颜色 */
LZH_API unsigned int rb_node_get_color(RB_NODE *node);

/* 是否为哨兵节点，如果哨兵节点或者空节点，返回 1，否则返回 0 */
LZH_API int rb_node_is_nil(RB_NODE *node);

/**
 * 红黑树模板，ns是命名空间，fns 是函数命名空间，keytype是索引类型，valuetype是元素类型。
 * 
 * 比较函数 RB_COMP 定义：
 *      若首个参数小于第二个，则返回负整数值，若首个参数大于第二个，
 * 则返回正整数值，若两参数等价，则返回零。
 * 
 * 迭代函数 RB_VISIT 定义：
 *      首个参数为当前 key，第二个参数为值 value，最后一个参数为用户传入的参数
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
