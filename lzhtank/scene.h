#ifndef __SCENE_H__
#define __SCENE_H__

#include <lzh_engine.h>
#include <string>
#include <map>
#include <vector>

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

    // ��Ӷ����������б�
    void AddObject(GameObject *obj);

    // �ͷŶ���
    void ToFreeGameObject(GameObject *obj);

    // ������ͷŵĶ���
    void ClearFreeObject();

    // ���������
    void SetMainCamera(Camera *camera);

    // ��ȡ����ָ��
    LZH_SCENE *GetSceneHandle() const;

protected:
    // ���볡������
    void InsertObject(GameObject *sceneObj);

    // �Ƴ���������
    void RemoveObject(GameObject *sceneObj);

    // ����������
    void ClearSceneObjects();

protected:
    void LastUpdate();
    static void SceneLastHandle(LZH_SCENE *scene, void *args);

protected:
    LZH_SCENE *sceneObj;
    LZH_ENGINE *engine;

    std::string sceneName;

    // ���������б�
    std::map<LZH_UINTPTR, GameObject *> sceneObjects;

    // ����׼��ɾ���б�
    std::vector<GameObject *> toFreeObjects;
};

/*===========================================================================*/

#endif /* __SCENE_H__ */
