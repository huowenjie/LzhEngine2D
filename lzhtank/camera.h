#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "gameobject.h"

/*===========================================================================*/
/* ÉãÏñ»ú */
/*===========================================================================*/

class Camera : public Object
{
public:
    Camera(LZH_ENGINE *engine);
    virtual ~Camera();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_CAMERA *camera;
};

/*===========================================================================*/

#endif /* __CAMERA_H__ */
