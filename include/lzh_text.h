#ifndef __LZH_TEXT_H__
#define __LZH_TEXT_H__

#include "lzh_type.h"

/*===========================================================================*/
/* �ı���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �����ı���� */
LZH_API LZH_TEXT *lzh_text_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* �����ı���� */
LZH_API void lzh_text_destroy(LZH_TEXT *text);

/* �������� */
LZH_API LZH_BOOL lzh_text_load_font(LZH_TEXT *text, const char *font);

/* ��������ߴ� */
LZH_API void lzh_text_set_font_size(LZH_TEXT *text, int pw, int ph);

/* ����������ɫ */
LZH_API void lzh_text_set_font_color(
    LZH_TEXT *text, float r, float g, float b, float a);

/* �����ı����� */
LZH_API void lzh_text_set_content(LZH_TEXT *text, const char *content);

/* �����ı�ƫ��ֵ */
LZH_API void lzh_text_set_offset(LZH_TEXT *text, float x, float y, float z);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TEXT_H__ */
