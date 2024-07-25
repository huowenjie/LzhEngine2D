#include <lzh_mem.h>

#include "lzh_core_collider2d.h"
#include "lzh_core_rigidbody2d.h"

/*===========================================================================*/

void lzh_collider2d_remove(LZH_COLLIDER2D *collider)
{
    if (collider) {
        lzh_collider2d_unload(collider, collider->rigidbody);
        LZH_FREE(collider);
    }
}

void lzh_collider2d_load(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body)
{
    LZH_B2_FIXUTRE *b2fixture = NULL;
    LZH_B2_SHAPE_BOX *b2box = NULL;
    LZH_B2_BODY *b2body = NULL;

    if (!collider || !body) {
        return;
    }

    b2body = body->b2body;
    if (!b2body) {
        return;
    }

    b2box = lzh_b2_shape_box_create(0.0f, 0.0f, 1.0f, 1.0f);
    if (!b2box) {
        return;
    }

    b2fixture = lzh_b2_fixture_create(b2body, b2box);
    if (!b2fixture) {
        lzh_b2_shape_box_destroy(b2box);
        return;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(b2fixture, collider);
    lzh_b2_shape_box_destroy(b2box);

    collider->b2fixture = b2fixture;
}

void lzh_collider2d_unload(LZH_COLLIDER2D *collider, LZH_RIGIDBODY2D *body)
{
    if (!collider || !body) {
        return;
    }

    if (body->b2body) {
        if (collider->b2fixture) {
            lzh_b2_fixture_destroy(body->b2body, collider->b2fixture);
            collider->b2fixture = NULL;
        }
    }
}

void lzh_collider2d_create_box2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float w, float h)
{
    LZH_RIGIDBODY2D *rigidbody = NULL;
    LZH_B2_BODY *b2body = NULL;
    LZH_B2_FIXUTRE *fixture = NULL;
    LZH_B2_SHAPE_BOX *b2box = NULL;
    void *data = NULL;

    if (!collider) {
        return;
    }

    rigidbody = collider->rigidbody;
    if (!rigidbody) {
        return;
    }

    b2body = rigidbody->b2body;
    if (!b2body) {
        return;
    }

    fixture = collider->b2fixture;
    if (fixture) {
        data = lzh_b2_fixture_get_data(fixture);
        b2box = lzh_b2_shape_box_create(
            cx, cy, w / 2.0f, w / 2.0f);
        if (!b2box) {
            goto end;
        }

        lzh_b2_fixture_destroy(b2body, fixture);
        collider->b2fixture = NULL;
    }

    fixture = lzh_b2_fixture_create(b2body, b2box);
    if (!fixture) {
        goto end;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(fixture, data);
    collider->b2fixture = fixture;

end:
    if (b2box) {
        lzh_b2_shape_box_destroy(b2box);
    }
}

void lzh_collider2d_create_circle2d(
    LZH_COLLIDER2D *collider, float cx, float cy, float r)
{
    LZH_RIGIDBODY2D *rigidbody = NULL;
    LZH_B2_BODY *b2body = NULL;
    LZH_B2_FIXUTRE *fixture = NULL;
    LZH_B2_SHAPE_CIRCLE *b2circle = NULL;
    void *data = NULL;

    if (!collider) {
        return;
    }

    rigidbody = collider->rigidbody;
    if (!rigidbody) {
        return;
    }

    b2body = rigidbody->b2body;
    if (!b2body) {
        return;
    }

    fixture = collider->b2fixture;
    if (fixture) {
        data = lzh_b2_fixture_get_data(fixture);
        b2circle = lzh_b2_shape_circle_create(cx, cy, r);
        if (!b2circle) {
            goto end;
        }

        lzh_b2_fixture_destroy(b2body, fixture);
        collider->b2fixture = NULL;
    }

    fixture = lzh_b2_fixture_create(b2body, b2circle);
    if (!fixture) {
        goto end;
    }

    /* 设置用户数据 */
    lzh_b2_fixture_set_data(fixture, data);
    collider->b2fixture = fixture;

end:
    if (b2circle) {
        lzh_b2_shape_circle_destroy(b2circle);
    }
}

/*===========================================================================*/
