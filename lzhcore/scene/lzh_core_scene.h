#ifndef __LZH_CORE_SCENE_H__
#define __LZH_CORE_SCENE_H__

#include <lzh_rbtree.h>
#include "../object/lzh_core_object.h"
#include "../box2d/lzh_b2_api.h"

/*===========================================================================*/
/* 场景内部定义 */
/*===========================================================================*/

/**
 * 定义渲染树
 * 
 * SCENE_OBJ_RB_NODE
 * SCENE_OBJ_RB_TREE
 * 
 * scene_obj_rb_create
 * scene_obj_rb_destroy
 * scene_obj_rb_insert
 * scene_obj_rb_delete
 * scene_obj_rb_find
 * scene_obj_rb_iterate
 */
RBTREE_DECLARE(SCENE_OBJ, scene_obj, LZH_HASH_CODE, LZH_OBJECT *)

/**
 * 定义摄像机深度排序树
 * 离摄像机越远越先渲染
 * 
 * SCENE_SORT_RB_NODE
 * SCENE_SORT_RB_TREE
 * 
 * scene_sort_rb_create
 * scene_sort_rb_destroy
 * scene_sort_rb_insert
 * scene_sort_rb_delete
 * scene_sort_rb_find
 * scene_sort_rb_iterate
 */
RBTREE_DECLARE(SCENE_SORT, scene_sort, float, LZH_OBJECT *)

/**
 * 定义场景释放树
 * 本帧结束之后，对需要删除的对象统一删除
 * 
 * SCENE_DEL_RB_NODE
 * SCENE_DEL_RB_TREE
 * 
 * scene_del_rb_create
 * scene_del_rb_destroy
 * scene_del_rb_insert
 * scene_del_rb_delete
 * scene_del_rb_find
 * scene_del_rb_iterate
 * scene_del_rb_create_iterator
 * scene_del_rb_destroy_iterator
 * scene_del_rb_it_init
 * scene_del_rb_it_next
 * scene_del_rb_it_value
 * scene_del_rb_it_key
 */
RBTREE_DECLARE(SCENE_DEL, scene_del, LZH_HASH_CODE, LZH_OBJECT *)

struct LZH_SCENE
{
    /* 基类 */
    LZH_BASE base;

    /* 对象渲染树 */
    SCENE_OBJ_RB_TREE *render_tree;

    /* 深度排序树 */
    SCENE_SORT_RB_TREE *sort_tree;

    /* 场景释放树 */
    SCENE_DEL_RB_TREE *del_tree;

    /* 场景主相机 */
    LZH_OBJECT *main_camera;

    /* 场景收尾回调 */
    LZH_SCENE_LAST last_handle;
    void *last_handle_args;

    /* box2d 引擎世界对象 */
    LZH_B2_WORLD *world2d;
};

/* 添加对象，名称不能相同 */
void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* 删除对象 */
void lzh_scene_del_object(LZH_SCENE *scene, const char *name);

/* 移除场景 */
void lzh_scene_remove(LZH_SCENE *scene);

/* 排序表回调 */
int lzh_scene_sort_comp(const void *a, const void *b);
void lzh_scene_sort_visit_draw(const SCENE_SORT_RB_NODE *node, void *args);

/* 对象树回调 */
int lzh_scene_objs_comp(const void *a, const void *b);
void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args);

/* 释放树回调 */
void lzh_scene_del_visit_free(const SCENE_DEL_RB_NODE *node, void *args);

/* 对象树迭代 */
void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_draw(const SCENE_OBJ_RB_NODE *node, void *args);
LZH_BOOL lzh_scene_objs_insert(LZH_OBJECT *object, LZH_SCENE *scene);

/*===========================================================================*/

#endif /* __LZH_CORE_SCENE_H__ */
