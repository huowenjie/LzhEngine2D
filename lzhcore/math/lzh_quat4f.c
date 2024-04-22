#include <math.h>
#include "lzh_quat4f.h"

/*===========================================================================*/

LZH_QUAT4F lzh_quat4f_real(float s)
{
    LZH_QUAT4F quat;

    quat.s = s;
    quat.x = 0.0f;
    quat.y = 0.0f;
    quat.z = 0.0f;
    return quat;
}

LZH_QUAT4F lzh_quat4f_pure(float x, float y, float z)
{
    LZH_QUAT4F quat;

    quat.s = 0.0f;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    return quat;
}

LZH_QUAT4F lzh_quat4f_vec3f(const LZH_VEC3F *v)
{
    LZH_QUAT4F quat = lzh_quat4f_pure(0.0f, 0.0f, 0.0f);

    quat.s = 0.0f;    
    if (v) {
        quat.v = *v;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_sxyz(float s, float x, float y, float z)
{
    LZH_QUAT4F quat;

    quat.s = s;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    return quat;
}

LZH_QUAT4F lzh_quat4f_sv(float s, const LZH_VEC3F *v)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    quat.s = s;
    if (v) {
        quat.v = *v;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_conjugate(const LZH_QUAT4F *q)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (q) {
        quat.s =  q->s;
        quat.x = -q->x;
        quat.y = -q->y;
        quat.z = -q->z;
    }
    return quat;
}

float lzh_quat4f_norm(const LZH_QUAT4F *q)
{
    float norm = 0.0f;

    if (q) {
        float s = q->s;
        float x = q->x;
        float y = q->y;
        float z = q->z;
        norm = sqrtf(s * s + x * x + y * y + z * z);
    }
    return norm;
}

LZH_QUAT4F lzh_quat4f_mul_scalar(const LZH_QUAT4F *q, float t)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (q) {
        quat.s = q->s * t;
        quat.x = q->x * t;
        quat.y = q->y * t;
        quat.z = q->z * t;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_div_scalar(const LZH_QUAT4F *q, float t)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (q && fabsf(t) > 1e-6) {
        float scalar = 1.0f / t;

        quat.s = q->s * t;
        quat.x = q->x * t;
        quat.y = q->y * t;
        quat.z = q->z * t;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_mul(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (qa && qb) {
        float a = qa->s;
        float b = qa->x;
        float c = qa->y;
        float d = qa->z;

        float e = qa->s;
        float f = qa->x;
        float g = qa->y;
        float h = qa->z;

        quat.s = a * e - b * f - c * g - d * h;
        quat.x = b * e + a * f - d * g + c * h;
        quat.y = c * e + d * f + a * g - b * h;
        quat.z = d * e - c * f + b * g + a * h;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_inverse(const LZH_QUAT4F *q)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (q) {
        LZH_QUAT4F conj = lzh_quat4f_conjugate(q);
        float norm = lzh_quat4f_norm(q);

        /* 共轭除以模长的平方 */
        quat = lzh_quat4f_div_scalar(&conj, norm * norm);
    }
    return quat;
}

/*===========================================================================*/
