#ifndef __LZH_CORE_TEXT_H__
#define __LZH_CORE_TEXT_H__

#include <lzh_text.h>
#include "lzh_component.h"

#include "../engine/lzh_core_engine.h"

/*===========================================================================*/
/* 文本组件(内部) */
/*===========================================================================*/

/* 文本组件对象 */
struct LZH_TEXT
{
    LZH_COMPONENT base;             /* 基本组件信息 */
    FT_Face text_face;              /* 字体信息 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_TEXT_H__ */
