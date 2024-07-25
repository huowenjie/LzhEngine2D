#ifndef __LZH_QUADTREE_H__
#define __LZH_QUADTREE_H__

#include "lzh_type.h"
#include "lzh_rectf.h"

/*===========================================================================*/
/* �Ĳ��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LZH_QUAD_TREE LZH_QUAD_TREE;

/* �����Ĳ��� */
LZH_QUAD_TREE *lzh_quad_tree_create();

/* �����Ĳ��� */
void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree);

/* ���ø��ڵ�ռ����� */
void lzh_quad_tree_init_root(LZH_QUAD_TREE *tree, const LZH_RECTF *region);

/* ��Ӷ��� */
void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object);

/* ����Ŀ��������ڵ�ǰ�����б��е������������� */
void lzh_quad_tree_find(
    LZH_QUAD_TREE *tree, const LZH_OBJECT *target, LZH_OBJECT **other, int *count);

/* ��ȡ�����ж����������� */
int lzh_quad_tree_obj_max_count(LZH_QUAD_TREE *tree);

/* ���������ӽڵ� */
void lzh_quad_tree_clear(LZH_QUAD_TREE *tree);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_QUADTREE_H__ */
