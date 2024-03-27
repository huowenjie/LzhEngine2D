#include <lzh_rectf.h>

/*===========================================================================*/

void lzh_rectf_init(LZH_RECTF *rect, float x, float y, float w, float h)
{
    if (rect) {
        rect->x = x;
        rect->y = y;
        rect->w = w;
        rect->h = h;
    }
}

LZH_BOOL lzh_rectf_intersection(const LZH_RECTF *a, const LZH_RECTF *b)
{
    float ar = 0.0f;
    float ab = 0.0f;
    float br = 0.0f;
    float bb = 0.0f;

    if (!a || !b) {
        return LZH_FALSE;
    }

    ar = a->x + a->w;
    ab = a->y + a->h;
    br = b->x + b->w;
    bb = b->y + b->h;
    
    if (ar < b->x || a->x > br || ab < b->y || a->y > bb) {
        return LZH_FALSE;
    }

    return LZH_TRUE;
}

/*===========================================================================*/
