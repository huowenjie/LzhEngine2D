#ifndef __LZH_VEC2D_H__
#define __LZH_VEC2D_H__

#include <cmath>

//-----------------------------------------------------------------------------
// 2 ά����
//-----------------------------------------------------------------------------

template <typename T>
class Lzh_Vec2d
{
public:
    Lzh_Vec2d()
    {
        this->x = 0;
        this->y = 0;
    }

    Lzh_Vec2d(float xy)
    {
        this->x = xy;
        this->y = xy;
    }

    Lzh_Vec2d(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

public:
    // �������
    static T Dot(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    // �������ļнǣ�����
    static float Angle(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        float len = (float)(v1.Length() * v2.Length());
        float tmp = ((float)v1.Dot(v2)) / (len);
        return std::acos(tmp);
    }

    // ������˵�ģ���� 2 άƽ���ϣ����Ǻ���������˺�ķ��򣬽�������ģ
    static T CrossValue(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

    // ������һ��������һ��������
    static Lzh_Vec2d Normalize(const Lzh_Vec2d &v)
    {
        return (v / v.Length());
    }

    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static Lzh_Vec2d Lerp(const Lzh_Vec2d &a, const Lzh_Vec2d &b, float t)
    {
        return a * (1.0f - t) + b * t;
    }

    // if a.x > b.x x => x = 0.0f ; y ͬ��
    static Lzh_Vec2d Step(const Lzh_Vec2d &a, const Lzh_Vec2d &b)
    {
        return Lzh_Vec2d((T)(a.x > b.x ? 0 : 1), (T)(a.y > b.y ? 0 : 1));
    }

public:
    // �����ӷ��ͼ���
    Lzh_Vec2d operator+(const Lzh_Vec2d &v) const
    {
        Lzh_Vec2d vec = *this;
        vec.x += v.x;
        vec.y += v.y;
        return vec;
    }

    Lzh_Vec2d operator-(const Lzh_Vec2d &v) const
    {
        Lzh_Vec2d vec = *this;
        vec.x -= v.x;
        vec.y -= v.y;
        return vec;
    }

    // ȡ������
    Lzh_Vec2d operator-() const
    {
        Lzh_Vec2d vec = *this;
        vec.x = -vec.x;
        vec.y = -vec.y;
        return vec;
    }

    // �����������
    Lzh_Vec2d operator*(T t) const
    {
        Lzh_Vec2d vec = *this;
        vec.x *= t;
        vec.y *= t;
        return vec;
    }

    friend Lzh_Vec2d operator*(T t, const Lzh_Vec2d &v)
    {
        Lzh_Vec2d vec = v;
        vec.x *= t;
        vec.y *= t;
        return vec;
    }

    // ������ʵ�����
    Lzh_Vec2d operator/(T t) const
    {
        Lzh_Vec2d vec = *this;
        vec.x /= t;
        vec.y /= t;
        return vec;
    }

    // �������������
    Lzh_Vec2d operator/(const Lzh_Vec2d &v) const
    {
        Lzh_Vec2d vec = *this;
        vec.x /= v.x;
        vec.y /= v.y;
        return vec;
    }

public:
    // ��������
    T Length() const
    {
        float val = x * x + y * y;
        return (T)std::sqrt(val);
    }

    // �������
    T Dot(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::Dot(*this, v);
    }

    // ����һ�������ļн�
    float Angle(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::Angle(*this, v);
    }

    // ����һ��������˵�ֵ
    T CrossValue(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::CrossValue(*this, v);
    }

    // ����ǰ������һ��
    void Normalize()
    {
        *this = Lzh_Vec2d::normalize(*this);
    }

public:
    T x;
    T y;
};

//-----------------------------------------------------------------------------

#endif // __LZH_VEC2D_H__
