#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include <lzh_vec2f.h>

#include "lzh_core_engine.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

LINK_DECLARE(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/* ����ṹ */
struct LZH_OBJECT {
    /* ������ */
    LZH_CONTEXT context;

    /* �������� */
    char *name;

    /* ������»ص��Ͳ���*/
    LZH_OBJECT_UPDATE update;
    void *update_param;

    /* �̶�ʱ����»ص��Ͳ��� */
    LZH_OBJECT_FIXEDUPDATE fixed_update;
    void *fixed_update_param;

    /* ������ */
    LZH_OBJECT *parent;

    /* �Ӷ������� */
    LZH_OBJ_LINK *children;

    /* ������� */
    LZH_CPNT_LINK *components;
};

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
