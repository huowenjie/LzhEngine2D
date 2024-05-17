#ifndef __TANK_H__
#define __TANK_H__

#include "object.h"

/*===========================================================================*/
/* tank */
/*===========================================================================*/

class Tank : public Object
{
public:
    Tank(LZH_ENGINE *engine);
    virtual ~Tank();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_OBJECT *chassis;
    LZH_OBJECT *turret;

    LZH_SPRITE *chassisSp;
    LZH_SPRITE *turretSp;

    LZH_TRANSFORM *chassisTransform;
    LZH_TRANSFORM *turretTransform;

    bool isAddedScene;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
