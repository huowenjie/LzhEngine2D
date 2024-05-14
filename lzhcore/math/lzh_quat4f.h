#ifndef __LZH_QUAT4F_H__
#define __LZH_QUAT4F_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* 四元数 */
/*===========================================================================*/

typedef struct {
    /**
     * [ s, v ]
     * [ s, x, y, z ]
     */
    float s;

    union {
        LZH_VEC3F v;
        struct {
            float x;
            float y;
            float z;
        };
    };
} LZH_QUAT4F;

/* 初始化实数 */
LZH_QUAT4F lzh_quat4f_real(float s);

/* 初始化纯四元数 */
LZH_QUAT4F lzh_quat4f_pure(float x, float y, float z);

/* 初始化纯四元数 */
LZH_QUAT4F lzh_quat4f_vec3f(const LZH_VEC3F *v);

/* 初始化四元数 */
LZH_QUAT4F lzh_quat4f_sxyz(float s, float x, float y, float z);

/* 初始化四元数 */
LZH_QUAT4F lzh_quat4f_sv(float s, const LZH_VEC3F *v);

/* 获取四元数的共轭 */
LZH_QUAT4F lzh_quat4f_conjugate(const LZH_QUAT4F *q);

/* 求四元数的模长 */
float lzh_quat4f_norm(const LZH_QUAT4F *q);

/* 四元数的加法 a + b */
LZH_QUAT4F lzh_quat4f_add(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* 四元数的减法 a - b */
LZH_QUAT4F lzh_quat4f_sub(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* 标量乘 q * t */
LZH_QUAT4F lzh_quat4f_mul_scalar(const LZH_QUAT4F *q, float t);

/* 标量除 q / t */
LZH_QUAT4F lzh_quat4f_div_scalar(const LZH_QUAT4F *q, float t);

/* 四元数乘法 a * b */
LZH_QUAT4F lzh_quat4f_mul(const LZH_QUAT4F *qa, const LZH_QUAT4F *qb);

/* 四元数的逆 */
LZH_QUAT4F lzh_quat4f_inverse(const LZH_QUAT4F *q);

/* 四元数旋转运算 v' = qvq*，四元数 q 必须保证是单位四元数 */
LZH_VEC3F lzh_quat4f_rotate(const LZH_QUAT4F *q, const LZH_VEC3F *v);

/* 创建一个绕旋转轴 u 旋转 theta 角度（单位：弧度）的旋转 */
LZH_QUAT4F lzh_quat4f_rotation(const LZH_VEC3F *u, float theta);

/* 从旋转四元数中获取角度 */
float lzh_quat4f_get_theta(const LZH_QUAT4F *q);

/* 从旋转四元数获取旋转轴 */
LZH_VEC3F lzh_quat4f_get_axis(const LZH_QUAT4F *q);

/*===========================================================================*/

#endif /* __LZH_QUAT4F_H__ */
