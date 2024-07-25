#ifndef __SR_VEC2F_H__
#define __SR_VEC2F_H__

//-----------------------------------------------------------------------------
// 2 ά����
//-----------------------------------------------------------------------------

class SR_Vec2f
{
public:
    SR_Vec2f();
    SR_Vec2f(float xy);
    SR_Vec2f(float x, float y);
    SR_Vec2f(const SR_Vec2f &v);
    ~SR_Vec2f();

public:
    // �������
    static float dot(const SR_Vec2f &v1, const SR_Vec2f &v2);

    // �������ļнǣ�����
    static float angle(const SR_Vec2f &v1, const SR_Vec2f &v2);

    // ������˵�ģ���� 2 άƽ���ϣ����Ǻ���������˺�ķ��򣬽�������ģ
    static float crossValue(const SR_Vec2f &v1, const SR_Vec2f &v2);

    // ������һ��������һ��������
    static SR_Vec2f normalize(const SR_Vec2f &v);

    // p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b
    static SR_Vec2f lerp(const SR_Vec2f &a, const SR_Vec2f &b, float t);

    // if a.x > b.x x => x = 0.0f ; y ͬ��
    static SR_Vec2f step(const SR_Vec2f &a, const SR_Vec2f &b);

public:
    SR_Vec2f & operator=(const SR_Vec2f &v);

    // �����ӷ��ͼ���
    SR_Vec2f operator+(const SR_Vec2f &v) const;
    SR_Vec2f operator-(const SR_Vec2f &v) const;

    // ȡ������
    SR_Vec2f operator-() const;

    // ������ʵ�����
    SR_Vec2f operator*(float t) const;
    friend SR_Vec2f operator*(float t, const SR_Vec2f &v);

    // ������ʵ�����
    SR_Vec2f operator/(float t) const;
    
    // �������������
    SR_Vec2f operator/(const SR_Vec2f &v) const;

    // ��������
    float length() const;

    // �������
    float dot(const SR_Vec2f &v) const;

    // ����һ�������ļн�
    float angle(const SR_Vec2f &v) const;

    // ����һ��������˵�ֵ
    float crossValue(const SR_Vec2f &v) const;

    // ����ǰ������һ��
    void normalize();

    // ��ӡ����
    void printValue(const char *title = nullptr) const;

public:
    float x;
    float y;
};

//-----------------------------------------------------------------------------

#endif // __SR_VEC2F_H__
