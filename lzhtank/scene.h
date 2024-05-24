#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>
#include <map>

#include "object.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

class GameObject;
class Camera;
class Scene : public Object
{
public:
    Scene(LZH_ENGINE *eg, const std::string &name);
    virtual ~Scene();

public:
    // ���س���
    void LoadScene();

    // ��Ӷ���������
    void AddObjectToScene(GameObject *obj);

    // �ӳ����Ƴ�����
    void DelObjectFromScene(GameObject *obj);

    // �ͷŶ���
    void ToFreeGameObject(GameObject *obj);

    // �ͷŶ���
    void FreeGameObject(const std::string &name);

    // �������
    void ClearGameObject();

    // ���������
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
