#include <math.h>
#include "lzh_vec3f.h"

/*===========================================================================*/

LZH_VEC3F lzh_vec3f_xyz(float x, float y, float z)
{
    LZH_VEC3F v;

    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

LZH_VEC3F lzh_vec3f_vec2f(const LZH_VEC2F *v, float z)
{
    LZH_VEC3F t = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (v) {
        t.x = v->x;
        t.y = v->y;
        t.z = z;
    }
    return t;
}

LZH_VEC3F lzh_vec3f_add(const LZH_VEC3F *a, const LZH_VEC3F *b)
{
    LZH_VEC3F c = { 0 };

    if (a && b) {
        c.x = a->x + b->x;
        c.y = a->y + b->y;
        c.z = a->z + b->z;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_sub(const LZH_VEC3F *a, const LZH_VEC3F *b)
{
    LZH_VEC3F c = { 0 };

    if (a && b) {
        c.x = a->x - b->x;
        c.y = a->y - b->y;
        c.z = a->z - b->z;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_mul(const LZH_VEC3F *a, float t)
{
    LZH_VEC3F c = { 0 };

    if (a) {
        c.x = a->x * t;
        c.y = a->y * t;
        c.z = a->z * t;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_div(const LZH_VEC3F *a, float t)
{
    LZH_VEC3F c = { 0 };

    if (a) {
        c.x = a->x / t;
        c.y = a->y / t;
        c.z = a->z / t;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_reverse(const LZH_VEC3F *a)
{
    LZH_VEC3F c = { 0 };

    if (a) {
        c.x = -a->x;
        c.y = -a->y;
        c.z = -a->z;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_normalize(const LZH_VEC3F *a)
{
    LZH_VEC3F c = { 0 };

    if (a) {
        float x = a->x;
        float y = a->y;
        float z = a->z;
        float len = sqrtf(x * x + y * y + z * z);

        if (fabsf(len) > 1e-6f) {
            c.x = x / len;
            c.y = y / len;
            c.z = z / len;
        }
    }
    return c;
}

LZH_VEC3F lzh_vec3f_lerp(const LZH_VEC3F *a, const LZH_VEC3F *b, float t)
{
    LZH_VEC3F c = { 0 };
    LZH_VEC3F d = { 0 };
    LZH_VEC3F e = { 0 };

    if (t <= 0.0f) {
        t = 0.0f;
    } else if (t >= 1.0f) {
        t = 1.0f;
    }

    c = lzh_vec3f_mul(a, 1.0f - t);
    d = lzh_vec3f_mul(b, t);
    e = lzh_vec3f_add(&c, &d);
    return e;
}

float lzh_vec3f_dot(const LZH_VEC3F *a, const LZH_VEC3F *b)
{
    float c = 0.0f;

    if (a && b) {
        c = a->x * b->x + a->y * b->y + a->z * b->z;
    }
    return c;
}

LZH_VEC3F lzh_vec3f_cross(const LZH_VEC3F *a, const LZH_VEC3F *b)
{
    LZH_VEC3F c = { 0 };

    if (a && b) {
        c.x = a->y * b->z - a->z * b->y;
        c.y = a->z * b->x - a->x * b->z;
        c.z = a->x * b->y - a->y * b->x;
    }
    return c;
}

float lzh_vec3f_length(const LZH_VEC3F *a)
{
    float len = 0.0f;

    if (a) {
        float x = a->x;
        float y = a->y;
        float z = a->z;
        len = sqrtf(x * x + y * y + z * z);
    }
    return len;
}

float lzh_vec3f_angle(const LZH_VEC3F *a, const LZH_VEC3F *b)
{
    float c = 0.0f;

    if (a && b) {
        float ll = lzh_vec3f_length(a) * lzh_vec3f_length(b);
        if (fabsf(ll) > 0.0f) {
            float dot = lzh_vec3f_dot(a, b);
            dot /= ll;

            c = acosf(dot);
        }
    }
    return c;
}

LZH_VEC3F lzh_vec3f_line_comb(const LZH_VEC3F *vlist, const float *wlist, int k)
{
    LZH_VEC3F c = { 0 };
    int i = 0;

    if (vlist && k > 0) {
        for (i = 0; i < k; i++) {
            c.x += (wlist[i] * vlist[i].x);
            c.y += (wlist[i] * vlist[i].y);
            c.y += (wlist[i] * vlist[i].y);
        }
    }

    return c;
}

LZH_BOOL lzh_vec3f_build_basic(
    const LZH_VEC3F *a,
    const LZH_VEC3F *b,
    LZH_VEC3F *w,
    LZH_VEC3F *u,
    LZH_VEC3F *v)
{
    LZH_VEC3F tw = { 0 };
    LZH_VEC3F tu = { 0 };
    LZH_VEC3F tv = { 0 };

    if (!a || !b) {
        return LZH_FALSE;
    }

    tw = lzh_vec3f_normalize(a);
    tu = lzh_vec3f_cross(b, &tw);
    tu = lzh_vec3f_normalize(&tu);
    tv = lzh_vec3f_cross(&tw, &tu);

    if (w) {
        *w = tw;
    }

    if (u) {
        *u = tu;
    }

    if (v) {
        *v = tv;
    }
    return LZH_TRUE;
}

/*===========================================================================*/
