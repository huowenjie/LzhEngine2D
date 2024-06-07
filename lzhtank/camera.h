#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gameobject.h"

/*===========================================================================*/
/* ÉãÏñ»ú */
/*===========================================================================*/

class Camera : public GameObject
{
public:
    Camera(LZH_ENGINE *engine, Scene *scene);
    virtual ~Camera();

public:
    float GetViewWidth() const;
    float GetViewHeight() const;

protected:
    LZH_CAMERA *camera;
};

/*===========================================================================*/

#endif /* __CAMERA_H__ */
