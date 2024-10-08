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

    int count = GetTankExplodeCount();
    const char **imgs = GetTankExplodePath();

    explodeSp = lzh_sprite_create_from_images(eg, object, imgs, count);

    char name[32];
    static int code = 1;

    sprintf(name, "Explode%d", code++);
    lzh_object_set_name(object, name);

    lzh_sprite_set_keyframe(explodeSp, count - 1, Explode::LastFrameCb, this);
}

Explode::~Explode()
{
    int count = GetTankExplodeCount();
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
