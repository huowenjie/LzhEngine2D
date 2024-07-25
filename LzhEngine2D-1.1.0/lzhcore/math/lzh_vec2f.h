#ifndef __LZH_VEC2F_H__
#define __LZH_VEC2F_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 二维向量 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x;
    float y;
} LZH_VEC2F;

/* 构建向量 */
LZH_VEC2F lzh_vec2f_xy(float x, float y);

/* 向量加 */
LZH_VEC2F lzh_vec2f_add(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* 向量减 */
LZH_VEC2F lzh_vec2f_sub(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* 向量与实数相乘 */
LZH_VEC2F lzh_vec2f_mul(const LZH_VEC2F *a, float t);

/* 向量与实数相除 */
LZH_VEC2F lzh_vec2f_div(const LZH_VEC2F *a, float t);

/* 向量取反 */
LZH_VEC2F lzh_vec2f_reverse(const LZH_VEC2F *a);

/* 向量旋转 */
LZH_VEC2F lzh_vec2f_rotate(const LZH_VEC2F *a, float theta);

/* 向量归一化 */
LZH_VEC2F lzh_vec2f_normalize(const LZH_VEC2F *a);

/* 向量线性插值, p = (1 - t) * a + t * b 当 t = 0 时返回 a，否则返回 b */
LZH_VEC2F lzh_vec2f_lerp(const LZH_VEC2F *a, const LZH_VEC2F *b, float t);

/* 向量点乘 */
float lzh_vec2f_dot(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* 向量叉乘的模，在 2 维平面上，我们忽略向量叉乘后的方向，仅计算其模 */
float lzh_vec2f_cross(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* 求向量的长度 */
float lzh_vec2f_length(const LZH_VEC2F *a);

/* 求两个向量的夹角 */
float lzh_vec2f_angle(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* 向量的线性组合，vlist 为向量列表，wlist 为权列表，k 为项数 */
LZH_VEC2F lzh_vec2f_line_comb(const LZH_VEC2F *vlist, const float *wlist, int k);

/* 判断点 p 是否在三角形 abc 内 */
LZH_BOOL lzh_vec2f_inside_triangle(
    const LZH_VEC2F *a,
    const LZH_VEC2F *b,
    const LZH_VEC2F *c,
    const LZH_VEC2F *p);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_VEC2F_H__ */
