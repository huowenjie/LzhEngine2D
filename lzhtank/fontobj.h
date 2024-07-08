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

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_TEXT *textCpnt;
};

/*===========================================================================*/

#endif /* __FONT_OBJ_H__ */
