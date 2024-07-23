#ifndef __LZH_CORE_RIGIDBODY2D_H__
#define __LZH_CORE_RIGIDBODY2D_H__

#include <lzh_rigidbody2d.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 刚体组件定义(内部) */
/*===========================================================================*/

struct LZH_RIGIDBODY2D {
    LZH_COMPONENT base;                 /* 基本组件信息 */
    LZH_B2_BODY *b2_body;               /* 2d 物理引擎刚体对象 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_RIGIDBODY2D_H__ */
