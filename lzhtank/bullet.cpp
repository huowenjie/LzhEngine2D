#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_transform.h>
#include <stddef.h>

#include "globalres.h"
#include "bullet.h"

/*===========================================================================*/

Bullet::Bullet(LZH_ENGINE *engine) : Object(engine)
{
    bulletSp = lzh_sprite_create(engine, get_tank_bullet_path());
    moveSpeed = 5.0f;
    fireDistance = 100.0f;

    lzh_object_add_component(object, bulletSp);
    lzh_object_set_name(object, "bullet");

    lzh_transform_scale(transform, 0.5f, 0.5f, 1.0f);
}

Bullet::~Bullet()
{
}

/*===========================================================================*/

void Bullet::Update(LZH_ENGINE *eg)
{
    float delta = 0.0f;
    float speed = 0.0f;
    float x = 0.0f;
    float y = 0.0f;

    if (!eg) {
        return;
    }

    delta = lzh_engine_interval(eg);
    speed = moveSpeed * delta;

    lzh_transform_get_forward(transform, &x, &y, NULL);
    x *= speed;
    y *= speed;
    lzh_transform_translate(transform, x, y, 0.0f);
}

void Bullet::FixedUpdate(LZH_ENGINE *eg)
{
}

/*===========================================================================*/
