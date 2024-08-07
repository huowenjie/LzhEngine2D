#ifndef __LZH_MATH_DEFINE_H__
#define __LZH_MATH_DEFINE_H__

/*===========================================================================*/
/* 常用的数学定义 */
/*===========================================================================*/

/* PI 定义 */
#define LZH_MATH_PI (3.141592654f)

/* 弧度转角度 */
#define LZH_MATH_R2A(rad) ((float)(((float)(rad)) * 57.295779513f))

/* 角度转弧度 */
#define LZH_MATH_A2R(angle) ((float)(((float)angle) * 0.01745329252f))

/* 两数取最大值 */
#define LZH_MATH_MAX(a, b) ((a) > (b) ? (a) : (b))

/* 两数取最小值 */
#define LZH_MATH_MIN(a, b) ((a) < (b) ? (a) : (b))

/*===========================================================================*/

#endif /* __LZH_MATH_DEFINE_H__ */
