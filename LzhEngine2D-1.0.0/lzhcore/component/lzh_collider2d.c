#include <lzh_engine.h>
#include <lzh_systool.h>

#include "lzh_core_rigidbody2d.h"
#include "lzh_core_collider2d.h"
#include "lzh_core_transform.h"
#include "lzh_core_camera.h"

#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

/* collider 的表示 */
static int lzh_collider_id = 0;

/*===========================================================================*/

LZH_COLLIDER2D *lzh_collider2d_create(LZH_RIGIDBODY2D *body)
{
    LZH_COLLIDER2D *collider = NULL;

    if (!body) {
        return NULL;
    }

    collider = LZH_MALLOC(sizeof(LZH_COLLIDER2D));
    if (!collider) {
        return NULL;
    }
    memset(collider, 0, sizeof(LZH_COLLIDER2D));

    collider->id = lzh_collider_id++;
    lzh_collider2d_load(collider, body);

    /* 将 collider 交予 rigidbody 管理 */
    lzh_rigidbody2d_add_cld2d(body, collider);
    return collider;
}

void lzh_collider2d_destroy(LZH_COLLIDER2D *collider)
{
    if (collider) {
        lzh_rigibody2d_remove_cld2d(collider->rigidbody, collider);
    }
}

void lzh_collider2d_set_box(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h)
{
    if (collider) {
        lzh_collider2d_create_box2d(collider, cx, cy, w, h);
    }
}

void lzh_collider2d_set_circle(
    LZH_COLLIDER2D *collider, float cx, float cy, float r)
{
    if (collider) {
        lzh_collider2d_create_circle2d(collider, cx, cy, r);
    }
}

void lzh_collider2d_set_start_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args)
{
    if (collider) {
        collider->start_contact = cb;
        collider->start_contact_args = args;
    }
}

void lzh_collider2d_set_end_contact(
    LZH_COLLIDER2D *collider, LZH_COLLIDER2D_CB cb, void *args)
{
    if (collider) {
        collider->end_contact = cb;
        collider->end_contact_args = args;
    }
}

/*===========================================================================*/
