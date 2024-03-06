#ifndef __OBJWIDGET_H__
#define __OBJWIDGET_H__

#include <lzh_type.h>

/*===========================================================================*/
/* 对象组件 */
/*===========================================================================*/

#define OBJ_TYPE_UNDEF 0
#define OBJ_TYPE_TANK 1
#define OBJ_TYPE_TURRET 1

typedef struct {
    int type;
    LZH_OBJECT *object;
    LZH_SPRITE *sprite;
} OBJ_WIDGET;

/* 初始化 */
void ow_init_widget(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res);

/* 终止 */
void ow_quit_widget(OBJ_WIDGET *widget);

/* 设置位置 */
void ow_set_pos(OBJ_WIDGET *widget, float x, float y);

/* 设置更新回调 */
void ow_set_update(
    OBJ_WIDGET *widget, LZH_OBJECT_UPDATE update, void *param);

/*===========================================================================*/

#endif /* __OBJWIDGET_H__ */