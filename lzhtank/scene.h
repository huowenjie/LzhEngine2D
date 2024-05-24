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
    void AddObjectToScene(GameObject *obj, bool isAutoDel = false);

    // �ӳ����Ƴ�����
    void DelObjectFromScene(GameObject *obj);

    // ���������
    void SetMainCamera(Camera *camera);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;
    std::map<std::string, GameObject *> sceneObjects;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
