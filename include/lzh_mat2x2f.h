#ifndef __LZH_MAT2X2F_H__
#define __LZH_MAT2X2F_H__

#include "lzh_vec2f.h"

/*===========================================================================*/
/* 2x2 ����������洢 */
/*===========================================================================*/

typedef union {
    struct {
        float m00;
        float m01;
        float m10;
        float m11;
    };

    float mat[4];
    float matij[2][2];
} LZH_MAT2X2F;

/* ������λ���� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_unit();

/* ��������� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_zero();

/* ��ת���� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_rotate(float theta);

/* �������� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_array(const float *elems);

/* �������� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_array2d(const float (*elems)[2]);

/* ת�þ��� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_transpose(const LZH_MAT2X2F *mat);

/* ����� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_inverse(const LZH_MAT2X2F *mat);

/* 2 x 2 ����ʽֵ */
LZH_API float lzh_mat2x2f_determinant(const LZH_MAT2X2F *mat); 

/* ����� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_add(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b);

/* ����� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_sub(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b);

/* ����� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_mul(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b);

/* ����ͱ����� */
LZH_API LZH_MAT2X2F lzh_mat2x2f_mul_real(const LZH_MAT2X2F *a, float b);

/* ����������� */
LZH_API LZH_VEC2F lzh_mat2x2f_mul_vec(const LZH_MAT2X2F *a, const LZH_VEC2F *b);

/*===========================================================================*/

#endif /* __LZH_MAT2X2F_H__ */
