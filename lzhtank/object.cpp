#include <lzh_object.h>
#include <lzh_transform.h>
#include <stddef.h>

#include "object.h"

/*===========================================================================*/

Object::Object(LZH_ENGINE *eg)
{
    engine = eg;
    object = lzh_object_create(eg);
    transform = lzh_object_get_transform(object);

    isAddedScene = false;
    currentScene = NULL;

    lzh_object_set_update(object, Object::UpdateTank, this);
    lzh_object_set_fixedupdate(object, Object::FixedUpdateTank, this);
}

Object::~Object()
{
    if (!isAddedScene) {
        lzh_object_destroy(object);
    }
}

void Object::SetCurrentScene(Scene *scene)
{
    currentScene = scene;
}

void Object::UpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args)
{
    if (eg && obj && args) {
        Object *inst = (Object *)args;
        inst->Update(eg);
    }
}

void Object::FixedUpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args)
{
    if (eg && obj && args) {
        Object *inst = (Object *)args;
        inst->FixedUpdate(eg);
    }
}

/*===========================================================================*/
