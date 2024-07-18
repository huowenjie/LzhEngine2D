#ifndef __LZH_CORE_TEXT_H__
#define __LZH_CORE_TEXT_H__

#include <lzh_text.h>
#include <lzh_rbtree.h>

#include "lzh_component.h"

#include "../graphic/lzh_texture.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/
/* �ı����(�ڲ�) */
/*===========================================================================*/

RBTREE_DECLARE(LZH_TEXT, lzh_text, int, LZH_CHARACTER *)

/* �ı�������� */
struct LZH_TEXT
{
    LZH_COMPONENT base;             /* ���������Ϣ */

    FT_Face text_face;              /* ������Ϣ */
    LZH_TEXT_RB_TREE *characters;   /* �ַ������� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_TEXT_H__ */
