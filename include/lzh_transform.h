#ifndef __LZH_TRANSFORM_H__
#define __LZH_TRANSFORM_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* 变换组件 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 坐标系采用右手坐标系 */

/* 获取对象 */
LZH_API LZH_OBJECT *lzh_transform_get_object(LZH_TRANSFORM *transform);

/* 平移 */
LZH_API void lzh_transform_translate(LZH_TRANSFORM *transform, const LZH_VEC3F *vec);

/* 缩放 */
LZH_API void lzh_transform_scale(LZH_TRANSFORM *transform, const LZH_VEC3F *scale);

/* 绕 z 轴旋转 */
LZH_API void lzh_transform_rotate_z(LZH_TRANSFORM *transform, float angle);

/* 获取当前世界坐标 */
LZH_API LZH_VEC3F lzh_transform_world_pos(LZH_TRANSFORM *transform);

/* 获取当前本地坐标 */
LZH_API LZH_VEC3F lzh_transform_local_pos(LZH_TRANSFORM *transform);

/* 获取在世界坐标下绕 z 轴的旋转 */
LZH_API float lzh_transform_world_angle_z(LZH_TRANSFORM *transform);

/* 获取在本地坐标下绕 z 轴的旋转 */
LZH_API float lzh_transform_local_angle_z(LZH_TRANSFORM *transform);

/* 获取在世界坐标下的缩放系数 */
LZH_API LZH_VEC3F lzh_transform_world_scale(LZH_TRANSFORM *transform);

/* 获取在本地坐标下的缩放系数 */
LZH_API LZH_VEC3F lzh_transform_local_scale(LZH_TRANSFORM *transform);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TRANSFORM_H__ */
