#ifndef __BULLET_H__
#define __BULLET_H__

#include "object.h"

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
    virtual void ColliderCb(LZH_OBJECT *self, LZH_OBJECT *target);

protected:
    LZH_SPRITE *bulletSp;
    LZH_COLLIDER *collider;

    // �ƶ��ٶ�
    float moveSpeed;

    // ���
    float fireDistance;

    // �������
    Object *fromObject;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
