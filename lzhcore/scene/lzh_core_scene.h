#ifndef __LZH_CORE_SCENE_H__
#define __LZH_CORE_SCENE_H__

#include <lzh_rbtree.h>
#include "../object/lzh_core_object.h"

/*===========================================================================*/
/* �����ڲ����� */
/*===========================================================================*/

/**
 * ��������Ⱦ��
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
 * ������Ⱦ��
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

struct LZH_SCENE
{
    /* ���� */
    LZH_BASE base;

    /* �㼶������Ⱦ�� */
    SCENE_LAYER_RB_TREE *layer_tree;
};

/* ���������ص� */
int lzh_scene_layer_comp(const void *a, const void *b);
void lzh_scene_layer_visit_free(const SCENE_LAYER_RB_NODE *node, void *args);
void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_SCENE_H__ */
