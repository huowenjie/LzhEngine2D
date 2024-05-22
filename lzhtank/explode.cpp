#include <lzh_sprite.h>
#include <lzh_object.h>

#include "globalres.h"
#include "explode.h"

/*===========================================================================*/

Explode::Explode(LZH_ENGINE *eg) : Object(eg)
{
    explodeSp = NULL;

    int count = get_tank_explode_count();
    const char **imgs = get_tank_explode_path();

    explodeSp = lzh_sprite_create_from_images(eg, imgs, count);
    lzh_object_add_component(object, explodeSp);
}

Explode::~Explode()
{
}

/*===========================================================================*/
