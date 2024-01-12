#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_keyboard.h>

/*===========================================================================*/

static LZH_UINT32 update(LZH_ENGINE *eg, void *args);
static LZH_UINT32 keyframe(void *args);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;
    LZH_SPRITE *sprite1 = NULL;
    LZH_SPRITE *sprite2 = NULL;
    LZH_SPRITE *sprite3 = NULL;

    LZH_OBJECT *object1 = NULL;
    LZH_OBJECT *object2 = NULL;
    LZH_OBJECT *object3 = NULL;
    const char *imgs[] = {
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode1.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode2.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode3.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode4.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode5.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode6.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode7.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode8.png",
        "/home/huowj/engine/LzhEngine2D/lzhtank/res/explode9.png",
        NULL
    };

    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

#ifndef _WINDOWS
    sprite1 = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/tank.png");
    sprite2 = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/turret.png");
    sprite3 = lzh_sprite_create_from_images(engine, imgs, 9);

    object1 = lzh_object_create(engine);
    object2 = lzh_object_create(engine);
    object3 = lzh_object_create(engine);

    lzh_object_set_size(object1, 30, 30);
    lzh_object_set_sprite(object1, sprite1);

    lzh_object_set_pos(object2, 0, 0);
    lzh_object_set_size(object2, 30, 30);
    lzh_object_set_sprite(object2, sprite2);

    lzh_sprite_set_fps(sprite3, 10);
    lzh_sprite_set_keyframe(sprite3, 8, keyframe, sprite3);

    lzh_object_set_pos(object3, 30, 0);
    lzh_object_set_size(object3, 30, 30);
    lzh_object_set_sprite(object3, sprite3);

    lzh_engine_set_update(engine, update, object1);
    lzh_engine_render(engine);

    lzh_object_destroy(object1);
    lzh_object_destroy(object2);
    lzh_object_destroy(object3);

    lzh_sprite_destroy(sprite1);
    lzh_sprite_destroy(sprite2);
    lzh_sprite_destroy(sprite3);

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

LZH_UINT32 keyframe(void *args)
{
    LZH_SPRITE *sp = (LZH_SPRITE *)args;
    lzh_sprite_enable_play(sp, LZH_FALSE);
    lzh_sprite_show(sp, LZH_FALSE);
    return 0;
}

/*===========================================================================*/
