#include <lzh_sprite.h>
#include <lzh_object.h>

#include "globalres.h"
#include "explode.h"
#include "scene.h"

/*===========================================================================*/

Explode::Explode(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_Explode;
    explodeSp = NULL;

    int count = get_tank_explode_count();
    const char **imgs = get_tank_explode_path();

    explodeSp = lzh_sprite_create_from_images(eg, imgs, count);
    lzh_object_add_component(object, explodeSp);

    char name[32];
    static int code = 1;

    sprintf(name, "Explode%d", code++);
    lzh_object_set_name(object, name);

    lzh_sprite_set_keyframe(explodeSp, count - 1, Explode::LastFrameCb, this);
}

Explode::~Explode()
{
    int count = get_tank_explode_count();
    lzh_sprite_set_keyframe(explodeSp, count - 1, NULL, NULL);
}

void Explode::LastFrame()
{
    currentScene->ToFreeGameObject(this);
}

LZH_UINT32 Explode::LastFrameCb(void *args)
{
    if (args) {
        Explode *exp = (Explode *)args;
        exp->LastFrame();
    }
    return 0;
}

/*===========================================================================*/
