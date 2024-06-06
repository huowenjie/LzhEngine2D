#include <lzh_mem.h>

#include "box2d.h"
#include "lzh_b2_contact_listener.h"
#include "lzh_b2_raycast_listener.h"

/*===========================================================================*/

struct LZH_B2_OBJECT
{
    void *object;
};

struct LZH_B2_WORLD 
{
    void *object;
    LzhB2ContactListener *listener;
};

struct LZH_B2_FIXUTRE
{
    void *object;
    void *data;
};

/*===========================================================================*/

LZH_B2_WORLD *lzh_b2_world_create(const LZH_VEC2F *gravity)
{
    b2Vec2 b2g;
    b2g.SetZero();

    if (gravity) {
        b2g.Set(gravity->x, gravity->y);
    }

    b2World *bw = new b2World(b2g);
    if (!bw) {
        return NULL;
    }

    LzhB2ContactListener *contact = new LzhB2ContactListener();
    bw->SetContactListener(contact);
    bw->SetAllowSleeping(false);

    LZH_B2_WORLD *world = (LZH_B2_WORLD *)LZH_MALLOC(sizeof(LZH_B2_WORLD));
    if (!world) {
        delete bw;
        return NULL;
    }
    memset(world, 0, sizeof(LZH_B2_WORLD));

    world->object = bw;
    world->listener = contact;
    return world;
}

void lzh_b2_world_destroy(LZH_B2_WORLD *world)
{
    if (world) {
        if (world->listener) {
            LzhB2ContactListener *listener = world->listener;
            delete listener;
            world->listener = NULL;
        }

        if (world->object) {
            b2World *bw = (b2World *)world->object;
            delete bw;
            world->object = NULL;
        }
        LZH_FREE(world);
    }
}

void lzh_b2_world_set_gravity(LZH_B2_WORLD *world, const LZH_VEC2F *gravity)
{
    if (world && world->object) {
        b2World *bw = (b2World *)world->object;
        if (gravity) {
            bw->SetGravity(b2Vec2(gravity->x, gravity->y));
        }
    }
}

void lzh_b2_world_set_begin_contact(
    LZH_B2_WORLD *world, LZH_B2_BEGIN_CONTACT cb, void *args)
{
    if (world && world->listener) {
        LzhB2ContactListener *listener = world->listener;
        listener->beginContact = cb;
        listener->beginContactParam = args;
    }
}

void lzh_b2_world_set_end_contact(
    LZH_B2_WORLD *world, LZH_B2_END_CONTACT cb, void *args)
{
    if (world && world->listener) {
        LzhB2ContactListener *listener = world->listener;
        listener->endContact = cb;
        listener->endContactParam = args;
    }
}

void lzh_b2_world_step(LZH_B2_WORLD *world, float step, int vit, int pit)
{
    if (world && world->object) {
        b2World *bw = (b2World *)world->object;
        bw->Step(step, vit, pit);
    }
}

LZH_BOOL lzh_b2_world_raycast(
    LZH_B2_WORLD *world,
    const LZH_VEC2F *start,
    const LZH_VEC2F *end,
    LZH_B2_RAYHIT *hit,
    LZH_B2_RAYHIT_OPT opt)
{
    b2World *bw = NULL;
    LzhB2RayCastListener *listener = NULL;
    LZH_VEC2F ptvec = lzh_vec2f_xy(0.0f, 0.0f);

    if (!world || !world->object) {
        return LZH_FALSE;
    }

    if (!start || !end) {
        return LZH_FALSE;
    }

    ptvec = lzh_vec2f_sub(end, start);
    if (lzh_vec2f_length(&ptvec) <= 1e-6) {
        return LZH_FALSE;
    }

    bw = (b2World *)world->object;
    listener = new LzhB2RayCastListener();
    listener->hitOption = opt;

    if (!listener) {
        return LZH_FALSE;
    }

    LZH_BOOL isHit = LZH_FALSE;

    do {
        bw->RayCast(listener, b2Vec2(start->x, start->y), b2Vec2(end->x, end->y));

        std::vector<LZH_B2_HITINFO> &infoList = listener->hitInfoList;
        if (infoList.empty()) {
            break;
        }

        if (opt == RO_CHECK) {    
            isHit = LZH_TRUE;
            break;
        }

        if (!hit) {
            break;
        }

        int count = infoList.size();
        LZH_B2_HITINFO *infos = 
            (LZH_B2_HITINFO *)LZH_MALLOC(count * sizeof(LZH_B2_HITINFO));
        if (!infos) {
            break;
        }
        memset(infos, 0, count * sizeof(LZH_B2_HITINFO));

        for (int i = 0; i < count; i++) {
            infos[i] = infoList[i];
        }

        hit->count = count;
        hit->infoList = infos;
        isHit = LZH_TRUE;
    } while (false);

    delete listener;
    return isHit;
}

void lzh_b2_rayhit_clear(LZH_B2_RAYHIT *hit)
{
    if (hit && hit->infoList) {
        LZH_FREE(hit->infoList);
        hit->count = 0;
    }
}

LZH_B2_BODY *lzh_b2_body_create(
    LZH_B2_WORLD *world, const LZH_VEC2F *pos, LZH_B2_BODY_TYPE type)
{
    if (!world || !world->object) {
        return NULL;
    }

    b2World *bw = (b2World *)world->object;
    b2Vec2 bpos;    
    b2BodyDef bddef;

    bpos.SetZero();
    if (pos) {
        bpos.Set(pos->x, pos->y);
    }
    bddef.position = bpos;

    switch (type) {
    case BT_DYNAMIC:
        bddef.type = b2_dynamicBody;
        break;

    case BT_KINEMATIC:
        bddef.type = b2_kinematicBody;
        break;

    case BT_STATIC:
    default:
        bddef.type = b2_staticBody;
        break;
    }

    b2Body *bd = bw->CreateBody(&bddef);
    if (!bd) {
        return NULL;
    }

    LZH_B2_BODY *body = (LZH_B2_BODY *)LZH_MALLOC(sizeof(LZH_B2_BODY));
    if (!body) {
        bw->DestroyBody(bd);
        return NULL;
    }
    memset(body, 0, sizeof(LZH_B2_BODY));

    body->object = bd;
    return body;
}

void lzh_b2_body_destroy(LZH_B2_WORLD *world, LZH_B2_BODY *body)
{
    if (!world || !world->object) {
        return;
    }

    b2World *bw = (b2World *)world->object;

    if (body) {
        if (body->object) {
            b2Body *bd = (b2Body *)body->object;
            bw->DestroyBody(bd);
        }
        LZH_FREE(body);
    }
}

void lzh_b2_body_set_transform(LZH_B2_BODY *body, const LZH_VEC2F *pos, float angle)
{
    if (!body || !body->object) {
        return;
    }

    if (!pos) {
        return;
    }

    b2Body *bd = (b2Body *)body->object;
    bd->SetTransform(b2Vec2(pos->x, pos->y), angle);
}

void lzh_b2_body_set_type(LZH_B2_BODY *body, LZH_B2_BODY_TYPE type)
{
    if (!body || !body->object) {
        return;
    }

    b2Body *bd = (b2Body *)body->object;
    
    switch (type) {
    case BT_DYNAMIC:
        bd->SetType(b2_dynamicBody);
        break;

    case BT_KINEMATIC:
        bd->SetType(b2_kinematicBody);
        break;

    case BT_STATIC:
    default:
        bd->SetType(b2_staticBody);
        break;
    }
}

LZH_B2_FIXUTRE *lzh_b2_fixture_create(LZH_B2_BODY *body, LZH_B2_SHAPE *shape)
{
    if (!body || !body->object) {
        return NULL;
    }

    if (!shape || !shape->object) {
        return NULL;
    }

    b2Body *bd = (b2Body *)body->object;
    b2Shape *bs = (b2Shape *)shape->object;

    b2Fixture *bf = bd->CreateFixture(bs, 0.0f);
    if (!bf) {
        return NULL;
    }

    LZH_B2_FIXUTRE *fixture = (LZH_B2_FIXUTRE *)LZH_MALLOC(sizeof(LZH_B2_FIXUTRE));
    if (!fixture) {
        bd->DestroyFixture(bf);
        return NULL;
    }
    memset(fixture, 0, sizeof(LZH_B2_FIXUTRE));

    fixture->object = bf;

    // 将包装对象 LZH_B2_FIXUTRE 缓存
    b2FixtureUserData &userData = bf->GetUserData();
    userData.pointer = (uintptr_t)fixture;
    return fixture;
}

void lzh_b2_fixture_destroy(LZH_B2_BODY *body, LZH_B2_FIXUTRE *fixture)
{
    if (!body || !body->object) {
        return;
    }

    b2Body *bd = (b2Body *)body->object;

    if (fixture) {
        if (fixture->object) {
            b2Fixture *bf = (b2Fixture *)fixture->object;
            fixture->data = NULL;

            b2FixtureUserData &data = bf->GetUserData();
            data.pointer = 0;

            bd->DestroyFixture(bf);
        }
        LZH_FREE(fixture);
    }
}

void lzh_b2_fixture_set_density(LZH_B2_FIXUTRE *fixture, float density)
{
    if (fixture && fixture->object) {
        b2Fixture *bf = (b2Fixture *)fixture->object;
        bf->SetDensity(density);
    }
}

void lzh_b2_fixture_set_data(LZH_B2_FIXUTRE *fixture, void *data)
{
    if (fixture) {
        fixture->data = data;
    }
}

void *lzh_b2_fixture_get_data(LZH_B2_FIXUTRE *fixture)
{
    if (fixture) { 
        return fixture->data;
    }
    return NULL;
}

LZH_B2_SHAPE_CIRCLE *lzh_b2_shape_circle_create(const LZH_VEC2F *center, float radius)
{
    b2CircleShape *bc = new b2CircleShape();
    if (!bc) {
        return NULL;
    }

    bc->m_p.SetZero();
    if (center) {
        bc->m_p.Set(center->x, center->y);
    }
    bc->m_radius = radius;

    LZH_B2_SHAPE_CIRCLE *circle = (LZH_B2_SHAPE_CIRCLE *)LZH_MALLOC(sizeof(LZH_B2_SHAPE_CIRCLE));
    if (!circle) {
        delete bc;
        return NULL;
    }
    memset(circle, 0, sizeof(LZH_B2_SHAPE_CIRCLE));

    circle->object = bc;
    return circle;
}

void lzh_b2_shape_circle_destroy(LZH_B2_SHAPE_CIRCLE *circle)
{
    if (circle) {
        if (circle->object) {
            b2CircleShape *bc = (b2CircleShape *)circle->object;
            delete bc;
            circle->object = NULL;
        }
        LZH_FREE(circle);
    }
}

LZH_B2_SHAPE_BOX *lzh_b2_shape_box_create(const LZH_VEC2F *center, float ew, float eh)
{
    b2PolygonShape *bp = new b2PolygonShape();
    if (!bp) {
        return NULL;
    }

    b2Vec2 ct;

    ct.SetZero();
    if (center) {
        ct.Set(center->x, center->y);
    }
    bp->SetAsBox(ew, eh, ct, 0.0f);

    LZH_B2_SHAPE_BOX *box = (LZH_B2_SHAPE_BOX *)LZH_MALLOC(sizeof(LZH_B2_SHAPE_BOX));
    if (!box) {
        delete bp;
        return NULL;
    }
    memset(box, 0, sizeof(LZH_B2_SHAPE_BOX));

    box->object = bp;
    return box;
}

void lzh_b2_shape_box_destroy(LZH_B2_SHAPE_BOX *box)
{
    if (box) {
        if (box->object) {
            b2PolygonShape *bp = (b2PolygonShape *)box->object;
            delete bp;
            box->object = NULL;
        }
        LZH_FREE(box);
    }
}

/*===========================================================================*/
