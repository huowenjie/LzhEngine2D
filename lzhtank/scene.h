#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>
#include <map>

/*===========================================================================*/
/* 场景 */
/*===========================================================================*/

class Object;
class Camera;
class Scene
{
public:
    Scene(LZH_ENGINE *eg, const std::string &name);
    ~Scene();

public:
    // 加载场景
    void LoadScene();

    // 添加对象至场景
    void AddObjectToScene(Object *obj, bool isAutoDel = false);

    // 从场景移除对象
    void DelObjectFromScene(Object *obj);

    // 设置主相机
    void SetMainCamera(Camera *camera);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;
    std::map<std::string, Object *> sceneObjects;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
