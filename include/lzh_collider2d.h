#ifndef __LZH_COLLIDER2D_H__
#define __LZH_COLLIDER2D_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 碰撞体 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 碰撞器类型 */
typedef enum LZH_COLLIDER2D_TYPE {
    UNDEF = 0,
    CT_BOX_2D,
    CT_CIRCLE_2D
} LZH_COLLIDER2D_TYPE;

/* 碰撞回调 */
typedef void (*LZH_COLLIDER2D_CB)(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

/* 创建碰撞组件 */
LZH_API LZH_COLLIDER2D *lzh_collider2d_create(LZH_RIGIDBODY2D *body);

/* 销毁碰撞组件 */
LZH_API void lzh_collider2d_destroy(LZH_COLLIDER2D *collider);

/* 设置碰撞器参数 */
LZH_API void lzh_collider2d_set_type(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_TYPE type);

/* 设置方形碰撞器，如果碰撞器形状是其他形状，则无效 */
LZH_API void lzh_collider2d_set_rect(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h);

/* 设置圆形碰撞器，如果碰撞器形状是其他形状，则无效 */
LZH_API void lzh_collider2d_set_circle(
    LZH_COLLIDER2D *collider, float cx, float cy, float r);

/* 设置开始碰撞回调 */
LZH_API void lzh_collider2d_set_start_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args);

/* 设置结束碰撞回调 */
LZH_API void lzh_collider2d_set_end_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_COLLIDER_H__ */
