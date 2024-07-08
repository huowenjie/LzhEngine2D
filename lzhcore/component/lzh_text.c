#include <lzh_mem.h>
#include "lzh_core_text.h"

/*===========================================================================*/

/* 字体渲染 */
static void lzh_text_draw(LZH_BASE *base, void *args);

/* 移除字体，不更改所属对象的信息 */
static void lzh_text_remove(LZH_COMPONENT *cpnt);

/*===========================================================================*/

LZH_TEXT *lzh_text_create(LZH_ENGINE *engine, LZH_OBJECT *object)
{
    LZH_TEXT *text = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine || !object) {
        return NULL;
    }

    text = LZH_MALLOC(sizeof(LZH_TEXT));
    if (!text) {
        return NULL;
    }
    memset(text, 0, sizeof(LZH_TEXT));

    base = &text->base;
    lzh_cpnt_init(base, LZH_CPNT_TEXT, object);

    base->base.engine = engine;
    base->base.draw = lzh_text_draw;
    base->remove_component = lzh_text_remove;

    text->text_face = NULL;
    return text;
}

void lzh_text_destroy(LZH_TEXT *text)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)text);
}

LZH_BOOL lzh_text_load_font(LZH_TEXT *text, const char *font)
{
    FT_Face face = NULL;
    LZH_ENGINE *engine = NULL;

    if (!text || !font || !*font) {
        return LZH_FALSE;
    }

    engine = text->base.base.engine;
    if (!engine) {
        return LZH_FALSE;
    }

    if (text->text_face) {
        if (FT_Done_Face(text->text_face)) {
            return LZH_FALSE;
        }
        text->text_face = NULL;
    }

    if (FT_New_Face(engine->ft_lib, font, 0, &face)) {
        return LZH_FALSE;
    }

    text->text_face = face;
    return LZH_TRUE;
}

void lzh_text_set_font_size(LZH_TEXT *text, int pw, int ph)
{
    FT_Face face = NULL;
    
    if (!text) {
        return;
    }

    face = text->text_face;
    if (!face) {
        return;
    }

    FT_Set_Pixel_Sizes(face, pw, ph);  
}

void lzh_text_set_font_color(
    LZH_TEXT *text, float r, float g, float b, float a)
{
    
}

void lzh_text_set_content(LZH_TEXT *text, const char *content)
{
    if (text && text->text_face) {
        FT_ULong charcode = 0;
        FT_UInt index = FT_Get_Char_Index(text->text_face, charcode);
    }
}

void lzh_text_set_offset(LZH_TEXT *text, float x, float y, float z)
{

}

/*===========================================================================*/

void lzh_text_draw(LZH_BASE *base, void *args)
{

}

void lzh_text_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TEXT *text = (LZH_TEXT *)cpnt;

        if (text->text_face) {
            FT_Face face = text->text_face;
            FT_Done_Face(face);
            text->text_face = NULL;
        }

        lzh_cpnt_quit(cpnt);
        LZH_FREE(text);
    }
}

/*===========================================================================*/
