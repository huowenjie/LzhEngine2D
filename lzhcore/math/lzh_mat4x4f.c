#include <math.h>
#include "lzh_mat3x3f.h"
#include "lzh_mat4x4f.h"

/*===========================================================================*/

LZH_MAT4X4F lzh_mat4x4f_unit()
{
    LZH_MAT4X4F mat;

    mat.m00 = 1.0f;
    mat.m01 = 0.0f;
    mat.m02 = 0.0f;
    mat.m03 = 0.0f;
    mat.m10 = 0.0f;
    mat.m11 = 1.0f;
    mat.m12 = 0.0f;
    mat.m13 = 0.0f;
    mat.m20 = 0.0f;
    mat.m21 = 0.0f;
    mat.m22 = 1.0f;
    mat.m23 = 0.0f;
    mat.m30 = 0.0f;
    mat.m31 = 0.0f;
    mat.m32 = 0.0f;
    mat.m33 = 1.0f;
    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_zero()
{
    LZH_MAT4X4F mat;

    mat.m00 = 0.0f;
    mat.m01 = 0.0f;
    mat.m02 = 0.0f;
    mat.m03 = 0.0f;
    mat.m10 = 0.0f;
    mat.m11 = 0.0f;
    mat.m12 = 0.0f;
    mat.m13 = 0.0f;
    mat.m20 = 0.0f;
    mat.m21 = 0.0f;
    mat.m22 = 0.0f;
    mat.m23 = 0.0f;
    mat.m30 = 0.0f;
    mat.m31 = 0.0f;
    mat.m32 = 0.0f;
    mat.m33 = 0.0f;
    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_array(const float *elems)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_zero();

    if (elems) {
        mat.m00 = elems[0];
        mat.m01 = elems[1];
        mat.m02 = elems[2];
        mat.m03 = elems[3];
        mat.m10 = elems[4];
        mat.m11 = elems[5];
        mat.m12 = elems[6];
        mat.m13 = elems[7];
        mat.m20 = elems[8];
        mat.m21 = elems[9];
        mat.m22 = elems[10];
        mat.m23 = elems[11];
        mat.m30 = elems[12];
        mat.m31 = elems[13];
        mat.m32 = elems[14];
        mat.m33 = elems[15];
    }
    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_array2d(const float (*elems)[4])
{
    LZH_MAT4X4F mat = lzh_mat4x4f_zero();

    if (elems) {
        mat.m00 = elems[0][0];
        mat.m01 = elems[0][1];
        mat.m02 = elems[0][2];
        mat.m03 = elems[0][3];
        mat.m10 = elems[1][0];
        mat.m11 = elems[1][1];
        mat.m12 = elems[1][2];
        mat.m13 = elems[1][3];
        mat.m20 = elems[2][0];
        mat.m21 = elems[2][1];
        mat.m22 = elems[2][2];
        mat.m23 = elems[2][3];
        mat.m30 = elems[3][0];
        mat.m31 = elems[3][1];
        mat.m32 = elems[3][2];
        mat.m33 = elems[3][3];
    }
    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_scale(float sx, float sy, float sz)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    mat.m00 = sx;
    mat.m11 = sy;
    mat.m22 = sz;

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_rotate_z(float theta)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    mat.m00 =  cosf(theta);
    mat.m01 = -sinf(theta);
    mat.m10 =  sinf(theta);
    mat.m11 =  cosf(theta);

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_rotate_x(float theta)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    mat.m11 =  cosf(theta);
    mat.m12 = -sinf(theta);
    mat.m21 =  sinf(theta);
    mat.m22 =  cosf(theta);

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_rotate_y(float theta)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    mat.m00 =  cosf(theta);
    mat.m20 = -sinf(theta);
    mat.m02 =  sinf(theta);
    mat.m22 =  cosf(theta);

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_reflect(const LZH_VEC3F *n)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    if (n) {
        float ax = -2.0f * n->x;
        float ay = -2.0f * n->y;
        float az = -2.0f * n->z;

        mat.m00 = 1.0f + ax * n->x;
        mat.m11 = 1.0f + ay * n->y;
        mat.m22 = 1.0f + az * n->z;

        mat.m01 = mat.m10 = ax * n->y;
        mat.m02 = mat.m20 = ax * n->z;
        mat.m12 = mat.m21 = ay * n->z;
    }

    return mat;
}

float lzh_mat4x4f_rotate_z_theta(LZH_MAT4X4F *mat)
{
    if (mat) {
        return acosf(mat->m00);
    }
    return 0.0f;
}

float lzh_mat4x4f_rotate_x_theta(LZH_MAT4X4F *mat)
{
    if (mat) {
        return acosf(mat->m00);
    }
    return 0.0f;
}

float lzh_mat4x4f_rotate_y_theta(LZH_MAT4X4F *mat)
{
    if (mat) {
        return acosf(mat->m00);
    }
    return 0.0f;
}

LZH_MAT4X4F lzh_mat4x4f_translate(float dx, float dy, float dz)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    mat.m03 = dx;
    mat.m13 = dy;
    mat.m23 = dz;

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_get_scale(const LZH_MAT4X4F *mat)
{
    LZH_MAT4X4F scale = lzh_mat4x4f_unit();

    if (mat) {
        scale.m00 = sqrtf(
            powf(mat->m00, 2) +
            powf(mat->m01, 2) +
            powf(mat->m02, 2)
            );
        scale.m11 = sqrtf(
            powf(mat->m10, 2) +
            powf(mat->m11, 2) +
            powf(mat->m12, 2)
            );
        scale.m22 = sqrtf(
            powf(mat->m20, 2) +
            powf(mat->m21, 2) +
            powf(mat->m22, 2)
            );
    }

    return scale;
}

LZH_MAT4X4F lzh_mat4x4f_get_rotate(const LZH_MAT4X4F *mat)
{
    LZH_MAT4X4F rotate = lzh_mat4x4f_unit();

    if (mat) {
        LZH_MAT4X4F scale = lzh_mat4x4f_get_scale(mat);

        if (rotate.m00 != 0) {
            rotate.m00 = mat->m00 / scale.m00;
            rotate.m10 = mat->m10 / scale.m00;
            rotate.m20 = mat->m20 / scale.m00;
            rotate.m30 = mat->m30 / scale.m00;
        }

        if (rotate.m11 != 0) {
            rotate.m01 = mat->m01 / scale.m11;
            rotate.m11 = mat->m11 / scale.m11;
            rotate.m21 = mat->m21 / scale.m11;
            rotate.m31 = mat->m31 / scale.m11;
        }

        if (rotate.m22 != 0) {
            rotate.m02 = mat->m02 / scale.m22;
            rotate.m12 = mat->m12 / scale.m22;
            rotate.m22 = mat->m22 / scale.m22;
            rotate.m32 = mat->m32 / scale.m22;
        }
    }

    return rotate;
}

LZH_MAT4X4F lzh_mat4x4f_get_translate(const LZH_MAT4X4F *mat)
{
    LZH_MAT4X4F trans = lzh_mat4x4f_unit();

    if (mat) {
        trans.m03 = mat->m03;
        trans.m13 = mat->m13;
        trans.m23 = mat->m23;
    }

    return trans;
}

LZH_MAT4X4F lzh_mat4x4f_volume_map(
    const LZH_VEC3F *l,
    const LZH_VEC3F *h,
    const LZH_VEC3F *lp,
    const LZH_VEC3F *hp
)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    if (l && h && lp && hp) {
        mat.m00 = (hp->x - lp->x) / (h->x - l->x);
        mat.m11 = (hp->y - lp->y) / (h->y - l->y);
        mat.m22 = (hp->z - lp->z) / (h->z - l->z);
#if 1
        mat.m03 = (lp->x * h->x - hp->x * l->x) / (h->x - l->x);
        mat.m13 = (lp->y * h->y - hp->y * l->y) / (h->y - l->y);
        mat.m23 = (lp->z * h->z - hp->z * l->z) / (h->z - l->z);
#else
        mat.m03 = -(h->x + l->x) / (hp->x - lp->x);
        mat.m13 = -(h->y + l->y) / (hp->y - lp->y);
        mat.m23 = -(h->z + l->z) / (hp->z - lp->z);
#endif
    }

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_viewport(int width, int height)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();

    float nx = (float)width;
    float ny = (float)height;

    mat.m00 = nx / 2.0f;
    mat.m11 = ny / 2.0f;
    mat.m03 = (nx - 1.0f) / 2.0f;
    mat.m13 = (ny - 1.0f) / 2.0f;

    return mat;
}

LZH_MAT4X4F lzh_mat4x4f_camera(
    const LZH_VEC3F *pos,
    const LZH_VEC3F *up,
    const LZH_VEC3F *target)
{
    LZH_VEC3F z = { 0.0f, 1.0f, 0.0f };
    LZH_VEC3F u = { 0 };
    LZH_VEC3F v = { 0 };
    LZH_VEC3F w = { 0 };

    LZH_MAT4X4F cam = lzh_mat4x4f_unit();

    if (!pos || !target) {
        return cam;
    }

    if (up) {
        z = *up;
    }

    w = lzh_vec3f_sub(pos, target);
    w = lzh_vec3f_normalize(&w);

    u = lzh_vec3f_cross(&z, &w);
    u = lzh_vec3f_normalize(&u);

    v = lzh_vec3f_cross(&w, &u);
    v = lzh_vec3f_normalize(&v);

    cam.m00 = u.x;
    cam.m01 = u.y;
    cam.m02 = u.z;
    cam.m03 = -pos->x;

    cam.m10 = v.x;
    cam.m11 = v.y;
    cam.m12 = v.z;
    cam.m13 = -pos->y;

    cam.m20 = w.x;
    cam.m21 = w.y;
    cam.m22 = w.z;
    cam.m23 = -pos->z;

    return cam;
}

LZH_MAT4X4F lzh_mat4x4f_perspective(float fov, float aspect, float near, float far)
{
    LZH_MAT4X4F per = lzh_mat4x4f_zero();

    float thfov = tanf(fov / 2.0f);

    per.m00 = 1.0f / (aspect * thfov);
    per.m11 = 1.0f / thfov;
    per.m22 = -(near + far) / (far - near);
    per.m23 = -(2.0f * far * near) / (far - near);
    per.m32 = -1.0f;
    return per;
}

LZH_MAT4X4F lzh_mat4x4f_ortho(
    float left, float top, float right, float bottom, float near, float far)
{
    LZH_MAT4X4F ortho = lzh_mat4x4f_unit();

    ortho.m00 = 2.0f / (right - left);
    ortho.m11 = 2.0f / (top - bottom);
    ortho.m22 = -2.0f / (far - near);
    ortho.m23 = -(far + near) / (far - near);
    return ortho;
}

LZH_MAT4X4F lzh_mat4x4f_transpose(const LZH_MAT4X4F *mat)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();

    if (mat) {
        tmp = *mat;
        tmp.m01 = mat->m10;
        tmp.m10 = mat->m01;
        tmp.m02 = mat->m20;
        tmp.m20 = mat->m02;
        tmp.m03 = mat->m30;
        tmp.m30 = mat->m03;
        tmp.m12 = mat->m21;
        tmp.m21 = mat->m12;
        tmp.m13 = mat->m31;
        tmp.m31 = mat->m13;
        tmp.m23 = mat->m32;
        tmp.m32 = mat->m23;
    }
    return tmp;
}

LZH_MAT4X4F lzh_mat4x4f_inverse(const LZH_MAT4X4F *mat)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();
    LZH_MAT4X4F adj = lzh_mat4x4f_zero();
    float det = 0.0f;

    if (!mat) {
        return tmp;
    }

    /* 求行列式 */
    det = lzh_mat4x4f_determinant(mat);

    /* 行列式为 0，不可逆，直接返回原矩阵 */
    if (det == 0.0f || fabsf(det) < 1e-6f) {
        return *mat;
    }

    /*
     * 利用克拉默法则来求解逆矩阵
     * inverse A = adj A / det A
     * [ +c00, -c10, +c20, -c30 ]
     * [ -c01, +c11, -c21, +c31 ]
     * [ +c02, -c12, +c22, -c32 ]
     * [ -c03, +c13, -c23, +c33 ]
     */
    /* c00 */
    tmp.m00 = mat->m11; tmp.m01 = mat->m12; tmp.m02 = mat->m13;
    tmp.m10 = mat->m21; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
    tmp.m20 = mat->m31; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m00 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c10 */
    tmp.m00 = mat->m01; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m21; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
    tmp.m20 = mat->m31; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m01 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c20 */
    tmp.m00 = mat->m01; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m11; tmp.m11 = mat->m12; tmp.m12 = mat->m13;
    tmp.m20 = mat->m31; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m02 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c30 */
    tmp.m00 = mat->m01; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m11; tmp.m11 = mat->m12; tmp.m12 = mat->m13;
    tmp.m20 = mat->m21; tmp.m21 = mat->m22; tmp.m22 = mat->m23;
    adj.m03 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c01 */
    tmp.m00 = mat->m10; tmp.m01 = mat->m12; tmp.m02 = mat->m13;
    tmp.m10 = mat->m20; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
    tmp.m20 = mat->m30; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m10 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c11 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m20; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
    tmp.m20 = mat->m30; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m11 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c21 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m10; tmp.m11 = mat->m12; tmp.m12 = mat->m13;
    tmp.m20 = mat->m30; tmp.m21 = mat->m32; tmp.m22 = mat->m33;
    adj.m12 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c31 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m02; tmp.m02 = mat->m03;
    tmp.m10 = mat->m10; tmp.m11 = mat->m12; tmp.m12 = mat->m13;
    tmp.m20 = mat->m20; tmp.m21 = mat->m22; tmp.m22 = mat->m23;
    adj.m13 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c02 */
    tmp.m00 = mat->m10; tmp.m01 = mat->m11; tmp.m02 = mat->m13;
    tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m23;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m33;
    adj.m20 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c12 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m03;
    tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m23;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m33;
    adj.m21 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c22 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m03;
    tmp.m10 = mat->m10; tmp.m11 = mat->m11; tmp.m12 = mat->m13;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m33;
    adj.m22 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c32 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m03;
    tmp.m10 = mat->m10; tmp.m11 = mat->m11; tmp.m12 = mat->m13;
    tmp.m20 = mat->m20; tmp.m21 = mat->m21; tmp.m22 = mat->m23;
    adj.m23 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c03 */
    tmp.m00 = mat->m10; tmp.m01 = mat->m11; tmp.m02 = mat->m12;
    tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m22;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m32;
    adj.m30 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c13 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m02;
    tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m22;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m32;
    adj.m31 = lzh_mat4x4f_determinant(&tmp) / det;

    /* c23 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m02;
    tmp.m10 = mat->m10; tmp.m11 = mat->m11; tmp.m12 = mat->m12;
    tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m32;
    adj.m32 = -(lzh_mat4x4f_determinant(&tmp)) / det;

    /* c33 */
    tmp.m00 = mat->m00; tmp.m01 = mat->m01; tmp.m02 = mat->m02;
    tmp.m10 = mat->m10; tmp.m11 = mat->m11; tmp.m12 = mat->m12;
    tmp.m20 = mat->m20; tmp.m21 = mat->m21; tmp.m22 = mat->m22;
    adj.m33 = lzh_mat4x4f_determinant(&tmp) / det;

    return adj;
}

float lzh_mat4x4f_determinant(const LZH_MAT4X4F *mat)
{
    float det = 0.0f;
    LZH_MAT3X3F tmp = lzh_mat3x3f_unit();

    if (mat) {
        tmp.m00 = mat->m11; tmp.m01 = mat->m12; tmp.m02 = mat->m13;
        tmp.m10 = mat->m21; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
        tmp.m20 = mat->m31; tmp.m21 = mat->m32; tmp.m22 = mat->m33;

        det = mat->m00 * lzh_mat3x3f_determinant(&tmp);

        tmp.m00 = mat->m10; tmp.m01 = mat->m12; tmp.m02 = mat->m13;
        tmp.m10 = mat->m20; tmp.m11 = mat->m22; tmp.m12 = mat->m23;
        tmp.m20 = mat->m30; tmp.m21 = mat->m32; tmp.m22 = mat->m33;

        det -= mat->m01 * lzh_mat3x3f_determinant(&tmp);

        tmp.m00 = mat->m10; tmp.m01 = mat->m11; tmp.m02 = mat->m13;
        tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m23;
        tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m33;

        det += mat->m02 * lzh_mat3x3f_determinant(&tmp);

        tmp.m00 = mat->m10; tmp.m01 = mat->m11; tmp.m02 = mat->m12;
        tmp.m10 = mat->m20; tmp.m11 = mat->m21; tmp.m12 = mat->m22;
        tmp.m20 = mat->m30; tmp.m21 = mat->m31; tmp.m22 = mat->m32;

        det -= mat->m03 * lzh_mat3x3f_determinant(&tmp);
    }
    return det;
}

LZH_MAT4X4F lzh_mat4x4f_add(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();

    if (a && b) {
        tmp.m00 = a->m00 + b->m00;
        tmp.m01 = a->m01 + b->m01;
        tmp.m02 = a->m02 + b->m02;
        tmp.m03 = a->m03 + b->m03;
        tmp.m10 = a->m10 + b->m10;
        tmp.m11 = a->m11 + b->m11;
        tmp.m12 = a->m12 + b->m12;
        tmp.m13 = a->m13 + b->m13;
        tmp.m20 = a->m20 + b->m20;
        tmp.m21 = a->m21 + b->m21;
        tmp.m22 = a->m22 + b->m22;
        tmp.m23 = a->m23 + b->m23;
        tmp.m30 = a->m30 + b->m30;
        tmp.m31 = a->m31 + b->m31;
        tmp.m32 = a->m32 + b->m32;
        tmp.m33 = a->m33 + b->m33;
    }
    return tmp;
}

LZH_MAT4X4F lzh_mat4x4f_sub(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();

    if (a && b) {
        tmp.m00 = a->m00 - b->m00;
        tmp.m01 = a->m01 - b->m01;
        tmp.m02 = a->m02 - b->m02;
        tmp.m03 = a->m03 - b->m03;
        tmp.m10 = a->m10 - b->m10;
        tmp.m11 = a->m11 - b->m11;
        tmp.m12 = a->m12 - b->m12;
        tmp.m13 = a->m13 - b->m13;
        tmp.m20 = a->m20 - b->m20;
        tmp.m21 = a->m21 - b->m21;
        tmp.m22 = a->m22 - b->m22;
        tmp.m23 = a->m23 - b->m23;
        tmp.m30 = a->m30 - b->m30;
        tmp.m31 = a->m31 - b->m31;
        tmp.m32 = a->m32 - b->m32;
        tmp.m33 = a->m33 - b->m33;
    }
    return tmp;
}

LZH_MAT4X4F lzh_mat4x4f_mul(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();

    if (a && b) {
        tmp.m00 = a->m00 * b->m00 + a->m01 * b->m10 + a->m02 * b->m20 + a->m03 * b->m30;
        tmp.m01 = a->m00 * b->m01 + a->m01 * b->m11 + a->m02 * b->m21 + a->m03 * b->m31;
        tmp.m02 = a->m00 * b->m02 + a->m01 * b->m12 + a->m02 * b->m22 + a->m03 * b->m32;
        tmp.m03 = a->m00 * b->m03 + a->m01 * b->m13 + a->m02 * b->m23 + a->m03 * b->m33;

        tmp.m10 = a->m10 * b->m00 + a->m11 * b->m10 + a->m12 * b->m20 + a->m13 * b->m30;
        tmp.m11 = a->m10 * b->m01 + a->m11 * b->m11 + a->m12 * b->m21 + a->m13 * b->m31;
        tmp.m12 = a->m10 * b->m02 + a->m11 * b->m12 + a->m12 * b->m22 + a->m13 * b->m32;
        tmp.m13 = a->m10 * b->m03 + a->m11 * b->m13 + a->m12 * b->m23 + a->m13 * b->m33;

        tmp.m20 = a->m20 * b->m00 + a->m21 * b->m10 + a->m22 * b->m20 + a->m23 * b->m30;
        tmp.m21 = a->m20 * b->m01 + a->m21 * b->m11 + a->m22 * b->m21 + a->m23 * b->m31;
        tmp.m22 = a->m20 * b->m02 + a->m21 * b->m12 + a->m22 * b->m22 + a->m23 * b->m32;
        tmp.m23 = a->m20 * b->m03 + a->m21 * b->m13 + a->m22 * b->m23 + a->m23 * b->m33;

        tmp.m30 = a->m30 * b->m00 + a->m31 * b->m10 + a->m32 * b->m20 + a->m33 * b->m30;
        tmp.m31 = a->m30 * b->m01 + a->m31 * b->m11 + a->m32 * b->m21 + a->m33 * b->m31;
        tmp.m32 = a->m30 * b->m02 + a->m31 * b->m12 + a->m32 * b->m22 + a->m33 * b->m32;
        tmp.m33 = a->m30 * b->m03 + a->m31 * b->m13 + a->m32 * b->m23 + a->m33 * b->m33;
    }
    return tmp;
}

LZH_MAT4X4F lzh_mat4x4f_mul_real(const LZH_MAT4X4F *a, float b)
{
    LZH_MAT4X4F tmp = lzh_mat4x4f_zero();

    if (a) {
        tmp.m00 = a->m00 * b;
        tmp.m01 = a->m01 * b;
        tmp.m02 = a->m02 * b;
        tmp.m03 = a->m03 * b;
        tmp.m10 = a->m10 * b;
        tmp.m11 = a->m11 * b;
        tmp.m12 = a->m12 * b;
        tmp.m13 = a->m13 * b;
        tmp.m20 = a->m20 * b;
        tmp.m21 = a->m21 * b;
        tmp.m22 = a->m22 * b;
        tmp.m23 = a->m23 * b;
        tmp.m30 = a->m30 * b;
        tmp.m31 = a->m31 * b;
        tmp.m32 = a->m32 * b;
        tmp.m33 = a->m33 * b;
    }
    return tmp;
}

LZH_VEC4F lzh_mat4x4f_mul_vec(const LZH_MAT4X4F *a, const LZH_VEC4F *b)
{
    LZH_VEC4F tmp = { 0 };

    if (a && b) {
        tmp.x = a->m00 * b->x + a->m01 * b->y + a->m02 * b->z + a->m03 * b->w;
        tmp.y = a->m10 * b->x + a->m11 * b->y + a->m12 * b->z + a->m13 * b->w;
        tmp.z = a->m20 * b->x + a->m21 * b->y + a->m22 * b->z + a->m23 * b->w;
        tmp.w = a->m30 * b->x + a->m31 * b->y + a->m32 * b->z + a->m33 * b->w;
    }
    return tmp;
}

/*===========================================================================*/
