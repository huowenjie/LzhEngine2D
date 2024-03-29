#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include "../component/lzh_component.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

LINK_DECLARE(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/* ����ṹ */
struct LZH_OBJECT {
    /* ���� */
    LZH_BASE base;

    /* ������ */
    LZH_OBJECT *parent;

    /* �Ӷ������� */
    LZH_OBJ_LINK *children;

    /* ������� */
    LZH_CPNT_LINK *components;

    /* ��Ⱦ�㼶 */
    int render_layer;

    /* ��Ⱦ˳�� */
    int render_sort;

    /*---------------------------------------------------*/
    /* ����ҵ�� */

    /* ������»ص��Ͳ���*/
    LZH_OBJECT_UPDATE update;
    void *update_param;

    /* �̶�ʱ����»ص��Ͳ��� */
    LZH_OBJECT_FIXEDUPDATE fixed_update;
    void *fixed_update_param;
};

/* �Ƴ��Ӷ��󣬲����ĸ��������Ϣ */
void lzh_object_remove(LZH_OBJECT *object);

/* �Ӷ���Ļص����� */
int lzh_link_object_comp(const void *obj1, const void *obj2);
void lzh_link_object_visit(const LZH_OBJ_LINK_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
