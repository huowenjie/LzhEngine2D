#ifndef __LZH_SCENE_H__
#define __LZH_SCENE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 场景 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 射线碰撞信息 */
typedef struct LZH_SCENE_RAYHIT_2D
{
    LZH_OBJECT *hitobj; /* 碰撞对象 */
    float nx;           /* 法线 x 坐标 */
    float ny;           /* 法线 y 坐标 */
    float hx;           /* 碰撞点 x 坐标 */
    float hy;           /* 碰撞点 y 坐标 */
} LZH_SCENE_RAYHIT_2D;

/* 创建场景 */
LZH_API LZH_SCENE *lzh_scene_create(LZH_ENGINE *engine);

/* 销毁场景 */
LZH_API void lzh_scene_destroy(LZH_SCENE *scene);

/* 设置场景名称 */
LZH_API void lzh_scene_set_name(LZH_SCENE *scene, const char *name);

/* 获取场景名称 */
LZH_API const char *lzh_scene_get_name(LZH_SCENE *scene);

/* 设置场景主相机，本方法不会将相机对象添加到渲染树 */
LZH_API void lzh_scene_set_main_camera(LZH_SCENE *scene, LZH_OBJECT *camera);

/* 设置收尾过程回调 */
LZH_API void lzh_scene_set_last_callback(
    LZH_SCENE *scene, LZH_SCENE_LAST cb, void *args);

/* 发射射线检测是否有对象碰撞，如果有，则返回碰撞对象 */
LZH_API LZH_BOOL lzh_scene_raycast2d(
    LZH_SCENE *scene, float sx, float sy, float ex, float ey, LZH_SCENE_RAYHIT_2D *info);

/*===========================================================================*/

/* 获取场景管理器 */
LZH_API LZH_SCENE_MANAGER *lzh_scene_get_manager(LZH_ENGINE *engine);

/* 加载场景 */
LZH_API void lzh_scene_manager_load(LZH_SCENE_MANAGER *manager, const char *name);

/* 卸载场景 */
LZH_API void lzh_scene_manager_unload(LZH_SCENE_MANAGER *manager);

/* 获取场景 */
LZH_API LZH_SCENE *lzh_scene_manager_get(LZH_SCENE_MANAGER *manager, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SCENE_H__ */