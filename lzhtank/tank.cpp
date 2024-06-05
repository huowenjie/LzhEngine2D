#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_transform.h>
#include <lzh_collider.h>

#include "globalres.h"
#include "scene.h"
#include "tank.h"
#include "bullet.h"

/*===========================================================================*/

Tank::Tank(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_Tank;
    
    chassis = new GameObject(eg, scene);
    turret = new GameObject(eg, scene);

    chassisTransform = chassis->GetTransform();
    turretTransform = turret->GetTransform();

    chassisSp = lzh_sprite_create(eg, chassis->GetObjectHandle(), GetTankResPath());
    turretSp = lzh_sprite_create(eg, turret->GetObjectHandle(), GetTankTurretPath());

    collider = lzh_collider_create(eg, object);

    moveSpeed = 5.0f;
    rotateSpeed = 60.0f;
    turretRotateSpeed = 60.0f;
    tankhp = 1;
    isCollideOther = false;

    prevX = 0.0f;
    prevY = 0.0f;
    statusCode = TK_IDLE;

    // 只单独命名两个子对象
    chassis->SetName("chassis");
    turret->SetName("turret");

    AddChild(turret);
    AddChild(chassis);

    turret->SetScale(0.5f, 0.5f);
    turret->SetDepth(0.1f);

    LZH_COLLIDER_PARAM param;
    param.type = BOX_2D;
    param.box2d.cx = 0.0f;
    param.box2d.cy = 0.0f;
    param.box2d.w = 1.0f;
    param.box2d.h = 1.0f;
    lzh_collider_set_param(collider, &param);
    lzh_collider_set_start_contact(collider, GameObject::ColliderObjectCb, this);
    lzh_collider_set_end_contact(collider, GameObject::ColliderObjectEndCb, this);
}

Tank::~Tank()
{
    if (turret) {
        delete turret;
    }

    if (chassis) {
        delete chassis;
    }
}

/*===========================================================================*/

void Tank::BeAttacked(GameObject *from)
{
    if (from) {
        tankhp--;

        if (!tankhp) {
            currentScene->ToFreeGameObject(this);
        }
    }
}

void Tank::Fire()
{
    if (currentScene) {
        Bullet *bullet = new Bullet(engine, currentScene);

        if (!bullet) {
            return;
        }

        float x = 0.0f;
        float y = 0.0f;
        float r = 0.0f;

        GetPosition(&x, &y);
        bullet->SetPosition(x, y);

        GameObject *turret = FindChildRecursion("turret");

        if (turret) {
            r = turret->GetRotateWorldAngle();
            bullet->SetRotate(r);
        }

        bullet->SetFromObject(this);
        currentScene->AddObject(bullet);
    }
}

void Tank::ChassisForward(float delta)
{
    float ms = moveSpeed * delta;
    float x = 0.0f;
    float y = 0.0f;

    lzh_transform_get_forward(transform, &x, &y, NULL);
    x *= ms;
    y *= ms;
    lzh_transform_translate(transform, x, y, 0.0f);

    statusCode |= TK_RUN_FORWARD;
    statusCode &= (~TK_RUN_BACKWARD);
}

void Tank::ChassisBackward(float delta)
{
    float ms = moveSpeed * delta;
    float x = 0.0f;
    float y = 0.0f;

    lzh_transform_get_backward(transform, &x, &y, NULL);
    x *= ms;
    y *= ms;
    lzh_transform_translate(transform, x, y, 0.0f);

    statusCode |= TK_RUN_BACKWARD;
    statusCode &= (~TK_RUN_FORWARD);
}

void Tank::ChassisRotateL(float delta)
{
    float rs = rotateSpeed * delta;
    lzh_transform_rotate_z(transform, rs);

    statusCode |= TK_ROTATE_L;
    statusCode &= (~TK_ROTATE_R);
}

void Tank::ChassisRotateR(float delta)
{
    float rs = -rotateSpeed * delta;
    lzh_transform_rotate_z(transform, rs);

    statusCode |= TK_ROTATE_R;
    statusCode &= (~TK_ROTATE_L);
}

void Tank::TurretRotateL(float delta)
{
    float ts = turretRotateSpeed * delta;
    lzh_transform_rotate_z(turretTransform, ts);

    statusCode |= TK_TURRET_ROTATE_L;
    statusCode &= (~TK_TURRET_ROTATE_R);
}

void Tank::TurretRotateR(float delta)
{
    float ts = -turretRotateSpeed * delta;
    lzh_transform_rotate_z(turretTransform, ts);

    statusCode |= TK_TURRET_ROTATE_R;
    statusCode &= (~TK_TURRET_ROTATE_L);
}

void Tank::SaveTransform()
{
    lzh_transform_get_pos(transform, &prevX, &prevY, NULL);
}

void Tank::RestoreTransform()
{
    lzh_transform_set_pos(transform, prevX, prevY, 0.0f);
}

/*===========================================================================*/

void Tank::Update(LZH_ENGINE *eg)
{
    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if (statusCode & TK_RUN_FORWARD) {
        lzh_transform_get_forward(transform, &deltaX, &deltaY, NULL);
    } else if (statusCode & TK_RUN_BACKWARD) {
        lzh_transform_get_backward(transform, &deltaX, &deltaY, NULL);
    } else {
        return;
    }

    GameObject *obj = currentScene->RayCastObject(
        prevX, prevY, prevX + deltaX, prevY + deltaY);
    if (obj) {
        printf("RayCast Object! Name = %s\n", obj->GetName().c_str());
        RestoreTransform();
    }

    statusCode = TK_IDLE;
}

void Tank::FixedUpdate(LZH_ENGINE *eg)
{
    if (isCollideOther) {
        //RestoreTransform();
    }
}

void Tank::ColliderCb(GameObject *self, GameObject *target)
{
    GameObject::ObjectType type = target->GetObjectType();
    if (type != OT_Explode || type != OT_Bullet) {
        //isCollideOther = true;
    }

    printf("ColliderCb tank!\n");
    //SaveTransform();
}

void Tank::ColliderEndCb(GameObject *self, GameObject *target)
{
    printf("ColliderEndCb tank!\n");
    isCollideOther = false;
}

/*===========================================================================*/
