#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider.h>

#include "../tool/lzh_quadtree.h"
#include "lzh_component.h"

/*===========================================================================*/
/* ��ײ�������(�ڲ�) */
/*===========================================================================*/

/* ��ײ������� */
struct LZH_COLLIDER {
    LZH_COMPONENT base;             /* ���������Ϣ */
    LZH_QUAD_TREE *quad;            /* �Ĳ��� */

    LZH_COLLIDER_PARAM param;       /* ������� */
    LZH_COLLIDER_CB callback;       /* ��ײ�ص� */
    void *args;                     /* �ص����� */
};

/* ��ȡ��ײ���� */
LZH_RECTF lzh_collider_rectf(LZH_COLLIDER *collider);

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
