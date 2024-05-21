#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider.h>

#include "../tool/lzh_quadtree.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 碰撞组件定义(内部) */
/*===========================================================================*/

/* 碰撞组件对象 */
struct LZH_COLLIDER {
    LZH_COMPONENT base;       /* 基本组件信息 */
    LZH_QUAD_TREE *quad;      /* 四叉树 */

    LZH_COLLIDER_PARAM param; /* 组件参数 */
    LZH_COLLIDER_CB callback; /* 碰撞回调 */
};

/*===========================================================================*/


#endif /* __LZH_CORE_COLLIDER_H__ */
