#include <lzh_engine.h>

#include "lzh_core_rigidbody2d.h"
#include "lzh_core_transform.h"
#include "lzh_core_camera.h"

#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

/* 移除碰撞组件 */
static void lzh_rigidbody2d_remove(LZH_COMPONENT *cpnt);

/* 碰撞更新 */
static void lzh_rigidbody2d_update(LZH_BASE *base, void *args);

/* 组件加载到对象中 */
static void lzh_rigidbody2d_b2_load(LZH_RIGIDBODY2D *body, LZH_OBJECT *object);

/* 组件从对象中移除 */
static void lzh_rigidbody2d_b2_unload(LZH_RIGIDBODY2D *body, LZH_OBJECT *object);

/*===========================================================================*/

LZH_RIGIDBODY2D *lzh_rigidbody2d_create(LZH_ENGINE *engine, LZH_OBJECT *object)
{
    LZH_RIGIDBODY2D *body = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine || !object) {
        return NULL;
    }

    body = LZH_MALLOC(sizeof(LZH_RIGIDBODY2D));
    if (!body) {
        return NULL;
    }
    memset(body, 0, sizeof(LZH_RIGIDBODY2D));

    base = &body->base;
    lzh_cpnt_init(base, LZH_CPNT_RIGIDBODY2D, object);

    base->base.engine = engine;
    base->base.fixed_update = lzh_rigidbody2d_update;
    base->remove_component = lzh_rigidbody2d_remove;
    body->collider2ds = cld2d_rb_create(lzh_rigidbody2d_cld2d_comp);

    lzh_rigidbody2d_b2_load(body, object);
    return body;
}

void lzh_rigidbody2d_destroy(LZH_RIGIDBODY2D *body)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)body);
}

/*===========================================================================*/

void lzh_rigidbody2d_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_RIGIDBODY2D *body = (LZH_RIGIDBODY2D *)cpnt;

        /* 必须先释放 collider 列表，collider 依赖 b2body 对象 */
        cld2d_rb_destroy(body->collider2ds, lzh_rigidbody2d_cld2d_delvisit, NULL);
        lzh_rigidbody2d_b2_unload(body, cpnt->object);

        lzh_cpnt_quit(cpnt);
        LZH_FREE(body);
    }
}

void lzh_rigidbody2d_update(LZH_BASE *base, void *args)
{
    LZH_RIGIDBODY2D *body = NULL;
    LZH_OBJECT *object = NULL;
    LZH_B2_BODY *b2body = NULL;
    LZH_TRANSFORM *transform = NULL;

    if (!base) {
        return;
    }

    body = (LZH_RIGIDBODY2D *)base;

    object = body->base.object;
    if (!object) {
        return;
    }
    
    b2body = body->b2body;
    if (!object) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    LZH_VEC3F pos = transform->local_pos;
    LZH_VEC2F pos2d = lzh_vec2f_xy(pos.x, pos.y);

    lzh_b2_body_set_transform(b2body, &pos2d, 0.0f);
}

void lzh_rigidbody2d_b2_load(LZH_RIGIDBODY2D *body, LZH_OBJECT *object)
{
    LZH_B2_BODY *b2_body = NULL;
    LZH_B2_WORLD *b2_world = NULL;
    LZH_SCENE *cur_scene = NULL;

    if (!body || !object) {
        return;
    }

    cur_scene = object->current_scene;
    if (!cur_scene) {
        return;
    }

    b2_world = cur_scene->world2d;
    if (!b2_world) {
        return;
    }

    b2_body = lzh_b2_body_create(b2_world, NULL, BT_DYNAMIC);
    if (!b2_body) {
        return;
    }

    body->b2body = b2_body;
}

void lzh_rigidbody2d_b2_unload(LZH_RIGIDBODY2D *body, LZH_OBJECT *object)
{
    LZH_B2_WORLD *b2_world = NULL;
    LZH_SCENE *cur_scene = NULL;

    if (!body || !object) {
        return;
    }

    cur_scene = object->current_scene;
    if (!cur_scene) {
        return;
    }

    b2_world = cur_scene->world2d;
    if (!b2_world) {
        return;
    }

    if (body->b2body) {
        lzh_b2_body_destroy(b2_world, body->b2body);
        body->b2body = NULL;
    }
}

/*===========================================================================*/
