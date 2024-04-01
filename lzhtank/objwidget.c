#include <lzh_object.h>
#include <lzh_sprite.h>
#include <stddef.h>

#include "objwidget.h"
#include "tank.h"
#include "bullet.h"

/*===========================================================================*/

void ow_init_widget(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res)
{
    // LZH_OBJECT *object = NULL;
    // LZH_SPRITE *sprite = NULL;

    // if (!widget || !engine) {
    //     return;
    // }

    // object = lzh_object_create(engine);
    // sprite = lzh_sprite_create(engine, res);

    // lzh_object_set_size(object, w, h);
    // lzh_object_set_sprite(object, sprite);

    // widget->object = object;
    // widget->sprite = sprite;
    // widget->type = type;
}

void ow_init_widget_images(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res[], int count)
{
    // LZH_OBJECT *object = NULL;
    // LZH_SPRITE *sprite = NULL;

    // if (!widget || !engine) {
    //     return;
    // }

    // object = lzh_object_create(engine);
    // sprite = lzh_sprite_create_from_images(engine, res, count);

    // lzh_object_set_size(object, w, h);
    // lzh_object_set_sprite(object, sprite);

    // widget->object = object;
    // widget->sprite = sprite;
    // widget->type = type;
}

void ow_quit_widget(OBJ_WIDGET *widget)
{
    // if (widget) {
    //     lzh_sprite_destroy(widget->sprite);
    //     lzh_object_destroy(widget->object);

    //     widget->sprite = NULL;
    //     widget->object = NULL;
    // }
}

void ow_destroy_widget(OBJ_WIDGET *widget)
{
    // if (widget) {
    //     if (widget->type == OBJ_TYPE_TANK) {
    //         tk_destroy_tank((TANK *)widget);
    //     } else if (widget->type == OBJ_TYPE_BULLET) {
    //         blt_destroy_bullet((BULLET *)widget);
    //     } else if (widget->type == OBJ_TYPE_EXPLODE) {
    //         ow_quit_widget(widget);
    //         LZH_FREE(widget);
    //     }
    // }
}

void ow_set_pos(OBJ_WIDGET *widget, float x, float y)
{
    // if (widget) {
    //     LZH_VEC2F pos = lzh_vec2f_xy(x, y);
    //     lzh_object_set_pos(widget->object, &pos);
    // }
}

// void ow_set_level(OBJ_WIDGET *widget, LEVEL *level)
// {
//     if (widget) {
//         widget->level = level;
//     }
// }

void ow_set_name(OBJ_WIDGET *widget, const char *name)
{
    // if (widget) {
    //     lzh_object_set_name(widget->object, name);
    // }
}

void ow_set_update(
    OBJ_WIDGET *widget, LZH_OBJECT_UPDATE update, void *param)
{
    // if (widget) {
    //     lzh_object_set_update(widget->object, update, param);
    // }
}

LZH_ENGINE *ow_get_engine(OBJ_WIDGET *widget)
{
    // if (widget) {
    //     return lzh_object_get_engine(widget->object);
    // }
    return NULL;
}

/*===========================================================================*/
