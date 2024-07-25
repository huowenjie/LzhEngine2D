#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider2d.h>

#include "lzh_component.h"
#include "../box2d/lzh_b2_api.h"

/*===========================================================================*/
/* 碰撞体定义(内部) */
/*===========================================================================*/

/* 碰撞体对象 */
struct LZH_COLLIDER2D {
    int id;                             /* 对象标识 */

    LZH_RIGIDBODY2D *rigidbody;         /* 所属 rigidbody */
    LZH_B2_FIXUTRE *b2fixture;         /* 2d 固定组件 */

    LZH_COLLIDER2D_CB start_contact;    /* 开始碰撞回调 */
    LZH_COLLIDER2D_CB end_contact;      /* 结束碰撞回调 */

    void *start_contact_args;           /* 开始碰撞回调参数 */
    void *end_contact_args;             /* 结束碰撞回调参数 */
};

/* 移除碰撞体 */
void lzh_collider2d_remove(LZH_COLLIDER2D *collider);

/* 组件加载到对象中 */
void lzh_collider2d_load(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body);

/* 组件从对象中移除 */
void lzh_collider2d_unload(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body);

/* 创建 box2d 形状 */
void lzh_collider2d_create_box2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h);

/* 创建 circle2d 形状 */
void lzh_collider2d_create_circle2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float r);

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
