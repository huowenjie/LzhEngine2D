#ifndef __LZH_MATRIX2X2_H__
#define __LZH_MATRIX2X2_H__

#include "LzhVector2d.h"

//-----------------------------------------------------------------------------
// 2 x 2 方阵，行主序存储
//-----------------------------------------------------------------------------

template <typename T>
class Lzh_Mat2x2
{
public:
    Lzh_Mat2x2()
    {
        this->m00 = (T)1;
        this->m01 = (T)0;
        this->m10 = (T)0;
        this->m11 = (T)1;
    }

    Lzh_Mat2x2(T elem)
    {
        this->m00 = elem;
        this->m01 = elem;
        this->m10 = elem;
        this->m11 = elem;
    }

    Lzh_Mat2x2(T *elems)
    {
        this->m00 = elems[0];
        this->m01 = elems[1];
        this->m10 = elems[2];
        this->m11 = elems[3];
    }

    Lzh_Mat2x2(T (*elems)[2])
    {
        this->m00 = elems[0][0];
        this->m01 = elems[0][1];
        this->m10 = elems[1][0];
        this->m11 = elems[1][1];
    }

public:
    // 单位矩阵
    static Lzh_Mat2x2 UnitMatrix()
    {
        return Lzh_Mat2x2();
    }

    // 零矩阵
    static Lzh_Mat2x2 ZeroMatrix()
    {
        return Lzh_Mat2x2((T)0);
    }

    // 转置矩阵
    static Lzh_Mat2x2 Transpose(const Lzh_Mat2x2 &mat)
    {
        Lzh_Mat2x2 tmp(mat);
        tmp.m01 = mat.m10;
        tmp.m10 = mat.m01;
        return tmp;
    }

    // 逆矩阵
    static Lzh_Mat2x2 Inverse(const Lzh_Mat2x2 &mat)
    {
        T det = mat.m00 * mat.m11 - mat.m01 * mat.m10;

        Lzh_Mat2x2 tmp;
        tmp.m00 = mat.m11;
        tmp.m01 = -mat.m01;
        tmp.m10 = -mat.m10;
        tmp.m11 = mat.m00;

        return tmp / det;
    }

    // 2 x 2 行列式值
    static T Determinant(const Lzh_Mat2x2 &mat)
    {
        return mat.m00 * mat.m11 - mat.m01 * mat.m10;
    }

public:
    Lzh_Mat2x2 operator+(const Lzh_Mat2x2 &mat) const
    {
        Lzh_Mat2x2 tmp(*this);

        tmp.m00 += mat.m00;
        tmp.m01 += mat.m01;
        tmp.m10 += mat.m10;
        tmp.m11 += mat.m11;

        return tmp;
    }

    Lzh_Mat2x2 operator-(const Lzh_Mat2x2 &mat) const
    {
        Lzh_Mat2x2 tmp(*this);

        tmp.m00 -= mat.m00;
        tmp.m01 -= mat.m01;
        tmp.m10 -= mat.m10;
        tmp.m11 -= mat.m11;

        return tmp;
    }

    Lzh_Mat2x2 operator*(T val) const
    {
        Lzh_Mat2x2 tmp(*this);

        tmp.m00 *= val;
        tmp.m01 *= val;
        tmp.m10 *= val;
        tmp.m11 *= val;

        return tmp;
    }

    friend Lzh_Mat2x2 operator*(T val, const Lzh_Mat2x2 &mat)
    {
        Lzh_Mat2x2 tmp(mat);

        tmp.m00 *= val;
        tmp.m01 *= val;
        tmp.m10 *= val;
        tmp.m11 *= val;

        return tmp;
    }

    Lzh_Mat2x2 operator/(T val) const
    {
        Lzh_Mat2x2 tmp(*this);

        tmp.m00 /= val;
        tmp.m01 /= val;
        tmp.m10 /= val;
        tmp.m11 /= val;

        return tmp;
    }

    Lzh_Mat2x2 operator*(const Lzh_Mat2x2 &mat) const
    {
        Lzh_Mat2x2 tmp;

        tmp.m00 = m00 * mat.m00 + m01 * mat.m10;
        tmp.m01 = m00 * mat.m01 + m01 * mat.m11;
        tmp.m10 = m10 * mat.m00 + m11 * mat.m10;
        tmp.m11 = m10 * mat.m01 + m11 * mat.m11;

        return tmp;
    }

    Lzh_Vec2d<T> operator*(const Lzh_Vec2d<T> &vec) const
    {
        Lzh_Vec2d<T> tmp;

        tmp.x = m00 * vec.x + m01 * vec.y;
        tmp.y = m10 * vec.x + m11 * vec.y;

        return tmp;
    }

    // 矩阵取值
    T *operator[](int i)
    {
        return matij[i];
    }

    // 逆矩阵
    Lzh_Mat2x2 operator-() const
    {
        return Lzh_Mat2x2::Inverse(*this);
    }

public:
    // 转置矩阵
    Lzh_Mat2x2 Transpose() const
    {
        return Lzh_Mat2x2::Transpose(*this);
    }

    // 求 2x2 行列式
    T Determinant() const
    {
        return Lzh_Mat2x2::Determinant(*this);
    }

public:
    union {
        struct {
            T m00;
            T m01;
            T m10;
            T m11;
        };

        T mat[4];
        T matij[2][2];
    };
};

//-----------------------------------------------------------------------------

#endif // __LZH_MATRIX2X2_H__
