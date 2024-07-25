#ifndef __LZH_VERTEX_H__
#define __LZH_VERTEX_H__

#include <lzh_type.h>
#include "lzh_opengl.h"

/*===========================================================================*/
/* 顶点 */
/*===========================================================================*/

/* 精灵顶点 */
typedef struct LZH_VERTEX {
    GLuint vao;                         /* 顶点数组对象 */
    GLuint vbo;                         /* 顶点缓冲对象 */
    GLuint ebo;                         /* 索引缓冲对象 */

    GLuint count;                       /* 绘制顶点数量 */
} LZH_VERTEX;

/* 精灵顶点 */
typedef LZH_VERTEX LZH_SPRITE_VERTEX;

/* 文字顶点 */
typedef LZH_VERTEX LZH_TEXT_VERTEX;

/* 创建通用精灵顶点 */
LZH_SPRITE_VERTEX *lzh_vertex_sprite();

/* 创建通用文字顶点 */
LZH_TEXT_VERTEX *lzh_vertex_text();

/* 设置文字顶点数据, (x, y) 代表的坐标系以左上角为原点 */
void lzh_vertex_text_data(
    LZH_TEXT_VERTEX *vertex, float x, float y, float w, float h);

/* 销毁顶点 */
void lzh_vertex_destroy(LZH_VERTEX *vertex);

/* 绘制顶点 */
void lzh_vertex_draw(LZH_VERTEX *vertex);
void lzh_vertex_sprite_draw(LZH_SPRITE_VERTEX *vertex);
void lzh_vertex_text_draw(LZH_TEXT_VERTEX *vertex);

/*===========================================================================*/

#endif /* __LZH_VERTEX_H__ */
