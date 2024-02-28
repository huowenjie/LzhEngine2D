#include <lzh_quadtree.h>
#include <lzh_mem.h>

/*===========================================================================*/

/* 定义 quad 树节点 */
typedef struct LZH_QUAD_NODE LZH_QUAD_NODE;

/* 默认每个节点保存的最大对象数量 */
#define MAX_OBJECT_COUNT 4

/*===========================================================================*/

struct LZH_QUAD_NODE
{
    /* 第一象限 */
    LZH_QUAD_NODE *rt;

    /* 第二象限 */
    LZH_QUAD_NODE *lt;

    /* 第三象限 */
    LZH_QUAD_NODE *lb;

    /* 第四象限 */
    LZH_QUAD_NODE *rb;

    /* 根节点地址 */
    LZH_QUAD_NODE *root;

    /* 当前节点表示的空间范围 */
    LZH_RECTF bound;

    /* 当前节点包含的对象列表 */
    LZH_OBJECT **objects;

    /* 当前节点的对象数量 */
    int obj_count;
};

struct LZH_QUAD_TREE
{
    LZH_QUAD_NODE *root;
    
    /* 子节点数量 */
    int count;

    /* 子节点可容纳对象的最大数量 */
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
