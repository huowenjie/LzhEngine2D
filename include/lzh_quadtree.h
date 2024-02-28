#ifndef __LZH_QUADTREE_H__
#define __LZH_QUADTREE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 四叉树 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建四叉树 */
LZH_API LZH_QUAD_TREE *lzh_quad_tree_create(const LZH_RECTF *region);

/* 销毁四叉树 */
LZH_API void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree);

/* 添加对象 */
LZH_API void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object);

/* 查找目标对象所在当前区域列表中的所有其他对象 */
LZH_API void lzh_quad_tree_find(
    LZH_QUAD_TREE *tree, const LZH_OBJECT *target, LZH_OBJECT **other, int *count);

/* 获取区域中对象的最大数量 */
LZH_API int lzh_quad_tree_obj_max_count(LZH_QUAD_TREE *tree);

/* 清理所有子节点 */
LZH_API void lzh_quad_tree_clear(LZH_QUAD_TREE *tree);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_QUADTREE_H__ */
