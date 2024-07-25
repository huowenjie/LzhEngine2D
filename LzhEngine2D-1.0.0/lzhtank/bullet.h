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

    // �ƶ��ٶ�
    float moveSpeed;

    // ���
    float fireDistance;

    // �Ƿ�ը
    bool isExplode;

    // �������
    GameObject *fromObject;

    // ���о���
    float flyingDistance;

    // Ŀ���ɫ
    LZH_UINT32 targetRoles;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
