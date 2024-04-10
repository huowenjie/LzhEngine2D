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

/* ��ȡǰ���������� x �������� */
LZH_API LZH_VEC3F lzh_transform_get_forward(LZH_TRANSFORM *transform);

/* ��ȡ������������ x �Ḻ���� */
LZH_API LZH_VEC3F lzh_transform_get_backward(LZH_TRANSFORM *transform);

/* ��ȡ������������ y �������� */
LZH_API LZH_VEC3F lzh_transform_get_leftward(LZH_TRANSFORM *transform);

/* ��ȡ������������ y �Ḻ���� */
LZH_API LZH_VEC3F lzh_transform_get_rightward(LZH_TRANSFORM *transform);

/* �������ĵ� */
LZH_API void lzh_transform_set_center(LZH_TRANSFORM *transform, const LZH_VEC3F *center);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TRANSFORM_H__ */
