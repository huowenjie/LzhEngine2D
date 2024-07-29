#ifndef __LZH_MATRIX3X3_H__
#define __LZH_MATRIX3X3_H__

#include "LzhVector3d.h"

//-----------------------------------------------------------------------------
// 3 x 3 方阵或 2 x 2 齐次矩阵，行主序存储
//-----------------------------------------------------------------------------

template <typename T>
class Lzh_Mat3x3f
{
public:
    Lzh_Mat3x3f()
    {
        this->m00 = this->m11 = this->m22 = (T)1;
        this->m01 = this->m02 = (T)0;
        this->m10 = this->m12 = (T)0;
        this->m20 = this->m21 = (T)0;
    }

    Lzh_Mat3x3f(T elem)
    {
        this->m00 = this->m01 = this->m02 = elem;
        this->m10 = this->m11 = this->m12 = elem;
        this->m20 = this->m21 = this->m22 = elem;
    }

    Lzh_Mat3x3f(T *elems)
    {
        this->m00 = elems[0]; this->m01 = elems[1]; this->m02 = elems[2];
        this->m10 = elems[3]; this->m11 = elems[4]; this->m12 = elems[5];
        this->m20 = elems[6]; this->m21 = elems[7]; this->m22 = elems[8];
    }

    Lzh_Mat3x3f(T (*elems)[3])
    {
        this->m00 = elems[0][0]; this->m01 = elems[0][1]; this->m02 = elems[0][2];
        this->m10 = elems[1][0]; this->m11 = elems[1][1]; this->m12 = elems[1][2];
        this->m20 = elems[2][0]; this->m21 = elems[2][1]; this->m22 = elems[2][2];
    }

public:
    // 单位矩阵
    static Lzh_Mat3x3f UnitMatrix()
    {
        return Lzh_Mat3x3f();
    }

    // 零矩阵
    static Lzh_Mat3x3f ZeroMatrix()
    {
        return Lzh_Mat3x3f((T)0);
    }

    // 转置矩阵
    static Lzh_Mat3x3f Transpose(const Lzh_Mat3x3f &mat)
    {
        Lzh_Mat3x3f tmp(mat);
        tmp.m01 = mat.m10; tmp.m10 = mat.m01; tmp.m02 = mat.m20;
        tmp.m20 = mat.m02; tmp.m12 = mat.m21; tmp.m21 = mat.m12;
        return tmp;
    }

    // 逆矩阵
    static Lzh_Mat3x3f Inverse(const Lzh_Mat3x3f &mat);

    // 求 3 x 3 行列式
    static T Determinant(const Lzh_Mat3x3f &mat);

public:
    // 二维齐次缩放矩阵
    static Lzh_Mat3x3f ScaleMatrix(T s)
    {
        Lzh_Mat3x3f mat;

        mat.m00 = s;
        mat.m11 = s;
        return mat;
    }

    // 二维齐次旋转矩阵
    static Lzh_Mat3x3f RotateMatrix(float theta)
    {
        Lzh_Mat3x3f mat;

        mat.m00 = (T)std::cos(theta);
        mat.m01 = (T)-std::sin(theta);
        mat.m10 = (T)std::sin(theta);
        mat.m11 = (T)std::cos(theta);
        return mat;
    }

    // 二维齐次平移矩阵
    static Lzh_Mat3x3f TranslateMatrix(T x, T y)
    {
        Lzh_Mat3x3f mat;

        mat.m02 = x;
        mat.m12 = y;
        return mat;
    }

public:
    // 加
    Lzh_Mat3x3f operator+(const Lzh_Mat3x3f &mat) const
    {
        Lzh_Mat3x3f tmp(*this);

        tmp.m00 += mat.m00; tmp.m01 += mat.m01; tmp.m02 += mat.m02;
        tmp.m10 += mat.m10; tmp.m11 += mat.m11; tmp.m12 += mat.m12;
        tmp.m20 += mat.m20; tmp.m21 += mat.m21; tmp.m22 += mat.m22;

        return tmp;
    }

    // 减
    Lzh_Mat3x3f operator-(const Lzh_Mat3x3f &mat) const
    {
        Lzh_Mat3x3f tmp(*this);

        tmp.m00 -= mat.m00; tmp.m01 -= mat.m01; tmp.m02 -= mat.m02;
        tmp.m10 -= mat.m10; tmp.m11 -= mat.m11; tmp.m12 -= mat.m12;
        tmp.m20 -= mat.m20; tmp.m21 -= mat.m21; tmp.m22 -= mat.m22;

        return tmp;
    }

    // 乘
    Lzh_Mat3x3f operator*(T val) const
    {
        Lzh_Mat3x3f tmp(*this);

        tmp.m00 *= val; tmp.m01 *= val; tmp.m02 *= val;
        tmp.m10 *= val; tmp.m11 *= val; tmp.m12 *= val;
        tmp.m20 *= val; tmp.m21 *= val; tmp.m22 *= val;

        return tmp;
    }

    friend Lzh_Mat3x3f operator*(T val, const Lzh_Mat3x3f &mat)
    {
        Lzh_Mat3x3f tmp(mat);

        tmp.m00 *= val; tmp.m01 *= val; tmp.m02 *= val;
        tmp.m10 *= val; tmp.m11 *= val; tmp.m12 *= val;
        tmp.m20 *= val; tmp.m21 *= val; tmp.m22 *= val;

        return tmp;
    }

    // 除
    Lzh_Mat3x3f operator/(T val) const
    {
        Lzh_Mat3x3f tmp(*this);

        tmp.m00 /= val; tmp.m01 /= val; tmp.m02 /= val;
        tmp.m10 /= val; tmp.m11 /= val; tmp.m12 /= val;
        tmp.m20 /= val; tmp.m21 /= val; tmp.m22 /= val;

        return tmp;
    }

    // 矩阵相乘
    Lzh_Mat3x3f operator*(const Lzh_Mat3x3f &mat) const;

    // 矩阵和向量相乘
    Lzh_Vec3d<T> operator*(const Lzh_Vec3d<T> &vec) const
    {
        Lzh_Vec3d<T> tmp;

        tmp.x = m00 * vec.x + m01 * vec.y + m02 * vec.z;
        tmp.y = m10 * vec.x + m11 * vec.y + m12 * vec.z;
        tmp.z = m20 * vec.x + m21 * vec.y + m22 * vec.z;

        return tmp;
    }

    // 矩阵取值
    T *operator[](int i)
    {
        return matij[i];
    }

    // 逆矩阵
    Lzh_Mat3x3f operator-() const
    {
        return Lzh_Mat3x3f::Inverse(*this);
    }

public:
    // 转置矩阵
    Lzh_Mat3x3f Transpose() const
    {
        return Lzh_Mat3x3f::Transpose(*this);
    }

    // 求 3 x 3 行列式值
    T Determinant() const
    {
        return Lzh_Mat3x3f::Determinant(*this);
    }

public:
    union {
        /**
         * [ m00, m01, m02 ]
         * [ m10, m11, m12 ]
         * [ m20, m21, m22 ]
         */
        struct {
            T m00; T m01; T m02;
            T m10; T m11; T m12;
            T m20; T m21; T m22;
        };

        T mat[9];
        T matij[3][3];
    };
};

//-----------------------------------------------------------------------------

template<typename T>
Lzh_Mat3x3f<T> Lzh_Mat3x3f<T>::operator*(const Lzh_Mat3x3f &mat) const
{
    Lzh_Mat3x3f tmp;

    tmp.m00 = m00 * mat.m00 + m01 * mat.m10 + m02 * mat.m20;
    tmp.m01 = m00 * mat.m01 + m01 * mat.m11 + m02 * mat.m21;
    tmp.m02 = m00 * mat.m02 + m01 * mat.m12 + m02 * mat.m22;
    tmp.m10 = m10 * mat.m00 + m11 * mat.m10 + m12 * mat.m20;
    tmp.m11 = m10 * mat.m01 + m11 * mat.m11 + m12 * mat.m21;
    tmp.m12 = m10 * mat.m02 + m11 * mat.m12 + m12 * mat.m22;
    tmp.m20 = m20 * mat.m00 + m21 * mat.m10 + m22 * mat.m20;
    tmp.m21 = m20 * mat.m01 + m21 * mat.m11 + m22 * mat.m21;
    tmp.m22 = m20 * mat.m02 + m21 * mat.m12 + m22 * mat.m22;

    return tmp;
}

template<typename T>
Lzh_Mat3x3f<T> Lzh_Mat3x3f<T>::Inverse(const Lzh_Mat3x3f &mat)
{
    // 求行列式
    T det = Lzh_Mat3x3f::Determinant(mat);

    /*
     * 利用克拉默法则来求解逆矩阵
     * inverse A = adj A / det A
     */
    Lzh_Mat3x3f adj;

    adj.m00 = (mat.m11 * mat.m22 - mat.m12 * mat.m21);
    adj.m01 = (mat.m02 * mat.m21 - mat.m01 * mat.m22);
    adj.m02 = (mat.m01 * mat.m12 - mat.m02 * mat.m11);

    adj.m10 = (mat.m12 * mat.m20 - mat.m10 * mat.m22);
    adj.m11 = (mat.m00 * mat.m22 - mat.m02 * mat.m20);
    adj.m12 = (mat.m02 * mat.m10 - mat.m00 * mat.m12);

    adj.m20 = (mat.m10 * mat.m21 - mat.m11 * mat.m20);
    adj.m21 = (mat.m01 * mat.m20 - mat.m00 * mat.m21);
    adj.m22 = (mat.m00 * mat.m11 - mat.m01 * mat.m10);

    return adj / det;
}

template<typename T>
T Lzh_Mat3x3f<T>::Determinant(const Lzh_Mat3x3f &mat)
{
    T det = 
        mat.m00 * mat.m11 * mat.m22 +
        mat.m02 * mat.m10 * mat.m21 +
        mat.m01 * mat.m12 * mat.m20 -
        mat.m00 * mat.m21 * mat.m12 - 
        mat.m01 * mat.m10 * mat.m22 -
        mat.m02 * mat.m11 * mat.m20;
    return det;
}

//-----------------------------------------------------------------------------

#endif // __LZH_MATRIX3X3_H__
