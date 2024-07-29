#ifndef __LZH_MATRIX4X4_H__
#define __LZH_MATRIX4X4_H__

#include "LzhVector4d.h"
#include "LzhMatrix3x3.h"

//-----------------------------------------------------------------------------
// 4 x 4 方阵或 3 x 3 齐次矩阵
//-----------------------------------------------------------------------------

template <typename T>
class Lzh_Mat4x4f
{
public:
    Lzh_Mat4x4f()
    {
        this->m00 = this->m11 = this->m22 = this->m33 = (T)1;
        this->m01 = this->m02 = this->m03 = (T)0;
        this->m10 = this->m12 = this->m13 = (T)0;
        this->m20 = this->m21 = this->m23 = (T)0;
        this->m30 = this->m31 = this->m32 = (T)0;
    }

    Lzh_Mat4x4f(T elem)
    {
        this->m00 = this->m01 = this->m02 = this->m03 = elem;
        this->m10 = this->m11 = this->m12 = this->m13 = elem;
        this->m20 = this->m21 = this->m22 = this->m23 = elem;
        this->m30 = this->m31 = this->m32 = this->m33 = elem;
    }

    Lzh_Mat4x4f(T *elems)
    {
        this->m00 = elems[0]; this->m01 = elems[1]; this->m02 = elems[2]; this->m03 = elems[3];
        this->m10 = elems[4]; this->m11 = elems[5]; this->m12 = elems[6]; this->m13 = elems[7];
        this->m20 = elems[8]; this->m21 = elems[9]; this->m22 = elems[10]; this->m23 = elems[11];
        this->m30 = elems[12]; this->m31 = elems[13]; this->m32 = elems[14]; this->m33 = elems[15];
    }

    Lzh_Mat4x4f(T (*elems)[4])
    {
        this->m00 = elems[0][0]; this->m01 = elems[0][1]; this->m02 = elems[0][2]; this->m03 = elems[0][3];
        this->m10 = elems[1][0]; this->m11 = elems[1][1]; this->m12 = elems[1][2]; this->m13 = elems[1][3];
        this->m20 = elems[2][0]; this->m21 = elems[2][1]; this->m22 = elems[2][2]; this->m23 = elems[2][3];
        this->m30 = elems[3][0]; this->m31 = elems[3][1]; this->m32 = elems[3][2]; this->m33 = elems[3][3];
    }

public:
    // 单位矩阵
    static Lzh_Mat4x4f UnitMatrix()
    {
        return Lzh_Mat4x4f();
    }

    // 零矩阵
    static Lzh_Mat4x4f ZeroMatrix()
    {
        return Lzh_Mat4x4f((T)0);
    }

    // 转置矩阵
    static Lzh_Mat4x4f Transpose(const Lzh_Mat4x4f &mat)
    {
        Lzh_Mat4x4f tmp(mat);

        tmp.m01 = mat.m10; tmp.m10 = mat.m01; tmp.m02 = mat.m20; tmp.m20 = mat.m02;
        tmp.m03 = mat.m30; tmp.m30 = mat.m03; tmp.m12 = mat.m21; tmp.m21 = mat.m12;
        tmp.m13 = mat.m31; tmp.m31 = mat.m13; tmp.m23 = mat.m32; tmp.m32 = mat.m23;

        return tmp;
    }

    // 逆矩阵
    static Lzh_Mat4x4f Inverse(const Lzh_Mat4x4f &mat);

    // 4x4 行列式
    static T Determinant(const Lzh_Mat4x4f &mat);

public:
    // 缩放变换
    static Lzh_Mat4x4f ScaleMatrix(float sx, float sy, float sz)
    {
        
    }

    // 围绕 z 轴的旋转的旋转矩阵
    static Lzh_Mat4x4f RotateZMatrix(float theta)
    {
        
    }

    // 围绕 X 轴的旋转的旋转矩阵
    static Lzh_Mat4x4f RotateXMatrix(float theta)
    {
        
    }

    // 围绕 Y 轴的旋转的旋转矩阵
    static Lzh_Mat4x4f RotateYMatrix(float theta)
    {
        
    }

    // 平移矩阵
    static Lzh_Mat4x4f TranslateMatrix(float dx, float dy, float dz)
    {
        Lzh_Mat4x4f trans;

        mat.m03 = dx;
        mat.m13 = dy;
        mat.m23 = dz;

        return trans;
    }

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
    static Lzh_Mat4x4f VolumeMapMatrix(
        const Lzh_Vec3d<T> &l,
        const Lzh_Vec3d<T> &h,
        const Lzh_Vec3d<T> &lp,
        const Lzh_Vec3d<T> &hp)
    {
        Lzh_Mat4x4f mat;

        mat.m00 = (hp->x - lp->x) / (h->x - l->x);
        mat.m11 = (hp->y - lp->y) / (h->y - l->y);
        mat.m22 = (hp->z - lp->z) / (h->z - l->z);

        mat.m03 = (lp->x * h->x - hp->x * l->x) / (h->x - l->x);
        mat.m13 = (lp->y * h->y - hp->y * l->y) / (h->y - l->y);
        mat.m23 = (lp->z * h->z - hp->z * l->z) / (h->z - l->z);

        return mat;
    }

    /**
     * 将标准化坐标投影到屏幕空间-视口变换
     * 
     * width 屏幕宽度
     * height 屏幕高度
     */
    static Lzh_Mat4x4f ViewportMatrix(T width, T height)
    {
        Lzh_Mat4x4f mat;

        float nx = (float)width;
        float ny = (float)height;

        mat.m00 = (T)(nx / 2.0f);
        mat.m11 = (T)(ny / 2.0f);
        mat.m03 = (T)((nx - 1.0f) / 2.0f);
        mat.m13 = (T)((ny - 1.0f) / 2.0f);

        return mat;
    }

    /**
     * 摄像机视觉变换矩阵 look at
     * 
     * pos 摄像机位置
     * up 上方向
     * target 目标位置
     */
    static Lzh_Mat4x4f CameraMatrix(
        const Lzh_Vec3d<T> &pos, const Lzh_Vec3d<T> &up, const Lzh_Vec3d<T> &target);

    /**
     * 透视投影矩阵
     * 
     * fov：视场角
     * aspect：宽高比
     * near：近平面
     * far：远平面
     */
    static Lzh_Mat4x4f PerspectiveMatrix(float fov, float aspect, float near, float far)
    {
        Lzh_Mat4x4f per;

        float thfov = tanf(fov / 2.0f);

        per.m00 =  (T)(1.0f / (aspect * thfov));
        per.m11 =  (T)(1.0f / thfov);
        per.m22 = -(T)((near + far) / (far - near));
        per.m23 = -(T)((2.0f * far * near) / (far - near));
        per.m32 = -(T)(1.0f);
        return per;
    }

    // 正交投影矩阵
    static Lzh_Mat4x4f OrthoMatrix(const Lzh_Vec3d<T> &l, const Lzh_Vec3d<T> &h)
    {
        Lzh_Mat4x4f ortho;

        ortho.m00 =   (T)((2.0f) / (right - left));
        ortho.m11 =   (T)((2.0f) / (top - bottom));
        ortho.m22 = - (T)((2.0f) / (far - near));

        ortho.m03 = - (right + left) / (right - left);
        ortho.m13 = - (top + bottom) / (top - bottom);
        ortho.m23 = - (far + near) / (far - near);
        return ortho;
    }

    // 正交投影矩阵(2D)
    static Lzh_Mat4x4f Ortho2dMatrix(const Lzh_Vec3d<T> &l, const Lzh_Vec3d<T> &h)
    {
        Lzh_Mat4x4f ortho;

        ortho.m00 = (T)((2.0f) / (right - left));
        ortho.m11 = (T)((2.0f) / (top - bottom));
        ortho.m22 = (T)(1.0f);

        ortho.m03 = - (right + left) / (right - left);
        ortho.m13 = - (top + bottom) / (top - bottom);
        return ortho;
    }

public:
    // 加
    Lzh_Mat4x4f operator+(const Lzh_Mat4x4f &mat) const
    {
        Lzh_Mat4x4f tmp(*this);

        tmp.m00 += mat.m00; tmp.m01 += mat.m01; tmp.m02 += mat.m02; tmp.m03 += mat.m03;
        tmp.m10 += mat.m10; tmp.m11 += mat.m11; tmp.m12 += mat.m12; tmp.m13 += mat.m13;
        tmp.m20 += mat.m20; tmp.m21 += mat.m21; tmp.m22 += mat.m22; tmp.m23 += mat.m23;
        tmp.m30 += mat.m30; tmp.m31 += mat.m31; tmp.m32 += mat.m32; tmp.m33 += mat.m33;

        return tmp;
    }

    // 减
    Lzh_Mat4x4f operator-(const Lzh_Mat4x4f &mat) const
    {
        Lzh_Mat4x4f tmp(*this);

        tmp.m00 -= mat.m00; tmp.m01 -= mat.m01; tmp.m02 -= mat.m02; tmp.m03 -= mat.m03;
        tmp.m10 -= mat.m10; tmp.m11 -= mat.m11; tmp.m12 -= mat.m12; tmp.m13 -= mat.m13;
        tmp.m20 -= mat.m20; tmp.m21 -= mat.m21; tmp.m22 -= mat.m22; tmp.m23 -= mat.m23;
        tmp.m30 -= mat.m30; tmp.m31 -= mat.m31; tmp.m32 -= mat.m32; tmp.m33 -= mat.m33;

        return tmp;
    }

    // 乘
    Lzh_Mat4x4f operator*(float val) const
    {
        Lzh_Mat4x4f tmp(*this);

        tmp.m00 *= val; tmp.m01 *= val; tmp.m02 *= val; tmp.m03 *= val;
        tmp.m10 *= val; tmp.m11 *= val; tmp.m12 *= val; tmp.m13 *= val;
        tmp.m20 *= val; tmp.m21 *= val; tmp.m22 *= val; tmp.m23 *= val;
        tmp.m30 *= val; tmp.m31 *= val; tmp.m32 *= val; tmp.m33 *= val;

        return tmp;
    }

    friend Lzh_Mat4x4f operator*(float val, const Lzh_Mat4x4f &mat)
    {
        Lzh_Mat4x4f tmp(mat);

        tmp.m00 *= val; tmp.m01 *= val; tmp.m02 *= val; tmp.m03 *= val;
        tmp.m10 *= val; tmp.m11 *= val; tmp.m12 *= val; tmp.m13 *= val;
        tmp.m20 *= val; tmp.m21 *= val; tmp.m22 *= val; tmp.m23 *= val;
        tmp.m30 *= val; tmp.m31 *= val; tmp.m32 *= val; tmp.m33 *= val;

        return tmp;
    }

    Lzh_Mat4x4f operator*(const Lzh_Mat4x4f &mat) const;

    // 矩阵和向量相乘
    Lzh_Vec4d<T> operator*(const Lzh_Vec4d<T> &vec) const
    {
        Lzh_Vec4d<T> tmp;

        tmp.x = m00 * vec.x + m01 * vec.y + m02 * vec.z + m03 * vec.w;
        tmp.y = m10 * vec.x + m11 * vec.y + m12 * vec.z + m13 * vec.w;
        tmp.z = m20 * vec.x + m21 * vec.y + m22 * vec.z + m23 * vec.w;
        tmp.w = m30 * vec.x + m31 * vec.y + m32 * vec.z + m33 * vec.w;
        return tmp;
    }

    // 矩阵取值
    T *operator[](int i)
    {
        return matij[i];
    }

    // 逆矩阵
    Lzh_Mat4x4f operator-() const
    {
        return Lzh_Mat4x4f::Inverse(*this);
    }

public:
    // 转置
    Lzh_Mat4x4f Transpose() const
    {
        return Lzh_Mat4x4f::Transpose(*this);
    }

    // 求 4 x 4 行列式
    T Determinant() const
    {
        return Lzh_Mat4x4f::Determinant(*this);
    }

public:
    union {
        /**
         * [ m00, m01, m02, m03 ]
         * [ m10, m11, m12, m13 ]
         * [ m20, m21, m22, m23 ]
         * [ m30, m31, m32, m33 ]
         */
        struct {
            T m00; T m01; T m02; T m03;
            T m10; T m11; T m12; T m13;
            T m20; T m21; T m22; T m23;
            T m30; T m31; T m32; T m33;
        };

        T mat[16];
        T matij[4][4];
    };
};

//-----------------------------------------------------------------------------

template<typename T>
Lzh_Mat4x4f<T> Lzh_Mat4x4f<T>::CameraMatrix(
    const Lzh_Vec3d<T> &pos, const Lzh_Vec3d<T> &up, const Lzh_Vec3d<T> &target)
{
    Lzh_Vec3d<T> z = up;
    Lzh_Vec3d<T> u;
    Lzh_Vec3d<T> v;
    Lzh_Vec3d<T> w;
    Lzh_Mat4x4f cam;

    w = pos - target;
    w = w.Normalize();

    u = z.Cross(w);
    u = u.Normalize();

    v = w.Cross(u);
    v = v.Normalize();

    cam.m00 = u.x; cam.m01 = u.y; cam.m02 = u.z; cam.m03 = -pos->x;
    cam.m10 = v.x; cam.m11 = v.y; cam.m12 = v.z; cam.m13 = -pos->y;
    cam.m20 = w.x; cam.m21 = w.y; cam.m22 = w.z; cam.m23 = -pos->z;
    return cam;
}

template<typename T>
Lzh_Mat4x4f<T> Lzh_Mat4x4f<T>::operator*(const Lzh_Mat4x4f &mat) const
{
    Lzh_Mat4x4f tmp((T)0);

    tmp.m00 = m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20 + m03 * mat.m30;
    tmp.m01 = m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21 + m03 * mat.m31;
    tmp.m02 = m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22 + m03 * mat.m32;
    tmp.m03 = m00 * mat.m03 + m01 * mat.m13 + m02 * mat.m23 + m03 * mat.m33;

    tmp.m10 = m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20 + m13 * mat.m30;
    tmp.m11 = m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31;
    tmp.m12 = m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32;
    tmp.m13 = m10 * mat.m03 + m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33;

    tmp.m20 = m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20 + m23 * mat.m30;
    tmp.m21 = m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31;
    tmp.m22 = m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32;
    tmp.m23 = m20 * mat.m03 + m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33;

    tmp.m30 = m30 * mat.m00 + m31 * mat.m10 + m32 * mat.m20 + m33 * mat.m30;
    tmp.m31 = m30 * mat.m01 + m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31;
    tmp.m32 = m30 * mat.m02 + m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32;
    tmp.m33 = m30 * mat.m03 + m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33;

    return tmp;
}

/*
 * 利用克拉默法则来求解逆矩阵
 * inverse A = adj A / det A
 * [ +c00, -c10, +c20, -c30 ]
 * [ -c01, +c11, -c21, +c31 ]
 * [ +c02, -c12, +c22, -c32 ]
 * [ -c03, +c13, -c23, +c33 ]
 */
template<typename T>
Lzh_Mat4x4f<T> Lzh_Mat4x4f<T>::Inverse(const Lzh_Mat4x4f &mat)
{
    // 求行列式
    T det = Lzh_Mat4x4f::Determinant(mat);

    Lzh_Mat4x4f adj;
    Lzh_Mat3x3f<T> tmp;

    // c00
    tmp.m00 = mat.m11; tmp.m01 = mat.m12; tmp.m02 = mat.m13;
    tmp.m10 = mat.m21; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m31; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m00 = tmp.Determinant() / det;

    // c10
    tmp.m00 = mat.m01; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m21; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m31; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m01 = -(tmp.Determinant()) / det;

    // c20
    tmp.m00 = mat.m01; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m11; tmp.m11 = mat.m12; tmp.m12 = mat.m13;
    tmp.m20 = mat.m31; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m02 = tmp.Determinant() / det;

    // c30
    tmp.m00 = mat.m01; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m11; tmp.m11 = mat.m12; tmp.m12 = mat.m13;
    tmp.m20 = mat.m21; tmp.m21 = mat.m22; tmp.m22 = mat.m23;
    adj.m03 = -(tmp.Determinant()) / det;

    // c01
    tmp.m00 = mat.m10; tmp.m01 = mat.m12; tmp.m02 = mat.m13;
    tmp.m10 = mat.m20; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m10 = -(tmp.Determinant()) / det;

    // c11
    tmp.m00 = mat.m00; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m20; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m11 = tmp.Determinant() / det;

    // c21
    tmp.m00 = mat.m00; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m10; tmp.m11 = mat.m12; tmp.m12 = mat.m13;
    tmp.m20 = mat.m30; tmp.m21 = mat.m32; tmp.m22 = mat.m33;
    adj.m12 = -(tmp.Determinant()) / det;

    // c31
    tmp.m00 = mat.m00; tmp.m01 = mat.m02; tmp.m02 = mat.m03;
    tmp.m10 = mat.m10; tmp.m11 = mat.m12; tmp.m12 = mat.m13;
    tmp.m20 = mat.m20; tmp.m21 = mat.m22; tmp.m22 = mat.m23;
    adj.m13 = tmp.Determinant() / det;

    // c02
    tmp.m00 = mat.m10; tmp.m01 = mat.m11; tmp.m02 = mat.m13;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m33;
    adj.m20 = tmp.Determinant() / det;

    // c12
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m03;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m33;
    adj.m21 = -(tmp.Determinant()) / det;

    // c22
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m03;
    tmp.m10 = mat.m10; tmp.m11 = mat.m11; tmp.m12 = mat.m13;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m33;
    adj.m22 = tmp.Determinant() / det;

    // c32
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m03;
    tmp.m10 = mat.m10; tmp.m11 = mat.m11; tmp.m12 = mat.m13;
    tmp.m20 = mat.m20; tmp.m21 = mat.m21; tmp.m22 = mat.m23;
    adj.m23 = -(tmp.Determinant()) / det;

    // c03
    tmp.m00 = mat.m10; tmp.m01 = mat.m11; tmp.m02 = mat.m12;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m22;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m32;
    adj.m30 = -(tmp.Determinant()) / det;

    // c13
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m02;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m22;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m32;
    adj.m31 = tmp.Determinant() / det;

    // c23
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m02;
    tmp.m10 = mat.m10; tmp.m11 = mat.m11; tmp.m12 = mat.m12;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m32;
    adj.m32 = -(tmp.Determinant()) / det;

    // c33
    tmp.m00 = mat.m00; tmp.m01 = mat.m01; tmp.m02 = mat.m02;
    tmp.m10 = mat.m10; tmp.m11 = mat.m11; tmp.m12 = mat.m12;
    tmp.m20 = mat.m20; tmp.m21 = mat.m21; tmp.m22 = mat.m22;
    adj.m33 = tmp.Determinant() / det;

    return adj;
}

template<typename T>
T Lzh_Mat4x4f<T>::Determinant(const Lzh_Mat4x4f &mat)
{
    T det = (T)0;
    Lzh_Mat3x3f<T> tmp;

    tmp.m00 = mat.m11; tmp.m01 = mat.m12; tmp.m02 = mat.m13;
    tmp.m10 = mat.m21; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m31; tmp.m21 = mat.m32; tmp.m22 = mat.m33;

    det = mat.m00 * tmp.Determinant();

    tmp.m00 = mat.m10; tmp.m01 = mat.m12; tmp.m02 = mat.m13;
    tmp.m10 = mat.m20; tmp.m11 = mat.m22; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m32; tmp.m22 = mat.m33;

    det -= mat.m01 * tmp.Determinant();

    tmp.m00 = mat.m10; tmp.m01 = mat.m11; tmp.m02 = mat.m13;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m23;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m33;

    det += mat.m02 * tmp.Determinant();

    tmp.m00 = mat.m10; tmp.m01 = mat.m11; tmp.m02 = mat.m12;
    tmp.m10 = mat.m20; tmp.m11 = mat.m21; tmp.m12 = mat.m22;
    tmp.m20 = mat.m30; tmp.m21 = mat.m31; tmp.m22 = mat.m32;

    det -= mat.m03 * tmp.Determinant();
    return det;
}

//-----------------------------------------------------------------------------

#endif // __LZH_MATRIX4X4_H__