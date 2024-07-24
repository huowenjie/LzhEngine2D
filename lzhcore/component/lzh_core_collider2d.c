#include <lzh_mem.h>
#include "lzh_core_collider2d.h"

/*===========================================================================*/

void lzh_collider2d_remove(LZH_COLLIDER2D *collider2d)
{
    //lzh_collider_b2_unload(collider, cpnt->object);
    LZH_FREE(collider2d);
}

/*===========================================================================*/
