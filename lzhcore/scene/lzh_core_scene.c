#include "lzh_core_scene.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

int lzh_scene_object_map_comp(const void *a, const void *b)
{
    LZH_HASH_CODE i1 = *((LZH_HASH_CODE *)a);
    LZH_HASH_CODE i2 = *((LZH_HASH_CODE *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

int lzh_scene_objs_comp(const void *a, const void *b)
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

void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_OBJECT *object = node->value;
        lzh_object_remove(object);
    }
}

void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->update) {
            base->update(base, base->update_param);
        }
    }
}

void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->fixed_update) {
            base->fixed_update(base, base->fixed_update_param);
        }
    }
}

void lzh_scene_objs_visit_draw(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->draw) {
            base->draw(base, base->draw_param);
        }
    }
}

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_OBJ, scene_obj, int, LZH_OBJECT *)

/*===========================================================================*/

RBTREE_IMPLEMENT(OBJECT_MAP, object_map, LZH_HASH_CODE, LZH_OBJECT *)

/*===========================================================================*/
