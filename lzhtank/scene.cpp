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
}

Scene::~Scene()
{
    for (
        std::map<std::string, GameObject *>::iterator it = sceneObjects.begin(); 
        it != sceneObjects.end(); ++it
    ) {
        if (it->second) {
            GameObject *obj = it->second;
            delete obj;
        }
    }

    sceneObjects.clear();
    //lzh_scene_destroy(sceneObj);
}

void Scene::LoadScene()
{
    LZH_SCENE_MANAGER *manager = lzh_scene_get_manager(engine);
    if (!manager) {
        return;
    };

    lzh_scene_manager_load(manager, sceneName.c_str());
}

void Scene::AddObjectToScene(GameObject *obj, bool isAutoDel)
{
    if (obj && sceneObj) {
        obj->isAddedScene = true;
        lzh_scene_add_object(sceneObj, obj->object);

        if (isAutoDel) {
            std::string name = obj->GetName();
            sceneObjects.insert(std::map<std::string, GameObject *>::value_type(name, obj));
        }
    }
}

void Scene::DelObjectFromScene(GameObject *obj)
{
    if (obj && sceneObj) {
        lzh_scene_del_object(sceneObj, obj->GetName().c_str());
    }
}

void Scene::SetMainCamera(Camera *camera)
{
    if (camera) {
        lzh_scene_set_main_camera(sceneObj, camera->object);
    }
}

/*===========================================================================*/
