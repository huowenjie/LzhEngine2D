#ifndef __OBJWIDGET_H__
#define __OBJWIDGET_H__

#include <lzh_type.h>

/*===========================================================================*/
/* ������� */
/*===========================================================================*/

#define OBJ_TYPE_UNDEF 0
#define OBJ_TYPE_TANK 1
#define OBJ_TYPE_TURRET 1

typedef struct {
    int type;
    LZH_OBJECT *object;
    LZH_SPRITE *sprite;
} OBJ_WIDGET;

/* ��ʼ�� */
void ow_init_widget(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res);

/* ��ֹ */
void ow_quit_widget(OBJ_WIDGET *widget);

/* ����λ�� */
void ow_set_pos(OBJ_WIDGET *widget, float x, float y);

/* ���ø��»ص� */
void ow_set_update(
    OBJ_WIDGET *widget, LZH_OBJECT_UPDATE update, void *param);

/*===========================================================================*/

#endif /* __OBJWIDGET_H__ */