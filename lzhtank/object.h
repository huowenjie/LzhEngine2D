#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <lzh_engine.h>
#include <string>

/*===========================================================================*/
/* ���� */
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
    // ���õ�ǰ��������
    void SetCurrentScene(Scene *scene);

    // ���û�ȡ����
    void SetName(const std::string &name);
    std::string GetName() const;

    // ����λ��
    void SetPosition(float x, float y);

    // ��ȡλ��
    void GetPosition(float *x, float *y);

    // ������ת�Ƕ�
    void SetRotate(float angle);

    // ��ȡ��ת�Ƕ�
    float GetRotateAngle();

    // �����Ӷ���
    Object *FindChild(const std::string &name);

    // �ݹ�����Ӷ���
    Object *FindChildRecursion(const std::string &name);

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    static void UpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void FixedUpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);

protected:
    LZH_ENGINE *engine;
    LZH_OBJECT *object;
    LZH_TRANSFORM *transform;

    // �Ƿ����������
    bool isAddedScene;

    // ��ǰ������������
    Scene *currentScene;
};

/*===========================================================================*/

#endif /* __OBJECT_H__ */
