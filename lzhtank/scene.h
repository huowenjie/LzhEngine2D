#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>
#include <map>

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

    // 添加对象至场景
    void AddObjectToScene(GameObject *obj);

    // 从场景移除对象
    void DelObjectFromScene(GameObject *obj);

    // 释放对象
    void ToFreeGameObject(GameObject *obj);

    // 释放对象
    void FreeGameObject(const std::string &name);

    // 清理对象
    void ClearGameObject();

    // 设置主相机
    void SetMainCamera(Camera *camera);

protected:
    void LastUpdate();
    static void SceneLastHandle(LZH_SCENE *scene, void *args);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;
    std::map<std::string, GameObject *> toFreeObjects;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
