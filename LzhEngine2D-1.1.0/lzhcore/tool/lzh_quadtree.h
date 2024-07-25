#ifndef __LZH_QUADTREE_H__
#define __LZH_QUADTREE_H__

#include "lzh_type.h"
#include "lzh_rectf.h"

/*===========================================================================*/
/* 四叉树 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LZH_QUAD_TREE LZH_QUAD_TREE;

/* 创建四叉树 */
LZH_QUAD_TREE *lzh_quad_tree_create();

/* 销毁四叉树 */
void lzh_quad_tree_destroy(LZH_QUAD_TREE *tree);

/* 设置根节点空间区域 */
void lzh_quad_tree_init_root(LZH_QUAD_TREE *tree, const LZH_RECTF *region);

/* 添加对象 */
void lzh_quad_tree_add(LZH_QUAD_TREE *tree, LZH_OBJECT *object);

/* 查找目标对象所在当前区域列表中的所有其他对象 */
void lzh_quad_tree_find(
    LZH_QUAD_TREE *tree, const LZH_OBJECT *target, LZH_OBJECT **other, int *count);

/* 获取区域中对象的最大数量 */
int lzh_quad_tree_obj_max_count(LZH_QUAD_TREE *tree);

/* 清理所有子节点 */
void lzh_quad_tree_clear(LZH_QUAD_TREE *tree);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_QUADTREE_H__ */
