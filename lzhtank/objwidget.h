#ifndef __OBJWIDGET_H__
#define __OBJWIDGET_H__

#include <lzh_type.h>
#include "level.h"

/*===========================================================================*/
/* 对象组件 */
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

/* 初始化 */
void ow_init_widget(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res);

/* 初始化多图精灵 */
void ow_init_widget_images(
    OBJ_WIDGET *widget, LZH_ENGINE *engine,
    float w, float h, int type, const char *res[], int count);

/* 终止 */
void ow_quit_widget(OBJ_WIDGET *widget);

/* 销毁组件 */
void ow_destroy_widget(OBJ_WIDGET *widget);

/* 设置位置 */
void ow_set_pos(OBJ_WIDGET *widget, float x, float y);

/* 设置名称 */
void ow_set_name(OBJ_WIDGET *widget, const char *name);

/* 设置当前关卡 */
void ow_set_level(OBJ_WIDGET *widget, LEVEL *level);

/* 设置更新回调 */
void ow_set_update(
    OBJ_WIDGET *widget, LZH_OBJECT_UPDATE update, void *param);

/* 获取引擎对象 */
LZH_ENGINE *ow_get_engine(OBJ_WIDGET *widget);

/*===========================================================================*/

#endif /* __OBJWIDGET_H__ */