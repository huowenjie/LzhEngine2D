#include "lzh_core_scene.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

int lzh_scene_layer_comp(const void *a, const void *b)
{
    int i1 = *((int *)a);
    int i2 = *((int *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_scene_layer_visit_free(const SCENE_LAYER_RB_NODE *node, void *args)
{
    if (node) {
        SCENE_OBJ_RB_TREE *sub_tree = node->value;
        scene_obj_rb_destroy(sub_tree, lzh_scene_objs_visit_free, NULL);
    }
}

void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_OBJECT *object = node->value;
        lzh_object_remove(object);
    }
}

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_OBJ, scene_obj, int, LZH_OBJECT *)

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_LAYER, scene_layer, int, SCENE_OBJ_RB_TREE *)

/*===========================================================================*/
