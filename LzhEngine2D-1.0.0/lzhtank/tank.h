#ifndef __TANK_H__
#define __TANK_H__

#include <vec2.hpp>
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

    // ǰ��
    void ChassisForward(float delta);

    // ����
    void ChassisBackward(float delta);

    // ������ת
    void ChassisRotateL(float delta);

    // ������ת
    void ChassisRotateR(float delta);

    // �ڹ�������ת
    void TurretRotateL(float delta);

    // �ڹ�������ת
    void TurretRotateR(float delta);

    // ���浱ǰ֡λ��״̬
    void SaveHitTransform();

    // �ָ���ǰ֡λ��״̬
    void RestoreHitTransform();

    // ������һ֡����λ��
    void SavePrevPosition();

protected:
    // ̽��ǰ���Ƿ�������
    bool CheckHitObject();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(GameObject *self, GameObject *target);
    virtual void ColliderEndCb(GameObject *self, GameObject *target);

protected:
    enum TankStatus {
        TK_IDLE = 0x00000000U,
        TK_RUN_FORWARD = 0x00000001U,
        TK_RUN_BACKWARD = 0x00000002U,
        TK_ROTATE_L = 0x00000004U,
        TK_ROTATE_R = 0x00000008U,
        TK_TURRET_ROTATE_L = 0x00000010U,
        TK_TURRET_ROTATE_R = 0x00000020U
    };

protected:
    GameObject *chassis;
    GameObject *turret;

    LZH_TRANSFORM *chassisTransform;
    LZH_TRANSFORM *turretTransform;

    LZH_SPRITE *chassisSp;
    LZH_SPRITE *turretSp;

    LZH_RIGIDBODY2D *rigidbody;
    LZH_COLLIDER2D *collider;

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

    // ��һ֡��ײλ��
    glm::vec2 hitSavePos;

    // ��һ֡λ��
    glm::vec2 prevPos;

    // ״̬��
    LZH_UINT32 statusCode;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
