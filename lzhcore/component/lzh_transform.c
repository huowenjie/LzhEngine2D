#include <lzh_transform.h>

#include "lzh_core_transform.h"
#include "../object/lzh_core_object.h"
#include "../math/lzh_mathdef.h"

/*===========================================================================*/

LZH_OBJECT *lzh_transform_get_object(LZH_TRANSFORM *transform)
{
    if (transform) {
        return transform->base.object;
    }
    return NULL;
}

void lzh_transform_translate(LZH_TRANSFORM *transform, const LZH_VEC3F *vec)
{
    if (transform && vec) {
        transform->local_pos = lzh_vec3f_add(&transform->local_pos, vec);
        lzh_transform_flush(transform);
    }
}

void lzh_transform_scale(LZH_TRANSFORM *transform, const LZH_VEC3F *scale)
{
    if (transform && scale) {
        transform->local_scale = *scale;
        lzh_transform_flush(transform);
    }
}

void lzh_transform_rotate_z(LZH_TRANSFORM *transform, float angle)
{
    if (transform) {
        transform->local_angle += LZH_A2R(angle);
        lzh_transform_flush(transform);
    }
}

LZH_VEC3F lzh_transform_world_pos(LZH_TRANSFORM *transform)
{
    return lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
}

LZH_VEC3F lzh_transform_local_pos(LZH_TRANSFORM *transform)
{
    return lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
}

float lzh_transform_world_angle_z(LZH_TRANSFORM *transform)
{
    return 0.0f;
}

float lzh_transform_local_angle_z(LZH_TRANSFORM *transform)
{
    return 0.0f;
}

LZH_VEC3F lzh_transform_world_scale(LZH_TRANSFORM *transform)
{
    return lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
}

LZH_VEC3F lzh_transform_local_scale(LZH_TRANSFORM *transform)
{
    return lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
}

LZH_VEC3F lzh_transform_get_forward(LZH_TRANSFORM *transform)
{
    LZH_VEC3F forward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        forward = transform->forward;
    }

    return forward;
}

LZH_VEC3F lzh_transform_get_backward(LZH_TRANSFORM *transform)
{
    LZH_VEC3F backward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        backward = transform->backward;
    }

    return backward;
}

LZH_VEC3F lzh_transform_get_leftward(LZH_TRANSFORM *transform)
{
    LZH_VEC3F leftward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        leftward = transform->leftward;
    }

    return leftward;
}

LZH_VEC3F lzh_transform_get_rightward(LZH_TRANSFORM *transform)
{
    LZH_VEC3F rightward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        rightward = transform->rightward;
    }

    return rightward;
}

void lzh_transform_set_center(LZH_TRANSFORM *transform, const LZH_VEC3F *center)
{
    if (transform && center) {
        transform->center_pos = *center;
        lzh_transform_flush(transform);
    }
}

/*===========================================================================*/
