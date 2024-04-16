#include <lzh_camera.h>
#include <lzh_mem.h>
#include <stddef.h>

#include "lzh_core_camera.h"

/*===========================================================================*/

/* 组件更新 */
static void lzh_camera_update(LZH_BASE *base, void *args);

/* 组件移除 */
static void lzh_camera_remove(LZH_COMPONENT *cpnt);

/* 相机数据更新 */
static void lzh_camera_flush(LZH_CAMERA *camera);

/*===========================================================================*/

LZH_CAMERA *lzh_camera_create(LZH_ENGINE *engine)
{
    LZH_CAMERA *camera = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine) {
        return NULL;
    }

    camera = LZH_MALLOC(sizeof(LZH_CAMERA));
    if (!camera) {
        return NULL;
    }
    memset(camera, 0, sizeof(LZH_CAMERA));

    base = &camera->base;
    lzh_cpnt_init(base);

    base->base.engine = engine;
    base->base.update = lzh_camera_update;
    base->base.fixed_update = lzh_camera_update;
    base->type = LZH_CPNT_CAMERA;
    base->remove_component = lzh_camera_remove;

    camera->type = LZH_CAMERA_PERSP;
    camera->view_port_w = 2.0f;
    camera->view_port_h = 2.0f;
    camera->view = lzh_mat4x4f_unit();
    camera->prog = lzh_mat4x4f_unit();

    return camera;
}

void lzh_camera_destroy(LZH_CAMERA *camera)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)camera);
}

void lzh_camera_set_viewport(
    LZH_CAMERA *camera, float width, float height)
{
    if (camera) {
        camera->view_port_w = width;
        camera->view_port_h = height;
        lzh_camera_flush(camera);
    }
}

void lzh_camera_set_perspective(LZH_CAMERA *camera, LZH_BOOL perspective)
{
    if (camera) {
        camera->type = perspective ? LZH_CAMERA_PERSP : LZH_CAMERA_ORTHO;
        lzh_camera_flush(camera);
    }
}

void lzh_camera_lookat(LZH_CAMERA *camera, float x, float y, float z)
{

}

/*===========================================================================*/

void lzh_camera_update(LZH_BASE *base, void *args)
{

}

void lzh_camera_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_CAMERA *camera = (LZH_CAMERA *)cpnt;
        lzh_cpnt_quit(cpnt);
        LZH_FREE(camera);
    }
}

void lzh_camera_flush(LZH_CAMERA *camera)
{
    if (!camera) {
        return;
    }
}

/*===========================================================================*/
