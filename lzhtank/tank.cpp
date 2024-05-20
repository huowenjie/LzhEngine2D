#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_transform.h>
#include <lzh_keyboard.h>

#include "globalres.h"
#include "scene.h"
#include "tank.h"
#include "bullet.h"

/*===========================================================================*/

Tank::Tank(LZH_ENGINE *engine) : Object(engine)
{
    chassis = lzh_object_create(engine);
    turret = lzh_object_create(engine);

    chassisSp = lzh_sprite_create(engine, get_tank_res_path());
    turretSp = lzh_sprite_create(engine, get_tank_turret_path());

    chassisTransform = lzh_object_get_transform(chassis);
    turretTransform = lzh_object_get_transform(turret);

    lzh_object_add_component(chassis, chassisSp);
    lzh_object_add_component(turret, turretSp);

    lzh_object_add_child(object, turret);
    lzh_object_add_child(object, chassis);

    lzh_object_set_name(object, "tank");
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
            r = turret->GetRotateAngle();
            bullet->SetRotate(r);
            delete turret;
        }

        currentScene->AddObjectToScene(bullet);
    }
}

/*===========================================================================*/

void Tank::Update(LZH_ENGINE *eg)
{
    float delta = 0.0f;
    float ms = 0.0f;
    float rs = 0.0f;
    float ts = 0.0f;

    float x = 0.0f;
    float y = 0.0f;

    if (!eg) {
        return;
    }

    delta = lzh_engine_interval(eg);
    ms = moveSpeed * delta;
    rs = rotateSpeed * delta;
    ts = turretRotateSpeed * delta;

    if (lzh_get_key_status(KEY_CODE_W)) {
        lzh_transform_get_forward(transform, &x, &y, NULL);
        x *= ms;
        y *= ms;
        lzh_transform_translate(transform, x, y, 0.0f);
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        lzh_transform_get_backward(transform, &x, &y, NULL);
        x *= ms;
        y *= ms;
        lzh_transform_translate(transform, x, y, 0.0f);
    }

    if (lzh_get_key_status(KEY_CODE_A)) {
        lzh_transform_rotate_z(transform, rs);
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        lzh_transform_rotate_z(transform, -rs);
    }

    if (lzh_get_key_status(KEY_CODE_Q)) {
        lzh_transform_rotate_z(turretTransform, ts);
    }

    if (lzh_get_key_status(KEY_CODE_E)) {
        lzh_transform_rotate_z(turretTransform, -ts);
    }

    if (lzh_get_key_down(eg, KEY_CODE_SPACE)) {
        Fire();
    }
}

void Tank::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
