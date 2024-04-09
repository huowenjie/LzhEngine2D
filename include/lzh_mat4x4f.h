#ifndef __LZH_MAT4X4F_H__
#define __LZH_MAT4X4F_H__

#include "lzh_vec4f.h"

/*===========================================================================*/
/* 4x4 方阵，行主序存储 */
/*===========================================================================*/

typedef union {
    /**
     * [ m00, m01, m02, m03 ]
     * [ m10, m11, m12, m13 ]
     * [ m20, m21, m22, m23 ]
     * [ m30, m31, m32, m33 ]
     */
    struct {
        float m00;
        float m01;
        float m02;
        float m03;
        float m10;
        float m11;
        float m12;
        float m13;
        float m20;
        float m21;
        float m22;
        float m23;
        float m30;
        float m31;
        float m32;
        float m33;
    };

    float mat[16];
    float matij[4][4];
} LZH_MAT4X4F;

/* 构建单位矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_unit();

/* 构建零矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_zero();

/* 构建矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_array(const float *elems);

/* 构建矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_array2d(const float (*elems)[4]);

/* 构建缩放矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_scale(float sx, float sy, float sz);

/* 构建旋转矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_z(float theta);

/* 构建旋转矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_x(float theta);

/* 构建旋转矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_rotate_y(float theta);

/* 构建镜像矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_reflect(const LZH_VEC3F *n);

/* 获取绕 z 轴正方向旋转角度 */
LZH_API float lzh_mat4x4f_rotate_z_theta(LZH_MAT4X4F *mat);

/* 获取绕 x 轴正方向旋转角度 */
LZH_API float lzh_mat4x4f_rotate_x_theta(LZH_MAT4X4F *mat);

/* 获取绕 y 轴正方向旋转角度 */
LZH_API float lzh_mat4x4f_rotate_y_theta(LZH_MAT4X4F *mat);

/* 构建平移矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_translate(float dx, float dy, float dz);

/* 从仿射矩阵提取缩放矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_scale(const LZH_MAT4X4F *mat);

/* 从仿射矩阵提取旋转矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_rotate(const LZH_MAT4X4F *mat);

/* 从仿射矩阵提取平移矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_get_translate(const LZH_MAT4X4F *mat);

/**
 * 体积盒投影矩阵
 * 将 [xl, xh] x [yl, yh] x [zl, zh] 投影到 [xpl, xph] x [ypl, yph] x [zpl, zph]
 * 
 * l 和 h 构成了待变换窗口的包围盒
 * lp 和 hp 构成了目标窗口的包围盒
 * 
 * l 的值为 xmin ymin zmin
 * h 的值为 xmax ymax zmax
 * 
 * lp 和 hp 同理
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_volume_map(
    const LZH_VEC3F *l,
    const LZH_VEC3F *h,
    const LZH_VEC3F *lp,
    const LZH_VEC3F *hp
);

/**
 * 将标准化坐标投影到屏幕空间-视口变换矩阵
 * 
 * width 屏幕宽度（像素）
 * height 屏幕高度（像素）
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_viewport(int width, int height);

/**
 * 摄像机视觉变换矩阵
 * 
 * pos 摄像机位置
 * target 目标位置
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_camera(const LZH_VEC3F *pos, const LZH_VEC3F *target);

/**
 * 透视投影矩阵
 * 
 * 将体积盒 [xl, xh] x [yl, yh] x [zl, zh] 中的物体
 * 进行透视变换，同时投影到规范化坐标系统 [-1, 1] 上
 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_perspective(const LZH_VEC3F *l, const LZH_VEC3F *h);

/* 转置矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_transpose(const LZH_MAT4X4F *mat);

/* 逆矩阵 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_inverse(const LZH_MAT4X4F *mat);

/* 4 x 4 行列式值 */
LZH_API float lzh_mat4x4f_determinant(const LZH_MAT4X4F *mat); 

/* 矩阵加 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_add(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* 矩阵减 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_sub(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* 矩阵乘 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_mul(const LZH_MAT4X4F *a, const LZH_MAT4X4F *b);

/* 矩阵和标量乘 */
LZH_API LZH_MAT4X4F lzh_mat4x4f_mul_real(const LZH_MAT4X4F *a, float b);

/* 矩阵和向量乘 */
LZH_API LZH_VEC4F lzh_mat4x4f_mul_vec(const LZH_MAT4X4F *a, const LZH_VEC4F *b);

/*===========================================================================*/

#endif /* __LZH_MAT4X4F_H__ */
