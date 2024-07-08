#include "fontobj.h"
#include "globalres.h"

/*===========================================================================*/

FontObj::FontObj(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_UI;
    textCpnt = lzh_text_create(eg, object);

    lzh_text_load_font(textCpnt, GetFontPath());
    lzh_text_set_font_size(textCpnt, 60, 60);
    lzh_text_set_content(textCpnt, "abc");
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
