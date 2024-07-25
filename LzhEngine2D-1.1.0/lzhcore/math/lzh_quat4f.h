#ifndef __LZH_QUAT4F_H__
#define __LZH_QUAT4F_H__

#include "lzh_vec3f.h"
#include "lzh_mat3x3f.h"
#include "lzh_mat4x4f.h"

/*===========================================================================*/
/* ��Ԫ�� */
/*===========================================================================*/

typedef struct {
    /**
     * [ s, v ]
     * [ s, x, y, z ]
     */
    float s;

    union {
        LZH_VEC3F v;
        struct {
            float x;
            float y;
            float z;
        };
    };
} LZH_QUAT4F;

/* ��ʼ��ʵ�� */
LZH_QUAT4F lzh_quat4f_real(float s);

/* ��ʼ������Ԫ�� */
LZH_QUAT4F lzh_quat4f_pure(float x, float y, float z);

/* ��ʼ������Ԫ�� */
LZH_QUAT4F lzh_quat4f_vec3f(const LZH_VEC3F *v);

/* ��ʼ����Ԫ�� */
LZH_QUAT4F lzh_quat4f_sxyz(float s, float x, float y, float z);

/* ��ʼ����Ԫ�� */
LZH_QUAT4F lzh_quat4f_sv(float s, const LZH_VEC3F *v);

/* ��ȡ��Ԫ���Ĺ��� */
LZH_QUAT4F lzh_quat4f_conjugate(const LZH_QUAT4F *q);

/* ����Ԫ����ģ�� */
float lzh_quat4f_norm(const LZH_QUAT4F *q);

/* ��Ԫ����һ�� */
LZH_QUAT4F lzh_quat4f_normalize(const LZH_QUAT4F *q);

/* ��Ԫ���ļӷ� a + b */
LZH_QUAT4F lzh_quat4f_add(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* ��Ԫ���ļ��� a - b */
LZH_QUAT4F lzh_quat4f_sub(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* ������ q * t */
LZH_QUAT4F lzh_quat4f_mul_scalar(const LZH_QUAT4F *q, float t);

/* ������ q / t */
LZH_QUAT4F lzh_quat4f_div_scalar(const LZH_QUAT4F *q, float t);

/* ��Ԫ���˷� a * b */
LZH_QUAT4F lzh_quat4f_mul(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* ��Ԫ������ */
LZH_QUAT4F lzh_quat4f_inverse(const LZH_QUAT4F *q);

/* ��Ԫ����ת���� v' = qvq*����Ԫ�� q ���뱣֤�ǵ�λ��Ԫ�� */
LZH_VEC3F lzh_quat4f_rotate(const LZH_QUAT4F *q, const LZH_VEC3F *v);

/* ����һ������ת�� u ��ת theta �Ƕȣ���λ�����ȣ�����ת */
LZH_QUAT4F lzh_quat4f_rotation(const LZH_VEC3F *u, float theta);

/* ����ת��Ԫ���л�ȡŷ���� yaw */
float lzh_quat4f_get_theta_z(const LZH_QUAT4F *q);

/* ����ת��Ԫ���л�ȡŷ���� pitch */
float lzh_quat4f_get_theta_y(const LZH_QUAT4F *q);

/* ����ת��Ԫ���л�ȡŷ���� roll */
float lzh_quat4f_get_theta_x(const LZH_QUAT4F *q);

/* ŷ����ת��Ϊ��Ԫ�� */
LZH_QUAT4F lzh_quat4f_euler2quat(float yaw, float pitch, float roll);

/* ����ת��Ԫ����ȡ��ת�� */
LZH_VEC3F lzh_quat4f_get_axis(const LZH_QUAT4F *q);

/* ����ת��Ԫ����ȡ 3x3 ��ת���� */
LZH_MAT3X3F lzh_quat4f_get_mat3x3f(const LZH_QUAT4F *q);

/* ����ת��Ԫ����ȡ 3x3 �����ת���� */
LZH_MAT4X4F lzh_quat4f_get_mat4x4f(const LZH_QUAT4F *q);

/* ��Ԫ�����Բ�ֵ */
LZH_QUAT4F lzh_quat4f_lerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/* ��Ԫ����һ�����Բ�ֵ */
LZH_QUAT4F lzh_quat4f_nlerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/* ��������ת��Ԫ��֮��ļнǣ���λ�����ȣ� */
float lzh_quat4f_angle(const LZH_QUAT4F *a, const LZH_QUAT4F *b);

/* ��Ԫ���������Բ�ֵ */
LZH_QUAT4F lzh_quat4f_slerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/*===========================================================================*/

#endif /* __LZH_QUAT4F_H__ */
