#ifndef __LZH_VEC3F_H__
#define __LZH_VEC3F_H__

#include "lzh_type.h"
#include "lzh_vec2f.h"

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
    float z;
} LZH_VEC3F;

/* �������� */
LZH_API LZH_VEC3F lzh_vec3f_xyz(float x, float y, float z);

/* �������� */
LZH_API LZH_VEC3F lzh_vec3f_vec2f(const LZH_VEC2F *v, float z);

/* ������ */
LZH_API LZH_VEC3F lzh_vec3f_add(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* ������ */
LZH_API LZH_VEC3F lzh_vec3f_sub(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* ������ʵ����� */
LZH_API LZH_VEC3F lzh_vec3f_mul(const LZH_VEC3F *a, float t);

/* ������ʵ����� */
LZH_API LZH_VEC3F lzh_vec3f_div(const LZH_VEC3F *a, float t);

/* ����ȡ�� */
LZH_API LZH_VEC3F lzh_vec3f_reverse(const LZH_VEC3F *a);

/* ������һ�� */
LZH_API LZH_VEC3F lzh_vec3f_normalize(const LZH_VEC3F *a);

/* �������Բ�ֵ, p = (1 - t) * a + t * b �� t = 0 ʱ���� a�����򷵻� b */
LZH_API LZH_VEC3F lzh_vec3f_lerp(const LZH_VEC3F *a, const LZH_VEC3F *b, float t);

/* ������� */
LZH_API float lzh_vec3f_dot(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* ������� */
LZH_API LZH_VEC3F lzh_vec3f_cross(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* �������ĳ��� */
LZH_API float lzh_vec3f_length(const LZH_VEC3F *a);

/* �����������ļн� */
LZH_API float lzh_vec3f_angle(const LZH_VEC3F *a, const LZH_VEC3F *b);

/* ������������ϣ�vlist Ϊ�����б�wlist ΪȨ�б�k Ϊ���� */
LZH_API LZH_VEC3F lzh_vec3f_line_comb(const LZH_VEC3F *vlist, const float *wlist, int k);

/* ���������������������� */
LZH_API LZH_BOOL lzh_vec3f_build_basic(
    const LZH_VEC3F *a,
    const LZH_VEC3F *b,
    LZH_VEC3F *w,
    LZH_VEC3F *u,
    LZH_VEC3F *v);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_VEC3F_H__ */
