#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "gameobject.h"

/*===========================================================================*/
/* explode */
/*===========================================================================*/

class Explode : public GameObject
{
public:
    Explode(LZH_ENGINE *eg, Scene *scene);
    virtual ~Explode();

protected:
    void LastFrame();
    static LZH_UINT32 LastFrameCb(void *args);

protected:
    LZH_SPRITE *explodeSp;
};

/*===========================================================================*/

#endif /* __EXPLODE_H__ */
