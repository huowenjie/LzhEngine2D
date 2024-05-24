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

    // �ƶ��ٶ�
    float moveSpeed;

    // ���
    float fireDistance;

    // �Ƿ�ը
    bool isExplode;

    // �������
    Object *fromObject;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
