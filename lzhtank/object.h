#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <lzh_engine.h>

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

class Scene;
class Object
{
    friend class Scene;

public:
    Object(LZH_ENGINE *eg);
    ~Object();

protected:
    virtual void Update(LZH_ENGINE *eg) = 0;
    virtual void FixedUpdate(LZH_ENGINE *eg) = 0;

protected:
    static void UpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);
    static void FixedUpdateTank(LZH_ENGINE *eg, LZH_OBJECT *obj, void *args);

protected:
    LZH_OBJECT *object;
    LZH_TRANSFORM *transform;

    /* �Ƿ���������� */
    bool isAddedScene;
};

/*===========================================================================*/

#endif /* __OBJECT_H__ */
