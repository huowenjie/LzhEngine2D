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

LZH_VEC3F lzh_quat4f_rotate(const LZH_QUAT4F *q, const LZH_VEC3F *v)
{
    LZH_QUAT4F r = lzh_quat4f_vec3f(v);
    LZH_QUAT4F c = lzh_quat4f_conjugate(q);

    if (!q || !v) {
        return lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    }

    /* v' = q * r * q' */
    r = lzh_quat4f_mul(q, &r);
    r = lzh_quat4f_mul(&r, &c);

    return lzh_vec3f_xyz(r.x, r.y, r.z);
}

LZH_QUAT4F lzh_quat4f_rotation(const LZH_VEC3F *u, float theta)
{
    LZH_VEC3F ru = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_QUAT4F q = lzh_quat4f_real(0.0f);
    float si = sinf(theta * 0.5f);
    float co = cosf(theta * 0.5f);

    if (!u) {
        return q;
    }

    ru = lzh_vec3f_normalize(u);
    q.s = co;
    q.x  = si * ru.x;
    q.y  = si * ru.y;
    q.z  = si * ru.z;
    return q;
}

float lzh_quat4f_get_theta(const LZH_QUAT4F *q)
{
    if (!q) {
        return 0.0f;
    }

    return 2.0f * acosf(q->s);
}

LZH_VEC3F lzh_quat4f_get_axis(const LZH_QUAT4F *q)
{
    float t = 0.0f;
    LZH_VEC3F u = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (!q) {
        return u;
    }

    t = sinf(acosf(q->s));

    if (fabsf(t) < 1e-6) {
        return u;
    }

    t = 1.0f / t;
    u.x = q->x * t;
    u.y = q->y * t;
    u.z = q->z * t;

    return u;
}

/*===========================================================================*/
