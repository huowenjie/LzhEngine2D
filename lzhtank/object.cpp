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

Object::Object(LZH_ENGINE *eg, LZH_OBJECT *obj)
{
    engine = eg;
    object = obj;
    transform = lzh_object_get_transform(object);

    isAddedScene = true;
    currentScene = NULL;

    lzh_object_set_update(object, Object::UpdateTank, this);
    lzh_object_set_fixedupdate(object, Object::FixedUpdateTank, this);
}

Object::~Object()
{
    lzh_object_set_update(object, NULL, NULL);
    lzh_object_set_fixedupdate(object, NULL, NULL);

    if (!isAddedScene) {
        lzh_object_destroy(object);
    }
}

void Object::SetCurrentScene(Scene *scene)
{
    currentScene = scene;
}

void Object::SetName(const std::string &name)
{
    if (!name.empty()) {
        lzh_object_set_name(object, name.c_str());
    }
}

std::string Object::GetName() const
{
    const char *name = lzh_object_get_name(object);
    return std::string(name);
}

void Object::SetPosition(float x, float y)
{
    if (transform) {
        lzh_transform_set_pos(transform, x, y, 0.0f);
    }
}

void Object::GetPosition(float *x, float *y)
{
    if (transform) {
        lzh_transform_get_pos(transform, x, y, NULL);
    }
}

void Object::SetRotate(float angle)
{
    if (transform) {
        lzh_transform_set_rotate_z(transform, angle);
    }
}

float Object::GetRotateAngle()
{
    if (transform) {
        return lzh_transform_get_rotate_z(transform);
    }
    return 0.0f;
}

Object *Object::FindChild(const std::string &name)
{
    if (name.empty()) {
        return NULL;
    }

    LZH_OBJECT *obj = lzh_object_find_child(object, name.c_str());
    if (!obj) {
        return NULL;
    }

    Object *newObj = new Object(engine, obj);
    newObj->currentScene = currentScene;

    return newObj;
}

Object *Object::FindChildRecursion(const std::string &name)
{
    if (name.empty()) {
        return NULL;
    }

    LZH_OBJECT *obj = lzh_object_find_child_recursion(object, name.c_str());
    if (!obj) {
        return NULL;
    }

    Object *newObj = new Object(engine, obj);
    newObj->currentScene = currentScene;

    return newObj;
}

void Object::Update(LZH_ENGINE *eg)
{
}

void Object::FixedUpdate(LZH_ENGINE *eg)
{
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
