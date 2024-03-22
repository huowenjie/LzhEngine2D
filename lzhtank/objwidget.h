#ifndef __OBJWIDGET_H__
#define __OBJWIDGET_H__

#include <lzh_type.h>
#include "level.h"

/*===========================================================================*/
/* ������� */
/*===========================================================================*/

#define OBJ_TYPE_UNDEF 0
#define OBJ_TYPE_TANK 1
#define OBJ_TYPE_TURRET 2
#define OBJ_TYPE_BULLET 3
#define OBJ_TYPE_EXPLODE 4

typedef struct {
    int type;
    LZH_OBJECT *object;
    LZH_SPRITE *sprite;
    LEVEL *level;
} OBJ_WIDGET;

/* ��ʼ�� */
void ow_init_widget(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res);

/* ��ʼ����ͼ���� */
void ow_init_widget_images(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res[], int count);

/* ��ֹ */
void ow_quit_widget(OBJ_WIDGET *widget);

/* ������� */
void ow_destroy_widget(OBJ_WIDGET *widget);

/* ����λ�� */
void ow_set_pos(OBJ_WIDGET *widget, float x, float y);

/* �������� */
void ow_set_name(OBJ_WIDGET *widget, const char *name);

/* ���õ�ǰ�ؿ� */
void ow_set_level(OBJ_WIDGET *widget, LEVEL *level);

/* ���ø��»ص� */
void ow_set_update(
    OBJ_WIDGET *widget, LZH_OBJECT_UPDATE update, void *param);

/* ��ȡ������� */
LZH_ENGINE *ow_get_engine(OBJ_WIDGET *widget);

/*===========================================================================*/

#endif /* __OBJWIDGET_H__ */