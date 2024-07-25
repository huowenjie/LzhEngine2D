#ifndef __LZH_RECTF_H__
#define __LZH_RECTF_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 浮点矩形 */
/*===========================================================================*/

typedef struct LZH_RECTF {
    float x, y;
    float w, h;
} LZH_RECTF;

/* 初始化矩形区域 */
LZH_API void lzh_rectf_init(LZH_RECTF *rect, float x, float y, float w, float h);

/* 判断两个矩形是否相交 */
LZH_API LZH_BOOL lzh_rectf_intersection(const LZH_RECTF *a, const LZH_RECTF *b);

/*===========================================================================*/

#endif /* __LZH_RECTF_H__ */