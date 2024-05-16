#ifndef __LZH_TRANSFORM_H__
#define __LZH_TRANSFORM_H__

#include "lzh_type.h"

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
LZH_API void lzh_transform_translate(LZH_TRANSFORM *transform, float x, float y, float z);

/* ���� */
LZH_API void lzh_transform_scale(LZH_TRANSFORM *transform, float sx, float sy, float sz);

/* �� z ����ת */
LZH_API void lzh_transform_rotate_z(LZH_TRANSFORM *transform, float angle);

/* �� x ����ת */
LZH_API void lzh_transform_rotate_x(LZH_TRANSFORM *transform, float angle);

/* �� y ����ת */
LZH_API void lzh_transform_rotate_y(LZH_TRANSFORM *transform, float angle);

/* ��ȡ��ǰ�������� */
LZH_API void lzh_transform_world_pos(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* ��ȡ��ǰ�������� */
LZH_API void lzh_transform_local_pos(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* ��ȡ�������������� z �����ת */
LZH_API float lzh_transform_world_angle_z(LZH_TRANSFORM *transform);

/* ��ȡ�ڱ����������� z �����ת */
LZH_API float lzh_transform_local_angle_z(LZH_TRANSFORM *transform);

/* ��ȡ�����������µ�����ϵ�� */
LZH_API void lzh_transform_world_scale(LZH_TRANSFORM *transform, float *sx, float *sy, float *sz);

/* ��ȡ�ڱ��������µ�����ϵ�� */
LZH_API void lzh_transform_local_scale(LZH_TRANSFORM *transform, float *sx, float *sy, float *sz);

/* ��ȡǰ���������� x �������� */
LZH_API void lzh_transform_get_forward(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* ��ȡ������������ x �Ḻ���� */
LZH_API void lzh_transform_get_backward(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* ��ȡ������������ y �������� */
LZH_API void lzh_transform_get_leftward(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* ��ȡ������������ y �Ḻ���� */
LZH_API void lzh_transform_get_rightward(LZH_TRANSFORM *transform, float *x, float *y, float *z);

/* �������ĵ� */
LZH_API void lzh_transform_set_center(LZH_TRANSFORM *transform, float x, float y, float z);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TRANSFORM_H__ */
