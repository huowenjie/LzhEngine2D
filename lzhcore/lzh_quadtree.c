#include <lzh_quadtree.h>
#include <lzh_mem.h>

/*===========================================================================*/

/* ���� quad ���ڵ� */
typedef struct LZH_QUAD_NODE LZH_QUAD_NODE;

/* Ĭ��ÿ���ڵ㱣������������� */
#define MAX_OBJECT_COUNT 4

/*===========================================================================*/

struct LZH_QUAD_NODE
{
    /* ��һ���� */
    LZH_QUAD_NODE *rt;

    /* �ڶ����� */
    LZH_QUAD_NODE *lt;

    /* �������� */
    LZH_QUAD_NODE *lb;

    /* �������� */
    LZH_QUAD_NODE *rb;

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
    LZH_QUAD_NODE *root;
    
    /* �ӽڵ����� */
    int count;

    /* �ӽڵ�����ɶ����������� */
    int obj_max_count;
};

/*===========================================================================*/

LZH_QUAD_TREE *lzh_quad_tree_create(const LZH_RECTF *region)
{
    return NULL;
}

void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree)
{

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

}

/*===========================================================================*/
