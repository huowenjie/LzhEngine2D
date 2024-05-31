#include <lzh_engine.h>

#include "lzh_core_collider.h"
#include "lzh_core_transform.h"
#include "lzh_core_camera.h"

#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

/**
 * 在组件中：
 * TODO
 * 1.创建四叉树
 * 
 * 组件 UPDATE 逻辑:
 * 2.获取当前场景对象
 * 3.遍历场景中的渲染树对象，将对象添加至四叉树
 * 4.获取和当前对象处于同一区域的对象
 * 5.循环判断是否相交（根据设定的碰撞类型）
 * 6.如果碰撞，调用碰撞回调函数
 * 7.清空四叉树对象
 * 参照 level.cpp 的实现
 */

/* 组件加载到对象中 */
static void lzh_collider_b2_load(LZH_COLLIDER *collider, LZH_OBJECT *object);

/* 组件从对象中移除 */
static void lzh_collider_b2_unload(LZH_COLLIDER *collider, LZH_OBJECT *object);

/* 创建 box2d 组件 */
static void lzh_collider_b2_create_box2d(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param);

/* 创建 circle 组件 */
static void lzh_collider_b2_create_circle2d(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param);

/* 移除碰撞组件 */
static void lzh_collider_remove(LZH_COMPONENT *cpnt);

/* 碰撞更新 */
static void lzh_collider_update(LZH_BASE *base, void *args);

/*===========================================================================*/

LZH_COLLIDER *lzh_collider_create(LZH_ENGINE *engine, LZH_OBJECT *object)
{
    LZH_COLLIDER *collider = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine || !object) {
        return NULL;
    }

    collider = LZH_MALLOC(sizeof(LZH_COLLIDER));
    if (!collider) {
        return NULL;
    }
    memset(collider, 0, sizeof(LZH_COLLIDER));

    base = &collider->base;
    lzh_cpnt_init(base, LZH_CPNT_COLLIDER, object);

    base->base.engine = engine;
    base->base.fixed_update = lzh_collider_update;
    base->remove_component = lzh_collider_remove;

    lzh_collider_b2_load(collider, object);
    return collider;
}

void lzh_collider_destroy(LZH_COLLIDER *collider)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)collider);
}

void lzh_collider_set_param(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param)
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

void lzh_collider_set_start_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args)
{
    if (collider) {
        collider->start_contact = cb;
        collider->start_contact_args = args;
    }
}

void lzh_collider_set_end_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args)
{
    if (collider) {
        collider->end_contact = cb;
        collider->end_contact_args = args;
    }
}

/*===========================================================================*/

void lzh_collider_b2_load(LZH_COLLIDER *collider, LZH_OBJECT *object)
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

void lzh_collider_b2_unload(LZH_COLLIDER *collider, LZH_OBJECT *object)
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

void lzh_collider_b2_create_box2d(LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param)
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

void lzh_collider_b2_create_circle2d(LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param)
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
void lzh_collider_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_COLLIDER *collider = (LZH_COLLIDER *)cpnt;
        lzh_collider_b2_unload(collider, cpnt->object);

        lzh_cpnt_quit(cpnt);
        LZH_FREE(collider);
    }
}

void lzh_collider_update(LZH_BASE *base, void *args)
{
    LZH_COLLIDER *collider = NULL;
    LZH_OBJECT *object = NULL;

    LZH_B2_BODY *body = NULL;

    if (!base) {
        return;
    }

    collider = (LZH_COLLIDER *)base;

    object = collider->base.object;
    if (!object) {
        return;
    }
    body = collider->b2_body;

    LZH_TRANSFORM *transform = object->transform;
    LZH_VEC3F pos = transform->local_pos;
    LZH_VEC2F pos2d = lzh_vec2f_xy(pos.x, pos.y);

    lzh_b2_body_set_transform(body, &pos2d, 0.0f);
}

/*===========================================================================*/
