#include <lzh_scene.h>

#include "camera.h"
#include "object.h"
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

void Scene::AddObjectToScene(Object *obj)
{
    if (obj && sceneObj) {
        obj->isAddedScene = true;
        lzh_scene_add_object(sceneObj, obj->object);
    }
}

void Scene::SetMainCamera(Camera *camera)
{
    if (camera) {
        lzh_scene_set_main_camera(sceneObj, camera->object);
    }
}

/*===========================================================================*/
