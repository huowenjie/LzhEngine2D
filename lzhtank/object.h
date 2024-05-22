#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <lzh_engine.h>
#include <string>

/*===========================================================================*/
/* 对象 */
/*===========================================================================*/

class Scene;
class Object
{
    friend class Scene;

public:
    Object(LZH_ENGINE *eg);
    Object(LZH_ENGINE *eg, LZH_OBJECT *obj);
    virtual ~Object();

public:
    // 设置当前所属场景
    void SetCurrentScene(Scene *scene);

    // 设置获取名称
    void SetName(const std::string &name);
    std::string GetName() const;

    // 设置位置
    void SetPosition(float x, float y);

    // 获取位置
    void GetPosition(float *x, float *y);

    // 设置旋转角度
    void SetRotate(float angle);

    // 获取旋转角度
    float GetRotateAngle();

    // 获取世界旋转角度
    float GetRotateWorldAngle();

    // 查找子对象
    Object *FindChild(const std::string &name);

    // 递归查找子对象
    Object *FindChildRecursion(const std::string &name);

    // 获取对象指针
    LZH_OBJECT *GetObjectHandle();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
    virtual void ColliderCb(LZH_OBJECT *self, LZH_OBJECT *target);

protected:
    static void UpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void FixedUpdateObject(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void ColliderObjectCb(LZH_OBJECT *self, LZH_OBJECT *target, void *args);

protected:
    LZH_ENGINE *engine;
    LZH_OBJECT *object;
    LZH_TRANSFORM *transform;

    // 是否被添加至场景
    bool isAddedScene;

    // 当前所属场景对象
    Scene *currentScene;
};

/*===========================================================================*/

#endif /* __OBJECT_H__ */
