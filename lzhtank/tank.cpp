#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_transform.h>
#include <lzh_keyboard.h>

#include "globalres.h"
#include "scene.h"
#include "tank.h"

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

    lzh_transform_scale(turretTransform, 0.5f, 0.5f, 0.5f);
    lzh_transform_translate(turretTransform, 0.0f, 0.0f, 0.1f);
}

Tank::~Tank()
{
}

/*===========================================================================*/

void Tank::Update(LZH_ENGINE *eg)
{
    float delta = 0.0f;
    float speed = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (!eg) {
        return;
    }

    delta = lzh_engine_interval(eg);
    speed = 1.0f * delta;

    if (lzh_get_key_status(KEY_CODE_W)) {
        /*lzh_transform_get_forward(transform, &x, &y, &z);
        x *= speed;
        y *= speed;*/
        z *= speed;
        lzh_transform_translate(transform ,x, y, speed);
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        /*lzh_transform_get_backward(transform, &x, &y, &z);
        x *= speed;
        y *= speed;*/
        z *= (-speed);
        lzh_transform_translate(transform , x, y, -speed);
    }

    if (lzh_get_key_status(KEY_CODE_R)) {
        /*lzh_transform_get_forward(transform, &x, &y, &z);
        x *= speed;
        y *= speed;*/
        x *= speed;
        lzh_transform_translate(transform, speed, 0.0f, 0.0f);
    }

    if (lzh_get_key_status(KEY_CODE_F)) {
        /*lzh_transform_get_backward(transform, &x, &y, &z);
        x *= speed;
        y *= speed;*/
        x *= (-speed);
        lzh_transform_translate(transform, -speed, 0.0f, 0.0f);
    }

    speed = 60.0f * delta;

    if (lzh_get_key_status(KEY_CODE_A)) {
        lzh_transform_rotate_z(transform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        lzh_transform_rotate_z(transform, -speed);
    }

    if (lzh_get_key_status(KEY_CODE_Z)) {
        lzh_transform_rotate_x(transform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_C)) {
        lzh_transform_rotate_x(transform, -speed);
    }

    if (lzh_get_key_status(KEY_CODE_T)) {
        lzh_transform_rotate_y(transform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_G)) {
        lzh_transform_rotate_y(transform, -speed);
    }

    if (lzh_get_key_status(KEY_CODE_Q)) {
        lzh_transform_rotate_z(turretTransform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_E)) {
        lzh_transform_rotate_z(turretTransform, -speed);
    }
}

void Tank::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
