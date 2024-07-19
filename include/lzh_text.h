#ifndef __LZH_TEXT_H__
#define __LZH_TEXT_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 文本组件 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建文本组件 */
LZH_API LZH_TEXT *lzh_text_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* 销毁文本组件 */
LZH_API void lzh_text_destroy(LZH_TEXT *text);

/* 加载字体 */
LZH_API LZH_BOOL lzh_text_load_font(LZH_TEXT *text, const char *font);

/* 设置字体尺寸 */
LZH_API void lzh_text_set_font_size(LZH_TEXT *text, int pw, int ph);

/* 设置字体颜色 */
LZH_API void lzh_text_set_font_color(
    LZH_TEXT *text, float r, float g, float b, float a);

/* 设置文本内容 */
LZH_API void lzh_text_set_content(LZH_TEXT *text, const char *content);

/* 获取文本宽度 */
LZH_API float lzh_text_get_width(LZH_TEXT *text);

/* 获取文本高度 */
LZH_API float lzh_text_get_height(LZH_TEXT *text);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TEXT_H__ */
