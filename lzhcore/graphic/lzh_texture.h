#ifndef __LZH_TEXTURE_H__
#define __LZH_TEXTURE_H__

#include "lzh_opengl.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

typedef struct LZH_TEXTURE
{
    GLuint  textureId;	
    GLint   format;
    int     width;
    int     height;
} LZH_TEXTURE;

LZH_TEXTURE *lzh_texture_create(const char *path);
void lzh_texture_destroy(LZH_TEXTURE *texture);

/*===========================================================================*/

#endif /* __LZH_TEXTURE_H__ */
