#include <lzh_object.h>
#include <lzh_transform.h>
#include <stddef.h>

#include "scene.h"
#include "gameobject.h"

/*===========================================================================*/

/* 将对象指针保存在 LZH_OBJECT 的扩展区 */
#define OBJECT_INSTANCE "object"

GameObject::GameObject(LZH_ENGINE *eg, Scene *scene)
{
    objType = OT_Object;
    engine = eg;
    object = lzh_object_create(eg);
    transform = lzh_object_get_transform(object);
    currentScene = scene;

    InitGameObject();
}

GameObject::GameObject(LZH_ENGINE *eg, LZH_OBJECT *obj, Scene *scene)
{
    objType = OT_Object;
    engine = eg;
    object = obj;
    transform = lzh_object_get_transform(object);
    currentScene = scene;

    InitGameObject();
}

GameObject::~GameObject()
{
    QuitGameObject();
}

void GameObject::SetCurrentScene(Scene *scene)
{
    currentScene = scene;
}

void GameObject::SetName(const std::string &name)
{
    if (!name.empty()) {
        lzh_object_set_name(object, name.c_str());
    }
}

std::string GameObject::GetName() const
{
    const char *name = lzh_object_get_name(object);
    // if (name && *name) {
    //     return std::string();
    // }
    return std::string(name);
}

void GameObject::SetPosition(float x, float y)
{
    if (transform) {
        lzh_transform_set_x(transform, x);
        lzh_transform_set_y(transform, y);
    }
}

void GameObject::SetDepth(float depth)
{
    if (transform) {
        lzh_transform_set_z(transform, depth);
    }
}

void GameObject::GetPosition(float *x, float *y)
{
    if (transform) {
        lzh_transform_get_pos(transform, x, y, NULL);
    }
}

void GameObject::SetRotate(float angle)
{
    if (transform) {
        lzh_transform_set_rotate_z(transform, angle);
    }
}

float GameObject::GetRotateAngle()
{
    if (transform) {
        return lzh_transform_get_rotate_z(transform);
    }
    return 0.0f;
}

float GameObject::GetRotateWorldAngle()
{
    if (transform) {
        return lzh_transform_get_rotate_wz(transform);
    }
    return 0.0f;
}

GameObject *GameObject::FindChild(const std::string &name)
{
    if (name.empty()) {
        return NULL;
    }

    LZH_OBJECT *obj = lzh_object_find_child(object, name.c_str());
    if (!obj) {
        return NULL;
    }

    GameObject *newObj = new GameObject(engine, obj, currentScene);
    newObj->currentScene = currentScene;

    return newObj;
}

GameObject *GameObject::FindChildRecursion(const std::string &name)
{
    if (name.empty()) {
        return NULL;
    }

    LZH_OBJECT *obj = lzh_object_find_child_recursion(object, name.c_str());
    if (!obj) {
        return NULL;
    }

    GameObject *newObj = new GameObject(engine, obj, currentScene);
    newObj->currentScene = currentScene;

    return newObj;
}

LZH_OBJECT *GameObject::GetObjectHandle() const
{
    return object;
}

GameObject::ObjectType GameObject::GetObjectType() const
{
    return objType;
}

void GameObject::InitGameObject()
{
    if (currentScene) {
        currentScene->AddObjectToScene(this);        
    }

    if (object) {
        lzh_object_set_update(object, GameObject::UpdateObject, this);
        lzh_object_set_fixedupdate(object, GameObject::FixedUpdateObject, this);
        lzh_object_add_extension(object, OBJECT_INSTANCE, this);
    }
}

void GameObject::QuitGameObject()
{
    if (object) {
        lzh_object_del_extension(object, OBJECT_INSTANCE);
        lzh_object_set_update(object, NULL, NULL);
        lzh_object_set_fixedupdate(object, NULL, NULL);
    }

    if (currentScene) {
        currentScene->DelObjectFromScene(this);
    }
}

void GameObject::Update(LZH_ENGINE *eg)
{
}

void GameObject::FixedUpdate(LZH_ENGINE *eg)
{
}

void GameObject::ColliderCb(GameObject *self, GameObject *target)
{

}

void GameObject::UpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args)
{
    if (eg && obj && args) {
        GameObject *inst = (GameObject *)args;
        inst->Update(eg);
    }
}

void GameObject::FixedUpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args)
{
    if (eg && obj && args) {
        GameObject *inst = (GameObject *)args;
        inst->FixedUpdate(eg);
    }
}

void GameObject::ColliderObjectCb(LZH_OBJECT *self, LZH_OBJECT *target, void *args)
{
    if (self && target && args) {
        GameObject *inst = (GameObject *)args;
        GameObject *selfObj = (GameObject *)lzh_object_get_extension(self, OBJECT_INSTANCE);
        GameObject *targObj = (GameObject *)lzh_object_get_extension(target, OBJECT_INSTANCE);

        inst->ColliderCb(selfObj, targObj);
    }
}

/*===========================================================================*/
