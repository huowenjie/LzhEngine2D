#ifndef __LZH_SPRITE_H__
#define __LZH_SPRITE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* �������� */
LZH_API LZH_SPRITE *lzh_sprite_create(LZH_ENGINE *engine, const char *res);

/* ������ͼ���� */
LZH_API LZH_SPRITE *lzh_sprite_create_from_images(
    LZH_ENGINE *engine, const char *res_list[], int count);

/* ������ͼ���鼯 */
LZH_API LZH_SPRITE *lzh_sprite_create_from_sheets(
    LZH_ENGINE *engine, const LZH_RECT *rect_list, int count);

/* ���پ��� */
LZH_API void lzh_sprite_destroy(LZH_SPRITE *sprite);

/* ���óߴ� */
LZH_API void lzh_sprite_set_size(LZH_SPRITE *sprite, int w, int h);

/* ����λ�� */
LZH_API void lzh_sprite_set_pos(LZH_SPRITE *sprite, int x, int y);

/* ��Ⱦ���� */
LZH_API void lzh_sprite_render(LZH_SPRITE *sprite);

/* ��Ⱦ���鼯 */
LZH_API void lzh_sprite_render_sheet(LZH_SPRITE *sprite, int index);

/* ��Ⱦ���鼯���� */
LZH_API void lzh_sprite_render_anim(LZH_SPRITE *sprite, int index);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SPRITE_H__ */
