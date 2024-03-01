#ifndef __LZH_VEC2F_H__
#define __LZH_VEC2F_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ��ά���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    float x;
    float y;
} LZH_VEC2F;

/* �������� */
LZH_API LZH_VEC2F lzh_vec2f_xy(float x, float y);

/* ������ */
LZH_API LZH_VEC2F lzh_vec2f_add(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* ������ */
LZH_API LZH_VEC2F lzh_vec2f_sub(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* ������ʵ����� */
LZH_API LZH_VEC2F lzh_vec2f_mul(const LZH_VEC2F *a, float t);

/* ������ʵ����� */
LZH_API LZH_VEC2F lzh_vec2f_div(const LZH_VEC2F *a, float t);

/* ����ȡ�� */
LZH_API LZH_VEC2F lzh_vec2f_reverse(const LZH_VEC2F *a);

/* ������һ�� */
LZH_API LZH_VEC2F lzh_vec2f_normalize(const LZH_VEC2F *a);

/* �������Բ�ֵ, p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b */
LZH_API LZH_VEC2F lzh_vec2f_lerp(const LZH_VEC2F *a, const LZH_VEC2F *b, float t);

/* ������� */
LZH_API float lzh_vec2f_dot(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* ������˵�ģ���� 2 άƽ���ϣ����Ǻ���������˺�ķ��򣬽�������ģ */
LZH_API float lzh_vec2f_cross(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* �������ĳ��� */
LZH_API float lzh_vec2f_length(const LZH_VEC2F *a);

/* �����������ļн� */
LZH_API float lzh_vec2f_angle(const LZH_VEC2F *a, const LZH_VEC2F *b);

/* ������������ϣ�vlist Ϊ�����б�wlist ΪȨ�б�k Ϊ���� */
LZH_API LZH_VEC2F lzh_vec2f_line_comb(const LZH_VEC2F *vlist, const float *wlist, int k);

/* �жϵ� p �Ƿ��������� abc �� */
LZH_API LZH_BOOL lzh_vec2f_inside_triangle(
    const LZH_VEC2F *a,
    const LZH_VEC2F *b,
    const LZH_VEC2F *c,
    const LZH_VEC2F *p);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_VEC2F_H__ */
