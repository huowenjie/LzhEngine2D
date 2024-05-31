#ifndef __LZH_COMPONENT_H__
#define __LZH_COMPONENT_H__

#include <lzh_type.h>
#include <lzh_rbtree.h>

#include "../lzh_base.h"

/*===========================================================================*/
/* 组件 */
/*===========================================================================*/

#define LZH_CPNT_UNDEF          0x00000000U /* 未定义的组件 */
#define LZH_CPNT_TRANSFORM      0x00000001U /* 变换组件 */
#define LZH_CPNT_CAMERA         0x00000002U /* 相机组件 */
#define LZH_CPNT_SPRITE         0x00000003U /* 精灵组件 */
#define LZH_CPNT_COLLIDER       0x00000004U /* 碰撞组件 */

typedef struct LZH_COMPONENT LZH_COMPONENT;

struct LZH_COMPONENT {
    /* 基类 */
    LZH_BASE base;

    /* 组件类型 */
    LZH_UINT32 type;

    /* 所属 object */
    LZH_OBJECT *object;

    /* 组件移除回调 */
    void (*remove_component)(LZH_COMPONENT *);
};

/**
 * 定义组件树
 * 
 * LZH_CPNT_RB_NODE
 * LZH_CPNT_RB_TREE
 * 
 * lzh_cpnt_rb_create
 * lzh_cpnt_rb_destroy
 * lzh_cpnt_rb_insert
 * lzh_cpnt_rb_delete
 * lzh_cpnt_rb_find
 * lzh_cpnt_rb_iterate
 */
RBTREE_DECLARE(LZH_CPNT, lzh_cpnt, LZH_UINT32, LZH_COMPONENT *)

void lzh_cpnt_init(LZH_COMPONENT *cpnt, LZH_UINT32 type, LZH_OBJECT *object);
void lzh_cpnt_quit(LZH_COMPONENT *cpnt);
void lzh_cpnt_destroy(LZH_COMPONENT *cpnt);

/* 精灵组件的回调函数 */
int lzh_cpnt_rb_comp(const void *cpnt1, const void *cpnt2);
void lzh_cpnt_rb_visit(const LZH_CPNT_RB_NODE *node, void *args);

/* 组件更新回调 */
void lzh_cpnt_rb_visit_update(const LZH_CPNT_RB_NODE *node, void *args);
void lzh_cpnt_rb_visit_fixedupdate(const LZH_CPNT_RB_NODE *node, void *args);
void lzh_cpnt_rb_visit_draw(const LZH_CPNT_RB_NODE *node, void *args);

/* 从组件表中获取对应类型的组件 */
LZH_COMPONENT *lzh_cpnt_get_type(LZH_CPNT_RB_TREE *tree, LZH_UINT32 type);

/*===========================================================================*/

#endif /* __LZH_COMPONENT_H__ */
