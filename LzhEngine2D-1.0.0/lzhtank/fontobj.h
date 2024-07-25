#ifndef __FONT_OBJ_H__
#define __FONT_OBJ_H__

#include <lzh_text.h>
#include "gameobject.h"

/*===========================================================================*/
/* tank */
/*===========================================================================*/

class FontObj : public GameObject
{
public:
    FontObj(LZH_ENGINE *eg, Scene *scene);
    virtual ~FontObj();

public:
    void SetText(const std::string &text);
    void SetTextColor(float r, float g, float b);
    void SetTextSize(float w, float h);

    float GetTextHeight() const;

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_TEXT *textCpnt;
};

/*===========================================================================*/

#endif /* __FONT_OBJ_H__ */
