#include <string.h>
#include <lzh_mem.h>
#include <lzh_engine.h>

#include "lzh_core_transform.h"
#include "../math/lzh_mathdef.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

/* 组件更新 */
static void lzh_transform_update(LZH_BASE *base, void *args);

/* 组件移除 */
static void lzh_transform_remove(LZH_COMPONENT *cpnt);

/* 子对象变换组件访问 */
static void lzh_transform_rb_flush(const LZH_OBJ_RB_NODE *node, void *args);

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

    transform->world_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    transform->local_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    transform->world_angle = 0.0f;
    transform->local_angle = 0.0f;

    /* 空对象的中心点为 (0, 0) */
    transform->center_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    transform->world_scale = lzh_vec3f_xyz(1.0f, 1.0f, 1.0f);
    transform->local_scale = lzh_vec3f_xyz(1.0f, 1.0f, 1.0f);
    transform->world_mat = lzh_mat4x4f_unit();

    return transform;
}

void lzh_transform_destroy(LZH_TRANSFORM *transform)
{
    if (transform) {
        /* 从所属对象组件表中移除组件对象 */
        if (transform->base.object) {
            LZH_OBJECT *obj = transform->base.object;
            lzh_cpnt_rb_delete(obj->components, LZH_CPNT_TRANSFORM, NULL, NULL);
            transform->base.object = NULL;
        }
        lzh_transform_remove((LZH_COMPONENT *)transform);
    }
}

void lzh_transform_flush(LZH_TRANSFORM *transform)
{
    if (transform) {
        LZH_OBJECT *object = transform->base.object;
        LZH_OBJECT *parent = object->parent;

        LZH_VEC3F *localpos = &transform->local_pos;
        LZH_VEC3F *localscale = &transform->local_scale;

        LZH_VEC3F center_pos = lzh_vec3f_reverse(&transform->center_pos);

        /* 首先计算当前局部变换矩阵 */
        LZH_MAT4X4F local = lzh_mat4x4f_unit();
        LZH_MAT4X4F trans = lzh_mat4x4f_translate(localpos->x, localpos->y, 0.0f);
        LZH_MAT4X4F rotate = lzh_mat4x4f_rotate_z(transform->local_angle);
        LZH_MAT4X4F scale = lzh_mat4x4f_scale(localscale->x, localscale->y, 1.0f);
        LZH_MAT4X4F center = lzh_mat4x4f_translate(center_pos.x, center_pos.y, center_pos.z);

        /* 先平移至对象的中心点，然后进行仿射变换，最后进行投影变换 */
        local = lzh_mat4x4f_mul(&center, &local);
        local = lzh_mat4x4f_mul(&scale, &local);
        local = lzh_mat4x4f_mul(&rotate, &local);
        local = lzh_mat4x4f_mul(&trans, &local);

        if (parent && parent->transform) {
            LZH_TRANSFORM *ptransform = parent->transform;
            LZH_MAT4X4F pworld = ptransform->world_mat;

            local = lzh_mat4x4f_mul(&pworld, &local);
        }

        transform->world_mat = local;

        /* 更新世界坐标系数据 */
        lzh_transform_sync_world(transform);

        /* 遍历子对象的 TRANSFORM 组件，更新子对象的矩阵 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_transform_rb_flush, NULL);
        }
    }
}

void lzh_transform_sync_world(LZH_TRANSFORM *transform)
{
    LZH_MAT4X4F rotate;
    LZH_MAT4X4F scale;
    LZH_MAT4X4F trans;

    if (!transform) {
        return;
    }

    rotate = lzh_mat4x4f_get_rotate(&transform->world_mat);
    scale = lzh_mat4x4f_get_scale(&transform->world_mat);
    trans = lzh_mat4x4f_get_translate(&transform->world_mat);

    transform->world_angle = lzh_mat4x4f_rotate_z_angle(&rotate);
    transform->world_pos = lzh_vec3f_xyz(trans.m03, trans.m13, trans.m23);
    transform->world_scale = lzh_vec3f_xyz(scale.m00, scale.m11, scale.m22);
}

/*===========================================================================*/

void lzh_transform_update(LZH_BASE *base, void *args)
{
    /* TODO */
}

void lzh_transform_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TRANSFORM *transform = (LZH_TRANSFORM *)cpnt;
        lzh_cpnt_quit((LZH_COMPONENT *)transform);
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

/*===========================================================================*/
