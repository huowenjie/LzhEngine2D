#ifndef __LZH_COLLIDER_H__
#define __LZH_COLLIDER_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 碰撞组件 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 碰撞器类型 */
typedef enum LZH_COLLIDER_TYPE {
    UNDEF = 0,
    BOX_2D,
    CIRCLE_2D
} LZH_COLLIDER_TYPE;

/* 方盒碰撞器 2D */
typedef struct LZH_COLLIDER_BOX_2D {
    float cx;       /* 中心点局部坐标 x */
    float cy;       /* 中心点局部坐标 y */
    float w;        /* 方盒的宽度 w */
    float h;        /* 方盒的高度 h */
} LZH_COLLIDER_BOX_2D;

/* 圆形碰撞器 2D */
typedef struct LZH_COLLIDER_CIRCLE_2D {
    float cx;       /* 圆心坐标 x */
    float cy;       /* 圆心坐标 y */
    float r;        /* 半径 */
} LZH_COLLIDER_CIRCLE_2D;

/* 碰撞器参数 */
typedef struct LZH_COLLIDER_PARAM {
    LZH_COLLIDER_TYPE type;

    union {
        LZH_COLLIDER_BOX_2D box2d;
        LZH_COLLIDER_CIRCLE_2D circle2d;
    };
} LZH_COLLIDER_PARAM;

/* 碰撞回调 */
typedef void (*LZH_COLLIDER_CB)(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

/* 创建碰撞组件 */
LZH_API LZH_COLLIDER *lzh_collider_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* 销毁碰撞组件 */
LZH_API void lzh_collider_destroy(LZH_COLLIDER *collider);

/* 设置碰撞器参数 */
LZH_API void lzh_collider_set_param(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param);

/* 设置开始碰撞回调 */
LZH_API void lzh_collider_set_start_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args);

/* 设置结束碰撞回调 */
LZH_API void lzh_collider_set_end_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_COLLIDER_H__ */
