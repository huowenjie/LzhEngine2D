#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include "../component/lzh_component.h"

/*===========================================================================*/
/* 对象(内部) */
/*===========================================================================*/

LINK_DECLARE(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/* 对象结构 */
struct LZH_OBJECT {
    /* 基类 */
    LZH_BASE base;

    /* 父对象 */
    LZH_OBJECT *parent;

    /* 子对象链表 */
    LZH_OBJ_LINK *children;

    /* 组件链表 */
    LZH_CPNT_LINK *components;

    /* 渲染层级 */
    int render_layer;

    /* 渲染顺序 */
    int render_sort;

    /*---------------------------------------------------*/
    /* 用于业务 */

    /* 对象更新回调和参数*/
    LZH_OBJECT_UPDATE update;
    void *update_param;

    /* 固定时间更新回调和参数 */
    LZH_OBJECT_FIXEDUPDATE fixed_update;
    void *fixed_update_param;
};

/* 移除子对象，不更改父对象的信息 */
void lzh_object_remove(LZH_OBJECT *object);

/* 子对象的回调函数 */
int lzh_link_object_comp(const void *obj1, const void *obj2);
void lzh_link_object_visit(const LZH_OBJ_LINK_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
