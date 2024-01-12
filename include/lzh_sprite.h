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

/* ���ƾ������ʾ������ */
LZH_API void lzh_sprite_show(LZH_SPRITE *sprite, LZH_BOOL show);

/* ���þ��鶯��Ĭ��֡�� */
LZH_API void lzh_sprite_set_fps(LZH_SPRITE *sprite, int fps);

/* ����/��ֹ���ž��鶯�� */
LZH_API void lzh_sprite_enable_play(LZH_SPRITE *sprite, LZH_BOOL enable);

/* ���ò�����ʼ֡ */
LZH_API void lzh_sprite_set_start_frame(LZH_SPRITE *sprite, int start);

/* ���ò��Ž���֡ */
LZH_API void lzh_sprite_set_end_frame(LZH_SPRITE *sprite, int end);

/*
 * ���ùؼ�֡�ص�����ĳһ֡���Ž�������ùؼ�֡�ص�, ֻ�ܴ�֧�ֶ����ľ�����
 * ���ã�֡����0��ʼ�㡣
 */
LZH_API void lzh_sprite_set_keyframe(
    LZH_SPRITE *sprite, int frame, LZH_KEYFRAME_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SPRITE_H__ */
