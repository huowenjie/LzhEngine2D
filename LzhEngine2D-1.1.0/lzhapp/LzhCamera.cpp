#include <lzh_object.h>
#include <lzh_camera.h>
#include <lzh_transform.h>

#include "camera.h"

/*===========================================================================*/

#define VIEW_WIDTH 32.0f
#define VIEW_HIEGHT 24.0f;

Camera::Camera(LZH_ENGINE *eg, Scene *scene) : GameObject(eg, scene)
{
    objType = OT_Camera;
    camera = lzh_camera_create(eg, object);

    lzh_object_set_name(object, "camera");

    lzh_camera_set_perspective(camera, LZH_FALSE);
    lzh_camera_lookat(camera, 0.0f, 0.0f, 0.0f);
    lzh_transform_translate(transform, 0.0f, 0.0f, 2.0f);
}

Camera::~Camera()
{
}

float Camera::GetViewWidth() const
{
    return VIEW_WIDTH;
}

float Camera::GetViewHeight() const
{
    return VIEW_HIEGHT;
}

/*===========================================================================*/
