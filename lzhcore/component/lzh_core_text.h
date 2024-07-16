#ifndef __LZH_CORE_TEXT_H__
#define __LZH_CORE_TEXT_H__

#include <lzh_text.h>
#include "lzh_component.h"

#include "../graphic/lzh_texture.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/
/* �ı����(�ڲ�) */
/*===========================================================================*/

/* �ı�������� */
struct LZH_TEXT
{
    LZH_COMPONENT base;         /* ���������Ϣ */
    GLuint vao;                 /* ����������� */
    GLuint vbo;                 /* ���㻺����� */
    GLuint ebo;                 /* ����������� */

    FT_Face text_face;          /* ������Ϣ */
    LZH_CHARACTER *text_char;
};

/*===========================================================================*/

#endif /* __LZH_CORE_TEXT_H__ */
