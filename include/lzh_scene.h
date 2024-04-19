#ifndef __LZH_SCENE_H__
#define __LZH_SCENE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �������� */
LZH_API LZH_SCENE *lzh_scene_create(LZH_ENGINE *engine);

/* ���ٳ��� */
LZH_API void lzh_scene_destroy(LZH_SCENE *scene);

/* ��Ӷ������Ʋ�����ͬ */
LZH_API void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* ɾ������ */
LZH_API void lzh_scene_del_object(LZH_SCENE *scene, const char *name);

/* ���ó������� */
LZH_API void lzh_scene_set_name(LZH_SCENE *scene, const char *name);

/* ��ȡ�������� */
LZH_API const char *lzh_scene_get_name(LZH_SCENE *scene);

/* ���ó�������������������Ὣ���������ӵ���Ⱦ�� */
LZH_API void lzh_scene_set_main_camera(LZH_SCENE *scene, LZH_OBJECT *camera);

/*===========================================================================*/

/* ��ȡ���������� */
LZH_API LZH_SCENE_MANAGER *lzh_scene_get_manager(LZH_ENGINE *engine);

/* ���س��� */
LZH_API void lzh_scene_manager_load(LZH_SCENE_MANAGER *manager, const char *name);

/* ж�س��� */
LZH_API void lzh_scene_manager_unload(LZH_SCENE_MANAGER *manager, const char *name);

/* ��ȡ���� */
LZH_API LZH_SCENE *lzh_scene_manager_get(LZH_SCENE_MANAGER *manager, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SCENE_H__ */