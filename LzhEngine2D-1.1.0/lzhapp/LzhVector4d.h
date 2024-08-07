
#ifndef __LZH_VECTOR4D_H__
#define __LZH_VECTOR4D_H__

#include "LzhVector3d.h"

//-----------------------------------------------------------------------------
// 3 ά��������� 4 ά����
//-----------------------------------------------------------------------------

/**
 * 4 ά����û�� 3 ά�����е�ˡ���˵ȵķ���������Ҫ���� 3 ά����任����οռ�Ĳü���
 * ƽ�����ڶ������ģ�͵Ĳ�������Ӧ�� LzhVector3d ���� LzhVector2d Ϊ��
 */
template <typename T>
class Lzh_Vec4d
{
public:
    Lzh_Vec4d()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }

    Lzh_Vec4d(T xyz, T w)
    {
        this->x = xyz;
        this->y = xyz;
        this->z = xyz;
        this->w = w;
    }

    Lzh_Vec4d(const Lzh_Vec3d<T> &v, T w)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = w;
    }
    
    Lzh_Vec4d(T x, T y, T z, T w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

public:
    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static Lzh_Vec4d Lerp(const Lzh_Vec4d &a, const Lzh_Vec4d &b, float t)
    {
        return a * (1.0f - t) + b * t;
    }

    // if a.x > b.x x => x = 0 : x = 1; y��z��w ͬ��
    static Lzh_Vec4d Step(const Lzh_Vec4d &a, const Lzh_Vec4d &b)
    {
        return Lzh_Vec4d(
            (T)(a.x > b.x ? 0 : 1),
            (T)(a.y > b.y ? 0 : 1),
            (T)(a.z > b.z ? 0 : 1),
            (T)(a.w > b.w ? 0 : 1)
        );
    }

public:
    Lzh_Vec4d operator+(const Lzh_Vec4d &v) const
    {
        return Lzh_Vec4d(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
    }

    Lzh_Vec4d operator-(const Lzh_Vec4d &v) const
    {
        return Lzh_Vec4d(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
    }

    Lzh_Vec4d operator-() const
    {
        return Lzh_Vec4d(-this->x, -this->y, -this->z, -this->w);
    }

    Lzh_Vec4d operator*(T t) const
    {
        return Lzh_Vec4d(this->x * t, this->y * t, this->z * t, this->w * t);
    }

    friend Lzh_Vec4d operator*(T t, const Lzh_Vec4d &v)
    {
        return Lzh_Vec4d(v.x * t, v.y * t, v.z * t, v.w * t);
    }

    Lzh_Vec4d operator/(T t) const
    {
        return Lzh_Vec4d(this->x / t, this->y / t, this->z / t, this->w / t);
    }

public:
    // ��γ���
    void homogenDivide()
    {
        x /= w;
        y /= w;
        z /= w;
        w = (T)1;
    }

public:
    T x;
    T y;
    T z;
    T w;
};

//-----------------------------------------------------------------------------

#endif // __LZH_VECTOR4D_H__
