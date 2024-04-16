#include "lzh_component.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

void lzh_cpnt_init(LZH_COMPONENT *cpnt)
{
    lzh_base_init((LZH_BASE *)cpnt);
    lzh_base_set_type((LZH_BASE *)cpnt, LZH_BT_COMPONENT);

    cpnt->object = NULL;
    cpnt->remove_component = NULL;
    cpnt->type = 0;
}

void lzh_cpnt_quit(LZH_COMPONENT *cpnt)
{
    cpnt->object = NULL;
    cpnt->remove_component = NULL;
    cpnt->type = 0;
    lzh_base_quit((LZH_BASE *)cpnt);
}

void lzh_cpnt_destroy(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        /* ??????????????? */
        if (cpnt->object) {
            LZH_OBJECT *obj = cpnt->object;
            lzh_cpnt_rb_delete(obj->components, cpnt->type, NULL, NULL);
            cpnt->object = NULL;
        }

        if (cpnt->remove_component) {
            cpnt->remove_component(cpnt);
        }
    }
}

/*===========================================================================*/

int lzh_cpnt_rb_comp(const void *cpnt1, const void *cpnt2)
{
    LZH_UINT32 *i1 = *((LZH_UINT32 **)cpnt1);
    LZH_UINT32 *i2 = *((LZH_UINT32 **)cpnt2);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_cpnt_rb_visit(const LZH_CPNT_RB_NODE *node, void *args)
{
    LZH_COMPONENT *cpnt = NULL;

    if (!node) {
        return;
    }

    cpnt = node->value;
    if (!cpnt) {
        return;
    }

    /* ÒÆ³ý×é¼þ */
    if (cpnt->remove_component) {
        cpnt->remove_component(cpnt);
    }
}

void lzh_cpnt_rb_visit_update(const LZH_CPNT_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->update) {
            base->update(base, base->update_param);
        }
    }
}

void lzh_cpnt_rb_visit_fixedupdate(const LZH_CPNT_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->fixed_update) {
            base->fixed_update(base, base->fixed_update_param);
        }
    }
}

void lzh_cpnt_rb_visit_draw(const LZH_CPNT_RB_NODE *node, void *args)
{
    if (node && node->value) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base->draw) {
            base->draw(base, base->draw_param);
        }
    }
}

LZH_COMPONENT *lzh_cpnt_get_type(LZH_CPNT_RB_TREE *tree, LZH_UINT32 type)
{
    LZH_COMPONENT *ret = NULL;

    if (!tree) {
        return NULL;
    }

    lzh_cpnt_rb_find(tree, type, &ret);
    return ret;
}

/*===========================================================================*/

RBTREE_IMPLEMENT(LZH_CPNT, lzh_cpnt, LZH_UINT32, LZH_COMPONENT *)

/*===========================================================================*/
