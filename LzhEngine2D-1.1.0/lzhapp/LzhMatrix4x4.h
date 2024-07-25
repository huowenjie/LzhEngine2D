#ifndef __SR_MAT4X4F_H__
#define __SR_MAT4X4F_H__

#include "sr_vec4f.h"

//-----------------------------------------------------------------------------
// 4 x 4 ����
//-----------------------------------------------------------------------------

class SR_Mat4x4f
{
public:
    SR_Mat4x4f();
    SR_Mat4x4f(float elem);
    SR_Mat4x4f(float *elems);
    SR_Mat4x4f(float (*elems)[4]);
    SR_Mat4x4f(const SR_Mat4x4f &mat);
    ~SR_Mat4x4f();

public: // ���õ� 3D ���Ա任����

    // ���ű任
    static SR_Mat4x4f scaleMatrix(float sx, float sy, float sz);

    // Χ�� z �����ת����ת����
    static SR_Mat4x4f rotateZMatrix(float theta);

    // Χ�� X �����ת����ת����
    static SR_Mat4x4f rotateXMatrix(float theta);

    // Χ�� Y �����ת����ת����
    static SR_Mat4x4f rotateYMatrix(float theta);

    // ƽ�ƾ���
    static SR_Mat4x4f translateMatrix(float dx, float dy, float dz);

    /**
     * �����ͶӰ����
     * �� [xl, xh] x [yl, yh] x [zl, zh] ͶӰ�� [xpl, xph] x [ypl, yph] x [zpl, zph]
     * 
     * l �� h �����˴��任���ڵİ�Χ��
     * lp �� hp ������Ŀ�괰�ڵİ�Χ��
     * 
     * l ��ֵΪ xmin ymin zmin
     * h ��ֵΪ xmax ymax zmax
     * 
     * lp �� hp ͬ��
     */
    static SR_Mat4x4f volumeMapMatrix(
        const SR_Vec3f &l,
        const SR_Vec3f &h,
        const SR_Vec3f &lp,
        const SR_Vec3f &hp
    );

    /**
     * ����׼������ͶӰ����Ļ�ռ�-�ӿڱ任
     * 
     * width ��Ļ��ȣ����أ�
     * height ��Ļ�߶ȣ����أ�
     */
    static SR_Mat4x4f viewportMatrix(int width, int height);

    /**
     * ������Ӿ��任����
     * 
     * pos �����λ��
     * target Ŀ��λ��
     */
    static SR_Mat4x4f cameraMatrix(const SR_Vec3f &pos, const SR_Vec3f &target);

    /**
     * ͸��ͶӰ����
     * 
     * ������� [xl, xh] x [yl, yh] x [zl, zh] �е�����
     * ����͸�ӱ任��ͬʱͶӰ���淶������ϵͳ [-1, 1] ��
     */
    static SR_Mat4x4f perspectiveMatrix(const SR_Vec3f &l, const SR_Vec3f &h);

    /**
     * ����ͶӰ����
     * 
     * ������� [xl, xh] x [yl, yh] x [zl, zh] �е�����
     * ���������任��ͬʱͶӰ���淶������ϵͳ [-1, 1] ��
     */
    static SR_Mat4x4f orthoMatrix(const SR_Vec3f &l, const SR_Vec3f &h);

public:
    // ��λ����
    static SR_Mat4x4f unitMatrix();

    // �����
    static SR_Mat4x4f zeroMatrix();

    // ת�þ���
    static SR_Mat4x4f transpose(const SR_Mat4x4f &mat);

    // �����
    static SR_Mat4x4f inverse(const SR_Mat4x4f &mat);

    // 4x4 ����ʽ
    static float determinant(const SR_Mat4x4f &mat);

public:
    SR_Mat4x4f & operator=(const SR_Mat4x4f &v);

    // �����
    SR_Mat4x4f operator+(const SR_Mat4x4f &mat) const;
    SR_Mat4x4f operator-(const SR_Mat4x4f &mat) const;

    // ����ͱ������
    SR_Mat4x4f operator*(float val) const;
    friend SR_Mat4x4f operator*(float val, const SR_Mat4x4f &mat);

    // �������
    SR_Mat4x4f operator*(const SR_Mat4x4f &mat) const;

    // ������������
    SR_Vec4f operator*(const SR_Vec4f &vec) const;

    // ����ȡֵ
    float *operator[](int i);

    // �����
    SR_Mat4x4f operator-() const;

public:
    // ת�þ���
    SR_Mat4x4f transpose() const;

    // �� 4 x 4 ����ʽ
    float determinant() const;

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    union {
        /**
         * [ m00, m01, m02, m03 ]
         * [ m10, m11, m12, m13 ]
         * [ m20, m21, m22, m23 ]
         * [ m30, m31, m32, m33 ]
         */
        struct {
            float m00;
            float m01;
            float m02;
            float m03;
            float m10;
            float m11;
            float m12;
            float m13;
            float m20;
            float m21;
            float m22;
            float m23;
            float m30;
            float m31;
            float m32;
            float m33;
        };

        float mat[16];
        float matij[4][4];
    };
};

//-----------------------------------------------------------------------------

#endif // __SR_MAT4X4F_H__