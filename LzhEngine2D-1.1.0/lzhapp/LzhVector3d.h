#ifndef __SR_VEC3F_H__
#define __SR_VEC3F_H__

#include "sr_vec2f.h"

//-----------------------------------------------------------------------------
// 3 ά����
//-----------------------------------------------------------------------------

class SR_Vec3f
{
public:
    SR_Vec3f();
    SR_Vec3f(float xyz);
    SR_Vec3f(const SR_Vec2f &v, float z = 0.0f);
    SR_Vec3f(float x, float y, float z);
    SR_Vec3f(const SR_Vec3f &v);
    ~SR_Vec3f();

public:
    // �������
    static float dot(const SR_Vec3f &v1, const SR_Vec3f &v2);

    // �������
    static SR_Vec3f cross(const SR_Vec3f &v1, const SR_Vec3f &v2);

    // ������˵�ģ
    static float crossValue(const SR_Vec3f &v1, const SR_Vec3f &v2);

    // �������ļнǣ�����
    static float angle(const SR_Vec3f &v1, const SR_Vec3f &v2);

    // ������һ��������һ��������
    static SR_Vec3f normalize(const SR_Vec3f &v);

    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static SR_Vec3f lerp(const SR_Vec3f &a, const SR_Vec3f &b, float t);

public:
    SR_Vec3f & operator=(const SR_Vec3f &v);

    // �����ӷ��ͼ���
    SR_Vec3f operator+(const SR_Vec3f &v) const;
    SR_Vec3f operator-(const SR_Vec3f &v) const;

    // ȡ������
    SR_Vec3f operator-() const;

    // ������ʵ�����
    SR_Vec3f operator*(float t) const;
    friend SR_Vec3f operator*(float t, const SR_Vec3f &v);

    // ������ʵ�����
    SR_Vec3f operator/(float t) const;

    // ��������
    float length() const;

    // �������
    float dot(const SR_Vec3f &v) const;

    // ����һ�������ļн�
    float angle(const SR_Vec3f &v) const;

    // ����һ��������˵�ֵ
    float crossValue(const SR_Vec3f &v) const;

    // �������
    SR_Vec3f cross(const SR_Vec3f &v) const;

    // ����ǰ������һ��
    void normalize();

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    float x;
    float y;
    float z;
};

//-----------------------------------------------------------------------------

#endif // __SR_VEC3F_H__
