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
    LZH_SPRITE *sprite1 = NULL;
    LZH_OBJECT *object1 = NULL;
    LZH_SPRITE *sprite2 = NULL;
    LZH_OBJECT *object2 = NULL;

    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

#ifdef _WINDOWS
    sprite = lzh_sprite_create(
        engine, "D:\\vs-projects\\LzhEngine2D\\LzhEngine2D\\lzhtank\\res\\tank.png");
#else
    sprite1 = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/tank.png");
    sprite2 = lzh_sprite_create(
        engine, "/home/huowj/engine/LzhEngine2D/lzhtank/res/turret.png");
#endif

    object1 = lzh_object_create(engine);
    object2 = lzh_object_create(engine);

    lzh_object_set_size(object1, 30, 30);
    lzh_object_set_sprite(object1, sprite1);

    lzh_object_set_pos(object2, 0, 0);
    lzh_object_set_size(object2, 30, 30);
    lzh_object_set_sprite(object2, sprite2);

    lzh_engine_set_update(engine, update, object1);
    lzh_engine_render(engine);

    lzh_object_destroy(object1);
    lzh_sprite_destroy(sprite1);
    lzh_object_destroy(object2);
    lzh_sprite_destroy(sprite2);
    lzh_engine_destroy(engine);
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

    printf("delta = %f, x = %f, y = %f\n", delta, globalx, globaly);
    lzh_object_set_pos(
        (LZH_OBJECT *)args, (int)(globalx + 0.5f), (int)(globaly + 0.5f));
    return 0;
}

/*===========================================================================*/
