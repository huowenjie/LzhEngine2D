#ifndef __LZH_QUADTREE_H__
#define __LZH_QUADTREE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* �Ĳ��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �����Ĳ��� */
LZH_API LZH_QUAD_TREE *lzh_quad_tree_create(const LZH_RECTF *region);

/* �����Ĳ��� */
LZH_API void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree);

/* ��Ӷ��� */
LZH_API void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object);

/* ����Ŀ��������ڵ�ǰ�����б��е������������� */
LZH_API void lzh_quad_tree_find(
    LZH_QUAD_TREE *tree, const LZH_OBJECT *target, LZH_OBJECT **other, int *count);

/* ��ȡ�����ж����������� */
LZH_API int lzh_quad_tree_obj_max_count(LZH_QUAD_TREE *tree);

/* ���������ӽڵ� */
LZH_API void lzh_quad_tree_clear(LZH_QUAD_TREE *tree);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_QUADTREE_H__ */
