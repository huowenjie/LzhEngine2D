#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include <lzh_vec2f.h>
#include "lzh_core_engine.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/
/* 对象(内部) */
/*===========================================================================*/

/* 对象结构 */
struct LZH_OBJECT {
    LZH_ENGINE *engine;

    /* 对象位置 */
    float x, y;

    /* 对象位置偏移, 默认为 0.0f */
    float offset_x, offset_y;

    /* 对象尺寸 */
    float w, h;

    /* 顺时针方向的旋转角度 */
    float angle;

    /* 旋转中心，默认为对象中心点 */
    float rx, ry;

    /* 对象正方向 */
    LZH_VEC2F forward;

    /* 精灵组件 */
    LZH_SPRITE *sprite;
};

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
