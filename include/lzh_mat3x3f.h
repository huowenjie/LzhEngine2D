#ifndef __LZH_MAT3X3F_H__
#define __LZH_MAT3X3F_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* 3x3 ����������洢 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    /**
     * [ m00, m01, m02 ]
     * [ m10, m11, m12 ]
     * [ m20, m21, m22 ]
     */
    struct {
        float m00;
        float m01;
        float m02;
        float m10;
        float m11;
        float m12;
        float m20;
        float m21;
        float m22;
    };

    float mat[9];
    float matij[3][3];
} LZH_MAT3X3F;

/* ������λ���� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_unit();

/* ��������� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_zero();

/* �������� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_array(const float *elems);

/* �������� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_array2d(const float (*elems)[3]);

/* ת�þ��� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_transpose(const LZH_MAT3X3F *mat);

/* ����� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_inverse(const LZH_MAT3X3F *mat);

/* 3 x 3 ����ʽֵ */
LZH_API float lzh_mat3x3f_determinant(const LZH_MAT3X3F *mat); 

/* ����� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_add(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* ����� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_sub(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* ����� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_mul(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* ����ͱ����� */
LZH_API LZH_MAT3X3F lzh_mat3x3f_mul_real(const LZH_MAT3X3F *a, float b);

/* ����������� */
LZH_API LZH_VEC3F lzh_mat3x3f_mul_vec(const LZH_MAT3X3F *a, const LZH_VEC3F *b);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_MAT3X3F_H__ */
