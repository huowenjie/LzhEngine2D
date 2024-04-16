#include <string.h>
#include <lzh_mem.h>
#include <lzh_engine.h>

#include "lzh_core_transform.h"
#include "../math/lzh_mathdef.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

/* 计算屏幕高度 */
static float lzh_transform_get_height(LZH_ENGINE *engine, float width);

/* 组件更新 */
static void lzh_transform_update(LZH_BASE *base, void *args);

/* 组件移除 */
static void lzh_transform_remove(LZH_COMPONENT *cpnt);

/* 子对象变换组件访问 */
static void lzh_transform_rb_flush(const LZH_OBJ_RB_NODE *node, void *args);

/* 更新当前对象的方向轴 */
static void lzh_transform_update_axis(LZH_TRANSFORM *transform, LZH_MAT4X4F *mat);

/*===========================================================================*/

LZH_TRANSFORM *lzh_transform_create(LZH_ENGINE *engine)
{
    LZH_TRANSFORM *transform = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine) {
        return NULL;
    }

    transform = LZH_MALLOC(sizeof(LZH_TRANSFORM));
    if (!transform) {
        return NULL;
    }
    memset(transform, 0, sizeof(LZH_TRANSFORM));

    base = &transform->base;
    lzh_cpnt_init(base);

    base->base.engine = engine;
    base->base.update = lzh_transform_update;
    base->base.fixed_update = lzh_transform_update;
    base->type = LZH_CPNT_TRANSFORM;
    base->remove_component = lzh_transform_remove;

    transform->screen_width = 1600.0f;
    transform->screen_height = lzh_transform_get_height(
        engine, transform->screen_width);
    transform->local_angle = 0.0f;

    transform->local_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    transform->center_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    transform->local_scale = lzh_vec3f_xyz(1.0f, 1.0f, 1.0f);

    transform->forward = lzh_vec3f_xyz(1.0f, 0.0f, 0.0f);
    transform->backward = lzh_vec3f_xyz(-1.0f, 0.0f, 0.0f);
    transform->leftward = lzh_vec3f_xyz(0.0f, 1.0f, 0.0f);
    transform->rightward = lzh_vec3f_xyz(0.0f, -1.0f, 0.0f);

    transform->model_mat = lzh_mat4x4f_unit();

    return transform;
}

void lzh_transform_destroy(LZH_TRANSFORM *transform)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)transform);
}

void lzh_transform_flush(LZH_TRANSFORM *transform)
{
    if (transform) {
        LZH_OBJECT *object = transform->base.object;
        LZH_OBJECT *parent = object->parent;

        LZH_VEC3F *localpos = &transform->local_pos;
        LZH_VEC3F *localscale = &transform->local_scale;
        LZH_VEC3F *centerpos = &transform->center_pos;

        /* 模型变换 */
        LZH_MAT4X4F local = lzh_mat4x4f_unit();
        LZH_MAT4X4F trans = lzh_mat4x4f_translate(localpos->x, localpos->y, localpos->z);
        LZH_MAT4X4F rotate = lzh_mat4x4f_rotate_z(transform->local_angle);
        LZH_MAT4X4F scale = lzh_mat4x4f_scale(localscale->x, localscale->y, localscale->z);

        /* 移动至旋转中心坐标  */
        LZH_MAT4X4F centermat = lzh_mat4x4f_translate(
            -centerpos->x,
            -centerpos->y,
            -centerpos->z);

        local = lzh_mat4x4f_mul(&scale, &local);

        /* 围绕中心点旋转 */
        local = lzh_mat4x4f_mul(&centermat, &local);
        local = lzh_mat4x4f_mul(&rotate, &local);
        centermat = lzh_mat4x4f_translate(
            centerpos->x,
            centerpos->y,
            centerpos->z);
        local = lzh_mat4x4f_mul(&centermat, &local);
        local = lzh_mat4x4f_mul(&trans, &local);

        if (parent && parent->transform) {
            LZH_TRANSFORM *ptransform = parent->transform;
            LZH_MAT4X4F pworld = ptransform->model_mat;

            local = lzh_mat4x4f_mul(&pworld, &local);
        }

        lzh_transform_update_axis(transform, &local);
        transform->model_mat = local;

        /* 遍历子对象的 TRANSFORM 组件，更新子对象的矩阵 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_transform_rb_flush, NULL);
        }
    }
}

/*===========================================================================*/

float lzh_transform_get_height(LZH_ENGINE *engine, float width)
{
    int iw = 0;
    int ih = 0;
    float fw = 0.0f;
    float fh = 0.0f;
    float hw = 0.0f;

    float fixed_w = width;
    float fixed_h = 0.0f;

    if (!engine) {
        return 0.0f;
    }

    /* 获取屏幕尺寸 */
    lzh_engine_win_size(engine, &iw, &ih);
    fw = (float)iw;
    fh = (float)ih;

    if (fw == 0 || fh == 0) {
        return 0.0f;
    }

    /* 计算屏幕高宽比 */
    hw = fh / fw;
    fixed_h = fixed_w * hw;

    return fixed_h;
}

void lzh_transform_update(LZH_BASE *base, void *args)
{
    /* TODO */
}

void lzh_transform_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TRANSFORM *transform = (LZH_TRANSFORM *)cpnt;
        lzh_cpnt_quit(cpnt);
        LZH_FREE(transform);
    }
}

void lzh_transform_rb_flush(const LZH_OBJ_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_OBJECT *object = node->value;
        LZH_TRANSFORM *transform = object->transform;

        if (transform) {
            lzh_transform_flush(transform);
        }
    }
}

void lzh_transform_update_axis(LZH_TRANSFORM *transform, LZH_MAT4X4F *mat)
{
    LZH_VEC4F forward;
    LZH_VEC4F backward;
    LZH_VEC4F leftward;
    LZH_VEC4F rightward;

    if (!transform || !mat) {
        return;
    }

    forward = lzh_vec4f_xyzw(1.0f, 0.0f, 0.0f, 0.0f);
    backward = lzh_vec4f_xyzw(-1.0f, 0.0f, 0.0f, 0.0f);
    leftward = lzh_vec4f_xyzw(0.0f, 1.0f, 0.0f, 0.0f);
    rightward = lzh_vec4f_xyzw(0.0f, -1.0f, 0.0f, 0.0f);

    forward = lzh_mat4x4f_mul_vec(mat, &forward);
    backward = lzh_mat4x4f_mul_vec(mat, &backward);
    leftward = lzh_mat4x4f_mul_vec(mat, &leftward);
    rightward = lzh_mat4x4f_mul_vec(mat, &rightward);

    transform->forward = lzh_vec3f_xyz(forward.x, forward.y, forward.z);
    transform->backward = lzh_vec3f_xyz(backward.x, backward.y, backward.z);
    transform->leftward = lzh_vec3f_xyz(leftward.x, leftward.y, leftward.z);
    transform->rightward = lzh_vec3f_xyz(rightward.x, rightward.y, rightward.z);

    transform->forward = lzh_vec3f_normalize(&transform->forward);
    transform->backward = lzh_vec3f_normalize(&transform->backward);
    transform->leftward = lzh_vec3f_normalize(&transform->leftward);
    transform->rightward = lzh_vec3f_normalize(&transform->rightward);
}

/*===========================================================================*/
