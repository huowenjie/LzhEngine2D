#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* ��ײ�������(�ڲ�) */
/*===========================================================================*/

/* ��ײ������� */
struct LZH_COLLIDER {
    LZH_COMPONENT base;             /* ���������Ϣ */

    LZH_B2_BODY *b2_body;           /* 2d �������������� */
    LZH_B2_FIXUTRE *b2_fixture;     /* 2d ��������������� */

    LZH_COLLIDER_CB start_contact;  /* ��ʼ��ײ�ص� */
    LZH_COLLIDER_CB end_contact;    /* ������ײ�ص� */

    void *start_contact_args;       /* ��ʼ��ײ�ص����� */
    void *end_contact_args;         /* ������ײ�ص����� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
