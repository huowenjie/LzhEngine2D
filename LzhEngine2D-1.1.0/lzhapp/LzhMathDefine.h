#ifndef __LZH_MATH_DEFINE_H__
#define __LZH_MATH_DEFINE_H__

/*===========================================================================*/
/* ���õ���ѧ���� */
/*===========================================================================*/

/* PI ���� */
#define LZH_MATH_PI (3.141592654f)

/* ����ת�Ƕ� */
#define LZH_MATH_R2A(rad) ((float)(((float)(rad)) * 57.295779513f))

/* �Ƕ�ת���� */
#define LZH_MATH_A2R(angle) ((float)(((float)angle) * 0.01745329252f))

/* ����ȡ���ֵ */
#define LZH_MATH_MAX(a, b) ((a) > (b) ? (a) : (b))

/* ����ȡ��Сֵ */
#define LZH_MATH_MIN(a, b) ((a) < (b) ? (a) : (b))

/*===========================================================================*/

#endif /* __LZH_MATH_DEFINE_H__ */