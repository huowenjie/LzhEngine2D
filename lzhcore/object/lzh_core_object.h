#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include "../component/lzh_component.h"

/*===========================================================================*/
/* 对象(内部) */
/*===========================================================================*/

/**
 * 定义子对象树
 * 
 * LZH_OBJ_RB_NODE
 * LZH_OBJ_RB_TREE
 * 
 * lzh_obj_rb_create
 * lzh_obj_rb_destroy
 * lzh_obj_rb_insert
 * lzh_obj_rb_delete
 * lzh_obj_rb_find
 * lzh_obj_rb_iterate
 */
RBTREE_DECLARE(LZH_OBJ, lzh_obj, LZH_HASH_CODE, LZH_OBJECT *)

/* 对象结构 */
struct LZH_OBJECT {
    /* 基类 */
    LZH_BASE base;

    /* 父对象 */
    LZH_OBJECT *parent;

    /* 子对象树 */
    LZH_OBJ_RB_TREE *children;

    /* 组件链表 */
    LZH_CPNT_RB_TREE *components;

    /* 渲染层级和顺序 */
    int render_sort;

    /* 变换组件 */
    LZH_TRANSFORM *transform;

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
int lzh_object_rb_comp(const void *obj1, const void *obj2);
void lzh_object_rb_visit(const LZH_OBJ_RB_NODE *node, void *args);

/* 子对象更新回调 */
void lzh_object_rb_visit_update(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_fixedupdate(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_draw(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_sort_draw(const LZH_OBJ_RB_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
