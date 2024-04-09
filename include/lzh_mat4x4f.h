#ifndef __LZH_MAT4X4F_H__
#define __LZH_MAT4X4F_H__

#include "lzh_vec4f.h"

/*===========================================================================*/
/* 4x4 ����������洢 */
/*===========================================================================*/

typedef union {
    /**
     * [ m00, m01, m02, m03 ]
     * [ m10, m11, m12, m13 ]
     * [ m20, m21, m22, m23 ]
     * [ m30, m31, m32, m33 ]
     */
    struct {
        float m00;
        float m01;
        float m02;
        float m03;
        float m10;
        float m11;
        float m12;
        float m13;
        float m20;
        float m21;
        float m22;
        float m23;
        float m30;
        float m31;
        float m32;
        float m33;
    };

    float mat[16];
    float matij[4][4];
} LZH_MAT4X4F;

/* ������λ���� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_unit();

/* ��������� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_zero();

/* �������� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_array(const float *elems);

/* �������� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_array2d(const float (*elems)[4]);

/* �������ž��� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_scale(float sx, float sy, float sz);

/* ������ת���� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_z(float theta);

/* ������ת���� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_x(float theta);

/* ������ת���� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_y(float theta);

/* ����������� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_reflect(const LZH_VEC3F *n);

/* ��ȡ�� z ����������ת�Ƕ� */
LZH_API float lzh_mat4x4f_rotate_z_theta(LZH_MAT4X4F *mat);

/* ��ȡ�� x ����������ת�Ƕ� */
LZH_API float lzh_mat4x4f_rotate_x_theta(LZH_MAT4X4F *mat);

/* ��ȡ�� y ����������ת�Ƕ� */
LZH_API float lzh_mat4x4f_rotate_y_theta(LZH_MAT4X4F *mat);

/* ����ƽ�ƾ��� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_translate(float dx, float dy, float dz);

/* �ӷ��������ȡ���ž��� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_scale(const LZH_MAT4X4F *mat);

/* �ӷ��������ȡ��ת���� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_rotate(const LZH_MAT4X4F *mat);

/* �ӷ��������ȡƽ�ƾ��� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_translate(const LZH_MAT4X4F *mat);

/**
 * �����ͶӰ����
 * �� [xl, xh] x [yl, yh] x [zl, zh] ͶӰ�� [xpl, xph] x [ypl, yph] x [zpl, zph]
 * 
 * l �� h �����˴��任���ڵİ�Χ��
 * lp �� hp ������Ŀ�괰�ڵİ�Χ��
 * 
 * l ��ֵΪ xmin ymin zmin
 * h ��ֵΪ xmax ymax zmax
 * 
 * lp �� hp ͬ��
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_volume_map(
    const LZH_VEC3F *l,
    const LZH_VEC3F *h,
    const LZH_VEC3F *lp,
    const LZH_VEC3F *hp
);

/**
 * ����׼������ͶӰ����Ļ�ռ�-�ӿڱ任����
 * 
 * width ��Ļ��ȣ����أ�
 * height ��Ļ�߶ȣ����أ�
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_viewport(int width, int height);

/**
 * ������Ӿ��任����
 * 
 * pos �����λ��
 * target Ŀ��λ��
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_camera(const LZH_VEC3F *pos, const LZH_VEC3F *target);

/**
 * ͸��ͶӰ����
 * 
 * ������� [xl, xh] x [yl, yh] x [zl, zh] �е�����
 * ����͸�ӱ任��ͬʱͶӰ���淶������ϵͳ [-1, 1] ��
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_perspective(const LZH_VEC3F *l, const LZH_VEC3F *h);

/* ת�þ��� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_transpose(const LZH_MAT4X4F *mat);

/* ����� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_inverse(const LZH_MAT4X4F *mat);

/* 4 x 4 ����ʽֵ */
LZH_API float lzh_mat4x4f_determinant(const LZH_MAT4X4F *mat); 

/* ����� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_add(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* ����� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_sub(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* ����� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_mul(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* ����ͱ����� */
LZH_API LZH_MAT4X4F lzh_mat4x4f_mul_real(const LZH_MAT4X4F *a, float b);

/* ����������� */
LZH_API LZH_VEC4F lzh_mat4x4f_mul_vec(const LZH_MAT4X4F *a, const LZH_VEC4F *b);

/*===========================================================================*/

#endif /* __LZH_MAT4X4F_H__ */
