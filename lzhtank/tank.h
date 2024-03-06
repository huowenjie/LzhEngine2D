#ifndef __TANK_H__
#define __TANK_H__

#include "objwidget.h"

/*===========================================================================*/
/* tank */
/*===========================================================================*/

typedef struct {
    OBJ_WIDGET widget;
} TURRET;

typedef struct {
    OBJ_WIDGET widget;
    TURRET *turret;
} TANK;

TANK *tk_create_tank(LZH_ENGINE *engine, float w, float h);
void tk_destroy_tank(TANK *tank);

/* 设置位置 */
void tk_set_pos(TANK *tank, float x, float y);

/* 移动和旋转 */
void tk_move_forward(TANK *tank, float speed);
void tk_move_backward(TANK *tank, float speed);
void tk_rotate_left(TANK *tank, float speed);
void tk_rotate_right(TANK *tank, float speed);

/*===========================================================================*/

#endif /* __TANK_H__ */