#ifndef __LZH_VEC4F_H__
#define __LZH_VEC4F_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* 三维齐次向量/四维向量 */
/*===========================================================================*/

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} LZH_VEC4F;

/* 构建向量 */
LZH_API LZH_VEC4F lzh_vec4f_xyzw(float x, float y, float z, float w);

/* 构建向量 */
LZH_API LZH_VEC4F lzh_vec4f_vec3f(const LZH_VEC3F *v, float w);

/* 向量加 */
LZH_API LZH_VEC4F lzh_vec4f_add(const LZH_VEC4F *a, const LZH_VEC4F *b);

/* 向量减 */
LZH_API LZH_VEC4F lzh_vec4f_sub(const LZH_VEC4F *a, const LZH_VEC4F *b);

/* 向量乘 */
LZH_API LZH_VEC4F lzh_vec4f_mul(const LZH_VEC4F *a, float t);

/* 向量除以整数 */
LZH_API LZH_VEC4F lzh_vec4f_div(const LZH_VEC4F *a, float t);

/* 向量取反 */
LZH_API LZH_VEC4F lzh_vec4f_reverse(const LZH_VEC4F *a);

/* 向量线性插值 p = (1 - t) * a + t * b 当 t = 0 时返回 a，否则返回 b */
LZH_API LZH_VEC4F lzh_vec4f_lerp(const LZH_VEC4F *a, const LZH_VEC4F *b, float t);

/* 向量线性组合 vlist 为向量列表，wlist 为权列表，k 为项数 */
LZH_API LZH_VEC4F lzh_vec4f_line_comb(const LZH_VEC4F *vlist, const float *wlist, int k);

/* 4d 向量齐次除法 */
LZH_API LZH_VEC4F lzh_vec4f_homogen_div(const LZH_VEC4F *a);

/*===========================================================================*/

#endif /* __LZH_VEC4F_H__ */
