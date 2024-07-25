#ifndef __SR_MAT3X3F_H__
#define __SR_MAT3X3F_H__

#include "sr_vec3f.h"

//-----------------------------------------------------------------------------
// 3 x 3 ����������洢
//-----------------------------------------------------------------------------

class SR_Mat3x3f
{
public:
    SR_Mat3x3f();
    SR_Mat3x3f(float elem);
    SR_Mat3x3f(float *elems);
    SR_Mat3x3f(float (*elems)[3]);
    SR_Mat3x3f(const SR_Mat3x3f &mat);
    ~SR_Mat3x3f();

public: // �������

    // ��λ����
    static SR_Mat3x3f unitMatrix();

    // �����
    static SR_Mat3x3f zeroMatrix();

public: // ����Ļ�������

    // ת�þ���
    static SR_Mat3x3f transpose(const SR_Mat3x3f &mat);

    // �����
    static SR_Mat3x3f inverse(const SR_Mat3x3f &mat);

    // �� 3 x 3 ����ʽ
    static float determinant(const SR_Mat3x3f &mat);

public:
    SR_Mat3x3f & operator=(const SR_Mat3x3f &v);

    // �����
    SR_Mat3x3f operator+(const SR_Mat3x3f &mat) const;
    SR_Mat3x3f operator-(const SR_Mat3x3f &mat) const;

    // ����ͱ������
    SR_Mat3x3f operator*(float val) const;
    friend SR_Mat3x3f operator*(float val, const SR_Mat3x3f &mat);

    // �������
    SR_Mat3x3f operator*(const SR_Mat3x3f &mat) const;

    // ������������
    SR_Vec3f operator*(const SR_Vec3f &vec) const;

    // ����ȡֵ
    float *operator[](int i);

    // �����
    SR_Mat3x3f operator-() const;

public:
    // ת�þ���
    SR_Mat3x3f transpose() const;

    // �� 3 x 3 ����ʽֵ
    float determinant() const;

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    union {
        /**
         * [ m00, m01, m02 ]
         * [ m10, m11, m12 ]
         * [ m20, m21, m22 ]
         */
        struct {
            float m00;
            float m01;
            float m02;
            float m10;
            float m11;
            float m12;
            float m20;
            float m21;
            float m22;
        };

        float mat[9];
        float matij[3][3];
    };
};

//-----------------------------------------------------------------------------

#endif // __SR_MAT3X3F_H__