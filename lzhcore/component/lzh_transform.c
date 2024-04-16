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

void lzh_transform_translate(LZH_TRANSFORM *transform, float x, float y, float z)
{
    if (transform) {
        LZH_VEC3F vec = lzh_vec3f_xyz(x, y, z);
        transform->local_pos = lzh_vec3f_add(&transform->local_pos, &vec);
        lzh_transform_flush(transform);
    }
}

void lzh_transform_scale(LZH_TRANSFORM *transform, float sx, float sy, float sz)
{
    if (transform) {
        LZH_VEC3F svec = lzh_vec3f_xyz(sx, sy, sz);
        transform->local_scale = svec;
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

void lzh_transform_world_pos(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
}

void lzh_transform_local_pos(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
}

float lzh_transform_world_angle_z(LZH_TRANSFORM *transform)
{
    return 0.0f;
}

float lzh_transform_local_angle_z(LZH_TRANSFORM *transform)
{
    return 0.0f;
}

void lzh_transform_world_scale(LZH_TRANSFORM *transform, float *sx, float *sy, float *sz)
{
}

void lzh_transform_local_scale(LZH_TRANSFORM *transform, float *sx, float *sy, float *sz)
{
}

void lzh_transform_get_forward(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
    LZH_VEC3F forward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        forward = transform->forward;
    }

    if (x) {
        *x = forward.x;
    }

    if (y) {
        *y = forward.y;
    }

    if (z) {
        *z = forward.z;
    }
}

void lzh_transform_get_backward(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
    LZH_VEC3F backward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        backward = transform->backward;
    }

    if (x) {
        *x = backward.x;
    }

    if (y) {
        *y = backward.y;
    }

    if (z) {
        *z = backward.z;
    }
}

void lzh_transform_get_leftward(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
    LZH_VEC3F leftward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        leftward = transform->leftward;
    }

    if (x) {
        *x = leftward.x;
    }

    if (y) {
        *y = leftward.y;
    }

    if (z) {
        *z = leftward.z;
    }
}

void lzh_transform_get_rightward(LZH_TRANSFORM *transform, float *x, float *y, float *z)
{
    LZH_VEC3F rightward = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (transform) {
        rightward = transform->rightward;
    }

    if (x) {
        *x = rightward.x;
    }

    if (y) {
        *y = rightward.y;
    }

    if (z) {
        *z = rightward.z;
    }
}

void lzh_transform_set_center(LZH_TRANSFORM *transform, float x, float y, float z)
{
    if (transform) {
        LZH_VEC3F center = lzh_vec3f_xyz(x, y, z);
        transform->center_pos = center;
        lzh_transform_flush(transform);
    }
}

/*===========================================================================*/
