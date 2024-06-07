#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <lzh_engine.h>
#include <string>
#include <glm.hpp>

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
        OT_Enemy,
        OT_Camera,
        OT_Bullet,
        OT_Explode
    };

    enum RoleType {
        RT_None = 0x00000000U,
        RT_Player = 0x00000001U,
        RT_Enemy = 0x00000002U,
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

    // ƽ��
    void Translate(float x, float y);

    // ����λ��
    void SetPosition(float x, float y);

    // �������
    void SetDepth(float depth);

    // ��ȡλ��
    void GetPosition(float *x, float *y);
    void GetPosition(glm::vec2 &pos);

    // ��ȡ��ǰǰ������
    void GetForward(glm::vec2 &forward);

    // ������ת�Ƕ�
    void SetRotate(float angle);

    // ��������
    void SetScale(float x, float y);

    // ��ȡ��ת�Ƕ�
    float GetRotateAngle();

    // ��ȡ������ת�Ƕ�
    float GetRotateWorldAngle();

public:
    // ����Ӷ���
    void AddChild(GameObject *child);

    // �����Ӷ���
    GameObject *FindChild(const std::string &name);

    // �ݹ�����Ӷ���
    GameObject *FindChildRecursion(const std::string &name);

    // �Ƿ�ǰ�������Ӷ���
    bool IsChild() const;

public:
    // ��ȡ����ָ��
    LZH_OBJECT *GetObjectHandle() const;

    // ��ȡ�任���ָ��
    LZH_TRANSFORM *GetTransform() const;

    // ��ȡ��������
    ObjectType GetObjectType() const;

    // ��ȡ�����ɫ
    RoleType GetObjectRole() const;

    // ���û�ȡĿ���ɫ
    void SetTargetRole(LZH_UINT32 roles);
    LZH_UINT32 GetTargetRole() const;

public:
    static const char *ObjectExtName();

protected:
    void InitGameObject();
    void QuitGameObject();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(GameObject *self, GameObject *target);
    virtual void ColliderEndCb(GameObject *self, GameObject *target);

protected:
    static void UpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void FixedUpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void ColliderObjectCb(LZH_OBJECT *self, LZH_OBJECT *target, void *args);
    static void ColliderObjectEndCb(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

protected:
    ObjectType objType;
    RoleType roleType;
    
    LZH_ENGINE *engine;
    LZH_OBJECT *object;
    LZH_TRANSFORM *transform;

    // ��ǰ������������
    Scene *currentScene;

    // Ŀ���ɫ�ϼ�
    LZH_UINT32 targetRole;
};

/*===========================================================================*/

#endif /* __GAMEOBJECT_H__ */
