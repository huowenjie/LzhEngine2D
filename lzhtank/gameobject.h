#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <lzh_engine.h>
#include <string>
#include "object.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

class Scene;
class GameObject : public Object
{
public:
    enum ObjectType {
        OT_Object = 0,
        OT_Player,
        OT_Tank,
        OT_Camera,
        OT_Explode
    };

public:
    GameObject(LZH_ENGINE *eg, Scene *scene);
    GameObject(LZH_ENGINE *eg, LZH_OBJECT *obj, Scene *scene);
    virtual ~GameObject();

public:
    // ���õ�ǰ��������
    void SetCurrentScene(Scene *scene);

    // ���û�ȡ����
    void SetName(const std::string &name);
    std::string GetName() const;

    // ����λ��
    void SetPosition(float x, float y);

    // �������
    void SetDepth(float depth);

    // ��ȡλ��
    void GetPosition(float *x, float *y);

    // ������ת�Ƕ�
    void SetRotate(float angle);

    // ��ȡ��ת�Ƕ�
    float GetRotateAngle();

    // ��ȡ������ת�Ƕ�
    float GetRotateWorldAngle();

    // �����Ӷ���
    GameObject *FindChild(const std::string &name);

    // �ݹ�����Ӷ���
    GameObject *FindChildRecursion(const std::string &name);

    // ��ȡ����ָ��
    LZH_OBJECT *GetObjectHandle() const;

    // ��ȡ��������
    ObjectType GetObjectType() const;

protected:
    void InitGameObject();
    void QuitGameObject();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(GameObject *self, GameObject *target);

protected:
    static void UpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void FixedUpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void ColliderObjectCb(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

protected:
    ObjectType objType;
    LZH_ENGINE *engine;
    LZH_OBJECT *object;
    LZH_TRANSFORM *transform;

    // ��ǰ������������
    Scene *currentScene;
};

/*===========================================================================*/

#endif /* __GAMEOBJECT_H__ */