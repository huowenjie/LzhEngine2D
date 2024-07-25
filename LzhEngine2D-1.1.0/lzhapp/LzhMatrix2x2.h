#ifndef __SR_MAT2X2F_H__
#define __SR_MAT2X2F_H__

#include "sr_vec2f.h"

//-----------------------------------------------------------------------------
// 2 x 2 ����������洢
//-----------------------------------------------------------------------------

class SR_Mat2x2f
{
public:
    SR_Mat2x2f();
    SR_Mat2x2f(float elem);
    SR_Mat2x2f(float *elems);
    SR_Mat2x2f(float (*elems)[2]);
    SR_Mat2x2f(const SR_Mat2x2f &mat);
    ~SR_Mat2x2f();

public:
    // ��λ����
    static SR_Mat2x2f unitMatrix();

    // �����
    static SR_Mat2x2f zeroMatrix();

    // ת�þ���
    static SR_Mat2x2f transpose(const SR_Mat2x2f &mat);

    // �����
    static SR_Mat2x2f inverse(const SR_Mat2x2f &mat);

    // 2 x 2 ����ʽֵ
    static float determinant(const SR_Mat2x2f &mat);

public:
    SR_Mat2x2f & operator=(const SR_Mat2x2f &mat);

    // �����
    SR_Mat2x2f operator+(const SR_Mat2x2f &mat) const;
    SR_Mat2x2f operator-(const SR_Mat2x2f &mat) const;

    // ����ͱ������
    SR_Mat2x2f operator*(float val) const;
    friend SR_Mat2x2f operator*(float val, const SR_Mat2x2f &mat);

    // �������
    SR_Mat2x2f operator*(const SR_Mat2x2f &mat) const;

    // ������������
    SR_Vec2f operator*(const SR_Vec2f &vec) const;

    // ����ȡֵ
    float *operator[](int i);

    // �����
    SR_Mat2x2f operator-() const;

public:
    // ת�þ���
    SR_Mat2x2f transpose() const;

    // �� 2x2 ����ʽ
    float determinant() const;

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    union {
        struct {
            float m00;
            float m01;
            float m10;
            float m11;
        };

        float mat[4];
        float matij[2][2];
    };
};

//-----------------------------------------------------------------------------

#endif // __SR_MAT2X2F_H__
