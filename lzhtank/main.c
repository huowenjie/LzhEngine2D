#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_keyboard.h>
#include <lzh_mem.h>

/*===========================================================================*/

static LZH_UINT32 update(LZH_ENGINE *eg, void *args);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;
    LZH_SPRITE *sprite1 = NULL;
    LZH_OBJECT *object1 = NULL;

    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

    LZH_MALLOC(2);

#ifndef _WINDOWS
    sprite1 = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/tank.png");

    object1 = lzh_object_create(engine);

    lzh_object_set_size(object1, 30, 30);
    lzh_object_set_sprite(object1, sprite1);

    lzh_engine_set_update(engine, update, object1);
    lzh_engine_render(engine);

    lzh_object_destroy(object1);
    lzh_sprite_destroy(sprite1);

    lzh_engine_destroy(engine);
#endif

    lzh_quit();
    return 0;
}

/*===========================================================================*/

static float globalx = -15.0f;
static float globaly = -15.0f;

LZH_UINT32 update(LZH_ENGINE *eg, void *args)
{
    float delta = lzh_engine_interval(eg);
    float speed = 100.0f * delta;

    if (lzh_get_key_status(KEY_CODE_W)) {
        globaly -= speed;
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        globaly += speed;
    }

    if (lzh_get_key_status(KEY_CODE_A)) {
        globalx -= speed;
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        globalx += speed;
    }

    lzh_object_set_pos(
        (LZH_OBJECT *)args, (int)(globalx + 0.5f), (int)(globaly + 0.5f));
    return 0;
}

/*===========================================================================*/
