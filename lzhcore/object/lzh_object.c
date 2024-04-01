#include <stdio.h>
#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>
#include <lzh_systool.h>

#include "lzh_core_object.h"
#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_sprite.h"

/*===========================================================================*/

static int global_order = 1;
static int global_sort = 0;

#define PI 3.141592654f

/* 更新内部参数 */
static void update_object_center(LZH_OBJECT *obj);
static void update_object_forward(LZH_OBJECT *obj);

/* 场景渲染队列渲染回调 */
static void lzh_object_update(LZH_BASE *base, void *args);
static void lzh_object_fixedupdate(LZH_BASE *base, void *args);
static void lzh_object_draw(LZH_BASE *base, void *args);

/* 生成新名称 */
static const char *lzh_gen_new_name(int order);

/*===========================================================================*/

LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine)
{
    LZH_OBJECT *obj = NULL;
    LZH_BASE *base = NULL;

    if (!engine) {
        return NULL;
    }

    obj = LZH_MALLOC(sizeof(LZH_OBJECT));
    if (!obj) {
        return NULL;
    }
    memset(obj, 0, sizeof(LZH_OBJECT));
    base = &obj->base;
    lzh_base_init(base);

    base->type = LZH_BT_OBJECT;
    base->name = NULL;
    base->hash = 0;
    base->engine = engine;
    base->update = lzh_object_update;
    base->fixed_update = lzh_object_fixedupdate;
    base->draw = lzh_object_draw;
    base->update_param = NULL;
    base->fixed_update_param = NULL;
    base->draw_param = NULL;

    obj->parent = NULL;
    obj->children = lzh_obj_rb_create(lzh_object_rb_comp);
    obj->components = lzh_cpnt_rb_create(lzh_cpnt_rb_comp);
    obj->render_layer = 0;
    obj->render_sort = global_sort++;

    obj->update = NULL;
    obj->update_param = NULL;
    obj->fixed_update = NULL;
    obj->fixed_update_param = NULL;

    /* 设置默认名称 */
    lzh_base_set_name(base, lzh_gen_new_name(global_order++));
    return obj;
}

void lzh_object_set_parent(LZH_OBJECT *object, LZH_OBJECT *parent)
{
    if (!object) {
        return;
    }

    if (object->parent) {
        LZH_OBJECT *pobj = object->parent;
        lzh_obj_rb_delete(pobj->children, object->base.hash, NULL, NULL);
        object->parent = NULL;
    }

    if (parent && object != parent) {
        lzh_obj_rb_insert(parent->children, object->base.hash, object);
        object->parent = parent;
    }
}

void lzh_object_add_child(LZH_OBJECT *object, LZH_OBJECT *child)
{
    lzh_object_set_parent(child, object);
}

void lzh_object_del_child(LZH_OBJECT *object, const char *name)
{
    LZH_HASH_CODE code = 0;

    if (!object || !object->children) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    code = lzh_gen_hash_code(name);
    lzh_obj_rb_delete(object->children, code, lzh_object_rb_visit, NULL);
}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {
        if (object->parent) {
            /* 移除父节点中缓存的子对象 */
            LZH_OBJECT *parent = object->parent;
            lzh_obj_rb_delete(parent->children, object->base.hash, lzh_object_rb_visit, NULL);
        }
        lzh_object_remove(object);
    }
}

void lzh_object_add_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;
        lzh_cpnt_rb_insert(object->components, elem->type, elem);
    }
}

void *lzh_object_del_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;
        lzh_cpnt_rb_delete(object->components, elem->type, NULL, NULL);
        return cpnt;
    }
    return NULL;
}

LZH_SPRITE *lzh_object_get_sprite(LZH_OBJECT *object)
{
    LZH_SPRITE *sp = NULL;
    
    if (!object || !object->components) {
        return NULL;
    }

    lzh_cpnt_rb_find(object->components, LZH_CPNT_SPRITE, (LZH_COMPONENT **)&sp);
    return sp;
}

LZH_HASH_CODE lzh_object_hash_code(LZH_OBJECT *object)
{
    if (object) {
        return object->base.hash;
    }
    return 0;
}

LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object)
{
    if (object) {
        return object->base.engine;
    }
    return NULL;
}

void lzh_object_set_name(LZH_OBJECT *object, const char *name)
{
    if (object) {
        lzh_base_set_name((LZH_BASE *)object, name);
    }
}

const char *lzh_object_get_name(LZH_OBJECT *object)
{
    if (object) {
        return object->base.name;
    }
    return NULL;
}

void lzh_object_set_layer(LZH_OBJECT *object, int layer)
{
    if (object) {
        object->render_layer = layer;
    }
}

int lzh_object_get_layer(LZH_OBJECT *object)
{
    if (object) {
        return object->render_layer;
    }
    return 0;
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

void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show)
{
    if (object) {
        // lzh_sprite_show(object->sprite, show);
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

void lzh_object_update(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;

        /* 更新子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_update, NULL);
        }

        /* 更新组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components,lzh_cpnt_rb_visit_update, NULL);
        }

        /* 用户层更新 */
        if (object->update) {
            object->update(base->engine, object, object->update_param);
        }
    }
}

void lzh_object_fixedupdate(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;

        /* 更新子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_fixedupdate, NULL);
        }

        /* 更新组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components,lzh_cpnt_rb_visit_fixedupdate, NULL);
        }

        /* 用户层更新 */
        if (object->fixed_update) {
            object->fixed_update(base->engine, object, object->fixed_update_param);
        }
    }
}

void lzh_object_draw(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;

        /* 绘制子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_draw, NULL);
        }

        /* 绘制组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components, lzh_cpnt_rb_visit_draw, NULL);
        }
    }
}

const char *lzh_gen_new_name(int order)
{
    static char default_name[32] = "";

    sprintf(default_name, "New Object%d", order);
    return default_name;
}

/*===========================================================================*/
