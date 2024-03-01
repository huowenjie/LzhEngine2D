#ifndef __LZH_MAT3X3F_H__
#define __LZH_MAT3X3F_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* 3x3 方阵，行主序存储 */
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

/* 构建单位矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_unit();

/* 构建零矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_zero();

/* 构建矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_array(const float *elems);

/* 构建矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_array2d(const float (*elems)[3]);

/* 转置矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_transpose(const LZH_MAT3X3F *mat);

/* 逆矩阵 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_inverse(const LZH_MAT3X3F *mat);

/* 3 x 3 行列式值 */
LZH_API float lzh_mat3x3f_determinant(const LZH_MAT3X3F *mat); 

/* 矩阵加 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_add(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* 矩阵减 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_sub(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* 矩阵乘 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_mul(const LZH_MAT3X3F *a, const LZH_MAT3X3F *b);

/* 矩阵和标量乘 */
LZH_API LZH_MAT3X3F lzh_mat3x3f_mul_real(const LZH_MAT3X3F *a, float b);

/* 矩阵和向量乘 */
LZH_API LZH_VEC3F lzh_mat3x3f_mul_vec(const LZH_MAT3X3F *a, const LZH_VEC3F *b);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_MAT3X3F_H__ */
