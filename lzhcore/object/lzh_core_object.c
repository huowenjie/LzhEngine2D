#include "lzh_core_object.h"

/*===========================================================================*/

LINK_IMPLEMENT(LZH_OBJ, lzh_obj, LZH_OBJECT *)

/*===========================================================================*/

void lzh_object_remove(LZH_OBJECT *object)
{
    if (object) {        
        lzh_base_quit((LZH_BASE *)object);

        if (object->components) {
            lzh_cpnt_link_clear(object->components, lzh_link_cpnts_visit, NULL);
            lzh_cpnt_link_destroy(object->components);
            object->components = NULL;
        }

        if (object->children) {
            lzh_obj_link_clear(object->children, lzh_link_object_visit, NULL);
            lzh_obj_link_destroy(object->children);
            object->children = NULL;
        }

        LZH_FREE(object);
    }
}

/*===========================================================================*/

int lzh_link_object_comp(const void *obj1, const void *obj2)
{
    LZH_OBJECT *object1 = *((LZH_OBJECT **)obj1);
    LZH_OBJECT *object2 = *((LZH_OBJECT **)obj2);

    if (!object1 && object1) {
        return -1;
    } else if (object1 && !object1) {
        return 1;
    } else if (!object1 && !object1) {
        return 0;
    }

    return strcmp(object1->base.name, object2->base.name);;
}

void lzh_link_object_visit(const LZH_OBJ_LINK_NODE *node, void *args)
{
    LZH_OBJECT *object = NULL;

    if (!node) {
        return;
    }

    object = node->value;
    if (!object) {
        return;
    }

    /* ÒÀ´ÎµÝ¹éÉ¾³ý */
    lzh_object_remove(object);
}

/*===========================================================================*/
