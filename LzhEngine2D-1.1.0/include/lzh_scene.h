#ifndef __LZH_SCENE_H__
#define __LZH_SCENE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ������ײ��Ϣ */
typedef struct LZH_SCENE_RAYHIT_2D
{
    LZH_OBJECT *hitobj; /* ��ײ���� */
    float nx;           /* ���� x ���� */
    float ny;           /* ���� y ���� */
    float hx;           /* ��ײ�� x ���� */
    float hy;           /* ��ײ�� y ���� */
} LZH_SCENE_RAYHIT_2D;

/* �������� */
LZH_API LZH_SCENE *lzh_scene_create(LZH_ENGINE *engine);

/* ���ٳ��� */
LZH_API void lzh_scene_destroy(LZH_SCENE *scene);

/* ���ó������� */
LZH_API void lzh_scene_set_name(LZH_SCENE *scene, const char *name);

/* ��ȡ�������� */
LZH_API const char *lzh_scene_get_name(LZH_SCENE *scene);

/* ���ó�������������������Ὣ����������ӵ���Ⱦ�� */
LZH_API void lzh_scene_set_main_camera(LZH_SCENE *scene, LZH_OBJECT *camera);

/* ������β���̻ص� */
LZH_API void lzh_scene_set_last_callback(
    LZH_SCENE *scene, LZH_SCENE_LAST cb, void *args);

/* �������߼���Ƿ��ж�����ײ������У��򷵻���ײ���� */
LZH_API LZH_BOOL lzh_scene_raycast2d(
    LZH_SCENE *scene, float sx, float sy, float ex, float ey, LZH_SCENE_RAYHIT_2D *info);

/*===========================================================================*/

/* ��ȡ���������� */
LZH_API LZH_SCENE_MANAGER *lzh_scene_get_manager(LZH_ENGINE *engine);

/* ���س��� */
LZH_API void lzh_scene_manager_load(LZH_SCENE_MANAGER *manager, const char *name);

/* ж�س��� */
LZH_API void lzh_scene_manager_unload(LZH_SCENE_MANAGER *manager);

/* ��ȡ���� */
LZH_API LZH_SCENE *lzh_scene_manager_get(LZH_SCENE_MANAGER *manager, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SCENE_H__ */