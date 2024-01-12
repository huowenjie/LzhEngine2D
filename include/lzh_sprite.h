#ifndef __LZH_SPRITE_H__
#define __LZH_SPRITE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 精灵 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建精灵 */
LZH_API LZH_SPRITE *lzh_sprite_create(LZH_ENGINE *engine, const char *res);

/* 创建多图精灵 */
LZH_API LZH_SPRITE *lzh_sprite_create_from_images(
    LZH_ENGINE *engine, const char *res_list[], int count);

/* 创建单图精灵集 */
LZH_API LZH_SPRITE *lzh_sprite_create_from_sheets(
    LZH_ENGINE *engine, const LZH_RECT *rect_list, int count);

/* 销毁精灵 */
LZH_API void lzh_sprite_destroy(LZH_SPRITE *sprite);

/* 控制精灵的显示或隐藏 */
LZH_API void lzh_sprite_show(LZH_SPRITE *sprite, LZH_BOOL show);

/* 设置精灵动画默认帧数 */
LZH_API void lzh_sprite_set_fps(LZH_SPRITE *sprite, int fps);

/* 允许/禁止播放精灵动画 */
LZH_API void lzh_sprite_enable_play(LZH_SPRITE *sprite, LZH_BOOL enable);

/* 设置播放起始帧 */
LZH_API void lzh_sprite_set_start_frame(LZH_SPRITE *sprite, int start);

/* 设置播放结束帧 */
LZH_API void lzh_sprite_set_end_frame(LZH_SPRITE *sprite, int end);

/*
 * 设置关键帧回调，在某一帧播放结束后调用关键帧回调, 只能从支持动画的精灵上
 * 设置，帧数从0开始算。
 */
LZH_API void lzh_sprite_set_keyframe(
    LZH_SPRITE *sprite, int frame, LZH_KEYFRAME_CB cb, void *args);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SPRITE_H__ */
