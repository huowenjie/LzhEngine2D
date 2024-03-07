#ifndef __BULLET_H__
#define __BULLET_H__

#include "objwidget.h"

/*===========================================================================*/
/* bullet */
/*===========================================================================*/

typedef struct {
    OBJ_WIDGET widget;
    OBJ_WIDGET *from;
} BULLET;

BULLET *blt_create_bullet(LZH_ENGINE *engine, float w, float h);
void blt_destroy_bullet(BULLET *bullet);

/* ÒÆ¶¯ */
void blt_move_forward(BULLET *bullet, float speed);

/* bonnnnn! */
void blt_explode(BULLET *bullet);

/*===========================================================================*/

#endif /* __BULLET_H__ */