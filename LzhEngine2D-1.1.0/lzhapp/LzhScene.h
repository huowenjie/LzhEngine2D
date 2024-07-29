#if 0
#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>
#include <map>
#include <vector>
#include <vec2.hpp>
#include "object.h"

/*===========================================================================*/
/* 场景 */
/*===========================================================================*/

class GameObject;
class Camera;

class Scene : public Object
{
public:
    Scene(LZH_ENGINE *eg, const std::string &name);
    virtual ~Scene();

public:
    // 加载场景
    void LoadScene();

    // 添加对象至管理列表
    void AddObject(GameObject *obj);

    // 释放对象
    void ToFreeGameObject(GameObject *obj);

    // 清理待释放的对象
    void ClearFreeObject();

    // 设置主相机
    void SetMainCamera(Camera *camera);

    // 获取主相机对象
    Camera *GetMainCamera() const;

    // 获取场景指针
    LZH_SCENE *GetSceneHandle() const;

    // 射线检测
    GameObject *RayCastObject(
        const glm::vec2 &start,
        const glm::vec2 &end,
        glm::vec2 *point,
        glm::vec2 *normal) const;

protected:
    // 插入场景对象
    void InsertObject(GameObject *sceneObj);

    // 移除场景对象
    void RemoveObject(GameObject *sceneObj);

    // 清理场景对象
    void ClearSceneObjects();

protected:
    void LastUpdate();
    static void SceneLastHandle(LZH_SCENE *scene, void *args);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;

    // 场景对象列表
    std::map<LZH_UINTPTR, GameObject *> sceneObjects;

    // 场景准备删除列表
    std::vector<GameObject *> toFreeObjects;

    // 主相机对象
    Camera *mainCamera;
};

/*===========================================================================*/
#endif
#endif /* __SCENE_H__ */
