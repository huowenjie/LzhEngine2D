#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider.h>

#include "../tool/lzh_quadtree.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 碰撞组件定义(内部) */
/*===========================================================================*/

/* 碰撞组件对象 */
struct LZH_CAMERA {
    LZH_COMPONENT base;       /* 基本组件信息 */
    LZH_COLLIDER_PARAM param; /* 组件参数 */

    LZH_QUAD_TREE *quad_tree; /* 四叉树 */
    LZH_COLLIDER_CB callback; /* 碰撞回调 */
};

/**
 * 在组件中：
 * TODO
 * 1.创建四叉树
 * 
 * 组件 UPDATE 逻辑:
 * 2.获取当前场景对象
 * 3.遍历场景中的渲染树对象，将对象添加至四叉树
 * 4.获取和当前对象处于同一区域的对象
 * 5.循环判断是否相交（根据设定的碰撞类型）
 * 6.如果碰撞，调用碰撞回调函数
 * 7.清空四叉树对象
 * 参照 level.cpp 的实现
 */

/*===========================================================================*/


#endif /* __LZH_CORE_COLLIDER_H__ */
