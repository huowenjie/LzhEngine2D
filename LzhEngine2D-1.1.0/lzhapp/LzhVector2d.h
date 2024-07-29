#ifndef __LZH_VEC2D_H__
#define __LZH_VEC2D_H__

#include <cmath>

//-----------------------------------------------------------------------------
// 2 维向量
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
    // 向量点乘
    static T Dot(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    // 求向量的夹角，弧度
    static float Angle(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        float len = (float)(v1.Length() * v2.Length());
        float tmp = ((float)v1.Dot(v2)) / (len);
        return std::acos(tmp);
    }

    // 向量叉乘的模，在 2 维平面上，我们忽略向量叉乘后的方向，仅计算其模
    static T CrossValue(const Lzh_Vec2d &v1, const Lzh_Vec2d &v2)
    {
        return v1.x * v2.y - v1.y * v2.x;
    }

    // 向量归一化并返回一个新向量
    static Lzh_Vec2d Normalize(const Lzh_Vec2d &v)
    {
        return (v / v.Length());
    }

    // p = (1 - t) * a + t * b 当 t = 0 时返回 a，否则返回 b
    static Lzh_Vec2d Lerp(const Lzh_Vec2d &a, const Lzh_Vec2d &b, float t)
    {
        return a * (1.0f - t) + b * t;
    }

    // if a.x > b.x x => x = 0.0f ; y 同理
    static Lzh_Vec2d Step(const Lzh_Vec2d &a, const Lzh_Vec2d &b)
    {
        return Lzh_Vec2d((T)(a.x > b.x ? 0 : 1), (T)(a.y > b.y ? 0 : 1));
    }

public:
    // 向量加法和减法
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

    // 取反向量
    Lzh_Vec2d operator-() const
    {
        Lzh_Vec2d vec = *this;
        vec.x = -vec.x;
        vec.y = -vec.y;
        return vec;
    }

    // 向量和数相乘
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

    // 向量和实数相除
    Lzh_Vec2d operator/(T t) const
    {
        Lzh_Vec2d vec = *this;
        vec.x /= t;
        vec.y /= t;
        return vec;
    }

    // 向量和向量相除
    Lzh_Vec2d operator/(const Lzh_Vec2d &v) const
    {
        Lzh_Vec2d vec = *this;
        vec.x /= v.x;
        vec.y /= v.y;
        return vec;
    }

public:
    // 向量长度
    T Length() const
    {
        float val = x * x + y * y;
        return (T)std::sqrt(val);
    }

    // 向量点乘
    T Dot(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::Dot(*this, v);
    }

    // 和另一个向量的夹角
    float Angle(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::Angle(*this, v);
    }

    // 和另一个向量叉乘的值
    T CrossValue(const Lzh_Vec2d &v) const
    {
        return Lzh_Vec2d::CrossValue(*this, v);
    }

    // 将当前向量归一化
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
