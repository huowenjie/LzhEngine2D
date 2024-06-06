#include <lzh_object.h>
#include <lzh_transform.h>
#include <lzh_keyboard.h>

#include "scene.h"
#include "player.h"

/*===========================================================================*/

Player::Player(LZH_ENGINE *eg, Scene *scene) : Tank(eg, scene)
{
    objType = OT_Player;
}

Player::~Player()
{
}

void Player::Update(LZH_ENGINE *eg)
{    
    float delta = lzh_engine_interval(eg);

    if (lzh_get_key_status(KEY_CODE_W)) {
        ChassisForward(delta);
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        ChassisBackward(delta);
    }

    if (lzh_get_key_status(KEY_CODE_A)) {
        ChassisRotateL(delta);
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        ChassisRotateR(delta);
    }

    if (lzh_get_key_status(KEY_CODE_Q)) {
        TurretRotateL(delta);
    }

    if (lzh_get_key_status(KEY_CODE_E)) {
        TurretRotateR(delta);
    }

    if (lzh_get_key_down(eg, KEY_CODE_SPACE)) {
        Fire();
    }

    Tank::Update(eg);
}

void Player::FixedUpdate(LZH_ENGINE *eg)
{

    Tank::FixedUpdate(eg);
}

/*===========================================================================*/