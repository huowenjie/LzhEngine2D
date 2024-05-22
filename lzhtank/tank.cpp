#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_transform.h>

#include "globalres.h"
#include "scene.h"
#include "tank.h"
#include "bullet.h"

/*===========================================================================*/

Tank::Tank(LZH_ENGINE *eg) : Object(eg)
{
    chassis = lzh_object_create(eg);
    turret = lzh_object_create(eg);

    chassisSp = lzh_sprite_create(eg, get_tank_res_path());
    turretSp = lzh_sprite_create(eg, get_tank_turret_path());

    chassisTransform = lzh_object_get_transform(chassis);
    turretTransform = lzh_object_get_transform(turret);

    lzh_object_add_component(chassis, chassisSp);
    lzh_object_add_component(turret, turretSp);

    lzh_object_add_child(object, turret);
    lzh_object_add_child(object, chassis);

    // 只单独命名两个子对象
    lzh_object_set_name(chassis, "chassis");
    lzh_object_set_name(turret, "turret");

    lzh_transform_scale(turretTransform, 0.5f, 0.5f, 0.5f);
    lzh_transform_translate(turretTransform, 0.0f, 0.0f, 0.1f);

    moveSpeed = 5.0f;
    rotateSpeed = 60.0f;
    turretRotateSpeed = 60.0f;
}

Tank::~Tank()
{
}

/*===========================================================================*/

void Tank::Fire()
{
    if (currentScene) {
        Bullet *bullet = new Bullet(engine);

        if (!bullet) {
            return;
        }

        float x = 0.0f;
        float y = 0.0f;
        float r = 0.0f;

        GetPosition(&x, &y);
        bullet->SetPosition(x, y);

        Object *turret = FindChildRecursion("turret");

        if (turret) {
            r = turret->GetRotateWorldAngle();
            bullet->SetRotate(r);
            delete turret;
        }

        currentScene->AddObjectToScene(bullet, true);
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
