#ifndef __LZH_RENDER_TREE_H__
#define __LZH_RENDER_TREE_H__

#include <lzh_type.h>
#include <lzh_rbtree.h>

/*===========================================================================*/
/* ��Ⱦ�� */
/*===========================================================================*/

/**
 * ��������Ⱦ��
 * 
 * SRT_RB_NODE
 * SRT_RB_TREE
 * 
 * srt_rb_create
 * srt_rb_destroy
 * srt_rb_insert
 * srt_rb_delete
 * srt_rb_find
 * srt_rb_iterate
 */
RBTREE_DECLARE(SRT, srt, int, LZH_OBJECT *)

/**
 * ������Ⱦ��
 * 
 * RT_RB_NODE
 * RT_RB_TREE
 * 
 * rt_rb_create
 * rt_rb_destroy
 * rt_rb_insert
 * rt_rb_delete
 * rt_rb_find
 * rt_rb_iterate
 */
RBTREE_DECLARE(RT, rt, int, SRT_RB_TREE *)

RT_RB_TREE *create_render_tree();
void destroy_render_tree(RT_RB_TREE *tree);

/* ��������ӵ���Ⱦ���� */
void render_tree_push(
    RT_RB_TREE *render_tree, int layer, int order, LZH_OBJECT *object);

/**
 * ��Ⱦ������ visit �ĸ������ֱ�Ϊ
 * 
 * layer RT_RB_TREE ���ڵ�� key
 * order SRT_RB_TREE ���ڵ�� key
 * object SRT_RB_TREE ���ڵ�Ķ���
 * args �û��ڵ��� render_tree_iterate ��������Ĳ���
 */
void render_tree_iterate(
    RT_RB_TREE *render_tree,
    void (*visit)(int, int, LZH_OBJECT *, void *),
    void *args
);

/*===========================================================================*/

#endif /* __LZH_RENDER_TREE_H__ */
