#include <lzh_camera.h>
#include <lzh_mem.h>
#include <lzh_engine.h>
#include <stddef.h>

#include "lzh_core_camera.h"
#include "lzh_core_transform.h"

#include "../engine/lzh_core_engine.h"
#include "../graphic/lzh_shader.h"
#include "../math/lzh_mathdef.h"

/*===========================================================================*/

/* 组件移除 */
static void lzh_camera_remove(LZH_COMPONENT *cpnt);

/* 相机数据更新 */
static void lzh_camera_orth_flush(LZH_CAMERA *camera);
static void lzh_camera_pers_flush(LZH_CAMERA *camera);

/*===========================================================================*/

LZH_CAMERA *lzh_camera_create(LZH_ENGINE *engine, LZH_OBJECT *object)
{
    LZH_CAMERA *camera = NULL;
    LZH_COMPONENT *base = NULL;

    float vw = 0.0f;
    float vh = 0.0f;

    if (!engine || !object) {
        return NULL;
    }

    camera = LZH_MALLOC(sizeof(LZH_CAMERA));
    if (!camera) {
        return NULL;
    }
    memset(camera, 0, sizeof(LZH_CAMERA));

    base = &camera->base;
    lzh_cpnt_init(base, LZH_CPNT_CAMERA, object);    
    lzh_engine_win_sizef(engine, &vw, &vh);

    base->base.engine = engine;
    base->remove_component = lzh_camera_remove;

    camera->type = LZH_CAMERA_PERSP;
    camera->view_port_w = vw * engine->window_scale;
    camera->view_port_h = vh * engine->window_scale;

    camera->up = lzh_vec3f_xyz(0.0f, 1.0f, 0.0f);
    camera->target = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
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
    if (camera) {
        camera->target = lzh_vec3f_xyz(x, y, z);
        lzh_camera_flush(camera);
    }
}

void lzh_camera_set_updir(LZH_CAMERA *camera, float x, float y, float z)
{
    if (camera) {
        camera->up = lzh_vec3f_xyz(x, y, z);
        lzh_camera_flush(camera);
    }
}

/*===========================================================================*/

void lzh_camera_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_CAMERA *camera = (LZH_CAMERA *)cpnt;
        lzh_cpnt_quit((LZH_COMPONENT *)camera);
        LZH_FREE(camera);
    }
}

void lzh_camera_flush(LZH_CAMERA *camera)
{
    LZH_OBJECT *object = NULL;
    LZH_TRANSFORM *transform = NULL;
    LZH_MAT4X4F lookat = lzh_mat4x4f_unit();

    LZH_VEC3F camera_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC3F camera_up = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC4F origin_up = lzh_vec4f_xyzw(0.0f, 0.0f, 0.0f, 1.0f);

    if (!camera) {
        return;
    }

    object = camera->base.object;
    if (!object) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    origin_up = lzh_vec4f_vec3f(&camera->up, 1.0f);
    origin_up = lzh_mat4x4f_mul_vec(&transform->model_mat, &origin_up);
    camera_up = lzh_vec3f_xyz(origin_up.x, origin_up.y, origin_up.z);
    camera_up = lzh_vec3f_normalize(&camera_up);

    camera_pos = transform->local_pos;
    lookat = lzh_mat4x4f_camera(&camera_pos, &camera_up, &camera->target);

    camera->view = lookat;

    if (camera->type == LZH_CAMERA_PERSP) {
        lzh_camera_pers_flush(camera);
    } else if (camera->type == LZH_CAMERA_ORTHO) {
        lzh_camera_orth_flush(camera);
    }
}

void lzh_camera_orth_flush(LZH_CAMERA *camera) 
{
    if (camera) {
        float vpw = camera->view_port_w / 2.0f;
        float vph = camera->view_port_h / 2.0f;

        camera->prog = lzh_mat4x4f_ortho(-vpw, vph, vpw, -vph, 0.1f, 100.0f);
    }
}

void lzh_camera_pers_flush(LZH_CAMERA *camera)
{
    if (camera) {
        LZH_MAT4X4F proj = lzh_mat4x4f_ortho2d(-30.0f, 30.0f, 30.0f, -30.0f);
        LZH_MAT4X4F perp = lzh_mat4x4f_perspective(LZH_PI / 4.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        camera->prog = lzh_mat4x4f_mul(&proj, &perp);
    }
}

/*===========================================================================*/
