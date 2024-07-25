#ifndef __LZH_TEXTURE_H__
#define __LZH_TEXTURE_H__

#include <lzh_type.h>
#include "lzh_opengl.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

/* ͼƬ���� */
typedef struct LZH_TEXTURE {
    GLuint  texid;	    /* ���� id */
    int     width;      /* ������ */
    int     height;     /* ����߶� */
    int     channels;   /* ͨ�� */
} LZH_TEXTURE;

/* �ַ����� */
typedef struct LZH_CHARACTER {
    LZH_TEXTURE base;
    int     bearing_x;  /* ԭ�������λͼ��ˮƽλ�� */
    int     bearing_y;  /* ԭ�������λͼ�Ĵ�ֱλ�� */
    int     advance;    /* ԭ�㵽��һ������ԭ���ˮƽ���� */
    int     unicode;    /* ��ǰ�ַ��� unicode ���� */
} LZH_CHARACTER;

/* ����ͼƬ���� */
LZH_TEXTURE *lzh_texture_create(const char *path);

/* ����ͼƬ���� */
void lzh_texture_destroy(LZH_TEXTURE *texture);

/* �������� */
void lzh_texture_active(LZH_TEXTURE *texture);

/*===========================================================================*/

/* �����ַ����� */
LZH_CHARACTER *lzh_character_create(
    const LZH_DATA *bitmap, int w, int h, int bx, int by, int advance, int unicode);

/* �����ַ����� */
void lzh_character_destroy(LZH_CHARACTER *character);

/*===========================================================================*/

#endif /* __LZH_TEXTURE_H__ */
