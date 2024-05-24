#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "gameobject.h"

/*===========================================================================*/
/* explode */
/*===========================================================================*/

class Explode : public GameObject
{
public:
    Explode(LZH_ENGINE *eg);
    virtual ~Explode();

protected:
    LZH_SPRITE *explodeSp;
};

/*===========================================================================*/

#endif /* __EXPLODE_H__ */
