#ifndef __LZH_VEC3D_H__
#define __LZH_VEC3D_H__

#include "LzhVector2d.h"

//-----------------------------------------------------------------------------
// 3 维向量
//-----------------------------------------------------------------------------

template <typename T>
class Lzh_Vec3d
{
public:
    Lzh_Vec3d()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Lzh_Vec3d(T xyz)
    {
        this->x = xyz;
        this->y = xyz;
        this->z = xyz;
    }

    Lzh_Vec3d(const Lzh_Vec2d<T> &v, T z = 0)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = z;
    }

    Lzh_Vec3d(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

public:
    // 向量点乘
    static T Dot(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        T t = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        return t;
    }

    // 向量叉乘
    static Lzh_Vec3d Cross(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        return Lzh_Vec3d(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    // 求向量的夹角，弧度
    static float Angle(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        float len = (float)(v1.Length() * v2.Length());
        float dot = (float)v1.Dot(v2);
        return std::acos(dot / len);
    }

    // 向量归一化并返回一个新向量
    static Lzh_Vec3d Normalize(const Lzh_Vec3d &v)
    {
        T len = v.Length();
        return v / len;
    }

    // p = (1 - t) * a + t * b 当 t = 0 时返回 a，否则返回 b
    static Lzh_Vec3d Lerp(const Lzh_Vec3d &a, const Lzh_Vec3d &b, float t)
    {
        return a * (1.0f - t) + b * t;
    }

    // if a.x > b.x x => x = 0 : x = 1; y、z 同理
    static Lzh_Vec3d Step(const Lzh_Vec3d &a, const Lzh_Vec3d &b)
    {
        return Lzh_Vec3d(
            (T)(a.x > b.x ? 0 : 1),
            (T)(a.y > b.y ? 0 : 1),
            (T)(a.z > b.z ? 0 : 1));
    }

public:
    Lzh_Vec3d operator+(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d(this->x + v.x, this->y + v.y, this->z + v.z);
    }

    Lzh_Vec3d operator-(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d(this->x - v.x, this->y - v.y, this->z - v.z);
    }

    // 取反向量
    Lzh_Vec3d operator-() const
    {
        return Lzh_Vec3d(-this->x, -this->y, -this->z);
    }

    // 向量和实数相乘
    Lzh_Vec3d operator*(T t) const
    {
        return Lzh_Vec3d(this->x * t, this->y * t, this->z * t);
    }

    friend Lzh_Vec3d operator*(T t, const Lzh_Vec3d &v)
    {
        return Lzh_Vec3d(v.x * t, v.y * t, v.z * t);
    }

    Lzh_Vec3d operator/(T t) const
    {
        return Lzh_Vec3d(this->x / t, this->y / t, this->z / t);
    }

public:
    // 向量长度
    T Length() const
    {
        float val = x * x + y * y + z * z;
        return (T)std::sqrt(val);
    }

    // 向量点乘
    T Dot(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Dot(*this, v);
    }

    // 和另一个向量的夹角
    T Angle(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Angle(*this, v);
    }

    // 向量叉乘
    Lzh_Vec3d Cross(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Cross(*this, v);
    }

    // 向量归一化
    void Normalize()
    {
        *this = Lzh_Vec3d::Normalize(*this);
    }

public:
    T x;
    T y;
    T z;
};

//-----------------------------------------------------------------------------

#endif // __LZH_VEC3D_H__
