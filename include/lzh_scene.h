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
LZH_API LZH_BOOL lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* 删除对象 */
LZH_API void lzh_scene_del_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* 设置场景名称 */
LZH_API void lzh_scene_set_name(LZH_SCENE *scene, const char *name);

/* 获取场景名称 */
LZH_API const char *lzh_scene_get_name(LZH_SCENE *scene);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SCENE_H__ */