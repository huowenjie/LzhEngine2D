#include <math.h>
#include "lzh_mat2x2f.h"

/*===========================================================================*/

LZH_VEC2F lzh_vec2f_xy(float x, float y)
{
    LZH_VEC2F v;
    
    v.x = x;
    v.y = y;
    return v;
}

LZH_VEC2F lzh_vec2f_add(const LZH_VEC2F *a, const LZH_VEC2F *b)
{
    LZH_VEC2F c = { 0 };

    if (a && b) {
        c.x = a->x + b->x;
        c.y = a->y + b->y;
    }
    return c;
}

LZH_VEC2F lzh_vec2f_sub(const LZH_VEC2F *a, const LZH_VEC2F *b)
{
    LZH_VEC2F c = { 0 };

    if (a && b) {
        c.x = a->x - b->x;
        c.y = a->y - b->y;
    }
    return c;
}

LZH_VEC2F lzh_vec2f_mul(const LZH_VEC2F *a, float t)
{
    LZH_VEC2F c = { 0 };

    if (a) {
        c.x = a->x * t;
        c.y = a->y * t;
    }
    return c;
}

LZH_VEC2F lzh_vec2f_div(const LZH_VEC2F *a, float t)
{
    LZH_VEC2F c = { 0 };

    if (a) {
        c.x = a->x / t;
        c.y = a->y / t;
    }
    return c;
}

LZH_VEC2F lzh_vec2f_reverse(const LZH_VEC2F *a)
{
    LZH_VEC2F c = { 0 };

    if (a) {
        c.x = -a->x;
        c.y = -a->y;
    }
    return c;
}

LZH_VEC2F lzh_vec2f_rotate(const LZH_VEC2F *a, float theta)
{
    LZH_VEC2F vec = { 0 };

    if (a) {
        LZH_MAT2X2F mat = lzh_mat2x2f_rotate(theta);
        vec = *a;
        vec = lzh_mat2x2f_mul_vec(&mat, &vec);
        vec = lzh_vec2f_normalize(&vec);
    }

    return vec;
}

LZH_VEC2F lzh_vec2f_normalize(const LZH_VEC2F *a)
{
    LZH_VEC2F c = { 0 };

    if (a) {
        float x = a->x;
        float y = a->y;
        float len = sqrtf(x * x + y * y);

        if (fabsf(len) > 1e-6f) {
            c.x = x / len;
            c.y = y / len;
        }
    }
    return c;
}

LZH_VEC2F lzh_vec2f_lerp(const LZH_VEC2F *a, const LZH_VEC2F *b, float t)
{
    LZH_VEC2F c = { 0 };
    LZH_VEC2F d = { 0 };
    LZH_VEC2F e = { 0 };

    if (t <= 0.0f) {
        t = 0.0f;
    } else if (t >= 1.0f) {
        t = 1.0f;
    }

    c = lzh_vec2f_mul(a, 1.0f - t);
    d = lzh_vec2f_mul(b, t);
    e = lzh_vec2f_add(&c, &d);
    return e;
}

float lzh_vec2f_dot(const LZH_VEC2F *a, const LZH_VEC2F *b)
{
    float c = 0.0f;

    if (a && b) {
        c = a->x * b->x + a->y * b->y;
    }
    return c;
}

float lzh_vec2f_cross(const LZH_VEC2F *a, const LZH_VEC2F *b)
{
    float c = 0.0f;

    if (a && b) {
        c = a->x * b->y - a->y * b->x;
    }
    return c;
}

float lzh_vec2f_length(const LZH_VEC2F *a)
{
    float len = 0.0f;

    if (a) {
        float x = a->x;
        float y = a->y;
        len = sqrtf(x * x + y * y);
    }
    return len;
}

float lzh_vec2f_angle(const LZH_VEC2F *a, const LZH_VEC2F *b)
{
    float c = 0.0f;

    if (a && b) {
        float ll = lzh_vec2f_length(a) * lzh_vec2f_length(b);
        if (fabsf(ll) > 0.0f) {
            float dot = lzh_vec2f_dot(a, b);
            dot /= ll;

            c = acosf(dot);
        }
    }
    return c;
}

LZH_VEC2F lzh_vec2f_line_comb(const LZH_VEC2F *vlist, const float *wlist, int k)
{
    LZH_VEC2F c = { 0 };
    int i = 0;

    if (vlist && k > 0) {
        for (i = 0; i < k; i++) {
            c.x += (wlist[i] * vlist[i].x);
            c.y += (wlist[i] * vlist[i].y);
        }
    }

    return c;
}

LZH_BOOL lzh_vec2f_inside_triangle(
    const LZH_VEC2F *a,
    const LZH_VEC2F *b,
    const LZH_VEC2F *c,
    const LZH_VEC2F *p)
{
    /* 采用叉乘法判断，也可以采用重心法判断 */
    LZH_VEC2F pa = lzh_vec2f_sub(p, a);
    LZH_VEC2F pb = lzh_vec2f_sub(p, b);
    LZH_VEC2F pc = lzh_vec2f_sub(p, c);

    float z1 = lzh_vec2f_cross(&pa, &pb);
    float z2 = lzh_vec2f_cross(&pb, &pc);
    float z3 = lzh_vec2f_cross(&pc, &pa);

    return z1 * z2 > 0 && z2 * z3 > 0;
}

/*===========================================================================*/
