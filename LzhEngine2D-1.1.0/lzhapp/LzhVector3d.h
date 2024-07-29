#ifndef __LZH_VEC3D_H__
#define __LZH_VEC3D_H__

#include "LzhVector2d.h"

//-----------------------------------------------------------------------------
// 3 ά����
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
    // �������
    static T Dot(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        T t = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        return t;
    }

    // �������
    static Lzh_Vec3d Cross(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        return Lzh_Vec3d(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    // �������ļнǣ�����
    static float Angle(const Lzh_Vec3d &v1, const Lzh_Vec3d &v2)
    {
        float len = (float)(v1.Length() * v2.Length());
        float dot = (float)v1.Dot(v2);
        return std::acos(dot / len);
    }

    // ������һ��������һ��������
    static Lzh_Vec3d Normalize(const Lzh_Vec3d &v)
    {
        T len = v.Length();
        return v / len;
    }

    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static Lzh_Vec3d Lerp(const Lzh_Vec3d &a, const Lzh_Vec3d &b, float t)
    {
        return a * (1.0f - t) + b * t;
    }

    // if a.x > b.x x => x = 0 : x = 1; y��z ͬ��
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

    // ȡ������
    Lzh_Vec3d operator-() const
    {
        return Lzh_Vec3d(-this->x, -this->y, -this->z);
    }

    // ������ʵ�����
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
    // ��������
    T Length() const
    {
        float val = x * x + y * y + z * z;
        return (T)std::sqrt(val);
    }

    // �������
    T Dot(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Dot(*this, v);
    }

    // ����һ�������ļн�
    T Angle(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Angle(*this, v);
    }

    // �������
    Lzh_Vec3d Cross(const Lzh_Vec3d &v) const
    {
        return Lzh_Vec3d::Cross(*this, v);
    }

    // ������һ��
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
