#if 0
#include <lzh_scene.h>
#include <lzh_object.h>

#include "camera.h"
#include "gameobject.h"
#include "scene.h"

/*===========================================================================*/

Scene::Scene(LZH_ENGINE *eg, const std::string &name)
{
    sceneObj = lzh_scene_create(eg);
    engine = eg;
    sceneName = name;

    mainCamera = NULL;

    lzh_scene_set_name(sceneObj, name.c_str());
    lzh_scene_set_last_callback(sceneObj, Scene::SceneLastHandle, this);
}

Scene::~Scene()
{
    ClearFreeObject();
    ClearSceneObjects();
}

void Scene::LoadScene()
{
    LZH_SCENE_MANAGER *manager = lzh_scene_get_manager(engine);
    if (!manager) {
        return;
    };

    lzh_scene_manager_load(manager, sceneName.c_str());
}

void Scene::AddObject(GameObject *obj)
{
    if (obj) {
        InsertObject(obj);
    }
}

void Scene::ToFreeGameObject(GameObject *obj)
{
    if (obj) {
        sceneObjects.erase((LZH_UINTPTR)obj);
        toFreeObjects.push_back(obj);
    }
}

void Scene::ClearFreeObject()
{
    while (!toFreeObjects.empty()) {
        GameObject *obj = toFreeObjects.back();
        if (obj) {
            delete obj;
        }
        toFreeObjects.pop_back();
    }
}

void Scene::LastUpdate()
{
    ClearFreeObject();
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
    mainCamera = camera;

    if (camera) {
        lzh_scene_set_main_camera(sceneObj, camera->GetObjectHandle());
    }
}


Camera *Scene::GetMainCamera() const
{
    return mainCamera;
}

LZH_SCENE *Scene::GetSceneHandle() const
{
    return sceneObj;
}

GameObject *Scene::RayCastObject(
    const glm::vec2 &start,
    const glm::vec2 &end,
    glm::vec2 *point,
    glm::vec2 *normal) const
{
    if (sceneObj) {
        LZH_SCENE_RAYHIT_2D hitInfo = { 0 };

        if (!lzh_scene_raycast2d(sceneObj, start.x, start.y, end.x, end.y, &hitInfo)) {
            return NULL;
        }

        if (!hitInfo.hitobj) {
            return NULL;
        }

        const char *extName = GameObject::ObjectExtName();
        GameObject *gameObj = (GameObject *)lzh_object_get_extension(hitInfo.hitobj, extName);

        if (point) {
            point->x = hitInfo.hx;
            point->y = hitInfo.hy;
        }

        if (normal) {
            normal->x = hitInfo.nx;
            normal->y = hitInfo.ny;
        }
        return gameObj;
    }
    return NULL;
}

void Scene::InsertObject(GameObject *sceneObj)
{
    if (sceneObj) {
        sceneObjects.insert(
            std::map<LZH_UINTPTR, GameObject *>::value_type((LZH_UINTPTR)sceneObj, sceneObj));
    }
}

void Scene::RemoveObject(GameObject *sceneObj)
{
    sceneObjects.erase((LZH_UINTPTR)sceneObj);
}

void Scene::ClearSceneObjects()
{
    for (
        std::map<LZH_UINTPTR, GameObject *>::iterator it = sceneObjects.begin(); 
        it != sceneObjects.end(); ++it
    ) {
        if (it->second) {
            GameObject *obj = it->second;

            if (!obj->IsChild()) {
                delete obj;
            }
        }
    }
    sceneObjects.clear();
}
#endif
/*===========================================================================*/
