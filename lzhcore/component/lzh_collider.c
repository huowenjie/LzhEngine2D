#include <lzh_engine.h>
#include "lzh_core_collider.h"

#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

/**
 * ������У�
 * TODO
 * 1.�����Ĳ���
 * 
 * ��� UPDATE �߼�:
 * 2.��ȡ��ǰ��������
 * 3.���������е���Ⱦ�����󣬽�����������Ĳ���
 * 4.��ȡ�͵�ǰ������ͬһ����Ķ���
 * 5.ѭ���ж��Ƿ��ཻ�������趨����ײ���ͣ�
 * 6.�����ײ��������ײ�ص�����
 * 7.����Ĳ�������
 * ���� level.cpp ��ʵ��
 */

/* �Ƴ���ײ��� */
static void lzh_collider_remove(LZH_COMPONENT *cpnt);

/* ��ײ���� */
static void lzh_collider_update(LZH_BASE *base, void *args);

/*===========================================================================*/

LZH_COLLIDER *lzh_collider_create(LZH_ENGINE *engine)
{
    LZH_COLLIDER *collider = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine) {
        return NULL;
    }

    collider = LZH_MALLOC(sizeof(LZH_COLLIDER));
    if (!collider) {
        return NULL;
    }
    memset(collider, 0, sizeof(LZH_COLLIDER));

    base = &collider->base;
    lzh_cpnt_init(base);

    base->base.engine = engine;
    base->type = LZH_CPNT_COLLIDER;
    base->base.update = lzh_collider_update;
    base->remove_component = lzh_collider_remove;

    collider->quad = lzh_quad_tree_create();
    return collider;
}

void lzh_collider_destroy(LZH_COLLIDER *collider)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)collider);
}

void lzh_collider_set_param(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param)
{
    if (collider && param) {
        collider->param = *param;
    }
}

void lzh_collider_set_callback(LZH_COLLIDER *collider, LZH_COLLIDER_CB cb)
{
    if (collider) {
        collider->callback = cb;
    }
}

/*===========================================================================*/

void lzh_collider_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_COLLIDER *collider = (LZH_COLLIDER *)cpnt;

        if (collider->quad) {
            lzh_quad_tree_clear(collider->quad);
            lzh_quad_tree_destroy(collider->quad);
        }

        lzh_cpnt_quit(cpnt);
        LZH_FREE(collider);
    }
}

static void add_collider(const SCENE_OBJ_RB_NODE *node, void *args)
{
    LZH_QUAD_TREE *quad = (LZH_QUAD_TREE *)args;
    if (!quad) {
        return;
    }

    if (node->value) {
        // TODO �жϱ������Ƿ��������ײ���
        // if (obj->type == OBJ_TYPE_TANK || obj->type == OBJ_TYPE_BULLET) {
        //     lzh_quad_tree_add(level->quad_tree, obj->object);
        // }
    }
}

void lzh_collider_update(LZH_BASE *base, void *args)
{
    LZH_COLLIDER *collider = NULL;
    LZH_OBJECT *object = NULL;
    LZH_ENGINE *engine = NULL;
    LZH_QUAD_TREE *quad = NULL;

    LZH_SCENE_MANAGER *sm = NULL;
    LZH_SCENE *cur_scene = NULL;

    int w = 0;
    int h = 0;
    LZH_RECTF region;

    if (!base) {
        return;
    }

    collider = (LZH_COLLIDER *)base;

    object = collider->base.object;
    if (!object) {
        return;
    }

    engine = object->base.engine;
    if (!engine) {
        return;
    }

    quad = collider->quad;
    if (!quad) {
        return;
    }

    sm = engine->scene_manager;
    if (!sm || !sm->scene_active) {
        return;
    }

    cur_scene = sm->scene_active;

    /* Ĭ�ϵ���ײ����Ϊ��Ļ��С������ */
    lzh_engine_win_size(engine, &w, &h);
    lzh_rectf_init(&region, 0.0f, 0.0f, (float)w, (float)h);
    lzh_quad_tree_init_root(quad, &region);

    /* ���������Ҫ������ײ���� */
    scene_obj_rb_iterate(cur_scene->render_tree, add_collider, quad);
}

/*===========================================================================*/
