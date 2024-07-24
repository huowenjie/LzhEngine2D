#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider2d.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* ��ײ�嶨��(�ڲ�) */
/*===========================================================================*/

/* ��ײ����� */
struct LZH_COLLIDER2D {
    LZH_HASH_CODE hash;                 /* �����ϣֵ */

    LZH_RIGIDBODY2D *rigidbody;         /* ���� rigidbody */
    LZH_B2_FIXUTRE *b2_fixture;         /* 2d �̶���� */

    LZH_COLLIDER2D_CB start_contact;    /* ��ʼ��ײ�ص� */
    LZH_COLLIDER2D_CB end_contact;      /* ������ײ�ص� */

    void *start_contact_args;           /* ��ʼ��ײ�ص����� */
    void *end_contact_args;             /* ������ײ�ص����� */
};

/* �Ƴ���ײ�� */
void lzh_collider2d_remove(LZH_COLLIDER2D *collider2d);

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
