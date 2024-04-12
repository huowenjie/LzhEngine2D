#ifndef __LZH_TEXTURE_H__
#define __LZH_TEXTURE_H__

#include "lzh_opengl.h"

/*===========================================================================*/
/* Œ∆¿Ì */
/*===========================================================================*/

typedef struct LZH_TEXTURE {
    GLuint  texid;	
    int     width;
    int     height;
    int     channels;
} LZH_TEXTURE;

LZH_TEXTURE *lzh_texture_create(const char *path);
void lzh_texture_destroy(LZH_TEXTURE *texture);

/*===========================================================================*/

#endif /* __LZH_TEXTURE_H__ */
