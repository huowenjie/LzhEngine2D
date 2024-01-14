#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include "lzh_core_engine.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/
/* 对象(内部) */
/*===========================================================================*/

/* 对象结构 */
struct LZH_OBJECT {
    LZH_ENGINE *engine;

    float x, y;
    float w, h;

    LZH_SPRITE *sprite;
};

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
