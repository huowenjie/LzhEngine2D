#ifndef __LZH_OBJECT_H__
#define __LZH_OBJECT_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ����ģ�� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �������� */
LZH_API LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine, LZH_SCENE *scene);

/* ���ø����� */
LZH_API void lzh_object_set_parent(LZH_OBJECT *object, LZH_OBJECT *parent);

/* ��ȡ������ */
LZH_API LZH_OBJECT *lzh_object_get_parent(LZH_OBJECT *object);

/* ����Ӷ��� */
LZH_API void lzh_object_add_child(LZH_OBJECT *object, LZH_OBJECT *child);

/* �����Ӷ��� */
LZH_API LZH_OBJECT *lzh_object_find_child(LZH_OBJECT *object, const char *name);

/* �ݹ�����Ӷ��� */
LZH_API LZH_OBJECT *lzh_object_find_child_recursion(LZH_OBJECT *object, const char *name);

/* �Ƴ��Ӷ����Ƴ��󷵻ظö��� */
LZH_API void lzh_object_del_child(LZH_OBJECT *object, const char *name);

/* ���ٶ�������ʱ���Ӷ���ȫ��ɾ�� */
LZH_API void lzh_object_destroy(LZH_OBJECT *object);

/* ��ȡ�任��� */
LZH_API LZH_TRANSFORM *lzh_object_get_transform(LZH_OBJECT *object);

/* ��ȡ������� */
LZH_API LZH_SPRITE *lzh_object_get_sprite(LZH_OBJECT *object);

/* ��ȡ����Ψһ���� */
LZH_API LZH_HASH_CODE lzh_object_hash_code(LZH_OBJECT *object);

/* ��ȡ������� */
LZH_API LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object);

/* ���ö������� */
LZH_API void lzh_object_set_name(LZH_OBJECT *object, const char *name);

/* ��ȡ�������� */
LZH_API const char *lzh_object_get_name(LZH_OBJECT *object);

/* �����չ���� */
LZH_API void lzh_object_add_extension(
    LZH_OBJECT *object, const char *name, void *ext);

/* ɾ����������չ���� */
LZH_API void lzh_object_del_extension(LZH_OBJECT *object, const char *name);

/* ��ȡ��չ���� */
LZH_API void *lzh_object_get_extension(LZH_OBJECT *object, const char *name);

/* ��ȡ��ǰ�������� */
LZH_API LZH_SCENE *lzh_object_get_current_scene(LZH_OBJECT *object);

/* ���ö�����»ص� */
LZH_API void lzh_object_set_update(
    LZH_OBJECT *object, LZH_OBJECT_UPDATE update, void *param);

/* ���ö���̶�ʱ����»ص� */
LZH_API void lzh_object_set_fixedupdate(
    LZH_OBJECT *object, LZH_OBJECT_FIXEDUPDATE update, void *param);

/* ����/��ʾ���� */
LZH_API void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
