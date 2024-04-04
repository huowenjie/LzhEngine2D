#include <lzh_transform.h>

#include "lzh_core_transform.h"
#include "../object/lzh_core_object.h"

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
        LZH_MAT4X4F trans = lzh_mat4x4f_translate(vec->x, vec->y, vec->z);
        LZH_VEC4F origin = lzh_vec4f_vec3f(&transform->local_pos, 1.0f);
        LZH_VEC4F pos = lzh_mat4x4f_mul_vec(&trans, &origin);
        transform->local_pos = lzh_vec3f_xyz(pos.x, pos.y, pos.z);

        lzh_transform_flush(transform);
    }
}

void lzh_transform_scale(LZH_TRANSFORM *transform, const LZH_VEC3F *scale)
{

}

void lzh_transform_rotate_z(LZH_TRANSFORM *transform, float angle)
{

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

/*===========================================================================*/
