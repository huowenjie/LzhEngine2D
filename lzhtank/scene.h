#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

class Object;
class Camera;
class Scene
{
public:
    Scene(LZH_ENGINE *eg, const std::string &name);
    ~Scene();

public:
    // ���س���
    void LoadScene();

    // ��Ӷ���������
    void AddObjectToScene(Object *obj);

    // ���������
    void SetMainCamera(Camera *camera);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
