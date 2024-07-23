#ifndef __LZH_COLLIDER2D_H__
#define __LZH_COLLIDER2D_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ��ײ�� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ��ײ������ */
typedef enum LZH_COLLIDER2D_TYPE {
    UNDEF = 0,
    CT_BOX_2D,
    CT_CIRCLE_2D
} LZH_COLLIDER2D_TYPE;

/* ��ײ�ص� */
typedef void (*LZH_COLLIDER2D_CB)(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

/* ������ײ��� */
LZH_API LZH_COLLIDER2D *lzh_collider2d_create(LZH_RIGIDBODY2D *body);

/* ������ײ��� */
LZH_API void lzh_collider2d_destroy(LZH_COLLIDER2D *collider);

/* ������ײ������ */
LZH_API void lzh_collider2d_set_type(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_TYPE type);

/* ���÷�����ײ���������ײ����״��������״������Ч */
LZH_API void lzh_collider2d_set_rect(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h);

/* ����Բ����ײ���������ײ����״��������״������Ч */
LZH_API void lzh_collider2d_set_circle(
    LZH_COLLIDER2D *collider, float cx, float cy, float r);

/* ���ÿ�ʼ��ײ�ص� */
LZH_API void lzh_collider2d_set_start_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args);

/* ���ý�����ײ�ص� */
LZH_API void lzh_collider2d_set_end_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_COLLIDER_H__ */
