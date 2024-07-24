#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider2d.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 碰撞体定义(内部) */
/*===========================================================================*/

/* 碰撞体对象 */
struct LZH_COLLIDER2D {
    LZH_HASH_CODE hash;                 /* 对象哈希值 */

    LZH_RIGIDBODY2D *rigidbody;         /* 所属 rigidbody */
    LZH_B2_FIXUTRE *b2_fixture;         /* 2d 固定组件 */

    LZH_COLLIDER2D_CB start_contact;    /* 开始碰撞回调 */
    LZH_COLLIDER2D_CB end_contact;      /* 结束碰撞回调 */

    void *start_contact_args;           /* 开始碰撞回调参数 */
    void *end_contact_args;             /* 结束碰撞回调参数 */
};

/* 移除碰撞体 */
void lzh_collider2d_remove(LZH_COLLIDER2D *collider2d);

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
