#ifndef __LZH_OBJECT_H__
#define __LZH_OBJECT_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 对象模型 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建对象 */
LZH_API LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine);

/* 销毁对象 */
LZH_API void lzh_object_destroy(LZH_OBJECT *object);

/* 设置尺寸 */
LZH_API void lzh_object_set_size(LZH_OBJECT *object, int w, int h);

/* 设置位置 */
LZH_API void lzh_object_set_pos(LZH_OBJECT *object, int x, int y);

/* 渲染对象 */
LZH_API void lzh_object_render(LZH_OBJECT *object);

/* 设置精灵组件 */
LZH_API void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
