#ifndef __LZH_SCENE_H__
#define __LZH_SCENE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 场景 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建场景 */
LZH_API LZH_SCENE *lzh_scene_create(LZH_ENGINE *engine);

/* 销毁场景 */
LZH_API void lzh_scene_destroy(LZH_SCENE *scene);

/* 添加对象，名称不能相同 */
LZH_API void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* 删除对象 */
LZH_API void lzh_scene_del_object(LZH_SCENE *scene, const char *name);

/* 设置场景名称 */
LZH_API void lzh_scene_set_name(LZH_SCENE *scene, const char *name);

/* 获取场景名称 */
LZH_API const char *lzh_scene_get_name(LZH_SCENE *scene);

/* 设置场景主相机，本方法不会将相机对象添加到渲染树 */
LZH_API void lzh_scene_set_main_camera(LZH_SCENE *scene, LZH_OBJECT *camera);

/*===========================================================================*/

/* 获取场景管理器 */
LZH_API LZH_SCENE_MANAGER *lzh_scene_get_manager(LZH_ENGINE *engine);

/* 加载场景 */
LZH_API void lzh_scene_manager_load(LZH_SCENE_MANAGER *manager, const char *name);

/* 卸载场景 */
LZH_API void lzh_scene_manager_unload(LZH_SCENE_MANAGER *manager, const char *name);

/* 获取场景 */
LZH_API LZH_SCENE *lzh_scene_manager_get(LZH_SCENE_MANAGER *manager, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SCENE_H__ */