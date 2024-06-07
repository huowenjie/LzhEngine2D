#include <lzh_object.h>
#include <lzh_transform.h>

#include "enemy.h"

/*===========================================================================*/

Enemy::Enemy(LZH_ENGINE *eg, Scene *scene) : Tank(eg, scene)
{
    objType = OT_Enemy;
    roleType = RT_Enemy;

    chassisTransform = chassis->GetTransform();
    turretTransform = turret->GetTransform();
}

Enemy::~Enemy()
{
}

void Enemy::Update(LZH_ENGINE *eg)
{
    Tank::Update(eg);
}

void Enemy::FixedUpdate(LZH_ENGINE *eg)
{
    Tank::FixedUpdate(eg);
}

/*===========================================================================*/
