#ifndef __LZH_COLLIDER_H__
#define __LZH_COLLIDER_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ��ײ��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ��ײ������ */
typedef enum LZH_COLLIDER_TYPE {
    UNDEF = 0,
    BOX_2D,
    CIRCLE_2D
} LZH_COLLIDER_TYPE;

/* ������ײ�� 2D */
typedef struct LZH_COLLIDER_BOX_2D {
    float cx;       /* ���ĵ�ֲ����� x */
    float cy;       /* ���ĵ�ֲ����� y */
    float w;        /* ���еĿ�� w */
    float h;        /* ���еĸ߶� h */
} LZH_COLLIDER_BOX_2D;

/* Բ����ײ�� 2D */
typedef struct LZH_COLLIDER_CIRCLE_2D {
    float cx;       /* Բ������ x */
    float cy;       /* Բ������ y */
    float r;        /* �뾶 */
} LZH_COLLIDER_CIRCLE_2D;

/* ��ײ������ */
typedef struct LZH_COLLIDER_PARAM {
    LZH_COLLIDER_TYPE type;

    union {
        LZH_COLLIDER_BOX_2D box2d;
        LZH_COLLIDER_CIRCLE_2D circle2d;
    };
} LZH_COLLIDER_PARAM;

/* ��ײ�ص� */
typedef void (*LZH_COLLIDER_CB)(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

/* ������ײ��� */
LZH_API LZH_COLLIDER *lzh_collider_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* ������ײ��� */
LZH_API void lzh_collider_destroy(LZH_COLLIDER *collider);

/* ������ײ������ */
LZH_API void lzh_collider_set_param(
    LZH_COLLIDER *collider, const LZH_COLLIDER_PARAM *param);

/* ���ÿ�ʼ��ײ�ص� */
LZH_API void lzh_collider_set_start_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args);

/* ���ý�����ײ�ص� */
LZH_API void lzh_collider_set_end_contact(
    LZH_COLLIDER *collider, LZH_COLLIDER_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_COLLIDER_H__ */
