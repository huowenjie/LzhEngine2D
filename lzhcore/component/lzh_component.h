#ifndef __LZH_COMPONENT_H__
#define __LZH_COMPONENT_H__

#include <lzh_type.h>
#include <lzh_link.h>

#include "../lzh_base.h"

/*===========================================================================*/
/* ��� */
/*===========================================================================*/

#define LZH_CPNT_UNDEF      0x00000000U /* δ�������� */
#define LZH_CPNT_TRANSFORM  0x00000001U /* �任��� */
#define LZH_CPNT_SPRITE     0x00000002U /* ������� */

typedef struct LZH_COMPONENT {
    /* ���� */
    LZH_BASE base;

    /* ������� */
    LZH_UINT32 type;

    /* ���� object */
    LZH_OBJECT *object;
} LZH_COMPONENT;

LINK_DECLARE(LZH_CPNT, lzh_cpnt, LZH_COMPONENT *)

/* ������Ļص����� */
int lzh_link_cpnts_comp(const void *str1, const void *str2);
void lzh_link_cpnts_visit(const LZH_CPNT_LINK_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
