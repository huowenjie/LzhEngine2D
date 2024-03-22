#ifndef __LZH_OBJECT_H__
#define __LZH_OBJECT_H__

#include "lzh_type.h"
#include "lzh_vec2f.h"
#include "lzh_rectf.h"

/*===========================================================================*/
/* ����ģ�� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �������� */
LZH_API LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine);

/* ���ٶ��� */
LZH_API void lzh_object_destroy(LZH_OBJECT *object);

/* ��ȡ������� */
LZH_API LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object);

/* ���ö������� */
LZH_API void lzh_object_set_name(LZH_OBJECT *object, const char *name);

/* ��ȡ�������� */
LZH_API const char *lzh_object_get_name(LZH_OBJECT *object);

/* ���ö�����»ص� */
LZH_API void lzh_object_set_update(
    LZH_OBJECT *object, LZH_OBJECT_UPDATE update, void *param);

/* ���ö���̶�ʱ����»ص� */
LZH_API void lzh_object_set_fixedupdate(
    LZH_OBJECT *object, LZH_OBJECT_FIXEDUPDATE update, void *param);

/* ���óߴ� */
LZH_API void lzh_object_set_size(LZH_OBJECT *object, float w, float h);

/* ����λ�� */
LZH_API void lzh_object_set_pos(LZH_OBJECT *object, const LZH_VEC2F *pos);

/* ������ת�Ƕȣ���λ�ǽǶ� */
LZH_API void lzh_object_set_angle(LZH_OBJECT *object, float angle);

/* ��ȡλ�� */
LZH_API LZH_VEC2F lzh_object_get_pos(LZH_OBJECT *object);
LZH_API float lzh_object_get_x(LZH_OBJECT *object);
LZH_API float lzh_object_get_y(LZH_OBJECT *object);

/* ��ȡ��Χ�� */
LZH_API LZH_RECTF lzh_object_get_rect(const LZH_OBJECT *object);

/* ��ȡ��ת�Ƕȣ���λ�ǽǶ� */
LZH_API float lzh_object_get_angle(LZH_OBJECT *object);

/* ��ȡǰ������ */
LZH_API LZH_VEC2F lzh_object_get_forward(LZH_OBJECT *object);

/* ���þ������ */
LZH_API void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp);

/* ����/��ʾ���� */
LZH_API void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
