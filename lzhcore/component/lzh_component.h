#ifndef __LZH_COMPONENT_H__
#define __LZH_COMPONENT_H__

#include <lzh_type.h>
#include <lzh_rbtree.h>

#include "../lzh_base.h"

/*===========================================================================*/
/* ��� */
/*===========================================================================*/

#define LZH_CPNT_UNDEF          0x00000000U /* δ�������� */
#define LZH_CPNT_TRANSFORM      0x00000001U /* �任��� */
#define LZH_CPNT_CAMERA         0x00000002U /* ������ */
#define LZH_CPNT_SPRITE         0x00000003U /* ������� */
#define LZH_CPNT_COLLIDER       0x00000004U /* ��ײ��� */

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

/**
 * ���������
 * 
 * LZH_CPNT_RB_NODE
 * LZH_CPNT_RB_TREE
 * 
 * lzh_cpnt_rb_create
 * lzh_cpnt_rb_destroy
 * lzh_cpnt_rb_insert
 * lzh_cpnt_rb_delete
 * lzh_cpnt_rb_find
 * lzh_cpnt_rb_iterate
 */
RBTREE_DECLARE(LZH_CPNT, lzh_cpnt, LZH_UINT32, LZH_COMPONENT *)

void lzh_cpnt_init(LZH_COMPONENT *cpnt, LZH_UINT32 type, LZH_OBJECT *object);
void lzh_cpnt_quit(LZH_COMPONENT *cpnt);
void lzh_cpnt_destroy(LZH_COMPONENT *cpnt);

/* ��������Ļص����� */
int lzh_cpnt_rb_comp(const void *cpnt1, const void *cpnt2);
void lzh_cpnt_rb_visit(const LZH_CPNT_RB_NODE *node, void *args);

/* ������»ص� */
void lzh_cpnt_rb_visit_update(const LZH_CPNT_RB_NODE *node, void *args);
void lzh_cpnt_rb_visit_fixedupdate(const LZH_CPNT_RB_NODE *node, void *args);
void lzh_cpnt_rb_visit_draw(const LZH_CPNT_RB_NODE *node, void *args);

/* ��������л�ȡ��Ӧ���͵���� */
LZH_COMPONENT *lzh_cpnt_get_type(LZH_CPNT_RB_TREE *tree, LZH_UINT32 type);

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
