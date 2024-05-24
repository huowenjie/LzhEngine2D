#include <lzh_object.h>
#include <lzh_camera.h>
#include <lzh_transform.h>

#include "camera.h"

/*===========================================================================*/

Camera::Camera(LZH_ENGINE *eg) : GameObject(eg)
{
    objType = OT_Camera;
    camera = lzh_camera_create(eg);

    lzh_object_add_component(object, camera);
    lzh_object_set_name(object, "camera");

    lzh_camera_set_viewport(camera, 16.0f, 12.0f);

    lzh_camera_set_perspective(camera, LZH_FALSE);
    lzh_camera_lookat(camera, 0.0f, 0.0f, 0.0f);
    lzh_transform_translate(transform, 0.0f, 0.0f, 2.0f);
}

Camera::~Camera()
{
}

/*===========================================================================*/

void Camera::Update(LZH_ENGINE *eg)
{

}

void Camera::FixedUpdate(LZH_ENGINE *eg)
{

}

/*===========================================================================*/
