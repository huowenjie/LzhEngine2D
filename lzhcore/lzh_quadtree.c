#include <lzh_quadtree.h>
#include <lzh_mem.h>
#include <string.h>

/*===========================================================================*/

/* ���� quad ���ڵ� */
typedef struct LZH_QUAD_NODE LZH_QUAD_NODE;

/* Ĭ��ÿ���ڵ㱣������������� */
#define MAX_OBJECT_COUNT 4

/* ������������, �ֱ�Ϊ�� 1��2��3��4 ���޽ڵ� */
#define QUAD_NODE_RT 0
#define QUAD_NODE_LT 1
#define QUAD_NODE_LB 2
#define QUAD_NODE_RB 3

/*===========================================================================*/

struct LZH_QUAD_NODE
{
    /* �ĸ����� */
    LZH_QUAD_NODE *child[4];

    /* ���ڵ��ַ */
    LZH_QUAD_NODE *root;

    /* ��ǰ�ڵ��ʾ�Ŀռ䷶Χ */
    LZH_RECTF bound;

    /* ��ǰ�ڵ�����Ķ����б� */
    LZH_OBJECT **objects;

    /* ��ǰ�ڵ�Ķ������� */
    int obj_count;
};

struct LZH_QUAD_TREE
{
    /* ���ڵ� */
    LZH_QUAD_NODE *root;

    /* �ӽڵ����� */
    int count;

    /* �ӽڵ�����ɶ����������� */
    int obj_max_count;
};

/*===========================================================================*/

/* �Ƴ��ڵ� */
static void quad_tree_clear_node(LZH_QUAD_NODE *node);

/*===========================================================================*/

LZH_QUAD_TREE *lzh_quad_tree_create(const LZH_RECTF *region)
{
    LZH_QUAD_TREE *tree = NULL;
    LZH_QUAD_NODE *root = NULL;
    LZH_OBJECT **objects = NULL;

    if (!region) {
        return NULL;
    }

    tree = LZH_MALLOC(sizeof(LZH_QUAD_TREE));
    if (!tree) {
        return NULL;
    }
    memset(tree, 0, sizeof(LZH_QUAD_TREE));

    root = LZH_MALLOC(sizeof(LZH_QUAD_NODE));
    if (!root) {
        goto err;
    }
    memset(root, 0, sizeof(LZH_QUAD_NODE));

    objects = LZH_MALLOC(MAX_OBJECT_COUNT * sizeof(LZH_OBJECT *));
    if (!objects) {
        goto err;
    }
    memset(objects, 0, MAX_OBJECT_COUNT * sizeof(LZH_OBJECT *));

    root->bound = *region;
    root->objects = objects;
    root->obj_count = 0;
    root->root = root;

    tree->root = root;
    tree->count = 1;
    tree->obj_max_count = MAX_OBJECT_COUNT;

    return tree;
err:
    if (objects) {
        LZH_FREE(objects);
        objects = NULL;
    }

    if (root) {
        LZH_FREE(root);
        root = NULL;
    }

    if (tree) {
        LZH_FREE(tree);
        tree = NULL;
    }
    return NULL;
}

void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree)
{
    if (tree) {
        lzh_quad_tree_clear(tree);
        LZH_FREE(tree);
    }
}

void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object)
{

}

void lzh_quad_tree_find(
    LZH_QUAD_TREE *tree, const LZH_OBJECT *target, LZH_OBJECT **other, int *count)
{
    
}

int lzh_quad_tree_obj_max_count(LZH_QUAD_TREE *tree)
{
    int count = 0;
    if (tree) {
        count = tree->obj_max_count;
    }
    return count;
}

void lzh_quad_tree_clear(LZH_QUAD_TREE *tree)
{
    if (tree) {
        quad_tree_clear_node(tree->root);
        tree->root = NULL;
        tree->count = 0;
    }
}

/*===========================================================================*/

void quad_tree_clear_node(LZH_QUAD_NODE *node)
{
    int i = 0;
    LZH_QUAD_NODE **child = NULL;

    if (!node) {
        return;
    }

    child = node->child;

    quad_tree_clear_node(child[0]);
    quad_tree_clear_node(child[1]);
    quad_tree_clear_node(child[2]);
    quad_tree_clear_node(child[3]);

    LZH_FREE(child[0]);
    LZH_FREE(child[1]);
    LZH_FREE(child[2]);
    LZH_FREE(child[3]);

    LZH_FREE(node->objects);
    LZH_FREE(node);
}

/*===========================================================================*/
