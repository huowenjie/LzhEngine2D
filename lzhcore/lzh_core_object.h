#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include <lzh_vec2f.h>

#include "lzh_core_engine.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/
/* 对象(内部) */
/*===========================================================================*/

LINK_DECLARE(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/* 对象结构 */
struct LZH_OBJECT {
    /* 上下文 */
    LZH_CONTEXT context;

    /* 对象名称 */
    char *name;

    /* 对象更新回调和参数*/
    LZH_OBJECT_UPDATE update;
    void *update_param;

    /* 固定时间更新回调和参数 */
    LZH_OBJECT_FIXEDUPDATE fixed_update;
    void *fixed_update_param;

    /* 父对象 */
    LZH_OBJECT *parent;

    /* 子对象链表 */
    LZH_OBJ_LINK *children;

    /* 组件链表 */
    LZH_CPNT_LINK *components;
};

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
