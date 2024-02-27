#include <math.h>
#include "lzh_mat2x2f.h"

/*===========================================================================*/

LZH_MAT2X2F lzh_mat2x2f_unit()
{
    LZH_MAT2X2F mat;
    
    mat.m00 = 1.0f;
    mat.m01 = 0.0f;
    mat.m10 = 0.0f;
    mat.m11 = 1.0f;
    return mat;
}

LZH_MAT2X2F lzh_mat2x2f_zero()
{
    LZH_MAT2X2F mat;

    mat.m00 = 0.0f;
    mat.m01 = 0.0f;
    mat.m10 = 0.0f;
    mat.m11 = 0.0f;
    return mat;
}

LZH_MAT2X2F lzh_mat2x2f_rotate(float theta)
{
    LZH_MAT2X2F mat;

    mat.m00 = cosf(theta);
    mat.m01 = -sinf(theta);
    mat.m10 = sinf(theta);
    mat.m11 = cosf(theta);
    return mat;
}

LZH_MAT2X2F lzh_mat2x2f_array(const float *elems)
{
    LZH_MAT2X2F mat = lzh_mat2x2f_zero();

    if (elems) {
        mat.m00 = elems[0];
        mat.m01 = elems[1];
        mat.m10 = elems[2];
        mat.m11 = elems[3];
    }
    return mat;
}

LZH_MAT2X2F lzh_mat2x2f_array2d(const float (*elems)[2])
{
    LZH_MAT2X2F mat = lzh_mat2x2f_zero();

    if (elems) {
        mat.m00 = elems[0][0];
        mat.m01 = elems[0][1];
        mat.m10 = elems[1][0];
        mat.m11 = elems[1][1];
    }
    return mat;
}

LZH_MAT2X2F lzh_mat2x2f_transpose(const LZH_MAT2X2F *mat)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();

    if (mat) {
        tmp = *mat;
        tmp.m01 = mat->m10;
        tmp.m10 = mat->m01;
    }

    return tmp;
}

LZH_MAT2X2F lzh_mat2x2f_inverse(const LZH_MAT2X2F *mat)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();
    float det = 0.0f;

    if (!mat) {
        return tmp;
    }

    /* 求行列式 */
    det = lzh_mat2x2f_determinant(mat);

    /* 行列式为 0，不可逆，直接返回原矩阵 */
    if (det == 0.0f || fabsf(det) < 1e-6f) {
        return *mat;
    }

    tmp.m00 =  mat->m11;
    tmp.m01 = -mat->m01;
    tmp.m10 = -mat->m10;
    tmp.m11 =  mat->m00;

    det = 1.0f / det;
    tmp = lzh_mat2x2f_mul_real(&tmp, det);
    return tmp;
}

float lzh_mat2x2f_determinant(const LZH_MAT2X2F *mat)
{
    float det = 0.0f;

    if (mat) {
        det = mat->m00 * mat->m11 - mat->m01 * mat->m10;
    }
    return det;
}

LZH_MAT2X2F lzh_mat2x2f_add(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();

    if (a && b) {
        tmp.m00 = a->m00 + b->m00;
        tmp.m01 = a->m01 + b->m01;
        tmp.m10 = a->m10 + b->m10;
        tmp.m11 = a->m11 + b->m11;
    }

    return tmp;
}

LZH_MAT2X2F lzh_mat2x2f_sub(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();

    if (a && b) {
        tmp.m00 = a->m00 - b->m00;
        tmp.m01 = a->m01 - b->m01;
        tmp.m10 = a->m10 - b->m10;
        tmp.m11 = a->m11 - b->m11;
    }

    return tmp;
}

LZH_MAT2X2F lzh_mat2x2f_mul(const LZH_MAT2X2F *a, const LZH_MAT2X2F *b)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();

    if (a && b) {
        tmp.m00 = a->m00 * b->m00 + a->m01 * b->m10;
        tmp.m01 = a->m00 * b->m01 + a->m01 * b->m11;
        tmp.m10 = a->m10 * b->m00 + a->m11 * b->m10;
        tmp.m11 = a->m10 * b->m01 + a->m11 * b->m11;
    }

    return tmp;
}

LZH_MAT2X2F lzh_mat2x2f_mul_real(const LZH_MAT2X2F *a, float b)
{
    LZH_MAT2X2F tmp = lzh_mat2x2f_zero();

    if (a) {
        tmp.m00 = a->m00 * b;
        tmp.m01 = a->m01 * b;
        tmp.m10 = a->m10 * b;
        tmp.m11 = a->m11 * b;
    }

    return tmp;
}

LZH_VEC2F lzh_mat2x2f_mul_vec(const LZH_MAT2X2F *a, const LZH_VEC2F *b)
{
    LZH_VEC2F tmp = { 0 };

    if (a && b) {
        tmp.x = a->m00 * b->x + a->m01 * b->y;
        tmp.y = a->m10 * b->x + a->m11 * b->y;
    }

    return tmp;
}

/*===========================================================================*/
