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

    // ��ȡ���������
    Camera *GetMainCamera() const;

    // ��ȡ����ָ��
    LZH_SCENE *GetSceneHandle() const;

    // ���߼��
    GameObject *RayCastObject(
        const glm::vec2 &start,
        const glm::vec2 &end,
        glm::vec2 *point,
        glm::vec2 *normal) const;

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

    // ���������
    Camera *mainCamera;
};

/*===========================================================================*/
#endif
#endif /* __SCENE_H__ */
