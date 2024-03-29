#include "lzh_component.h"

/*===========================================================================*/

LINK_IMPLEMENT(LZH_CPNT, lzh_cpnt, LZH_COMPONENT *)

int lzh_link_cpnt_comp(const void *cpnt1, const void *cpnt2)
{
    LZH_COMPONENT *component1 = *((LZH_COMPONENT **)cpnt1);
    LZH_COMPONENT *component2 = *((LZH_COMPONENT **)cpnt2);

    if (!component1 && component2) {
        return -1;
    } else if (component1 && !component2) {
        return 1;
    } else if (!component1 && !component2) {
        return 0;
    }

    return strcmp(component1->base.name, component2->base.name);
}

void lzh_link_cpnt_visit(const LZH_CPNT_LINK_NODE *node, void *args)
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

LZH_COMPONENT *lzh_link_cpnt_get_type(LZH_CPNT_LINK *link, LZH_UINT32 type)
{
    LZH_COMPONENT *ret = NULL;
    LZH_CPNT_LINK_NODE *node = NULL;
    int count = 0;
    int i = 0;

    if (!link) {
        return NULL;
    }

    node = link->head;
    count = link->count;
    i = 0;

    while (i++ < count) {
        LZH_COMPONENT *cpnt = node->value;

        if (cpnt && cpnt->type == type) {
            ret = cpnt;
            break;
        }
        node = node->next;
    }

    return ret;
}

/*===========================================================================*/
