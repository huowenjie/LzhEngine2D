#include <lzh_object.h>
#include <lzh_transform.h>

#include "enemy.h"

/*===========================================================================*/

Enemy::Enemy(LZH_ENGINE *eg, Scene *scene) : Tank(eg, scene)
{
    objType = OT_Player;

    chassisTransform = chassis->GetTransform();
    turretTransform = turret->GetTransform();
}

Enemy::~Enemy()
{
}

void Enemy::Update(LZH_ENGINE *eg)
{
}

void Enemy::FixedUpdate(LZH_ENGINE *eg)
{
}

/*===========================================================================*/
