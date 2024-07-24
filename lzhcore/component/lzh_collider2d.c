#include <lzh_engine.h>

#include "lzh_core_rigidbody2d.h"
#include "lzh_core_collider2d.h"
#include "lzh_core_transform.h"
#include "lzh_core_camera.h"

#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

/* 组件加载到对象中 */
static void lzh_collider_b2_load(LZH_COLLIDER2D *collider, LZH_OBJECT *object);

/* 组件从对象中移除 */
static void lzh_collider_b2_unload(LZH_COLLIDER2D *collider, LZH_OBJECT *object);

#if 0
/* 创建 box2d 组件 */
static void lzh_collider_b2_create_box2d(
    LZH_COLLIDER2D *collider, const LZH_COLLIDER_PARAM *param);

/* 创建 circle 组件 */
static void lzh_collider_b2_create_circle2d(
    LZH_COLLIDER2D *collider, const LZH_COLLIDER_PARAM *param);
#endif

/*===========================================================================*/

LZH_COLLIDER2D *lzh_collider2d_create(LZH_RIGIDBODY2D *body)
{
    LZH_COLLIDER2D *collider = NULL;
    LZH_COMPONENT *base = NULL;

    if (!body) {
        return NULL;
    }

    collider = LZH_MALLOC(sizeof(LZH_COLLIDER2D));
    if (!collider) {
        return NULL;
    }
    memset(collider, 0, sizeof(LZH_COLLIDER2D));

    // base = &collider->base;
    // lzh_cpnt_init(base, LZH_CPNT_COLLIDER2D, object);

    // base->base.engine = engine;
    // base->remove_component = lzh_collider2d_remove;

    // lzh_collider_b2_load(collider, object);
    return collider;
}

void lzh_collider2d_destroy(LZH_COLLIDER2D *collider)
{
    if (collider) {
        lzh_rigibody2d_remove_cld2d(collider->rigidbody, collider);
    }    
}

#if 0
void lzh_collider2d_set_param(
    LZH_COLLIDER2D *collider, const LZH_COLLIDER_PARAM *param)
{
    if (!param) {
        return;
    }

    if (param->type == BOX_2D) {
        lzh_collider_b2_create_box2d(collider, param);
    } else if (param->type == CIRCLE_2D) {
        lzh_collider_b2_create_circle2d(collider, param);
    }
}
#endif

void lzh_collider2d_set_type(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_TYPE type)
{
    
}

void lzh_collider2d_set_rect(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h)
{
    
}

void lzh_collider2d_set_circle(
    LZH_COLLIDER2D *collider, float cx, float cy, float r)
{

}

void lzh_collider2d_set_start_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args)
{
    if (collider) {
        collider->start_contact = cb;
        collider->start_contact_args = args;
    }
}

void lzh_collider2d_set_end_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args)
{
    if (collider) {
        collider->end_contact = cb;
        collider->end_contact_args = args;
    }
}

/*===========================================================================*/

#if 0
void lzh_collider_b2_load(LZH_COLLIDER2D *collider, LZH_OBJECT *object)
{
    LZH_B2_BODY *b2_body = NULL;
    LZH_B2_FIXUTRE *b2_fixture = NULL;
    LZH_B2_WORLD *b2_world = NULL;
    LZH_B2_SHAPE_BOX *b2_box = NULL;
    LZH_SCENE *cur_scene = NULL;

    if (!collider || !object) {
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

    b2_box = lzh_b2_shape_box_create(NULL, 1.0f, 1.0f);
    if (!b2_box) {
        lzh_b2_body_destroy(b2_world, b2_body);
        return;
    }

    b2_fixture = lzh_b2_fixture_create(b2_body, b2_box);
    if (!b2_fixture) {
        lzh_b2_shape_box_destroy(b2_box);
        lzh_b2_body_destroy(b2_world, b2_body);
        return;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(b2_fixture, object);

    collider->b2_body = b2_body;
    collider->b2_fixture = b2_fixture;
    lzh_b2_shape_box_destroy(b2_box);
}

void lzh_collider_b2_unload(LZH_COLLIDER2D *collider, LZH_OBJECT *object)
{
    LZH_B2_WORLD *b2_world = NULL;
    LZH_SCENE *cur_scene = NULL;

    if (!collider || !object) {
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

    if (collider->b2_body) {
        if (collider->b2_fixture) {
            lzh_b2_fixture_destroy(collider->b2_body, collider->b2_fixture);
            collider->b2_fixture = NULL;
        }

        lzh_b2_body_destroy(b2_world, collider->b2_body);
        collider->b2_body = NULL;
    }
}

void lzh_collider_b2_create_box2d(LZH_COLLIDER2D *collider, const LZH_COLLIDER_PARAM *param)
{
    LZH_B2_BODY *body = NULL;
    LZH_B2_FIXUTRE *fixture = NULL;
    const LZH_COLLIDER_BOX_2D *box2d = NULL;
    LZH_B2_SHAPE_BOX *b2_box = NULL;
    void *data = NULL;

    LZH_VEC2F center;

    if (!collider || !param) {
        return;
    }

    body = collider->b2_body;
    if (!body) {
        return;
    }

    fixture = collider->b2_fixture;
    if (!fixture) {
        return;
    }

    box2d = &param->box2d;
    center = lzh_vec2f_xy(box2d->cx, box2d->cy);
    data = lzh_b2_fixture_get_data(fixture);

    b2_box = lzh_b2_shape_box_create(
        &center, box2d->w / 2.0f, box2d->h / 2.0f);
    if (!b2_box) {
        return;
    }

    lzh_b2_fixture_destroy(body, fixture);
    collider->b2_fixture = NULL;

    fixture = lzh_b2_fixture_create(body, b2_box);
    if (!fixture) {
        lzh_b2_shape_box_destroy(b2_box);
        return;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(fixture, data);

    collider->b2_fixture = fixture;
    lzh_b2_shape_box_destroy(b2_box);
}

void lzh_collider_b2_create_circle2d(LZH_COLLIDER2D *collider, const LZH_COLLIDER_PARAM *param)
{
    LZH_B2_BODY *body = NULL;
    LZH_B2_FIXUTRE *fixture = NULL;
    const LZH_COLLIDER_CIRCLE_2D *circle2d = NULL;
    LZH_B2_SHAPE_CIRCLE *b2_circle = NULL;
    void *data = NULL;

    LZH_VEC2F center;

    if (!collider || !param) {
        return;
    }

    body = collider->b2_body;
    if (!body) {
        return;
    }

    fixture = collider->b2_fixture;
    if (!fixture) {
        return;
    }

    circle2d = &param->circle2d;
    center = lzh_vec2f_xy(circle2d->cx, circle2d->cy);
    data = lzh_b2_fixture_get_data(fixture);

    b2_circle = lzh_b2_shape_circle_create(&center, circle2d->r);
    if (!b2_circle) {
        return;
    }

    lzh_b2_fixture_destroy(body, fixture);
    collider->b2_fixture = NULL;

    fixture = lzh_b2_fixture_create(body, b2_circle);
    if (!fixture) {
        lzh_b2_shape_circle_destroy(b2_circle);
        return;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(fixture, data);

    collider->b2_fixture = fixture;
    lzh_b2_shape_circle_destroy(b2_circle);
}
#endif

/*===========================================================================*/
