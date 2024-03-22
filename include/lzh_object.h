#ifndef __LZH_OBJECT_H__
#define __LZH_OBJECT_H__

#include "lzh_type.h"
#include "lzh_vec2f.h"
#include "lzh_rectf.h"

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

/* 获取引擎对象 */
LZH_API LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object);

/* 设置对象名称 */
LZH_API void lzh_object_set_name(LZH_OBJECT *object, const char *name);

/* 获取对象名称 */
LZH_API const char *lzh_object_get_name(LZH_OBJECT *object);

/* 设置对象更新回调 */
LZH_API void lzh_object_set_update(
    LZH_OBJECT *object, LZH_OBJECT_UPDATE update, void *param);

/* 设置对象固定时间更新回调 */
LZH_API void lzh_object_set_fixedupdate(
    LZH_OBJECT *object, LZH_OBJECT_FIXEDUPDATE update, void *param);

/* 设置尺寸 */
LZH_API void lzh_object_set_size(LZH_OBJECT *object, float w, float h);

/* 设置位置 */
LZH_API void lzh_object_set_pos(LZH_OBJECT *object, const LZH_VEC2F *pos);

/* 设置旋转角度，单位是角度 */
LZH_API void lzh_object_set_angle(LZH_OBJECT *object, float angle);

/* 获取位置 */
LZH_API LZH_VEC2F lzh_object_get_pos(LZH_OBJECT *object);
LZH_API float lzh_object_get_x(LZH_OBJECT *object);
LZH_API float lzh_object_get_y(LZH_OBJECT *object);

/* 获取包围盒 */
LZH_API LZH_RECTF lzh_object_get_rect(const LZH_OBJECT *object);

/* 获取旋转角度，单位是角度 */
LZH_API float lzh_object_get_angle(LZH_OBJECT *object);

/* 获取前进向量 */
LZH_API LZH_VEC2F lzh_object_get_forward(LZH_OBJECT *object);

/* 设置精灵组件 */
LZH_API void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp);

/* 隐藏/显示对象 */
LZH_API void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
