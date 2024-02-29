#include <lzh_quadtree.h>
#include <lzh_mem.h>
#include <lzh_object.h>
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

/* �������������� */
#define QUAD_NODE_INDEX_RT 0x00000001
#define QUAD_NODE_INDEX_LT 0x00000002
#define QUAD_NODE_INDEX_LB 0x00000004
#define QUAD_NODE_INDEX_RB 0x00000008
#define QUAD_NODE_INDEX_MASK 0x0000000F
#define QUAD_NODE_INDEX_CUR 0x000000FF

/*===========================================================================*/

struct LZH_QUAD_NODE
{
    /* �ĸ����� */
    LZH_QUAD_NODE *child[4];

    /* ����ַ */
    LZH_QUAD_TREE *tree;

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

/* �����½ڵ� */
static LZH_QUAD_NODE *create_quad_node();

/* �Ƴ��ڵ� */
static void destroy_quad_node(LZH_QUAD_NODE *node);

/* ��λ���ռ�ڵ� */
static LZH_UINT32 get_quad_node_index(LZH_QUAD_NODE *node, const LZH_RECTF *rect);

/* ��ӽڵ� */
static void add_quad_node(LZH_QUAD_NODE *node, LZH_OBJECT *object);

/* ���ѽڵ� */
static void split_quad_node(LZH_QUAD_NODE *node);

/* ������� */
static void insert_object(LZH_QUAD_NODE *node, LZH_OBJECT *object);

/* ɾ������ */
static void remove_object(LZH_QUAD_NODE *node, LZH_OBJECT *object);

/*===========================================================================*/

LZH_QUAD_TREE *lzh_quad_tree_create()
{
    LZH_QUAD_TREE *tree = NULL;

    tree = LZH_MALLOC(sizeof(LZH_QUAD_TREE));
    if (!tree) {
        return NULL;
    }
    memset(tree, 0, sizeof(LZH_QUAD_TREE));

    tree->obj_max_count = MAX_OBJECT_COUNT;
    return tree;
}

void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree)
{
    if (tree) {
        lzh_quad_tree_clear(tree);
        LZH_FREE(tree);
    }
}

void lzh_quad_tree_init_root(LZH_QUAD_TREE *tree, const LZH_RECTF *region)
{
    LZH_QUAD_NODE *root = NULL;

    if (!tree || !region) {
        return;
    }

    root = tree->root;
    if (!root) {
        root = create_quad_node();
        if (!root) {
            return;
        }

        root->obj_count = 0;
        root->tree = tree;

        tree->root = root;
        tree->count = 1;
    }

    root->bound = *region;
}

void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object)
{
    if (!tree || !object) {
        return;
    }

    if (!tree->root) {
        return;
    }

    add_quad_node(tree->root, object);
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
        destroy_quad_node(tree->root);
        tree->root = NULL;
        tree->count = 0;
    }
}

/*===========================================================================*/

LZH_QUAD_NODE *create_quad_node()
{
    LZH_OBJECT **objects = NULL;

    LZH_QUAD_NODE *node = LZH_MALLOC(sizeof(LZH_QUAD_NODE));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(LZH_QUAD_NODE));

    objects = LZH_MALLOC(MAX_OBJECT_COUNT * sizeof(LZH_OBJECT *));
    if (!objects) {
        goto err;
    }
    memset(objects, 0, MAX_OBJECT_COUNT * sizeof(LZH_OBJECT *));

    node->objects = objects;
    node->obj_count = 0;
    return node;
err:
    if (objects) {
        LZH_FREE(objects);
        objects = NULL;
    }

    if (node) {
        LZH_FREE(node);
        node = NULL;
    }
    return NULL;
}

void destroy_quad_node(LZH_QUAD_NODE *node)
{
    LZH_QUAD_NODE **child = NULL;

    if (!node) {
        return;
    }

    child = node->child;

    destroy_quad_node(child[0]);
    destroy_quad_node(child[1]);
    destroy_quad_node(child[2]);
    destroy_quad_node(child[3]);

    if (child[0]) {
        LZH_FREE(child[0]);
    }

    if (child[1]) {
        LZH_FREE(child[1]);
    }

    if (child[2]) {
        LZH_FREE(child[2]);
    }

    if (child[3]) {
        LZH_FREE(child[3]);
    }

    LZH_FREE(node->objects);
    LZH_FREE(node);
}

LZH_UINT32 get_quad_node_index(LZH_QUAD_NODE *node, const LZH_RECTF *rect)
{
    return 0;
}

void add_quad_node(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{
    LZH_RECTF objrect = { 0 };
    LZH_UINT32 index = 0;
    LZH_QUAD_TREE *tree = NULL;

    if (!node || !object) {
        return;
    }

    objrect = lzh_object_get_rect(object);

    /* ��ȡ�������� */
    index = get_quad_node_index(node, &objrect);
    if (!index) {
        return;
    }

    tree = node->tree;
    if (!tree) {
        return;
    }

    /* ��ǰ�ڵ�Ĵ���ʽ */
    if (index == QUAD_NODE_INDEX_CUR) {
        /* ��������������ƣ������ӽڵ㴦������ֱ�ӻ������ */
        if (node->obj_count >= tree->obj_max_count) {
            split_quad_node(node);
            add_quad_node(node, object);
        } else {
            insert_object(node, object);
        }
        return;
    }

    if ((index & QUAD_NODE_INDEX_RT) == QUAD_NODE_INDEX_RT) {
        add_quad_node(node->child[QUAD_NODE_RT], object);
    }

    if ((index & QUAD_NODE_INDEX_LT) == QUAD_NODE_INDEX_LT) {
        add_quad_node(node->child[QUAD_NODE_LT], object);
    }

    if ((index & QUAD_NODE_INDEX_LB) == QUAD_NODE_INDEX_LB) {
        add_quad_node(node->child[QUAD_NODE_LB], object);
    }

    if ((index & QUAD_NODE_INDEX_RB) == QUAD_NODE_INDEX_RB) {
        add_quad_node(node->child[QUAD_NODE_RB], object);
    }

    if ((index & QUAD_NODE_INDEX_MASK) != 0) {
        remove_object(node, object);
    }
}

void split_quad_node(LZH_QUAD_NODE *node)
{

}

void insert_object(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{

}

void remove_object(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{

}

/*===========================================================================*/
