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

    chassisSp = lzh_sprite_create(eg, chassis->GetObjectHandle(), get_tank_res_path());
    turretSp = lzh_sprite_create(eg, turret->GetObjectHandle(), get_tank_turret_path());

    collider = lzh_collider_create(eg, object);

    moveSpeed = 5.0f;
    rotateSpeed = 60.0f;
    turretRotateSpeed = 60.0f;
    tankhp = 1;

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

/*===========================================================================*/

void Tank::Update(LZH_ENGINE *eg)
{

}

void Tank::FixedUpdate(LZH_ENGINE *eg)
{
}

void Tank::ColliderCb(GameObject *self, GameObject *target)
{
    GameObject::ObjectType type = target->GetObjectType();
    if (type != OT_Explode || type != OT_Bullet) {
        isCollideOther = true;
    }
}

/*===========================================================================*/
