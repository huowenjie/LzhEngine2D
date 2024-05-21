#include <lzh_object.h>
#include <lzh_transform.h>
#include <lzh_keyboard.h>

#include "player.h"

/*===========================================================================*/

Player::Player(LZH_ENGINE *eg) : Tank(eg)
{
}

Player::~Player()
{
}

void Player::Update(LZH_ENGINE *eg)
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

void Player::FixedUpdate(LZH_ENGINE *eg)
{
}

/*===========================================================================*/