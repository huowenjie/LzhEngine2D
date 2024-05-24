#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gameobject.h"

/*===========================================================================*/
/* ����� */
/*===========================================================================*/

class Camera : public GameObject
{
public:
    Camera(LZH_ENGINE *engine, Scene *scene);
    virtual ~Camera();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_CAMERA *camera;
};

/*===========================================================================*/

#endif /* __CAMERA_H__ */
