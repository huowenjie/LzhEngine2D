#ifndef __LZH_TEXTURE_H__
#define __LZH_TEXTURE_H__

#include <lzh_type.h>
#include "lzh_opengl.h"

/*===========================================================================*/
/* 纹理 */
/*===========================================================================*/

/* 图片纹理 */
typedef struct LZH_TEXTURE {
    GLuint  texid;	    /* 纹理 id */
    int     width;      /* 纹理宽度 */
    int     height;     /* 纹理高度 */
    int     channels;   /* 通道 */
} LZH_TEXTURE;

/* 字符纹理 */
typedef struct LZH_CHARACTER {
    LZH_TEXTURE base;
    int     bearing_x;  /* 原点相对于位图的水平位置 */
    int     bearing_y;  /* 原点相对于位图的垂直位置 */
    int     advance;    /* 原点到下一个字形原点的水平距离 */
    int     unicode;    /* 当前字符的 unicode 编码 */
} LZH_CHARACTER;

/* 创建图片纹理 */
LZH_TEXTURE *lzh_texture_create(const char *path);

/* 销毁图片纹理 */
void lzh_texture_destroy(LZH_TEXTURE *texture);

/* 激活纹理 */
void lzh_texture_active(LZH_TEXTURE *texture);

/*===========================================================================*/

/* 创建字符纹理 */
LZH_CHARACTER *lzh_character_create(
    const LZH_DATA *bitmap, int w, int h, int bx, int by, int advance, int unicode);

/* 销毁字符纹理 */
void lzh_character_destroy(LZH_CHARACTER *character);

/*===========================================================================*/

#endif /* __LZH_TEXTURE_H__ */
