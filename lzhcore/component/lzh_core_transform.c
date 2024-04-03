#include <string.h>
#include <lzh_mem.h>

#include "lzh_core_transform.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

/* 组件更新 */
static void lzh_transform_update(LZH_BASE *base, void *args);

/* 组件移除 */
static void lzh_transform_remove(LZH_COMPONENT *cpnt);

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
    transform->center_pos = lzh_vec2f_xy(0.0f, 0.0f);

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

/*===========================================================================*/

void lzh_transform_update(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_TRANSFORM *tansform = (LZH_TRANSFORM *)base;
        int i = 0;
    }
}

void lzh_transform_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TRANSFORM *transform = (LZH_TRANSFORM *)cpnt;
        lzh_cpnt_quit((LZH_COMPONENT *)transform);
        LZH_FREE(transform);
    }
}

/*===========================================================================*/
