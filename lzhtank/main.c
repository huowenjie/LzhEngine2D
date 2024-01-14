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
#else
    sprite1 = lzh_sprite_create(
        engine, "D:\\vs-projects\\LzhEngine2D\\LzhEngine2D\\lzhtank\\res\\tank.png");

    object1 = lzh_object_create(engine);

    lzh_object_set_size(object1, 160.0f, 160.0f);
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

static float globalx = 0.0f;
static float globaly = 0.0f;

LZH_UINT32 update(LZH_ENGINE *eg, void *args)
{
    float delta = lzh_engine_interval(eg);
    float speed = 1.0f * delta;

    globalx += speed;

    lzh_object_set_pos(
        (LZH_OBJECT *)args, globalx, globaly);
    printf("target = %f, %f\n", globalx, globaly);
    return 0;
}

/*===========================================================================*/
