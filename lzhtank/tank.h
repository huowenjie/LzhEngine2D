#ifndef __TANK_H__
#define __TANK_H__

#include <lzh_engine.h>

/*===========================================================================*/
/* tank */
/*===========================================================================*/

class Tank
{
public:
    Tank(LZH_ENGINE *engine);
    ~Tank();

protected:
    void Update();
    void FixedUpdate();

protected:
    static void UpdateTank(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);
    static void FixedUpdateTank(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);

protected:
    LZH_OBJECT *object;
    LZH_OBJECT *chassis;
    LZH_OBJECT *turret;

    LZH_SPRITE *chassisSp;
    LZH_SPRITE *turretSp;

    LZH_TRANSFORM *transform;
    LZH_TRANSFORM *chassisTransform;
    LZH_TRANSFORM *turretTransform;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
