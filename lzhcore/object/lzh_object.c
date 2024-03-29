#include <stdio.h>
#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>

#include "lzh_core_object.h"
#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_sprite.h"

/*===========================================================================*/

static int global_order = 1;
#define PI 3.141592654f

/* 更新内部参数 */
static void update_object_center(LZH_OBJECT *obj);
static void update_object_forward(LZH_OBJECT *obj);

/* 场景渲染队列渲染回调 */
static void lzh_object_update(LZH_BASE *base, void *args);
static void lzh_object_fixedupdate(LZH_BASE *base, void *args);

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
    base->update_param = NULL;
    base->fixed_update = lzh_object_fixedupdate;
    base->fixed_update_param = NULL;

    obj->parent = NULL;
    obj->children = lzh_obj_link_create(lzh_link_object_comp);
    obj->components = lzh_cpnt_link_create(lzh_link_cpnt_comp);

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
        lzh_obj_link_remove_value(pobj->children, object);
        object->parent = NULL;
    }

    if (parent) {
        lzh_obj_link_push(parent->children, object);
        object->parent = parent;
    }
}

void lzh_object_add_child(LZH_OBJECT *object, LZH_OBJECT *child)
{
    lzh_object_set_parent(child, object);
}

LZH_OBJECT *lzh_object_del_child(LZH_OBJECT *object, LZH_OBJECT *child)
{
    if (!object || !child) {
        return NULL;
    }

    if (object != child->parent) {
        return NULL;
    }

    lzh_object_set_parent(child, NULL);
    return child;
}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {
        if (object->parent) {
            /* 移除父节点中缓存的子对象 */
            LZH_OBJECT *parent = object->parent;
            int index = lzh_obj_link_index(parent->children, object);

            if (index >= 0) {
                lzh_obj_link_remove(parent->children, index, NULL);
            }
        }
        lzh_object_remove(object);
    }
}

void lzh_object_add_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;

        lzh_cpnt_link_push(object->components, elem);
    }
}

void *lzh_object_del_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;

        if (lzh_cpnt_link_remove_value(object->components, elem)) {
            return cpnt;
        }
    }
    return NULL;
}

LZH_SPRITE *lzh_object_get_sprite(LZH_OBJECT *object)
{
    LZH_CPNT_LINK *link = NULL;
    LZH_CPNT_LINK_NODE *node = NULL;
    int count = 0;
    int i = 0;

    LZH_SPRITE *sp = NULL;
    
    if (!object || !object->components) {
        return NULL;
    }

    link = object->components;
    node = link->head;
    count = link->count;
    i = 0;

    while (i++ < count) {
        LZH_COMPONENT *cpnt = node->value;

        if (cpnt && cpnt->type == LZH_CPNT_SPRITE) {
            sp = (LZH_SPRITE *)cpnt;
            break;
        }
        node = node->next;
    }

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
            LZH_OBJ_LINK *link = object->children;
            LZH_OBJ_LINK_NODE *node = link->head;

            int count = link->count;
            int i = 0;

            while (i++ < count) {
                LZH_OBJECT *child = node->value;

                if (child && child->base.update) {
                    child->base.update((LZH_BASE *)child, child->base.update_param);
                }
                node = node->next;
            }
        }

        /* 更新组件 */
        if (object->components) {
            LZH_CPNT_LINK *link = object->components;
            LZH_CPNT_LINK_NODE *node = link->head;

            int count = link->count;
            int i = 0;

            while (i++ < count) {
                LZH_COMPONENT *cpnt = node->value;

                if (cpnt && cpnt->base.update) {
                    cpnt->base.update((LZH_BASE *)cpnt, cpnt->base.update_param);
                }
                node = node->next;
            }
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
            LZH_OBJ_LINK *link = object->children;
            LZH_OBJ_LINK_NODE *node = link->head;

            int count = link->count;
            int i = 0;

            while (i++ < count) {
                LZH_OBJECT *child = node->value;

                if (child && child->base.fixed_update) {
                    child->base.fixed_update((LZH_BASE *)child, child->base.fixed_update_param);
                }
                node = node->next;
            }
        }

        /* 更新组件 */
        if (object->components) {
            LZH_CPNT_LINK *link = object->components;
            LZH_CPNT_LINK_NODE *node = link->head;

            int count = link->count;
            int i = 0;

            while (i++ < count) {
                LZH_COMPONENT *cpnt = node->value;

                if (cpnt && cpnt->base.fixed_update) {
                    cpnt->base.fixed_update((LZH_BASE *)cpnt, cpnt->base.fixed_update_param);
                }
                node = node->next;
            }
        }

        /* 用户层更新 */
        if (object->fixed_update) {
            object->fixed_update(base->engine, object, object->fixed_update_param);
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
