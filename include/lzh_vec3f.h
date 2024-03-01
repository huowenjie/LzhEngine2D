#ifndef __LZH_VEC3F_H__
#define __LZH_VEC3F_H__

#include "lzh_type.h"
#include "lzh_vec2f.h"

/*===========================================================================*/
/* 三维向量 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x;
    float y;
    float z;
} LZH_VEC3F;

/* 构建向量 */
LZH_API LZH_VEC3F lzh_vec3f_xyz(float x, float y, float z);

/* 构建向量 */
LZH_API LZH_VEC3F lzh_vec3f_vec2f(const LZH_VEC2F *v, float z);

/* 向量加 */
LZH_API LZH_VEC3F lzh_vec3f_add(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* 向量减 */
LZH_API LZH_VEC3F lzh_vec3f_sub(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* 向量与实数相乘 */
LZH_API LZH_VEC3F lzh_vec3f_mul(const LZH_VEC3F *a, float t);

/* 向量与实数相除 */
LZH_API LZH_VEC3F lzh_vec3f_div(const LZH_VEC3F *a, float t);

/* 向量取反 */
LZH_API LZH_VEC3F lzh_vec3f_reverse(const LZH_VEC3F *a);

/* 向量归一化 */
LZH_API LZH_VEC3F lzh_vec3f_normalize(const LZH_VEC3F *a);

/* 向量线性插值, p = (1 - t) * a + t * b 当 t = 0 时返回 a，否则返回 b */
LZH_API LZH_VEC3F lzh_vec3f_lerp(const LZH_VEC3F *a, const LZH_VEC3F *b, float t);

/* 向量点乘 */
LZH_API float lzh_vec3f_dot(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* 向量叉乘 */
LZH_API LZH_VEC3F lzh_vec3f_cross(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* 求向量的长度 */
LZH_API float lzh_vec3f_length(const LZH_VEC3F *a);

/* 求两个向量的夹角 */
LZH_API float lzh_vec3f_angle(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* 向量的线性组合，vlist 为向量列表，wlist 为权列表，k 为项数 */
LZH_API LZH_VEC3F lzh_vec3f_line_comb(const LZH_VEC3F *vlist, const float *wlist, int k);

/* 基于两个向量构建正交基 */
LZH_API LZH_BOOL lzh_vec3f_build_basic(
    const LZH_VEC3F *a,
    const LZH_VEC3F *b,
    LZH_VEC3F *w,
    LZH_VEC3F *u,
    LZH_VEC3F *v);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_VEC3F_H__ */
