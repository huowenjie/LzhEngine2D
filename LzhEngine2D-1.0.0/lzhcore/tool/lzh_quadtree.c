#include <lzh_mem.h>
#include <lzh_object.h>
#include <string.h>

#include "lzh_quadtree.h"
#include "../component/lzh_component.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

/* ���� quad ���ڵ� */
typedef struct LZH_QUAD_NODE LZH_QUAD_NODE;

/* Ĭ��ÿ���ڵ㱣������������� */
#define MAX_OBJECT_COUNT 4

/* Ĭ�������߶� */
#define MAX_HEIGHT 5

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

    /* ��ǰ�ڵ�߶� */
    int node_height;
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

/* ���ҽڵ� */
static void find_quad_node(
    LZH_QUAD_NODE *node, const LZH_OBJECT *target, LZH_OBJECT **other, int *count,
    int offset);

/* ���Ҷ��� */
static void find_object(
    LZH_QUAD_NODE *node, const LZH_OBJECT *target, LZH_OBJECT **other, int *count);

/* ��ȡ������� */
static LZH_BOOL get_object_rect(const LZH_OBJECT *object, LZH_RECTF *rect);

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
        root->node_height = 1;
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
    if (!tree || !target) {
        return;
    }

    if (!count) {
        return;
    }

    find_quad_node(tree->root, target, other, count, 0);
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
    node->node_height = 0;
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

    if (child[0]) {
        destroy_quad_node(child[0]);
        destroy_quad_node(child[1]);
        destroy_quad_node(child[2]);
        destroy_quad_node(child[3]);

        child[0] = NULL;
        child[1] = NULL;
        child[2] = NULL;
        child[3] = NULL;
    }

    LZH_FREE(node->objects);
    LZH_FREE(node);
}

LZH_UINT32 get_quad_node_index(LZH_QUAD_NODE *node, const LZH_RECTF *rect)
{
    LZH_UINT32 index = 0;
    LZH_RECTF *bound = NULL;

    float quadw = 0.0f;
    float quadh = 0.0f;

    LZH_RECTF rect_rt;
    LZH_RECTF rect_lt;
    LZH_RECTF rect_lb;
    LZH_RECTF rect_rb;

    if (!node || !rect) {
        return index;
    }

    bound = &node->bound;
    quadw = bound->w / 2.0f;
    quadh = bound->h / 2.0f;

    lzh_rectf_init(&rect_rt, bound->x + quadw, bound->y, quadw, quadh);
    lzh_rectf_init(&rect_lt, bound->x, bound->y, quadw, quadh);
    lzh_rectf_init(&rect_lb, bound->x, bound->y + quadh, quadw, quadh);
    lzh_rectf_init(&rect_rb, bound->x + quadw, bound->y + quadh, quadw, quadh);

    /* Ŀ����κ��ĸ����޵��ཻ���� */
    if (lzh_rectf_intersection(&rect_rt, rect)) {
        index |= QUAD_NODE_INDEX_RT;
    }

    if (lzh_rectf_intersection(&rect_lt, rect)) {
        index |= QUAD_NODE_INDEX_LT;
    }

    if (lzh_rectf_intersection(&rect_lb, rect)) {
        index |= QUAD_NODE_INDEX_LB;
    }

    if (lzh_rectf_intersection(&rect_rb, rect)) {
        index |= QUAD_NODE_INDEX_RB;
    }

    return index;
}

void add_quad_node(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{
    LZH_RECTF objrect = { 0 };
    LZH_UINT32 index = 0;
    LZH_QUAD_TREE *tree = NULL;

    if (!node || !object) {
        return;
    }

    tree = node->tree;
    if (!tree) {
        return;
    }

    /* �����ж��Ƿ���ѣ����δ���ѣ�ֱ���ڵ�ǰ�ڵ��ϲ��� */
    if (!node->child[0]) {
        insert_object(node, object);

        if ((node->obj_count >= tree->obj_max_count) && (node->node_height < MAX_HEIGHT)) {
            int i = 0;
            int count = node->obj_count;
            LZH_OBJECT **objs = node->objects;

            split_quad_node(node);

            /* ���Ѻ󣬽���ǰ�ڵ�Ķ�����䵽�����ӽڵ㣬���Ƴ���ǰ�ڵ�Ķ��� */
            for (i = 0; i < count; i++) {
                add_quad_node(node, objs[i]);
                objs[i] = NULL;
                node->obj_count--;
            }
        }
        return;
    }

    if (!get_object_rect(object, &objrect)) {
        return;
    }

    /* ��ȡ�������� */
    index = get_quad_node_index(node, &objrect);
    if (!index) {
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
}

void split_quad_node(LZH_QUAD_NODE *node)
{
    LZH_QUAD_TREE *tree = NULL;
    LZH_RECTF *bound = NULL;
    float w = 0.0f;
    float h = 0.0f;

    if (!node) {
        return;
    }

    /* �ӽڵ�����򲻷��� */
    if (node->child[QUAD_NODE_RT]) {
        return;
    }

    tree = node->tree;
    if (!tree) {
        return;
    }

    bound = &node->bound;
    w = bound->w / 2.0f;
    h = bound->h / 2.0f;

    node->child[QUAD_NODE_RT] = create_quad_node();
    node->child[QUAD_NODE_LT] = create_quad_node();
    node->child[QUAD_NODE_LB] = create_quad_node();
    node->child[QUAD_NODE_RB] = create_quad_node();

    lzh_rectf_init(&node->child[QUAD_NODE_RT]->bound, bound->x + w, bound->y, w, h);
    lzh_rectf_init(&node->child[QUAD_NODE_LT]->bound, bound->x, bound->y, w, h);
    lzh_rectf_init(&node->child[QUAD_NODE_LB]->bound, bound->x, bound->y + h, w, h);
    lzh_rectf_init(&node->child[QUAD_NODE_RB]->bound, bound->x + w, bound->y + h, w, h);

    node->child[QUAD_NODE_RT]->tree = tree;
    node->child[QUAD_NODE_LT]->tree = tree;
    node->child[QUAD_NODE_LB]->tree = tree;
    node->child[QUAD_NODE_RB]->tree = tree;

    node->child[QUAD_NODE_RT]->node_height = node->node_height + 1;
    node->child[QUAD_NODE_LT]->node_height = node->node_height + 1;
    node->child[QUAD_NODE_LB]->node_height = node->node_height + 1;
    node->child[QUAD_NODE_RB]->node_height = node->node_height + 1;

    tree->count += 4;
}

void insert_object(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{
    int i = 0;
    int num = 0;
    LZH_QUAD_TREE *tree = NULL;
    LZH_OBJECT **objs = NULL;

    if (!node || !node->tree) {
        return;
    }

    tree = node->tree;
    num = tree->obj_max_count;
    objs = node->objects;

    for (i = 0; i < num; i++) {
        if (!objs[i]) {
            objs[i] = object;
            node->obj_count++;
            break;
        }
    }
}

#if 0
void remove_object(LZH_QUAD_NODE *node, LZH_OBJECT *object)
{
    int i = 0;
    int num = 0;
    LZH_QUAD_TREE *tree = NULL;
    LZH_OBJECT **objs = NULL;

    if (!node || !node->tree) {
        return;
    }

    tree = node->tree;
    num = tree->obj_max_count;
    objs = node->objects;

    for (i = 0; i < num; i++) {
        if (objs[i] == object) {
            objs[i] = NULL;
            node->obj_count--;
            break;
        }
    }
}
#endif

void find_quad_node(
    LZH_QUAD_NODE *node, const LZH_OBJECT *target, LZH_OBJECT **other, int *count,
    int offset)
{
    LZH_RECTF objrect = { 0 };
    LZH_UINT32 index = 0;

    int num = 0;

    if (!node || !target) {
        return;
    }

    if (!count) {
        return;
    }

    /* �����ж��Ƿ���ѣ����δ���ѣ�ֱ���ڵ�ǰ�ڵ��ϲ��� */
    if (!node->child[0]) {
        find_object(node, target, other ? (other + offset) : NULL, count);
        return;
    }

    if (!get_object_rect(target, &objrect)) {
        return;
    }

    /* ��ȡ�������� */
    index = get_quad_node_index(node, &objrect);
    if (!index) {
        return;
    }

    if ((index & QUAD_NODE_INDEX_RT) == QUAD_NODE_INDEX_RT) {
        find_quad_node(node->child[QUAD_NODE_RT], target, other, &num, offset);
        offset += num;
    }

    if ((index & QUAD_NODE_INDEX_LT) == QUAD_NODE_INDEX_LT) {
        find_quad_node(node->child[QUAD_NODE_LT], target, other, &num, offset);
        offset += num;
    }

    if ((index & QUAD_NODE_INDEX_LB) == QUAD_NODE_INDEX_LB) {
        find_quad_node(node->child[QUAD_NODE_LB], target, other, &num, offset);
        offset += num;
    }

    if ((index & QUAD_NODE_INDEX_RB) == QUAD_NODE_INDEX_RB) {
        find_quad_node(node->child[QUAD_NODE_RB], target, other, &num, offset);
        offset += num;
    }

    *count = offset;
}

void find_object(
    LZH_QUAD_NODE *node, const LZH_OBJECT *target, LZH_OBJECT **other, int *count)
{    
    int i = 0;
    int j = 0;
    int num = 0;
    LZH_QUAD_TREE *tree = NULL;
    LZH_OBJECT **objs = NULL;

    if (!node || !target) {
        return;
    }

    if (!count) {
        return;
    }

    if (!node || !node->tree) {
        return;
    }

    tree = node->tree;
    num = tree->obj_max_count;
    objs = node->objects;

    if (!other) {
        *count = node->obj_count;
        return;
    }

    for (i = 0; i < num; i++) {
        if (objs[i] && objs[i] != target) {
            other[j++] = objs[i];
        }
    }

    *count = j;
}

LZH_BOOL get_object_rect(const LZH_OBJECT *object, LZH_RECTF *rect)
{
#if 0
    LZH_COLLIDER *collider = NULL;

    if (!object || !rect) {
        return LZH_FALSE;
    }

    collider = (LZH_COLLIDER *)lzh_cpnt_get_type(object->components, LZH_CPNT_COLLIDER);
    if (!collider) {
        return LZH_FALSE;
    }

    *rect = lzh_collider_rectf(collider);
#endif
    return LZH_TRUE;
}

/*===========================================================================*/
