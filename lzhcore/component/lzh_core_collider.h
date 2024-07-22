#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 碰撞组件定义(内部) */
/*===========================================================================*/

/* 碰撞组件对象 */
struct LZH_COLLIDER {
    LZH_COMPONENT base;             /* 基本组件信息 */

    LZH_B2_BODY *b2_body;           /* 2d 物理引擎刚体对象 */
    LZH_B2_FIXUTRE *b2_fixture;     /* 2d 物理引擎物理组件 */

    LZH_COLLIDER_CB start_contact;  /* 开始碰撞回调 */
    LZH_COLLIDER_CB end_contact;    /* 结束碰撞回调 */

    void *start_contact_args;       /* 开始碰撞回调参数 */
    void *end_contact_args;         /* 结束碰撞回调参数 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
