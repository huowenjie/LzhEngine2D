#ifndef __LZH_VERTEX_H__
#define __LZH_VERTEX_H__

#include <lzh_type.h>
#include "lzh_opengl.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

/* ���鶥�� */
typedef struct LZH_VERTEX {
    GLuint vao;                         /* ����������� */
    GLuint vbo;                         /* ���㻺����� */
    GLuint ebo;                         /* ����������� */

    GLuint count;                       /* ���ƶ������� */
} LZH_VERTEX;

/* ���鶥�� */
typedef LZH_VERTEX LZH_SPRITE_VERTEX;

/* ���ֶ��� */
typedef LZH_VERTEX LZH_TEXT_VERTEX;

/* ����ͨ�þ��鶥�� */
LZH_SPRITE_VERTEX *lzh_vertex_sprite();

/* ����ͨ�����ֶ��� */
LZH_TEXT_VERTEX *lzh_vertex_text();

/* �������ֶ�������, (x, y) ���������ϵ�����Ͻ�Ϊԭ�� */
void lzh_vertex_text_data(
    LZH_TEXT_VERTEX *vertex, float x, float y, float w, float h);

/* ���ٶ��� */
void lzh_vertex_destroy(LZH_VERTEX *vertex);

/* ���ƶ��� */
void lzh_vertex_draw(LZH_VERTEX *vertex);
void lzh_vertex_sprite_draw(LZH_SPRITE_VERTEX *vertex);
void lzh_vertex_text_draw(LZH_TEXT_VERTEX *vertex);

/*===========================================================================*/

#endif /* __LZH_VERTEX_H__ */
