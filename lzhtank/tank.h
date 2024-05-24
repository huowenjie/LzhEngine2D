#ifndef __TANK_H__
#define __TANK_H__

#include "gameobject.h"

/*===========================================================================*/
/* tank */
/*===========================================================================*/

class Tank : public Object
{
public:
    Tank(LZH_ENGINE *eg);
    virtual ~Tank();

public:
    // 被攻击
    void BeAttacked(Object *from);

protected:
    // 开火发射炮弹
    void Fire();

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

    LZH_COLLIDER *collider;

    // 移动速度
    float moveSpeed;

    // 旋转速度
    float rotateSpeed;

    // 炮塔旋转速度
    float turretRotateSpeed;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
