#ifndef __BULLET_H__
#define __BULLET_H__

#include "gameobject.h"

/*===========================================================================*/
/* bullet */
/*===========================================================================*/

class Bullet : public Object
{
public:
    Bullet(LZH_ENGINE *eg);
    virtual ~Bullet();

public:
    void SetFromObject(Object *from);

protected:
    void BulletExplode();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(Object *self, Object *target);

protected:
    LZH_SPRITE *bulletSp;
    LZH_COLLIDER *collider;

    // 移动速度
    float moveSpeed;

    // 射程
    float fireDistance;

    // 是否爆炸
    bool isExplode;

    // 发射对象
    Object *fromObject;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
