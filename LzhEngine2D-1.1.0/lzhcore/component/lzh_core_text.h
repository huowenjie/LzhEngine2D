#ifndef __LZH_CORE_TEXT_H__
#define __LZH_CORE_TEXT_H__

#include <lzh_text.h>
#include <lzh_rbtree.h>

#include "lzh_component.h"

#include "../graphic/lzh_texture.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/
/* 文本组件(内部) */
/*===========================================================================*/

RBTREE_DECLARE(LZH_TEXT, lzh_text, int, LZH_CHARACTER *)

/* 文本组件对象 */
struct LZH_TEXT
{
    LZH_COMPONENT base;             /* 基本组件信息 */

    FT_Face text_face;              /* 字体信息 */
    LZH_TEXT_RB_TREE *characters;   /* 字符串序列 */

    LZH_VEC4F text_color;           /* 文本颜色 */
    float width;                    /* 文本对象宽度 */
    float height;                   /* 文本对象高度 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_TEXT_H__ */
