#ifndef __TANK_H__
#define __TANK_H__

#include "gameobject.h"

/*===========================================================================*/
/* tank */
/*===========================================================================*/

class Tank : public GameObject
{
public:
    Tank(LZH_ENGINE *eg, Scene *scene);
    virtual ~Tank();

public:
    // 被攻击
    void BeAttacked(GameObject *from);

protected:
    // 开火发射炮弹
    void Fire();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(GameObject *self, GameObject *target);
    virtual void ColliderEndCb(GameObject *self, GameObject *target);

protected:
    GameObject *chassis;
    GameObject *turret;

    LZH_SPRITE *chassisSp;
    LZH_SPRITE *turretSp;

    LZH_COLLIDER *collider;

    // 移动速度
    float moveSpeed;

    // 旋转速度
    float rotateSpeed;

    // 炮塔旋转速度
    float turretRotateSpeed;

    // 生命值
    int tankhp;

    // 是否碰撞到别的对象
    bool isCollideOther;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
