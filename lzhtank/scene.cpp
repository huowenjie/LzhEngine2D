#include <lzh_scene.h>

#include "camera.h"
#include "gameobject.h"
#include "scene.h"

/*===========================================================================*/

Scene::Scene(LZH_ENGINE *eg, const std::string &name)
{
    sceneObj = lzh_scene_create(eg);
    engine = eg;
    sceneName = name;

    lzh_scene_set_name(sceneObj, name.c_str());
    lzh_scene_set_last_callback(sceneObj, Scene::SceneLastHandle, this);
}

Scene::~Scene()
{
    ClearGameObject();
}

void Scene::LoadScene()
{
    LZH_SCENE_MANAGER *manager = lzh_scene_get_manager(engine);
    if (!manager) {
        return;
    };

    lzh_scene_manager_load(manager, sceneName.c_str());
}

void Scene::AddObjectToScene(GameObject *obj)
{
    if (obj && sceneObj) {
        lzh_scene_add_object(sceneObj, obj->GetObjectHandle());
    }
}

void Scene::DelObjectFromScene(GameObject *obj)
{
    if (obj && sceneObj) {
        lzh_scene_del_object(sceneObj, obj->GetName().c_str());
    }
}

void Scene::ToFreeGameObject(GameObject *obj)
{
    if (obj) {
        std::string name = obj->GetName();
        if (!name.empty()) {
            toFreeObjects.insert(
                std::map<std::string, GameObject *>::value_type(obj->GetName(), obj));
        }
    }
}

void Scene::FreeGameObject(const std::string &name)
{
    if (!name.empty()) {
        std::map<std::string, GameObject *>::iterator it = toFreeObjects.find(name);
        if (it != toFreeObjects.end()) {
            GameObject *obj = it->second;
            if (obj) {
                delete obj;
                it->second = NULL;
            }
            toFreeObjects.erase(name);
        }
    }
}

void Scene::ClearGameObject()
{
    for (
        std::map<std::string, GameObject *>::iterator it = toFreeObjects.begin(); 
        it != toFreeObjects.end(); ++it
    ) {
        if (it->second) {
            GameObject *obj = it->second;
            delete obj;
        }
    }

    toFreeObjects.clear();
}

void Scene::LastUpdate()
{
    ClearGameObject();
}

void Scene::SceneLastHandle(LZH_SCENE *scene, void *args)
{
    if (args) {
        Scene *scene = (Scene *)args;
        scene->LastUpdate();
    }
}

void Scene::SetMainCamera(Camera *camera)
{
    if (camera) {
        lzh_scene_set_main_camera(sceneObj, camera->GetObjectHandle());
    }
}

/*===========================================================================*/
