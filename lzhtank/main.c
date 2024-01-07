#include <stddef.h>
#include <lzh_engine.h>
#include <lzh_sprite.h>
#include <lzh_keyboard.h>

/*===========================================================================*/

static LZH_UINT32 update(LZH_ENGINE *eg, void *args);

/*===========================================================================*/

int main(int argc, char* argv[])
{
    LZH_ENGINE *engine = NULL;
    LZH_SPRITE *siprite = NULL;
    
    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

    siprite = lzh_sprite_create(
        engine, "D:\\vs-projects\\LzhEngine2D\\LzhEngine2D\\lzhtank\\res\\tank.png");

    lzh_engine_set_update(engine, update, siprite);
    lzh_engine_render(engine);

    lzh_sprite_destroy(siprite);
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/

static float globalx = 0.0f;
static float globaly = 0.0f;

LZH_UINT32 update(LZH_ENGINE *eg, void *args)
{
    int delta = lzh_engine_delta(eg);
    float fdelta = ((float)delta) / 1000.0f;
    float speed = 50.0f * fdelta;

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

    lzh_sprite_set_pos((LZH_SPRITE *)args, (int)globalx, (int)globaly);
    lzh_sprite_render((LZH_SPRITE *)args);
    return 0;
}

/*===========================================================================*/
