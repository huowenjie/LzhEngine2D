#include "lzh_core_rigidbody2d.h"
#include "lzh_core_collider2d.h"

/*===========================================================================*/

RBTREE_IMPLEMENT(CLD2D, cld2d, int, LZH_COLLIDER2D *)

int lzh_rigidbody2d_cld2d_comp(const void *a, const void *b)
{
    LZH_HASH_CODE i1 = *((int *)a);
    LZH_HASH_CODE i2 = *((int *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_rigidbody2d_cld2d_delvisit(const CLD2D_RB_NODE *node, void *args)
{
    if (node) {
        LZH_COLLIDER2D *collider = node->value;
        lzh_collider2d_remove(collider);
    }
}

/*===========================================================================*/

void lzh_rigidbody2d_add_cld2d(
    LZH_RIGIDBODY2D *rigidbody, LZH_COLLIDER2D *collider2d)
{
    if (rigidbody && collider2d) {
        collider2d->rigidbody = rigidbody;
        cld2d_rb_insert(rigidbody->collider2ds, collider2d->id, collider2d);
    }
}

void lzh_rigibody2d_remove_cld2d(LZH_RIGIDBODY2D *rigidbody, LZH_COLLIDER2D *collider2d)
{
    if (rigidbody && collider2d) {
        cld2d_rb_delete(
            rigidbody->collider2ds, collider2d->id,
            lzh_rigidbody2d_cld2d_delvisit, NULL);
    }
}

/*===========================================================================*/
