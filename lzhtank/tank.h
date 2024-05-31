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
    // ������
    void BeAttacked(GameObject *from);

protected:
    // �������ڵ�
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

    // �ƶ��ٶ�
    float moveSpeed;

    // ��ת�ٶ�
    float rotateSpeed;

    // ������ת�ٶ�
    float turretRotateSpeed;

    // ����ֵ
    int tankhp;

    // �Ƿ���ײ����Ķ���
    bool isCollideOther;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
