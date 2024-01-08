#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_keyboard.h>

/*===========================================================================*/

static LZH_UINT32 update(LZH_ENGINE *eg, void *args);

/*===========================================================================*/

int main(int argc, char* argv[])
{
    LZH_ENGINE *engine = NULL;
    LZH_SPRITE *sprite = NULL;
    LZH_OBJECT *object = NULL;

    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

#ifdef _WINDOWS
    sprite = lzh_sprite_create(
        engine, "D:\\vs-projects\\LzhEngine2D\\LzhEngine2D\\lzhtank\\res\\tank.png");
#else
    sprite = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/tank.png");
#endif

    object = lzh_object_create(engine);

    lzh_object_set_size(object, 30, 30);
    lzh_object_set_sprite(object, sprite);

    lzh_engine_set_update(engine, update, object);
    lzh_engine_render(engine);

    lzh_object_destroy(object);
    lzh_sprite_destroy(sprite);
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/

static float globalx = 0.0f;
static float globaly = 0.0f;

LZH_UINT32 update(LZH_ENGINE *eg, void *args)
{
    float delta = lzh_engine_interval(eg);
    float speed = 80.0f * delta;

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

    lzh_object_set_pos((LZH_OBJECT *)args, (int)globalx, (int)globaly);
    return 0;
}

/*===========================================================================*/
