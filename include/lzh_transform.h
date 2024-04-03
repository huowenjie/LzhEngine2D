#ifndef __LZH_TRANSFORM_H__
#define __LZH_TRANSFORM_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* �任��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ����ϵ������������ϵ */

/* ��ȡ���� */
LZH_API LZH_OBJECT *lzh_transform_get_object(LZH_TRANSFORM *transform);

/* ƽ�� */
LZH_API void lzh_transform_translate(LZH_TRANSFORM *transform, const LZH_VEC3F *vec);

/* ���� */
LZH_API void lzh_transform_scale(LZH_TRANSFORM *transform, const LZH_VEC3F *scale);

/* �� z ����ת */
LZH_API void lzh_transform_rotate_z(LZH_TRANSFORM *transform, float angle);

/* ��ȡ��ǰ�������� */
LZH_API LZH_VEC3F lzh_transform_world_pos(LZH_TRANSFORM *transform);

/* ��ȡ��ǰ�������� */
LZH_API LZH_VEC3F lzh_transform_local_pos(LZH_TRANSFORM *transform);

/* ��ȡ�������������� z �����ת */
LZH_API float lzh_transform_world_angle_z(LZH_TRANSFORM *transform);

/* ��ȡ�ڱ����������� z �����ת */
LZH_API float lzh_transform_local_angle_z(LZH_TRANSFORM *transform);

/* ��ȡ�����������µ�����ϵ�� */
LZH_API LZH_VEC3F lzh_transform_world_scale(LZH_TRANSFORM *transform);

/* ��ȡ�ڱ��������µ�����ϵ�� */
LZH_API LZH_VEC3F lzh_transform_local_scale(LZH_TRANSFORM *transform);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TRANSFORM_H__ */
