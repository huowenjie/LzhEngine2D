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
    // ������
    void BeAttacked(Object *from);

protected:
    // �������ڵ�
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

    // �ƶ��ٶ�
    float moveSpeed;

    // ��ת�ٶ�
    float rotateSpeed;

    // ������ת�ٶ�
    float turretRotateSpeed;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
