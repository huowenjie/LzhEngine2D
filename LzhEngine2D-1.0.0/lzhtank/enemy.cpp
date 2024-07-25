#include <lzh_object.h>
#include <lzh_transform.h>
#include <lzh_systool.h>

#include "enemy.h"
#include "scene.h"
#include "camera.h"

/*===========================================================================*/

Enemy::Enemy(LZH_ENGINE *eg, Scene *scene) : Tank(eg, scene)
{
    objType = OT_Enemy;
    roleType = RT_Enemy;
    targetRole |= RT_Player;

    chassisTransform = chassis->GetTransform();
    turretTransform = turret->GetTransform();

    visitList[0] = glm::vec2(-8.0f, -8.0f);
    visitList[1] = glm::vec2(8.0f, 8.0f);
    visitList[2] = glm::vec2(8.0f, -8.0f);
    visitList[3] = glm::vec2(-8.0f, 8.0f);

    currentIndex = 0;
    intervalCount = 0.0f;
}

Enemy::~Enemy()
{
}

bool Enemy::MoveToPos(glm::vec2 &pos, float delta)
{
    glm::vec2 objpos;
    GetPosition(objpos);

    glm::vec2 dir = pos - objpos;
    glm::vec2 forward;
    GetForward(forward);

    float distance = glm::length(dir);

    dir = glm::normalize(dir);
    forward = glm::normalize(forward);

    float cosTheta = glm::dot(forward, dir);

    if (fabsf(cosTheta - 1.0f) > 0.1f) {
        ChassisRotateL(delta);
    } else if (distance > 0.5f) {
        ChassisForward(delta);
    } else {
        return true;
    }

    return false;
}

void Enemy::Update(LZH_ENGINE *eg)
{
    if (!currentScene) {
        return;
    }

    float delta = lzh_engine_interval(eg);

    if (MoveToPos(visitList[currentIndex], delta)) {
        currentIndex = (currentIndex + 1) % 4;
    }

    intervalCount += delta;

    if (intervalCount > 2.0f) {
        Fire();
        intervalCount = 0.0f;
    }

    Tank::Update(eg);
}

void Enemy::FixedUpdate(LZH_ENGINE *eg)
{
    Tank::FixedUpdate(eg);
}

/*===========================================================================*/
