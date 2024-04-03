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
