#ifndef __BULLET_H__
#define __BULLET_H__

#include "gameobject.h"

/*===========================================================================*/
/* bullet */
/*===========================================================================*/

class Bullet : public GameObject
{
public:
    Bullet(LZH_ENGINE *eg, Scene *scene, LZH_UINT32 roles = RT_None);
    virtual ~Bullet();

public:
    void SetFromObject(GameObject *from);

protected:
    void BulletExplode();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(GameObject *self, GameObject *target);

protected:
    LZH_SPRITE *bulletSp;
    LZH_RIGIDBODY2D *rigidbody;
    LZH_COLLIDER2D *collider;

    // 移动速度
    float moveSpeed;

    // 射程
    float fireDistance;

    // 是否爆炸
    bool isExplode;

    // 发射对象
    GameObject *fromObject;

    // 飞行距离
    float flyingDistance;

    // 目标角色
    LZH_UINT32 targetRoles;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
