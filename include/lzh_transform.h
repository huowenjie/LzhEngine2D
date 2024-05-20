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

/* ����λ�� */
LZH_API void lzh_transform_set_pos(LZH_TRANSFORM *transform, float x, float y, float z);

/* ��ȡλ�� */
LZH_API void lzh_transform_get_pos(LZH_TRANSFORM *transform, float *x, float *y, float *z);

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

/* ������ z ����ת�Ƕ� */
LZH_API void lzh_transform_set_rotate_z(LZH_TRANSFORM *transform, float angle);

/* ������ x ����ת�Ƕ� */
LZH_API void lzh_transform_set_rotate_x(LZH_TRANSFORM *transform, float angle);

/* ������ y ����ת�Ƕ� */
LZH_API void lzh_transform_set_rotate_y(LZH_TRANSFORM *transform, float angle);

/* ��ȡ�� z ����ת�Ƕ� */
LZH_API float lzh_transform_get_rotate_z(LZH_TRANSFORM *transform);

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
