#include <stdlib.h>
#include <string.h>

#include <lzh_rbtree.h>

/*===========================================================================*/

int rb_left_rotate(RB_TREE *tree, RB_NODE *node)
{
    RB_NODE *y = NULL;

    if (!tree || !node) {
        return -1;
    }

    y = node->right;
    node->right = y->left;

    if (!rb_node_is_nil(y->left)) {
        y->left->parent = node;
    }

    y->parent = node->parent;

    /* 处理各种父结点的边界情况 */
    if (node == tree->root) {
        tree->root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else if (node == node->parent->right) {
        node->parent->right = y;
    }

    y->left = node;
    node->parent = y;
    return 0;
}

int rb_right_rotate(RB_TREE *tree, RB_NODE *node)
{
    RB_NODE *x = NULL;

    if (!tree || !node) {
        return -1;
    }

    x = node->left;
    node->left = x->right;

    if (!rb_node_is_nil(x->right)) {
        x->right->parent = node;
    }

    x->parent = node->parent;

    /* 处理各种父结点的边界情况 */
    if (node == tree->root) {
        tree->root = x;
    } else if (node == node->parent->left) {
        node->parent->left = x;
    } else if (node == node->parent->right) {
        node->parent->right = x;
    }

    x->right = node;
    node->parent = x;
    return 0;
}

int rb_insert_fixup_tree(RB_TREE *tree, RB_NODE *node)
{
    RB_NODE *tmp = NULL;

    if (!tree || !node || rb_node_is_nil(node)) {
        return -1;
    }

    tmp = node;

    while (tmp->parent && (rb_node_get_color(tmp->parent) == RBTREE_COLOR_RED)) {
        RB_NODE *uncle = tree->nil;
        RB_NODE *parent = tmp->parent;

        /* 判断当前结点的父亲结点是否是祖父的左孩子或者右孩子 */
        if (parent == parent->parent->left) {
            uncle = parent->parent->right;

            if (uncle && (rb_node_get_color(uncle) == RBTREE_COLOR_RED)) {
                rb_node_set_color(uncle, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);

                tmp = parent->parent;
                parent = tmp->parent;
            } else if (tmp == parent->right) {
                tmp = parent;
                rb_left_rotate(tree, tmp);
                parent = tmp->parent;

                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);
                rb_right_rotate(tree, parent->parent);
            } else if (tmp == parent->left) {
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);
                rb_right_rotate(tree, parent->parent);
            }
        } else {
            uncle = parent->parent->left;

            if (uncle && (rb_node_get_color(uncle) == RBTREE_COLOR_RED)) {
                rb_node_set_color(uncle, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);

                tmp = parent->parent;
                parent = tmp->parent;
            } else if (tmp == parent->left) {
                tmp = parent;
                rb_right_rotate(tree, tmp);
                parent = tmp->parent;

                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);
                rb_left_rotate(tree, parent->parent);
            } else if (tmp == parent->right) {
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent->parent, RBTREE_COLOR_RED);
                rb_left_rotate(tree, parent->parent);
            }
        }
    }

    rb_node_set_color(tree->root, RBTREE_COLOR_BLACK);
    return 0;
}

int rb_delete_fixup_tree(RB_TREE *tree, RB_NODE *node)
{
    if (!tree) {
        return -1;
    }

    while (node != tree->root && (rb_node_get_color(node) == RBTREE_COLOR_BLACK)) {
        RB_NODE *parent = node->parent;

        if (node == parent->left) {
            RB_NODE *brother = parent->right;

            if (rb_node_get_color(brother) == RBTREE_COLOR_RED) {
                rb_node_set_color(brother, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent, RBTREE_COLOR_RED);

                rb_left_rotate(tree, parent);
                parent = node->parent;
                brother = parent->right;
            }

            if ((rb_node_get_color(brother->left) == RBTREE_COLOR_BLACK) &&
                (rb_node_get_color(brother->right) == RBTREE_COLOR_BLACK)) {
                rb_node_set_color(brother, RBTREE_COLOR_RED);
                node = parent;
            } else if (rb_node_get_color(brother->right) == RBTREE_COLOR_BLACK) {
                rb_node_set_color(brother->left, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother, RBTREE_COLOR_RED);

                rb_right_rotate(tree, brother);
                parent = node->parent;
                brother = parent->right;

                rb_node_set_color(brother, parent->flag & RBTREE_COLOR_MASK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother->right, RBTREE_COLOR_BLACK);

                rb_left_rotate(tree, parent);
                node = tree->root;
            } else {
                rb_node_set_color(brother, parent->flag & RBTREE_COLOR_MASK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother->right, RBTREE_COLOR_BLACK);

                rb_left_rotate(tree, parent);
                node = tree->root;
            }
        } else {
            RB_NODE *brother = parent->left;

            if (rb_node_get_color(brother) == RBTREE_COLOR_RED) {
                rb_node_set_color(brother, RBTREE_COLOR_BLACK);
                rb_node_set_color(parent, RBTREE_COLOR_RED);

                rb_right_rotate(tree, parent);
                parent = node->parent;
                brother = parent->left;
            }

            if ((rb_node_get_color(brother->right) == RBTREE_COLOR_BLACK) &&
                (rb_node_get_color(brother->left) == RBTREE_COLOR_BLACK)) {
                rb_node_set_color(brother, RBTREE_COLOR_RED);
                node = parent;
            } else if (rb_node_get_color(brother->left) == RBTREE_COLOR_BLACK) {
                rb_node_set_color(brother->right, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother, RBTREE_COLOR_RED);

                rb_left_rotate(tree, brother);
                parent = node->parent;
                brother = parent->left;

                rb_node_set_color(brother, parent->flag & RBTREE_COLOR_MASK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother->left, RBTREE_COLOR_BLACK);

                rb_right_rotate(tree, parent);
                node = tree->root;
            } else {
                rb_node_set_color(brother, parent->flag & RBTREE_COLOR_MASK);
                rb_node_set_color(parent, RBTREE_COLOR_BLACK);
                rb_node_set_color(brother->left, RBTREE_COLOR_BLACK);

                rb_right_rotate(tree, parent);
                node = tree->root;
            }
        }
    }

    rb_node_set_color(node, RBTREE_COLOR_BLACK);
    return 0;
}

int rb_node_transplant(RB_TREE *tree, RB_NODE *dest, RB_NODE *src)
{
    if (!tree || !dest || !src) {
        return -1;
    }

    if (!dest->parent) {
        tree->root = src;
    } else if (dest->parent->left == dest) {
        dest->parent->left = src;
    } else if (dest->parent->right == dest) {
        dest->parent->right = src;
    }

    src->parent = dest->parent;
    return 0;
}

int rb_node_height(const RB_NODE *node)
{
    int height = 0;

    if (!node) {
        return 0;
    }

    while (node) {
        node = node->parent;
        if (node) {
            height++;
        }
    }
    return height;
}

void rb_node_set_color(RB_NODE *node, unsigned int color)
{
    if (node) {
        node->flag = node->flag & (~RBTREE_COLOR_MASK);
        node->flag |= color;
    }
}

unsigned int rb_node_get_color(RB_NODE *node)
{
    if (node) {
        return node->flag & RBTREE_COLOR_MASK;
    }
    return RBTREE_COLOR_BLACK;
}

int rb_node_is_nil(RB_NODE *node)
{
    if (!node || (node->flag & RBTREE_NIL_NODE)) {
        return 1;
    }
    return 0;
}

/*===========================================================================*/
