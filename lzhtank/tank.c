#include <lzh_mem.h>
#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_engine.h>

#include "globalres.h"
#include "tank.h"

/*===========================================================================*/

TANK *tk_create_tank(LZH_ENGINE *engine, float w, float h)
{
    LZH_SPRITE *sprite = NULL;
    LZH_OBJECT *object = NULL;

    TANK *tk = LZH_MALLOC(sizeof(TANK));
    if (!tk) {
        return NULL;
    }

    sprite = lzh_sprite_create(engine, get_tank_res_path());
    object = lzh_object_create(engine);

    lzh_object_set_size(object, w, h);
    lzh_object_set_sprite(object, sprite);

    tk->object = object;
    tk->sprite = sprite;
    return tk;
}

void tk_destroy_tank(TANK *tank)
{
    if (tank) {
        lzh_sprite_destroy(tank->sprite);
        lzh_object_destroy(tank->object);
        LZH_FREE(tank);
    }
}

void tk_set_pos(TANK *tank, float x, float y)
{
    if (tank) {
        lzh_object_set_pos(tank->object, x, y);
    }
}

/*===========================================================================*/
