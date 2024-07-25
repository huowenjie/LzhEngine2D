#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_transform.h>
#include <lzh_rigidbody2d.h>
#include <lzh_collider2d.h>
#include <cstddef>
#include <cmath>

#include "globalres.h"
#include "bullet.h"
#include "explode.h"
#include "scene.h"
#include "tank.h"

/*===========================================================================*/

Bullet::Bullet(LZH_ENGINE *eg, Scene *scene, LZH_UINT32 roles) : GameObject(eg, scene)
{
    objType = OT_Bullet;
    bulletSp = lzh_sprite_create(eg, object, GetTankBulletPath());
    
    rigidbody = lzh_rigidbody2d_create(eg, object);
    collider = lzh_collider2d_create(rigidbody);

    moveSpeed = 5.0f;
    fireDistance = 100.0f;
    isExplode = false;
    fromObject = NULL;
    flyingDistance = 0.0f;
    targetRoles = roles;

    char name[32];
    static int code = 1;

    sprintf(name, "bullet%d", code++);
    lzh_object_set_name(object, name);

    lzh_transform_scale(transform, 0.5f, 0.5f, 1.0f);
    lzh_collider2d_set_box(collider, 0.0f, 0.0f, 0.5f, 0.5f);
    lzh_collider2d_set_start_contact(collider, GameObject::ColliderObjectCb, this);
}

Bullet::~Bullet()
{
    //lzh_collider2d_set_start_contact(collider, NULL, NULL);
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
        Explode *explode = new Explode(engine, currentScene);

        float x = 0.0f;
        float y = 0.0f;

        GetPosition(&x, &y);
        explode->SetPosition(x, y);
        explode->SetDepth(0.5f);
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

    flyingDistance += std::sqrt(x * x + y * y);

    if (flyingDistance > 10.0f) {
        // 播放爆炸动画并销毁自己
        BulletExplode();
        currentScene->ToFreeGameObject(this);
    }
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

    // 播放动画
    BulletExplode();

    LZH_UINT32 targetRole = (LZH_UINT32)target->GetObjectRole();
    if (targetRoles & targetRole) {
        Tank *tank = (Tank *)target;
        tank->BeAttacked(fromObject);
    }

    currentScene->ToFreeGameObject(this);
}

/*===========================================================================*/
