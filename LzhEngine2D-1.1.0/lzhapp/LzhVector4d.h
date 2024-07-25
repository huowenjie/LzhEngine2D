#ifndef __SR_VEC4F_H__
#define __SR_VEC4F_H__

#include "sr_vec3f.h"

//-----------------------------------------------------------------------------
// 3 ά��������� 4 ά����
//-----------------------------------------------------------------------------

/**
 * 4 ά����û�� 3 ά�����е�ˡ���˵ȵķ���������Ҫ���� 3 ά����任����οռ�Ĳü���
 * ƽ�����ڶ������ģ�͵Ĳ�������Ӧ�� SR_Vec3f ���� SR_Vec2f Ϊ��
 */
class SR_Vec4f
{
public:
    SR_Vec4f();
    SR_Vec4f(float xyz, float w);
    SR_Vec4f(const SR_Vec3f &v, float w = 1.0f);
    SR_Vec4f(float x, float y, float z, float w);
    SR_Vec4f(const SR_Vec4f &v);
    ~SR_Vec4f();

public:
    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static SR_Vec4f lerp(const SR_Vec4f &a, const SR_Vec4f &b, float t);

public:
    SR_Vec4f & operator=(const SR_Vec4f &v);

    // �����ӷ��ͼ���
    SR_Vec4f operator+(const SR_Vec4f &v) const;
    SR_Vec4f operator-(const SR_Vec4f &v) const;

    // ȡ������
    SR_Vec4f operator-() const;

    // ������ʵ�����
    SR_Vec4f operator*(float t) const;
    friend SR_Vec4f operator*(float t, const SR_Vec4f &v);

    // ������ʵ�����
    SR_Vec4f operator/(float t) const;

    // ��γ���
    void homogenDivide();

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    float x;
    float y;
    float z;
    float w;
};

#endif // __SR_VEC4F_H__
