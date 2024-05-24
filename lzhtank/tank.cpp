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
    chassis = lzh_object_create(eg);
    turret = lzh_object_create(eg);

    chassisSp = lzh_sprite_create(eg, get_tank_res_path());
    turretSp = lzh_sprite_create(eg, get_tank_turret_path());

    chassisTransform = lzh_object_get_transform(chassis);
    turretTransform = lzh_object_get_transform(turret);

    collider = lzh_collider_create(eg);
    
    moveSpeed = 5.0f;
    rotateSpeed = 60.0f;
    turretRotateSpeed = 60.0f;

    lzh_object_add_component(chassis, chassisSp);
    lzh_object_add_component(turret, turretSp);
    lzh_object_add_component(object, collider);

    lzh_object_add_child(object, turret);
    lzh_object_add_child(object, chassis);

    // 只单独命名两个子对象
    lzh_object_set_name(chassis, "chassis");
    lzh_object_set_name(turret, "turret");

    lzh_transform_scale(turretTransform, 0.5f, 0.5f, 0.5f);
    lzh_transform_translate(turretTransform, 0.0f, 0.0f, 0.1f);

    LZH_COLLIDER_PARAM param;
    param.type = BOX_2D;
    param.box2d.x = -0.5f;
    param.box2d.y = 0.5f;
    param.box2d.w = 1.0f;
    param.box2d.h = 1.0f;
    lzh_collider_set_param(collider, &param);
}

Tank::~Tank()
{
}

/*===========================================================================*/

void Tank::BeAttacked(GameObject *from)
{
    
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
            delete turret;
        }

        bullet->SetFromObject(this);
    }
}

/*===========================================================================*/

void Tank::Update(LZH_ENGINE *eg)
{
}

void Tank::FixedUpdate(LZH_ENGINE *eg)
{
}

/*===========================================================================*/
