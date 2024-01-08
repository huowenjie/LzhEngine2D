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
LZH_API LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine);

/* ���ٶ��� */
LZH_API void lzh_object_destroy(LZH_OBJECT *object);

/* ���óߴ� */
LZH_API void lzh_object_set_size(LZH_OBJECT *object, int w, int h);

/* ����λ�� */
LZH_API void lzh_object_set_pos(LZH_OBJECT *object, int x, int y);

/* ��Ⱦ���� */
LZH_API void lzh_object_render(LZH_OBJECT *object);

/* ���þ������ */
LZH_API void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
