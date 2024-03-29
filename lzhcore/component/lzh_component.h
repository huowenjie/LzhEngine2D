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

typedef struct LZH_COMPONENT LZH_COMPONENT;

struct LZH_COMPONENT {
    /* ���� */
    LZH_BASE base;

    /* ������� */
    LZH_UINT32 type;

    /* ���� object */
    LZH_OBJECT *object;

    /* ����Ƴ��ص� */
    void (*remove_component)(LZH_COMPONENT *);
};

LINK_DECLARE(LZH_CPNT, lzh_cpnt, LZH_COMPONENT *)

/* ��������Ļص����� */
int lzh_link_cpnt_comp(const void *cpnt1, const void *cpnt2);
void lzh_link_cpnt_visit(const LZH_CPNT_LINK_NODE *node, void *args);

/* ��������л�ȡ��Ӧ���͵���� */
LZH_COMPONENT *lzh_link_cpnt_get_type(LZH_CPNT_LINK *link, LZH_UINT32 type);

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
