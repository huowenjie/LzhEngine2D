#ifndef __LZH_CORE_SCENE_H__
#define __LZH_CORE_SCENE_H__

#include <lzh_rbtree.h>
#include "../object/lzh_core_object.h"
#include "../box2d/lzh_b2_api.h"

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
RBTREE_DECLARE(SCENE_OBJ, scene_obj, LZH_HASH_CODE, LZH_OBJECT *)

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
 * ���峡���ͷ���
 * ��֡����֮�󣬶���Ҫɾ���Ķ���ͳһɾ��
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
    /* ���� */
    LZH_BASE base;

    /* ������Ⱦ�� */
    SCENE_OBJ_RB_TREE *render_tree;

    /* ��������� */
    SCENE_SORT_RB_TREE *sort_tree;

    /* �����ͷ��� */
    SCENE_DEL_RB_TREE *del_tree;

    /* ��������� */
    LZH_OBJECT *main_camera;

    /* ������β�ص� */
    LZH_SCENE_LAST last_handle;
    void *last_handle_args;

    /* box2d ����������� */
    LZH_B2_WORLD *world2d;
};

/* ��Ӷ������Ʋ�����ͬ */
void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object);

/* ɾ������ */
void lzh_scene_del_object(LZH_SCENE *scene, const char *name);

/* �Ƴ����� */
void lzh_scene_remove(LZH_SCENE *scene);

/* �����ص� */
int lzh_scene_sort_comp(const void *a, const void *b);
void lzh_scene_sort_visit_draw(const SCENE_SORT_RB_NODE *node, void *args);

/* �������ص� */
int lzh_scene_objs_comp(const void *a, const void *b);
void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args);

/* �ͷ����ص� */
void lzh_scene_del_visit_free(const SCENE_DEL_RB_NODE *node, void *args);

/* ���������� */
void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args);
void lzh_scene_objs_visit_draw(const SCENE_OBJ_RB_NODE *node, void *args);
LZH_BOOL lzh_scene_objs_insert(LZH_OBJECT *object, LZH_SCENE *scene);

/*===========================================================================*/

#endif /* __LZH_CORE_SCENE_H__ */
