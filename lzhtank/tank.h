#ifndef __TANK_H__
#define __TANK_H__

#include <lzh_type.h>

/*===========================================================================*/
/* tank */
/*===========================================================================*/

typedef struct {
    LZH_OBJECT *object;
    LZH_SPRITE *sprite;
} TANK;

TANK *tk_create_tank(LZH_ENGINE *engine, float w, float h);
void tk_destroy_tank(TANK *tank);

void tk_set_pos(TANK *tank, float x, float y);

/*===========================================================================*/

#endif /* __TANK_H__ */