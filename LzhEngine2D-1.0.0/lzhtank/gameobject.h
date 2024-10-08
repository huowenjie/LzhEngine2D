#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <lzh_engine.h>
#include <string>
#include <glm.hpp>

#include "object.h"

/*===========================================================================*/
/* 对象 */
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
        OT_Explode,
        OT_UI
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
    // 设置当前所属场景
    void SetCurrentScene(Scene *scene);

    // 设置获取名称
    void SetName(const std::string &name);
    std::string GetName() const;

    // 平移
    void Translate(float x, float y);

    // 设置位置
    void SetPosition(float x, float y);

    // 设置深度
    void SetDepth(float depth);

    // 获取位置
    void GetPosition(float *x, float *y);
    void GetPosition(glm::vec2 &pos);

    // 获取当前前进向量
    void GetForward(glm::vec2 &forward);

    // 设置旋转角度
    void SetRotate(float angle);

    // 设置缩放
    void SetScale(float x, float y);

    // 获取旋转角度
    float GetRotateAngle();

    // 获取世界旋转角度
    float GetRotateWorldAngle();

public:
    // 添加子对象
    void AddChild(GameObject *child);

    // 查找子对象
    GameObject *FindChild(const std::string &name);

    // 递归查找子对象
    GameObject *FindChildRecursion(const std::string &name);

    // 是否当前对象是子对象
    bool IsChild() const;

public:
    // 获取对象指针
    LZH_OBJECT *GetObjectHandle() const;

    // 获取变换组件指针
    LZH_TRANSFORM *GetTransform() const;

    // 获取对象类型
    ObjectType GetObjectType() const;

    // 获取对象角色
    RoleType GetObjectRole() const;

    // 设置获取目标角色
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

    // 当前所属场景对象
    Scene *currentScene;

    // 目标角色合集
    LZH_UINT32 targetRole;
};

/*===========================================================================*/

#endif /* __GAMEOBJECT_H__ */
