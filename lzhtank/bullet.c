#include <lzh_mem.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <string.h>

#include "globalres.h"
#include "bullet.h"

/*===========================================================================*/

LZH_UINT32 explode_destroy_cb(void *args);

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
    #if 0
    if (bullet) {
        LZH_OBJECT *object = bullet->widget.object;

        LZH_VEC2F forward = lzh_object_get_forward(object);
        LZH_VEC2F pos = lzh_object_get_pos(object);

        forward = lzh_vec2f_mul(&forward, speed);
        pos = lzh_vec2f_add(&pos, &forward);
        lzh_object_set_pos(object, &pos);
    }
    #endif
}

void blt_explode(BULLET *bullet)
{
#if 0
    OBJ_WIDGET *explode = NULL;
    LZH_ENGINE *eg = NULL;
    LEVEL *level = NULL;
    LZH_VEC2F pos;

    int count = 0;
    const char **res = NULL;

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

    count = get_tank_explode_count();
    res = get_tank_explode_path();

    ow_init_widget_images(
        explode, eg, 20.0f, 20.0f, OBJ_TYPE_EXPLODE, res, count);

    pos = lzh_object_get_pos(bullet->widget.object);
    ow_set_pos(explode, pos.x, pos.y);

    lzh_sprite_show(explode->sprite, LZH_TRUE);
    lzh_sprite_enable_play(explode->sprite, LZH_TRUE);

    /* 播放完毕后在最后一帧销毁 */
    lzh_sprite_set_keyframe(explode->sprite, count - 1, explode_destroy_cb, explode);
#endif
}

LZH_UINT32 explode_destroy_cb(void *args)
{
    OBJ_WIDGET *explode = NULL;

    if (!args) {
        return 0;
    }

    explode = (OBJ_WIDGET *)args;
    ow_quit_widget(explode);
    LZH_FREE(explode);
    return 0;
}

/*===========================================================================*/
