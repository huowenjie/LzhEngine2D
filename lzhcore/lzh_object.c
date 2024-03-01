#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_mat2x2f.h>

#include "lzh_mem.h"
#include "lzh_core_object.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/

#define PI 3.141592654f

static int global_order = 0;

/* �����ڲ����� */
static void update_object_center(LZH_OBJECT *obj);
static void update_object_forward(LZH_OBJECT *obj);

/*===========================================================================*/

LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine)
{
    LZH_OBJECT *obj = NULL;

    if (!engine) {
        return NULL;
    }

    obj = LZH_MALLOC(sizeof(LZH_OBJECT));
    if (!obj) {
        return NULL;
    }

    render_tree_push(engine->render_tree, 0, global_order++, obj);

    obj->engine = engine;
    obj->x = 0.0f;
    obj->y = 0.0f;
    obj->offset_x = 0.0f;
    obj->offset_y = 0.0f;
    obj->w = 0;
    obj->h = 0;
    obj->angle = 0.0f;
    obj->rx = 0.0f;
    obj->ry = 0.0f;
    obj->forward = lzh_vec2f_xy(0.0f, -1.0f);
    obj->sprite = NULL;
    return obj;
}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {
        LZH_FREE(object);
    }
}

void lzh_object_set_size(LZH_OBJECT *object, float w, float h)
{
    if (object) {
        object->w = w;
        object->h = h;
        update_object_center(object);
    }
}

void lzh_object_set_pos(LZH_OBJECT *object, const LZH_VEC2F *pos)
{
    if (object && pos) {
        object->x = pos->x;
        object->y = pos->y;
    }
}

void lzh_object_set_angle(LZH_OBJECT *object, float angle)
{
    if (object) {
        object->angle = angle;
        update_object_forward(object);
    }
}

LZH_VEC2F lzh_object_get_pos(LZH_OBJECT *object)
{
    LZH_VEC2F pos = lzh_vec2f_xy(0.0f, 0.0f);

    if (object) {
        pos.x = object->x;
        pos.y = object->y;
    }
    return pos;
}

float lzh_object_get_x(LZH_OBJECT *object)
{
    float x = 0.0f;
    if (object) {
        x = object->x;
    }
    return x;
}

float lzh_object_get_y(LZH_OBJECT *object)
{
    float y = 0.0f;
    if (object) {
        y = object->y;
    }
    return y;
}

LZH_RECTF lzh_object_get_rect(const LZH_OBJECT *object)
{
    LZH_RECTF rect = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (object) {
        rect.x = object->x;
        rect.y = object->y;
        rect.w = object->w;
        rect.h = object->h;
    }
    return rect;
}

float lzh_object_get_angle(LZH_OBJECT *object)
{
    float angle = 0.0f;
    if (object) {
        angle = object->angle;
    }
    return angle;
}

LZH_VEC2F lzh_object_get_forward(LZH_OBJECT *object)
{
    LZH_VEC2F vec = lzh_vec2f_xy(0.0f, 0.0f);
    if (object) {
        vec = object->forward;
    }
    return vec;
}

void lzh_object_render(LZH_OBJECT *object)
{
    if (object) {
        if (object->sprite) {
            lzh_sprite_render(object, object->sprite);
        }
    }
}

void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp)
{
    if (object && sp) {
        object->sprite = sp;
    }
}

/*===========================================================================*/

void update_object_center(LZH_OBJECT *obj)
{
    if (obj) {
        obj->rx = obj->x + (obj->w / 2.0f);
        obj->ry = obj->y + (obj->h / 2.0f);
    }
}

void update_object_forward(LZH_OBJECT *obj)
{
    if (obj) {
        float angle = obj->angle;
        float theta = angle * (PI / 180.0f);

        LZH_MAT2X2F mat = lzh_mat2x2f_rotate(theta);
        LZH_VEC2F forward = lzh_vec2f_xy(0.0f, -1.0f);

        forward = lzh_mat2x2f_mul_vec(&mat, &forward);
        forward = lzh_vec2f_normalize(&forward);
        obj->forward = forward;
    }
}

/*===========================================================================*/