#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>

#include "../engine/lzh_core_engine.h"
#include "../object/lzh_core_object.h"
#include "../component/lzh_core_sprite.h"

/*===========================================================================*/

#define PI 3.141592654f

static int global_order = 0;

/* 更新内部参数 */
static void update_object_center(LZH_OBJECT *obj);
static void update_object_forward(LZH_OBJECT *obj);

static void lzh_object_update(LZH_CONTEXT *ctx, void *args);
static void lzh_object_fixedupdate(LZH_CONTEXT *ctx, void *args);

/*===========================================================================*/

LINK_IMPLEMENT(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/*===========================================================================*/

LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine)
{
    LZH_OBJECT *obj = NULL;
    LZH_CONTEXT *ctx = NULL;

    if (!engine) {
        return NULL;
    }

    obj = LZH_MALLOC(sizeof(LZH_OBJECT));
    if (!obj) {
        return NULL;
    }
    memset(obj, 0, sizeof(LZH_OBJECT));
    ctx = &obj->context;

    render_tree_push(engine->render_tree, 0, global_order++, obj);

    ctx->invoker = obj;
    ctx->engine = engine;
    ctx->update = lzh_object_update;
    ctx->update_param = NULL;
    ctx->fixed_update = lzh_object_fixedupdate;
    ctx->fixed_update_param = NULL;

    obj->name = NULL;
    obj->update = NULL;
    obj->update_param = NULL;
    obj->fixed_update = NULL;
    obj->fixed_update_param = NULL;

    return obj;
}

LZH_OBJECT *lzh_object_create_child(LZH_ENGINE *engine, LZH_OBJECT *parent)
{
    return NULL;
}

LZH_OBJECT *lzh_object_set_parent(LZH_ENGINE *engine, LZH_OBJECT *parent)
{
    return NULL;
}

void lzh_object_add_child(LZH_ENGINE *engine, LZH_OBJECT *child)
{

}

void lzh_object_del_child(LZH_ENGINE *engine, LZH_HASH_CODE hash)
{

}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {
        if (object->name) {
            LZH_FREE(object->name);
            object->name = NULL;
        }
        LZH_FREE(object);
    }
}

LZH_HASH_CODE lzh_object_hash_code(LZH_OBJECT *object)
{
    return 0;
}

LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object)
{
    if (object) {
        return object->context.engine;
    }
    return NULL;
}

void lzh_object_set_name(LZH_OBJECT *object, const char *name)
{
    char *buf = NULL;
    size_t size = 0;

    if (!object) {
        return;   
    }

    if (!name || !*name) {
        return;
    }

    size = strlen(name) + 1;
    buf = LZH_MALLOC(size);
    if (!buf) {
        return;
    }
    memset(buf, 0, size);
    strcpy(buf, name);

    if (object->name) {
        LZH_FREE(object->name);
    }
    object->name = buf;
}

const char *lzh_object_get_name(LZH_OBJECT *object)
{
    if (object) {
        return object->name;
    }
    return NULL;
}

void lzh_object_set_update(
    LZH_OBJECT *object, LZH_OBJECT_UPDATE update, void *param)
{
    if (object) {
        object->update = update;
        object->update_param = param;
    }
}

void lzh_object_set_fixedupdate(
    LZH_OBJECT *object, LZH_OBJECT_FIXEDUPDATE update, void *param)
{
    if (object) {
        object->fixed_update = update;
        object->fixed_update_param = param;
    }
}

void lzh_object_set_size(LZH_OBJECT *object, float w, float h)
{
#if 0
    if (object) {
        object->w = w;
        object->h = h;
        update_object_center(object);
    }
#endif
}

void lzh_object_set_pos(LZH_OBJECT *object, const LZH_VEC2F *pos)
{
#if 0
    if (object && pos) {
        object->x = pos->x;
        object->y = pos->y;
    }
#endif
}

void lzh_object_set_angle(LZH_OBJECT *object, float angle)
{
#if 0
    if (object) {
        object->angle = angle;
        update_object_forward(object);
    }
#endif
}

LZH_VEC2F lzh_object_get_pos(LZH_OBJECT *object)
{
#if 0
    LZH_VEC2F pos = lzh_vec2f_xy(0.0f, 0.0f);

    if (object) {
        pos.x = object->x;
        pos.y = object->y;
    }
    return pos;
#endif
    return lzh_vec2f_xy(0.0f, 0.0f);
}

float lzh_object_get_x(LZH_OBJECT *object)
{
#if 0
    float x = 0.0f;
    if (object) {
        x = object->x;
    }
    return x;
#endif
    return 0.0f;
}

float lzh_object_get_y(LZH_OBJECT *object)
{
#if 0
    float y = 0.0f;
    if (object) {
        y = object->y;
    }
    return y;
#endif
    return 0.0f;
}

LZH_RECTF lzh_object_get_rect(const LZH_OBJECT *object)
{
    LZH_RECTF rect = { 0.0f, 0.0f, 0.0f, 0.0f };
#if 0
    if (object) {
        rect.x = object->x;
        rect.y = object->y;
        rect.w = object->w;
        rect.h = object->h;
    }
#endif
    return rect;
}

float lzh_object_get_angle(LZH_OBJECT *object)
{
    float angle = 0.0f;
#if 0
    if (object) {
        angle = object->angle;
    }
#endif
    return angle;
}

LZH_VEC2F lzh_object_get_forward(LZH_OBJECT *object)
{
    LZH_VEC2F vec = lzh_vec2f_xy(0.0f, 0.0f);
#if 0
    if (object) {
        vec = object->forward;
    }
#endif
    return vec;
}

void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp)
{
    if (object && sp) {
        // object->sprite = sp;
    }
}

void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show)
{
    if (object) {
        // lzh_sprite_show(object->sprite, show);
    }
}

/*===========================================================================*/

void lzh_object_update(LZH_CONTEXT *ctx, void *args)
{
    if (ctx) {
        LZH_OBJECT *object = (LZH_OBJECT *)ctx;

        if (object->update) {
            object->update(ctx->engine, object, object->update_param);
        }

        // if (object->sprite) {
        //     lzh_sprite_render(object, object->sprite);
        // }
    }
}

void lzh_object_fixedupdate(LZH_CONTEXT *ctx, void *args)
{
    if (ctx) {
        LZH_OBJECT *object = (LZH_OBJECT *)ctx;

        if (object->fixed_update) {
            object->fixed_update(ctx->engine, object, object->fixed_update_param);
        }
    }
}

/*===========================================================================*/

void update_object_center(LZH_OBJECT *obj)
{
    if (obj) {
        // obj->rx = obj->x + (obj->w / 2.0f);
        // obj->ry = obj->y + (obj->h / 2.0f);
    }
}

void update_object_forward(LZH_OBJECT *obj)
{
    if (obj) {
        // float angle = obj->angle;
        // float theta = angle * (PI / 180.0f);

        // LZH_VEC2F forward = lzh_vec2f_xy(0.0f, -1.0f);
        // obj->forward = lzh_vec2f_rotate(&forward, theta);
    }
}

/*===========================================================================*/
