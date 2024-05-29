#include <lzh_engine.h>

#include "lzh_core_collider.h"
#include "lzh_core_transform.h"
#include "lzh_core_camera.h"

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

/* �����ײ���� */
static void add_collider(const SCENE_OBJ_RB_NODE *node, void *args);

/* ��ȡ����������� */
void get_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param);

/* ��ȡ���β��� */
static void get_box2d_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param);

/* ��ȡԲ�β��� */
static void get_circle2d_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param);

/* ��ȡ��ײ���� */
static LZH_OBJECT *get_collider_object(LZH_COLLIDER *collider, LZH_OBJECT *src);

/* ��ȡ������ײ���� */
static LZH_OBJECT *get_collider_box2d_object(LZH_COLLIDER *collider, LZH_OBJECT *src);

/* ��ȡԲ����ײ���� */
static LZH_OBJECT *get_collider_circle2d_object(LZH_COLLIDER *collider, LZH_OBJECT *src);

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
    collider->b2_body = NULL;
    collider->b2_fixture = NULL;
    /* ��Ҫ�ڹ��ص������ʱ����г�ʼ�� TODO */
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

void lzh_collider_set_callback(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args)
{
    if (collider) {
        collider->callback = cb;
        collider->args = args;
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

void lzh_collider_update(LZH_BASE *base, void *args)
{
    LZH_COLLIDER *collider = NULL;
    LZH_OBJECT *object = NULL;
    LZH_OBJECT *collide_obj = NULL;
    LZH_QUAD_TREE *quad = NULL;

    LZH_SCENE *cur_scene = NULL;
    LZH_CAMERA *camera = NULL;

    LZH_RECTF region;

    if (!base) {
        return;
    }

    collider = (LZH_COLLIDER *)base;

    object = collider->base.object;
    if (!object) {
        return;
    }

    quad = collider->quad;
    if (!quad) {
        return;
    }

    cur_scene = object->current_scene;
    if (!cur_scene || !cur_scene->main_camera) {
        return;
    }

    camera = (LZH_CAMERA *)lzh_cpnt_get_type(
        cur_scene->main_camera->components, LZH_CPNT_CAMERA);
    if (!camera) {
        return;
    }

    /* Ĭ�ϵ���ײ����Ϊ��Ļ��С������ */
    lzh_rectf_init(
        &region,
        -camera->view_port_w / 2.0f,
        -camera->view_port_h / 2.0f,
        camera->view_port_w,
        camera->view_port_h
    );
    lzh_quad_tree_init_root(quad, &region);

    /* ���������Ҫ������ײ���� */
    scene_obj_rb_iterate(cur_scene->render_tree, add_collider, quad);

    /* ��⵽��ײ֮�󣬵��ûص�����֪ͨ�û� */
    collide_obj = get_collider_object(collider, object);
    if (collide_obj && collider->callback) {
        collider->callback(object, collide_obj, collider->args);
    }

    /* ����Ĳ����ڵ� */
    lzh_quad_tree_clear(quad);
}

void add_collider(const SCENE_OBJ_RB_NODE *node, void *args)
{
    LZH_QUAD_TREE *quad = (LZH_QUAD_TREE *)args;
    if (!quad) {
        return;
    }

    LZH_OBJECT *object = node->value;
    if (object) {
        /* �жϱ������Ƿ��������ײ��� */
        if (lzh_cpnt_get_type(object->components, LZH_CPNT_COLLIDER)) {
            lzh_quad_tree_add(quad, object);
        }
    }
}

void get_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param)
{
    if (!collider || !param) {
        return;
    }

    if (collider->param.type == BOX_2D) {
        get_box2d_world_param(collider, param);
    } else if (collider->param.type == CIRCLE_2D) {
        get_circle2d_world_param(collider, param);
    }
}

void get_box2d_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param)
{
    LZH_OBJECT *object = NULL;
    LZH_TRANSFORM *transform = NULL;
    LZH_MAT4X4F model = lzh_mat4x4f_unit();
    LZH_VEC4F pos;

    if (!collider || !param) {
        return;
    }

    object = collider->base.object;
    if (!object) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    /* ֻ��ȡƽ�ƾ��� */
    model = lzh_mat4x4f_get_translate(&transform->model_mat);
    pos = lzh_vec4f_xyzw(
        collider->param.box2d.x, collider->param.box2d.y, 0.0f, 1.0f);
    pos = lzh_mat4x4f_mul_vec(&model, &pos);

    param->type = collider->param.type;
    param->box2d.x = pos.x;
    param->box2d.y = pos.y;
    param->box2d.w = collider->param.box2d.w;
    param->box2d.h = collider->param.box2d.h;
}

void get_circle2d_world_param(LZH_COLLIDER *collider, LZH_COLLIDER_PARAM *param)
{
    LZH_OBJECT *object = NULL;
    LZH_TRANSFORM *transform = NULL;
    LZH_MAT4X4F model = lzh_mat4x4f_unit();
    LZH_VEC4F pos;

    if (!collider || !param) {
        return;
    }

    object = collider->base.object;
    if (!object) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    /* ֻ��ȡƽ�ƾ��� */
    model = lzh_mat4x4f_get_translate(&transform->model_mat);
    pos = lzh_vec4f_xyzw(
        collider->param.circle2d.cx, collider->param.circle2d.cy, 0.0f, 1.0f);
    pos = lzh_mat4x4f_mul_vec(&model, &pos);

    param->type = collider->param.type;
    param->circle2d.cx = pos.x;
    param->circle2d.cy = pos.y;
    param->circle2d.r = collider->param.circle2d.r;
}

LZH_OBJECT *get_collider_object(LZH_COLLIDER *collider, LZH_OBJECT *src)
{
    if (!collider || !src) {
        return NULL;
    }

    if (collider->param.type == BOX_2D) {
        return get_collider_box2d_object(collider, src);
    } else if (collider->param.type == CIRCLE_2D) {
        return get_collider_circle2d_object(collider, src);
    }

    return NULL;
}

LZH_OBJECT *get_collider_box2d_object(LZH_COLLIDER *collider, LZH_OBJECT *src)
{
    int count = 0;
    int i = 0;

    LZH_OBJECT **list = NULL;
    LZH_OBJECT *ret = NULL;
    LZH_RECTF src_rect;
    LZH_RECTF cld_rect;

    LZH_QUAD_TREE *quad = NULL;
    LZH_COLLIDER_PARAM param;

    if (!collider || !src) {
        return ret;
    }

    get_world_param(collider, &param);
    quad = collider->quad;
    if (!quad) {
        return ret;
    }

    lzh_quad_tree_find(quad, src, list, &count);

    if (!count) {
        return ret;
    }

    list = LZH_MALLOC(sizeof(LZH_OBJECT *) * count);
    if (!list) {
        return ret;
    }
    memset(list, 0, sizeof(LZH_OBJECT *) * count);

    lzh_quad_tree_find(quad, src, list, &count);

    src_rect.x = param.box2d.x;
    src_rect.y = param.box2d.y;
    src_rect.w = param.box2d.w;
    src_rect.h = param.box2d.h;

    for (i = 0; i < count; i++) {
        LZH_OBJECT *obj = list[i];

        if (!obj || obj == src) {
            continue;
        }

        LZH_COMPONENT *cpnt = lzh_cpnt_get_type(obj->components, LZH_CPNT_COLLIDER);
        if (cpnt) {
            LZH_COLLIDER *cld = (LZH_COLLIDER *)cpnt;
            LZH_COLLIDER_PARAM cld_param;

            get_world_param(cld, &cld_param);
            cld_rect.x = cld_param.box2d.x;
            cld_rect.y = cld_param.box2d.y;
            cld_rect.w = cld_param.box2d.w;
            cld_rect.h = cld_param.box2d.h;

            if (lzh_rectf_intersection(&src_rect, &cld_rect)) {
                ret = obj;
                break;
            }
        }
    }

    LZH_FREE(list);
    return ret;
}

LZH_OBJECT *get_collider_circle2d_object(LZH_COLLIDER *collider, LZH_OBJECT *src)
{
    return NULL;
}

LZH_RECTF lzh_collider_rectf(LZH_COLLIDER *collider)
{
    LZH_RECTF rect = { 0 };
    LZH_COLLIDER_PARAM param;

    if (!collider) {
        return rect;
    }

    get_world_param(collider, &param);

    if (param.type == BOX_2D) {
        rect.x = param.box2d.x;
        rect.y = param.box2d.y;
        rect.w = param.box2d.w;
        rect.h = param.box2d.h;
    } else if (param.type == CIRCLE_2D) {
        rect.x = param.circle2d.cx;
        rect.y = param.circle2d.cy;
        rect.w = param.circle2d.r;
        rect.h = param.circle2d.r;
    }

    return rect;
}

/*===========================================================================*/
