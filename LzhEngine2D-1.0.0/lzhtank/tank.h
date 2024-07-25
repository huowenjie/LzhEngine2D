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
    // 被攻击
    void BeAttacked(GameObject *from);

protected:
    // 开火发射炮弹
    void Fire();

    // 前进
    void ChassisForward(float delta);

    // 后退
    void ChassisBackward(float delta);

    // 向右旋转
    void ChassisRotateL(float delta);

    // 向右旋转
    void ChassisRotateR(float delta);

    // 炮管向左旋转
    void TurretRotateL(float delta);

    // 炮管向右旋转
    void TurretRotateR(float delta);

    // 保存当前帧位移状态
    void SaveHitTransform();

    // 恢复当前帧位移状态
    void RestoreHitTransform();

    // 保存上一帧对象位置
    void SavePrevPosition();

protected:
    // 探测前方是否有物体
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

    // 上一帧碰撞位置
    glm::vec2 hitSavePos;

    // 上一帧位置
    glm::vec2 prevPos;

    // 状态码
    LZH_UINT32 statusCode;
};

/*===========================================================================*/

#endif /* __TANK_H__ */
