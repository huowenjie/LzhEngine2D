#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include "../component/lzh_component.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

/**
 * �����Ӷ�����
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

/**
 * ������չ������
 * 
 * LZH_EXT_RB_NODE
 * LZH_EXT_RB_TREE
 * 
 * lzh_ext_rb_create
 * lzh_ext_rb_destroy
 * lzh_ext_rb_insert
 * lzh_ext_rb_delete
 * lzh_ext_rb_find
 * lzh_ext_rb_iterate
 * lzh_ext_rb_create_iterator
 * lzh_ext_rb_destroy_iterator
 * lzh_ext_rb_it_init
 * lzh_ext_rb_it_next
 * lzh_ext_rb_it_value
 * lzh_ext_rb_it_key
 */
RBTREE_DECLARE(LZH_EXT, lzh_ext, LZH_HASH_CODE, LZH_UINTPTR)

/* ����ṹ */
struct LZH_OBJECT {
    /* ���� */
    LZH_BASE base;

    /* ������ */
    LZH_OBJECT *parent;

    /* �Ӷ����� */
    LZH_OBJ_RB_TREE *children;

    /* ������� */
    LZH_CPNT_RB_TREE *components;

    /* �任��� */
    LZH_TRANSFORM *transform;

    /*---------------------------------------------------*/
    /* ����ҵ�� */

    /* ������»ص��Ͳ���*/
    LZH_OBJECT_UPDATE update;
    void *update_param;

    /* �̶�ʱ����»ص��Ͳ��� */
    LZH_OBJECT_FIXEDUPDATE fixed_update;
    void *fixed_update_param;

    /*---------------------------------------------------*/
    /* ��չ�������ڴ洢�������ݵ�ַ */
    LZH_EXT_RB_TREE *extension;

    /* ��ǰ�������� */
    LZH_SCENE *current_scene;
};

/* ���ٶ��� */
void lzh_object_remove(LZH_OBJECT *object);

/* ������� */
void lzh_object_add_component(LZH_OBJECT *object, void *cpnt);

/* �Ƴ�������������ָ�� */
void lzh_object_del_component(LZH_OBJECT *object, void *cpnt);

/* �Ӷ���Ļص����� */
int lzh_object_rb_comp(const void *obj1, const void *obj2);
void lzh_object_rb_visit(const LZH_OBJ_RB_NODE *node, void *args);

/* �Ӷ�����»ص� */
void lzh_object_rb_visit_update(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_fixedupdate(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_draw(const LZH_OBJ_RB_NODE *node, void *args);
void lzh_object_rb_visit_sort_draw(const LZH_OBJ_RB_NODE *node, void *args);

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */