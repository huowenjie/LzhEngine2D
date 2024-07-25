#ifndef __LZH_CORE_COLLIDER_H__
#define __LZH_CORE_COLLIDER_H__

#include <lzh_collider2d.h>

#include "lzh_component.h"
#include "../box2d/lzh_b2_api.h"

/*===========================================================================*/
/* ��ײ�嶨��(�ڲ�) */
/*===========================================================================*/

/* ��ײ����� */
struct LZH_COLLIDER2D {
    int id;                             /* �����ʶ */

    LZH_RIGIDBODY2D *rigidbody;         /* ���� rigidbody */
    LZH_B2_FIXUTRE *b2fixture;         /* 2d �̶���� */

    LZH_COLLIDER2D_CB start_contact;    /* ��ʼ��ײ�ص� */
    LZH_COLLIDER2D_CB end_contact;      /* ������ײ�ص� */

    void *start_contact_args;           /* ��ʼ��ײ�ص����� */
    void *end_contact_args;             /* ������ײ�ص����� */
};

/* �Ƴ���ײ�� */
void lzh_collider2d_remove(LZH_COLLIDER2D *collider);

/* ������ص������� */
void lzh_collider2d_load(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body);

/* ����Ӷ������Ƴ� */
void lzh_collider2d_unload(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body);

/* ���� box2d ��״ */
void lzh_collider2d_create_box2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h);

/* ���� circle2d ��״ */
void lzh_collider2d_create_circle2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float r);

/*===========================================================================*/

#endif /* __LZH_CORE_COLLIDER_H__ */
