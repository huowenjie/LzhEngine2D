#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "object.h"

/*===========================================================================*/
/* explode */
/*===========================================================================*/

class Explode : public Object
{
public:
    Explode(LZH_ENGINE *eg);
    virtual ~Explode();

protected:
    LZH_SPRITE *explodeSp;
};

/*===========================================================================*/

#endif /* __EXPLODE_H__ */
