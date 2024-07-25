#ifndef __LZH_CORE_RIGIDBODY2D_H__
#define __LZH_CORE_RIGIDBODY2D_H__

#include <lzh_rigidbody2d.h>
#include <lzh_rbtree.h>

#include "lzh_component.h"
#include "../box2d/lzh_b2_api.h"

/*===========================================================================*/
/* 刚体组件定义(内部) */
/*===========================================================================*/

RBTREE_DECLARE(CLD2D, cld2d, int, LZH_COLLIDER2D *)

struct LZH_RIGIDBODY2D {
    LZH_COMPONENT base;                 /* 基本组件信息 */
    LZH_B2_BODY *b2body;                /* box2d 物理引擎刚体对象 */

    CLD2D_RB_TREE *collider2ds;         /* 碰撞体列表 */
};

/* 比较函数 */
int lzh_rigidbody2d_cld2d_comp(const void *a, const void *b);

/* 移除函数 */
void lzh_rigidbody2d_cld2d_delvisit(const CLD2D_RB_NODE *node, void *args);

/* 向列表中添加碰撞体 */
void lzh_rigidbody2d_add_cld2d(
    LZH_RIGIDBODY2D *rigidbody, LZH_COLLIDER2D *collider2d);

/* 移除碰撞体 */
void lzh_rigibody2d_remove_cld2d(LZH_RIGIDBODY2D *rigidbody, LZH_COLLIDER2D *collider2d);

/*===========================================================================*/

#endif /* __LZH_CORE_RIGIDBODY2D_H__ */
