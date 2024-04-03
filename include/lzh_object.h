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

/* 设置父对象 */
LZH_API void lzh_object_set_parent(LZH_OBJECT *object, LZH_OBJECT *parent);

/* 添加子对象 */
LZH_API void lzh_object_add_child(LZH_OBJECT *object, LZH_OBJECT *child);

/* 移除子对象，移除后返回该对象 */
LZH_API void lzh_object_del_child(LZH_OBJECT *object, const char *name);

/* 销毁对象，销毁时将子对象全部删除 */
LZH_API void lzh_object_destroy(LZH_OBJECT *object);

/* 添加组件 */
LZH_API void lzh_object_add_component(LZH_OBJECT *object, void *cpnt);

/* 移除组件并返回组件指针 */
LZH_API void *lzh_object_del_component(LZH_OBJECT *object, void *cpnt);

/* 获取精灵组件 */
LZH_API LZH_SPRITE *lzh_object_get_sprite(LZH_OBJECT *object);

/* 获取对象唯一编码 */
LZH_API LZH_HASH_CODE lzh_object_hash_code(LZH_OBJECT *object);

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

/* 隐藏/显示对象 */
LZH_API void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_OBJECT_H__ */
