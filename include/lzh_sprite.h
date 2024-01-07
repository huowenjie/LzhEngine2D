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

/* 设置尺寸 */
LZH_API void lzh_sprite_set_size(LZH_SPRITE *sprite, int w, int h);

/* 设置位置 */
LZH_API void lzh_sprite_set_pos(LZH_SPRITE *sprite, int x, int y);

/* 渲染精灵 */
LZH_API void lzh_sprite_render(LZH_SPRITE *sprite);

/* 渲染精灵集 */
LZH_API void lzh_sprite_render_sheet(LZH_SPRITE *sprite, int index);

/* 渲染精灵集动画 */
LZH_API void lzh_sprite_render_anim(LZH_SPRITE *sprite, int index);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_SPRITE_H__ */
