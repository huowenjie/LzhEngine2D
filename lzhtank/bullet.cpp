#include <lzh_sprite.h>
#include <lzh_object.h>

#include "globalres.h"
#include "bullet.h"

/*===========================================================================*/

Bullet::Bullet(LZH_ENGINE *engine) : Object(engine)
{
    bulletSp = lzh_sprite_create(engine, get_tank_bullet_path());
    lzh_object_add_component(object, bulletSp);
}

Bullet::~Bullet()
{

}

/*===========================================================================*/

void Bullet::Update(LZH_ENGINE *eg)
{

}

void Bullet::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
