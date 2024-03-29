#ifndef __LZH_COMPONENT_H__
#define __LZH_COMPONENT_H__

#include <lzh_type.h>
#include <lzh_link.h>

#include "../lzh_base.h"

/*===========================================================================*/
/* 组件 */
/*===========================================================================*/

#define LZH_CPNT_UNDEF      0x00000000U /* 未定义的组件 */
#define LZH_CPNT_TRANSFORM  0x00000001U /* 变换组件 */
#define LZH_CPNT_SPRITE     0x00000002U /* 精灵组件 */

typedef struct LZH_COMPONENT LZH_COMPONENT;

struct LZH_COMPONENT {
    /* 基类 */
    LZH_BASE base;

    /* 组件类型 */
    LZH_UINT32 type;

    /* 所属 object */
    LZH_OBJECT *object;

    /* 组件移除回调 */
    void (*remove_component)(LZH_COMPONENT *);
};

LINK_DECLARE(LZH_CPNT, lzh_cpnt, LZH_COMPONENT *)

/* 精灵组件的回调函数 */
int lzh_link_cpnt_comp(const void *cpnt1, const void *cpnt2);
void lzh_link_cpnt_visit(const LZH_CPNT_LINK_NODE *node, void *args);

/* 从组件表中获取对应类型的组件 */
LZH_COMPONENT *lzh_link_cpnt_get_type(LZH_CPNT_LINK *link, LZH_UINT32 type);

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
