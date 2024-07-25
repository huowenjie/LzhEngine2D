#include <math.h>
#include "lzh_mathdef.h"
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

LZH_QUAT4F lzh_quat4f_normalize(const LZH_QUAT4F *q)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (q) {
        float norm = lzh_quat4f_norm(q);

        if (fabsf(norm) < 1e-6f) {
            return quat;
        }

        quat = lzh_quat4f_div_scalar(q, norm);
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_add(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (qa && qb) {
        quat.s = qa->s + qb->s;
        quat.x = qa->x + qb->x;
        quat.y = qa->y + qb->y;
        quat.z = qa->z + qb->z;
    }
    return quat;
}

LZH_QUAT4F lzh_quat4f_sub(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    if (qa && qb) {
        quat.s = qa->s - qb->s;
        quat.x = qa->x - qb->x;
        quat.y = qa->y - qb->y;
        quat.z = qa->z - qb->z;
    }
    return quat;
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

        quat.s = q->s * scalar;
        quat.x = q->x * scalar;
        quat.y = q->y * scalar;
        quat.z = q->z * scalar;
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

        float e = qb->s;
        float f = qb->x;
        float g = qb->y;
        float h = qb->z;

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

float lzh_quat4f_get_theta_z(const LZH_QUAT4F *q)
{
    if (q) {
        float s = 2.0f * (q->s * q->z + q->x * q->y);
        float c = 1.0f - 2.0f * (q->y * q->y + q->z * q->z);
        return atan2f(s, c);
    }
    return 0.0f;
}

float lzh_quat4f_get_theta_y(const LZH_QUAT4F *q)
{
    if (q) {
        float s = 2.0f * (q->s * q->y - q->z * q->x);
        if (fabsf(s) >= 1.0f) {
            return copysignf(LZH_PI / 2.0f, s);
        } else {
            return asinf(s);
        }
    }
    return 0.0f;
}
float lzh_quat4f_get_theta_x(const LZH_QUAT4F *q)
{
    if (q) {
        float s = 2.0f * (q->s * q->x + q->y * q->z);
        float c = 1.0f - 2.0f * (q->x * q->x + q->y * q->y);
        return atan2f(s, c);
    }
    return 0.0f;    
}

LZH_QUAT4F lzh_quat4f_euler2quat(float yaw, float pitch, float roll)
{
    LZH_QUAT4F quat = lzh_quat4f_real(0.0f);

    float cy = cosf(yaw * 0.5f);
    float sy = sinf(yaw * 0.5f);
    float cp = cosf(pitch * 0.5f);
    float sp = sinf(pitch * 0.5f);
    float cr = cosf(roll * 0.5f);
    float sr = sinf(roll * 0.5f);
 
    quat.s = cy * cp * cr + sy * sp * sr;
    quat.x = cy * cp * sr - sy * sp * cr;
    quat.y = sy * cp * sr + cy * sp * cr;
    quat.z = sy * cp * cr - cy * sp * sr;

    return quat;
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

LZH_MAT3X3F lzh_quat4f_get_mat3x3f(const LZH_QUAT4F *q)
{
    LZH_MAT3X3F mat = lzh_mat3x3f_unit();
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;
    float d = 0.0f;

    if (!q) {
        return mat;
    }

    a = q->s;
    b = q->x;
    c = q->y;
    d = q->z;

    mat.m00 = 1.0f - 2.0f * (c * c + d * d);
    mat.m01 = 2.0f * (b * c - a * d);
    mat.m02 = 2.0f * (a * c + b * d);

    mat.m10 = 2.0f * (b * c + a * d);
    mat.m11 = 1.0f - 2.0f * (b * b + d * d);
    mat.m12 = 2.0f * (c * d - a * b);

    mat.m20 = 2.0f * (b * d - a * c);
    mat.m21 = 2.0f * (a * b + c * d);
    mat.m22 = 1.0f - 2.0f * (b * b + c * c);

    return mat;
}

LZH_MAT4X4F lzh_quat4f_get_mat4x4f(const LZH_QUAT4F *q)
{
    LZH_MAT4X4F mat = lzh_mat4x4f_unit();
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;
    float d = 0.0f;

    if (!q) {
        return mat;
    }

    a = q->s;
    b = q->x;
    c = q->y;
    d = q->z;

    mat.m00 = 1.0f - 2.0f * (c * c + d * d);
    mat.m01 = 2.0f * (b * c - a * d);
    mat.m02 = 2.0f * (a * c + b * d);

    mat.m10 = 2.0f * (b * c + a * d);
    mat.m11 = 1.0f - 2.0f * (b * b + d * d);
    mat.m12 = 2.0f * (c * d - a * b);

    mat.m20 = 2.0f * (b * d - a * c);
    mat.m21 = 2.0f * (a * b + c * d);
    mat.m22 = 1.0f - 2.0f * (b * b + c * c);

    return mat;
}

LZH_QUAT4F lzh_quat4f_lerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t)
{
    LZH_QUAT4F q = lzh_quat4f_real(0.0f);
    LZH_QUAT4F m = lzh_quat4f_real(0.0f);

    if (!a || !b) {
        return q;
    }

    if (t < 0.0f) {
        t = 0.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }

    /* q = (1 - t) * a + t * b */
    q = lzh_quat4f_mul_scalar(a, 1.0f - t);
    m = lzh_quat4f_mul_scalar(b, t);
    q = lzh_quat4f_add(&q, &m);

    return q;
}

LZH_QUAT4F lzh_quat4f_nlerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t)
{
    LZH_QUAT4F q = lzh_quat4f_lerp(a, b, t);
    return lzh_quat4f_normalize(&q);
}

float lzh_quat4f_angle(const LZH_QUAT4F *a, const LZH_QUAT4F *b)
{
    if (a && b) {
        float theta = 
            a->s * b->s + 
            a->x * b->x +
            a->y * b->y +
            a->z * b->z;

        if (theta < -1.0f || theta > 1.0f) {
            return 0.0f;
        }

        return acosf(theta);
    }
    return 0.0f;
}

LZH_QUAT4F lzh_quat4f_slerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t)
{
    LZH_QUAT4F q = lzh_quat4f_real(0.0f);
    LZH_QUAT4F m = lzh_quat4f_real(0.0f);
    
    float theta = 0.0f;
    float s = 0.0f;
    float i = 0.0f;
    float j = 0.0f;

    if (!a || !b) {
        return q;
    }

    if (t < 0.0f) {
        t = 0.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }

    theta = lzh_quat4f_angle(a, b);
    s = sinf(theta);

    if (fabsf(s) < 1e-6f) {
        return lzh_quat4f_nlerp(a, b, t);
    }

    i = sinf((1.0f - t) * theta) / s;
    j = sinf(t * theta) / s;

    q = lzh_quat4f_mul_scalar(a, i);
    m = lzh_quat4f_mul_scalar(b, j);
    q = lzh_quat4f_add(&q, &m);

    return q;
}

/*===========================================================================*/
