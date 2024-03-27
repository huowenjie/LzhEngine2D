#ifndef __LZH_COMPONENT_H__
#define __LZH_COMPONENT_H__

#include <lzh_type.h>
#include <lzh_link.h>

#include "lzh_context.h"

/*===========================================================================*/
/* 组件 */
/*===========================================================================*/

#define LZH_CPNT_UNDEF      0x00000000U /* 未定义的组件 */
#define LZH_CPNT_TRANSFORM  0x00000001U /* 变换组件 */
#define LZH_CPNT_SPRITE     0x00000002U /* 精灵组件 */

typedef struct LZH_COMPONENT {
    /* 组件上下文 */
    LZH_CONTEXT context;

    /* 组件类型 */
    LZH_UINT32 type;

    /* 所属 object */
    LZH_OBJECT *object;
} LZH_COMPONENT;

LINK_DECLARE(LZH_CPNT, lzh_cpnt, LZH_COMPONENT *)

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
