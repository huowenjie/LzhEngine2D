#include <lzh_object.h>
#include "lzh_core_object.h"
#include "../component/lzh_core_transform.h"
#include "../scene/lzh_core_scene.h"

/*===========================================================================*/

void lzh_object_remove(LZH_OBJECT *object)
{
    if (object) {
        if (object->extension) {
            lzh_ext_rb_destroy(object->extension, NULL, NULL);
            object->extension = NULL;
        }

        if (object->transform) {
            lzh_transform_destroy(object->transform);
        }

        if (object->components) {
            lzh_cpnt_rb_destroy(object->components, lzh_cpnt_rb_visit, NULL);
            object->components = NULL;
        }

        if (object->children) {
            lzh_obj_rb_destroy(object->children, lzh_object_rb_visit, NULL);
            object->children = NULL;
        }

        /* 当前对象正在被父对象销毁 */
        if ((object->base.state & LZH_BST_OBJECT_CLEAR) != LZH_BST_OBJECT_CLEAR) {
            if (object->parent) {
                LZH_OBJECT *parent = object->parent;
                lzh_obj_rb_delete(parent->children, object->base.hash, NULL, NULL);
                object->parent = NULL;
            }
        }

        lzh_base_quit((LZH_BASE *)object);
        LZH_FREE(object);
    }
}

void lzh_object_add_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;

        elem->object = object;
        
        if (elem->type == LZH_CPNT_TRANSFORM) {
            return;
        }
        lzh_cpnt_rb_insert(object->components, elem->type, elem);
    }
}

void lzh_object_del_component(LZH_OBJECT *object, void *cpnt)
{
    if (object && object->components && cpnt) {
        LZH_COMPONENT *elem = (LZH_COMPONENT *)cpnt;

        lzh_cpnt_rb_delete(object->components, elem->type, NULL, NULL);

        elem->object = NULL;
    }
}

/*===========================================================================*/

int lzh_object_rb_comp(const void *obj1, const void *obj2)
{
    LZH_HASH_CODE i1 = *((LZH_HASH_CODE *)obj1);
    LZH_HASH_CODE i2 = *((LZH_HASH_CODE *)obj2);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_object_rb_visit(const LZH_OBJ_RB_NODE *node, void *args)
{
    LZH_OBJECT *object = NULL;

    if (!node) {
        return;
    }

    object = node->value;
    if (!object) {
        return;
    }

    /* 依次递归删除 */
    object->base.state |= LZH_BST_OBJECT_CLEAR;
    lzh_object_remove(object);
}

void lzh_object_rb_visit_update(const LZH_OBJ_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->update) {
            base->update(base, base->update_param);
        }
    }
}

void lzh_object_rb_visit_fixedupdate(const LZH_OBJ_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->fixed_update) {
            base->fixed_update(base, base->fixed_update_param);
        }
    }
}

void lzh_object_rb_visit_draw(const LZH_OBJ_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->draw) {
            base->draw(base, args);
        }
    }
}

void lzh_object_rb_visit_sort_draw(const LZH_OBJ_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->sort_draw) {
            base->sort_draw(base, args);
        }
    }
}

/*===========================================================================*/

RBTREE_IMPLEMENT(LZH_OBJ, lzh_obj, LZH_HASH_CODE, LZH_OBJECT *)
RBTREE_IMPLEMENT(LZH_EXT, lzh_ext, LZH_HASH_CODE, LZH_UINTPTR)

/*===========================================================================*/
