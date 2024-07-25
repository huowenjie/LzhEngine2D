#ifndef __LZH_QUAT4F_H__
#define __LZH_QUAT4F_H__

#include "lzh_vec3f.h"
#include "lzh_mat3x3f.h"
#include "lzh_mat4x4f.h"

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

/* 四元数归一化 */
LZH_QUAT4F lzh_quat4f_normalize(const LZH_QUAT4F *q);

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

/* 从旋转四元数中获取欧拉角 yaw */
float lzh_quat4f_get_theta_z(const LZH_QUAT4F *q);

/* 从旋转四元数中获取欧拉角 pitch */
float lzh_quat4f_get_theta_y(const LZH_QUAT4F *q);

/* 从旋转四元数中获取欧拉角 roll */
float lzh_quat4f_get_theta_x(const LZH_QUAT4F *q);

/* 欧拉角转换为四元数 */
LZH_QUAT4F lzh_quat4f_euler2quat(float yaw, float pitch, float roll);

/* 从旋转四元数获取旋转轴 */
LZH_VEC3F lzh_quat4f_get_axis(const LZH_QUAT4F *q);

/* 从旋转四元数获取 3x3 旋转矩阵 */
LZH_MAT3X3F lzh_quat4f_get_mat3x3f(const LZH_QUAT4F *q);

/* 从旋转四元数获取 3x3 齐次旋转矩阵 */
LZH_MAT4X4F lzh_quat4f_get_mat4x4f(const LZH_QUAT4F *q);

/* 四元数线性插值 */
LZH_QUAT4F lzh_quat4f_lerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/* 四元数归一化线性插值 */
LZH_QUAT4F lzh_quat4f_nlerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/* 求两个旋转四元数之间的夹角（单位：弧度） */
float lzh_quat4f_angle(const LZH_QUAT4F *a, const LZH_QUAT4F *b);

/* 四元数球面线性插值 */
LZH_QUAT4F lzh_quat4f_slerp(const LZH_QUAT4F *a, const LZH_QUAT4F *b, float t);

/*===========================================================================*/

#endif /* __LZH_QUAT4F_H__ */
