#include "fontobj.h"
#include "globalres.h"

#include <lzh_transform.h>

/*===========================================================================*/

FontObj::FontObj(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_UI;
    textCpnt = lzh_text_create(eg, object);

    lzh_text_load_font(textCpnt, GetFontPath());
    lzh_text_set_font_size(textCpnt, 60, 60);
    lzh_text_set_content(textCpnt, "abcÖÐ¹ú");
    lzh_text_set_font_color(textCpnt, 1.0f, 1.0f, 1.0f, 1.0f);

    float height = lzh_text_get_height(textCpnt);
    lzh_transform_set_pos(transform, -40.0f, 30.0f - height, 0.0f);
}

FontObj::~FontObj()
{
}

void FontObj::Update(LZH_ENGINE *eg)
{

}

void FontObj::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
