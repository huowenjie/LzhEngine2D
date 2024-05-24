#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_transform.h>
#include <lzh_collider.h>
#include <stddef.h>
#include <stdio.h>

#include "globalres.h"
#include "bullet.h"
#include "explode.h"
#include "scene.h"
#include "tank.h"

/*===========================================================================*/

Bullet::Bullet(LZH_ENGINE *eg) : GameObject(eg)
{
    bulletSp = lzh_sprite_create(eg, get_tank_bullet_path());
    collider = lzh_collider_create(eg);
    moveSpeed = 5.0f;
    fireDistance = 100.0f;
    isExplode = false;
    fromObject = NULL;

    lzh_object_add_component(object, bulletSp);
    lzh_object_add_component(object, collider);

    char name[32];
    static int code = 1;

    sprintf(name, "bullet%d", code++);
    lzh_object_set_name(object, name);

    lzh_transform_scale(transform, 0.5f, 0.5f, 1.0f);

    LZH_COLLIDER_PARAM param;
    param.type = BOX_2D;
    param.box2d.x = -0.25f;
    param.box2d.y = 0.25f;
    param.box2d.w = 0.5f;
    param.box2d.h = 0.5f;
    lzh_collider_set_param(collider, &param);
    lzh_collider_set_callback(collider, GameObject::ColliderObjectCb, this);
}

Bullet::~Bullet()
{
}

/*===========================================================================*/

void Bullet::SetFromObject(GameObject *from)
{
    if (from) {
        fromObject = from;
    }
}

/*===========================================================================*/

void Bullet::BulletExplode()
{
    if (currentScene) {
        Explode *explode = new Explode(engine);

        float x = 0.0f;
        float y = 0.0f;

        GetPosition(&x, &y);
        explode->SetPosition(x, y);
        explode->SetDepth(0.5f);
        currentScene->AddObjectToScene(explode, true);
        isExplode = true;
    }
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

void Bullet::ColliderCb(GameObject *self, GameObject *target)
{
    if (!self || !target) {
        return;
    }

    if (!fromObject) {
        return;
    }

    if (fromObject == target) {
        return;
    }

    if (isExplode) {
        return;
    }

    // ²¥·Å¶¯»­
    BulletExplode();

    if (target->GetObjectType() == OT_Tank) {
        Tank *tank = (Tank *)target;
        tank->BeAttacked(fromObject);

        // TODO
        printf(
            "-------Bullet::ColliderCb--self = %s, target = %s\n",
            self->GetName().c_str(), target->GetName().c_str()
        );
    }

    currentScene->DelObjectFromScene(this);
}

/*===========================================================================*/
