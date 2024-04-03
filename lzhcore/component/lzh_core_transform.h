#ifndef __LZH_CORE_TRANSFORM_H__
#define __LZH_CORE_TRANSFORM_H__

#include <lzh_mat4x4f.h>
#include <lzh_vec4f.h>

#include "lzh_component.h"

/*===========================================================================*/
/* 变换组件定义 */
/*===========================================================================*/

struct LZH_TRANSFORM {
    LZH_COMPONENT base;     /* 基本组件信息 */

    LZH_VEC3F world_pos;    /* 对象世界坐标 */
    LZH_VEC3F local_pos;    /* 对象局部坐标 */

    float world_angle;      /* 世界旋转角度 */
    float local_angle;      /* 局部旋转角度 */
    LZH_VEC2F center_pos;   /* 旋转中心点 */

    LZH_VEC3F world_scale;  /* 世界坐标缩放 */
    LZH_VEC3F local_scale;  /* 本地坐标缩放 */

    LZH_MAT4X4F world_mat;  /* 变换矩阵 */
};

/* 创建组件 */
LZH_TRANSFORM *lzh_transform_create(LZH_ENGINE *engine);

/* 销毁组件 */
void lzh_transform_destroy(LZH_TRANSFORM *transform);

/*===========================================================================*/

#endif /* __LZH_CORE_TRANSFORM_H__ */
