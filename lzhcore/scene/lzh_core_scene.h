#ifndef __LZH_CORE_SCENE_H__
#define __LZH_CORE_SCENE_H__

#include <lzh_rbtree.h>
#include "../object/lzh_core_object.h"

/*===========================================================================*/
/* �����ڲ����� */
/*===========================================================================*/

/**
 * ������Ⱦ��
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
 * ������������������
 * �������ԽԶԽ����Ⱦ
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
 * ����Hash-����ӳ����û����ٶ�λ����
 * 
 * OBJECT_MAP_RB_NODE
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
    /* ���� */
    LZH_BASE base;

    /* ������Ⱦ�� */
    SCENE_OBJ_RB_TREE *render_tree;

    /* ����ӳ��� */
    OBJECT_MAP_RB_TREE *object_map;

    /* ��������� */
    SCENE_SORT_RB_TREE *sort_tree;

    /* ��������� */
    LZH_OBJECT *main_camera;
};

/* �Ƴ����� */
void lzh_scene_remove(LZH_SCENE *scene);

/* ӳ���Ƚ� */
int lzh_scene_object_map_comp(const void *a, const void *b);

/* �����ص� */
int lzh_scene_sort_comp(const void *a, const void *b);
void lzh_scene_sort_visit_draw(const SCENE_SORT_RB_NODE *node, void *args);

/* �������ص� */
int lzh_scene_objs_comp(const void *a, const void *b);
void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args);

/* ���������� */
void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_draw(const SCENE_OBJ_RB_NODE *node, void *args);
LZH_BOOL lzh_scene_objs_insert(LZH_OBJECT *object, LZH_SCENE *scene);

/*===========================================================================*/

#endif /* __LZH_CORE_SCENE_H__ */
