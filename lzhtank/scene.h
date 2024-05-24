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
    void AddObjectToScene(GameObject *obj, bool isAutoDel = false);

    // 从场景移除对象
    void DelObjectFromScene(GameObject *obj);

    // 设置主相机
    void SetMainCamera(Camera *camera);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;
    std::map<std::string, GameObject *> sceneObjects;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
