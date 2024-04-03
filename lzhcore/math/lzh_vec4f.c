#include <math.h>
#include "lzh_vec4f.h"

/*===========================================================================*/

LZH_VEC4F lzh_vec4f_xyzw(float x, float y, float z, float w)
{
    LZH_VEC4F v;
    
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

LZH_VEC4F lzh_vec4f_vec3f(const LZH_VEC3F *v, float w)
{
    LZH_VEC4F t = lzh_vec4f_xyzw(0.0f, 0.0f, 0.0f, 0.0f);

    if (v) {
        t.x = v->x;
        t.y = v->y;
        t.z = v->z;
        t.w = w;
    }
    return t;
}

LZH_VEC4F lzh_vec4f_add(const LZH_VEC4F *a, const LZH_VEC4F *b)
{
    LZH_VEC4F c = { 0 };

    if (a && b) {
        c.x = a->x + b->x;
        c.y = a->y + b->y;
        c.z = a->z + b->z;
        c.w = a->w + b->w;
    }
    return c;
}

LZH_VEC4F lzh_vec4f_sub(const LZH_VEC4F *a, const LZH_VEC4F *b)
{
    LZH_VEC4F c = { 0 };

    if (a && b) {
        c.x = a->x - b->x;
        c.y = a->y - b->y;
        c.z = a->z - b->z;
        c.w = a->w - b->w;
    }
    return c;
}

LZH_VEC4F lzh_vec4f_mul(const LZH_VEC4F *a, float t)
{
    LZH_VEC4F c = { 0 };

    if (a) {
        c.x = a->x * t;
        c.y = a->y * t;
        c.z = a->z * t;
        c.w = a->w * t;
    }
    return c;
}

LZH_VEC4F lzh_vec4f_div(const LZH_VEC4F *a, float t)
{
    LZH_VEC4F c = { 0 };

    if (a) {
        c.x = a->x / t;
        c.y = a->y / t;
        c.z = a->z / t;
        c.w = a->w / t;
    }
    return c;
}

LZH_VEC4F lzh_vec4f_reverse(const LZH_VEC4F *a)
{
    LZH_VEC4F c = { 0 };

    if (a) {
        c.x = -a->x;
        c.y = -a->y;
        c.z = -a->z;
        c.w = -a->w;
    }
    return c;
}

LZH_VEC4F lzh_vec4f_lerp(const LZH_VEC4F *a, const LZH_VEC4F *b, float t)
{
    LZH_VEC4F c = { 0 };
    LZH_VEC4F d = { 0 };
    LZH_VEC4F e = { 0 };

    if (t <= 0.0f) {
        t = 0.0f;
    } else if (t >= 1.0f) {
        t = 1.0f;
    }

    c = lzh_vec4f_mul(a, 1.0f - t);
    d = lzh_vec4f_mul(b, t);
    e = lzh_vec4f_add(&c, &d);
    return e;
}

LZH_VEC4F lzh_vec4f_line_comb(const LZH_VEC4F *vlist, const float *wlist, int k)
{
    LZH_VEC4F c = { 0 };
    int i = 0;

    if (vlist && k > 0) {
        for (i = 0; i < k; i++) {
            c.x += (wlist[i] * vlist[i].x);
            c.y += (wlist[i] * vlist[i].y);
            c.z += (wlist[i] * vlist[i].z);
            c.w += (wlist[i] * vlist[i].w);
        }
    }

    return c;
}

LZH_VEC4F lzh_vec4f_homogen_div(const LZH_VEC4F *a)
{
    LZH_VEC4F c = { 0 };

    if (a && fabsf(a->w) > 1e-6f) {
        c.x = a->x / a->w;
        c.y = a->y / a->w;
        c.z = a->z / a->w;
        c.w = 1.0f;
    }
    return c;
}

/*===========================================================================*/
