#ifndef __LZH_VEC4F_H__
#define __LZH_VEC4F_H__

#include "lzh_vec3f.h"

/*===========================================================================*/
/* ��ά�������/��ά���� */
/*===========================================================================*/

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} LZH_VEC4F;

/* �������� */
LZH_API LZH_VEC4F lzh_vec4f_xyzw(float x, float y, float z, float w);

/* �������� */
LZH_API LZH_VEC4F lzh_vec4f_vec3f(const LZH_VEC3F *v, float w);

/* ������ */
LZH_API LZH_VEC4F lzh_vec4f_add(const LZH_VEC4F *a, const LZH_VEC4F *b);

/* ������ */
LZH_API LZH_VEC4F lzh_vec4f_sub(const LZH_VEC4F *a, const LZH_VEC4F *b);

/* ������ */
LZH_API LZH_VEC4F lzh_vec4f_mul(const LZH_VEC4F *a, float t);

/* ������������ */
LZH_API LZH_VEC4F lzh_vec4f_div(const LZH_VEC4F *a, float t);

/* ����ȡ�� */
LZH_API LZH_VEC4F lzh_vec4f_reverse(const LZH_VEC4F *a);

/* �������Բ�ֵ p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b */
LZH_API LZH_VEC4F lzh_vec4f_lerp(const LZH_VEC4F *a, const LZH_VEC4F *b, float t);

/* ����������� vlist Ϊ�����б�wlist ΪȨ�б�k Ϊ���� */
LZH_API LZH_VEC4F lzh_vec4f_line_comb(const LZH_VEC4F *vlist, const float *wlist, int k);

/* 4d ������γ��� */
LZH_API LZH_VEC4F lzh_vec4f_homogen_div(const LZH_VEC4F *a);

/*===========================================================================*/

#endif /* __LZH_VEC4F_H__ */
