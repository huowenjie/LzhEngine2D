#include <lzh_mem.h>
#include <lzh_object.h>
#include <string.h>

#include "globalres.h"
#include "bullet.h"

/*===========================================================================*/

BULLET *blt_create_bullet(LZH_ENGINE *engine, float w, float h)
{
    BULLET *bullet = NULL;

    if (!engine) {
        return NULL;
    }

    bullet = LZH_MALLOC(sizeof(BULLET));
    if (!bullet) {
        return NULL;
    }
    memset(bullet, 0, sizeof(BULLET));

    ow_init_widget((OBJ_WIDGET *)bullet, engine, w, h, OBJ_TYPE_BULLET, get_tank_bullet_path());
    return bullet;
}

void blt_destroy_bullet(BULLET *bullet)
{
    if (bullet) {
        ow_quit_widget((OBJ_WIDGET *)bullet);
        LZH_FREE(bullet);
    }
}

void blt_move_forward(BULLET *bullet, float speed)
{
    if (bullet) {
        LZH_OBJECT *object = bullet->widget.object;

        LZH_VEC2F forward = lzh_object_get_forward(object);
        LZH_VEC2F pos = lzh_object_get_pos(object);

        forward = lzh_vec2f_mul(&forward, speed);
        pos = lzh_vec2f_add(&pos, &forward);
        lzh_object_set_pos(object, &pos);
    }
}

void blt_explode(BULLET *bullet)
{
    OBJ_WIDGET *explode = NULL;
    LZH_ENGINE *eg = NULL;
    LEVEL *level = NULL;

    if (!bullet) {
        return;
    }

    eg = lzh_object_get_engine(bullet->widget.object);
    if (!eg) {
        return;
    }

    level = bullet->widget.level;
    if (!level) {
        return;
    }

    explode = LZH_MALLOC(sizeof(OBJ_WIDGET));
    if (!explode) {
        return;
    }
    memset(explode, 0, sizeof(OBJ_WIDGET));
    
    ow_init_widget_images(
        (OBJ_WIDGET *)bullet, eg, 20.0f, 20.0f,
        OBJ_TYPE_EXPLODE, get_tank_explode_path(), get_tank_explode_count());
    // TODO
}

/*===========================================================================*/
