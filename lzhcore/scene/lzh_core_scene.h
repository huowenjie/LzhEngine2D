#ifndef __LZH_CORE_SCENE_H__
#define __LZH_CORE_SCENE_H__

#include <lzh_rbtree.h>
#include "../object/lzh_core_object.h"

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
RBTREE_DECLARE(SCENE_OBJ, scene_obj, int, LZH_OBJECT *)

/**
 * 定义层级树
 * 
 * SCENE_LAYER_RB_NODE
 * SCENE_LAYER_RB_TREE
 * 
 * scene_layer_rb_create
 * scene_layer_rb_destroy
 * scene_layer_rb_insert
 * scene_layer_rb_delete
 * scene_layer_rb_find
 * scene_layer_rb_iterate
 */
RBTREE_DECLARE(SCENE_LAYER, scene_layer, int, SCENE_OBJ_RB_TREE *)

/**
 * 定义Hash-对象映射表，用户快速定位对象
 * 
 * OBJECT_MAPP_RB_NODE
 * OBJECT_MAP_RB_TREE
 * 
 * object_map_rb_create
 * object_map_rb_destroy
 * object_map_rb_insert
 * object_map_rb_delete
 * object_map_rb_find
 * object_map_rb_iterate
 */
RBTREE_DECLARE(OBJECT_MAP, object_map, LZH_HASH_CODE, LZH_OBJECT *)

struct LZH_SCENE
{
    /* 基类 */
    LZH_BASE base;

    /* 层级对象渲染树 */
    SCENE_LAYER_RB_TREE *layer_tree;

    /* 层级对象映射表 */
    OBJECT_MAP_RB_TREE *object_map;
};

/* 映射表比较 */
int lzh_scene_object_map_comp(const void *a, const void *b);

/* 层级树回调 */
int lzh_scene_layer_comp(const void *a, const void *b);
void lzh_scene_layer_visit_free(const SCENE_LAYER_RB_NODE *node, void *args);

/* 对象树回调 */
int lzh_scene_objs_comp(const void *a, const void *b);
void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args);

/* 层级树迭代 */
void lzh_scene_layer_visit_update(const SCENE_LAYER_RB_NODE *node, void *args);
void lzh_scene_layer_visit_fixedupdate(const SCENE_LAYER_RB_NODE *node, void *args);

/* 对象树迭代 */
void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_SCENE_H__ */
