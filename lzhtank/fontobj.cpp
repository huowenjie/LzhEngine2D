#include "fontobj.h"
#include "globalres.h"

#include <lzh_transform.h>

/*===========================================================================*/

FontObj::FontObj(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_UI;
    textCpnt = lzh_text_create(eg, object);

    lzh_text_load_font(textCpnt, GetFontPath());
    lzh_text_set_font_size(textCpnt, 20, 20);
    lzh_text_set_content(textCpnt, "Running");
    lzh_text_set_font_color(textCpnt, 1.0f, 1.0f, 1.0f, 1.0f);
}

FontObj::~FontObj()
{
}

void FontObj::SetText(const std::string &text)
{
    lzh_text_set_content(textCpnt, text.c_str());
}

void FontObj::SetTextColor(float r, float g, float b)
{
    lzh_text_set_font_color(textCpnt, r, g, b, 1.0f);
}

void FontObj::SetTextSize(float w, float h)
{
    lzh_text_set_font_size(textCpnt, w, h);
}

float FontObj::GetTextHeight() const
{
    return lzh_text_get_height(textCpnt);
}

void FontObj::Update(LZH_ENGINE *eg)
{
    static float tcount = 0.0f;

    tcount += lzh_engine_interval(eg);
    float r = fabsf(sin(tcount));
    float g = fabsf(cos(tcount));
    float b = fabsf(sin(tcount));

    SetTextColor(r, g, b);
}

void FontObj::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
