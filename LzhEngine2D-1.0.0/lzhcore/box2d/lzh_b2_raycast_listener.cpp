#include "b2_fixture.h"
#include "lzh_b2_raycast_listener.h"

/*===========================================================================*/

LzhB2RayCastListener::LzhB2RayCastListener()
{
    hitOption = RO_CHECK;
}

LzhB2RayCastListener::~LzhB2RayCastListener()
{
}

float LzhB2RayCastListener::ReportFixture(
    b2Fixture *fixture,
    const b2Vec2 &point,
    const b2Vec2 &normal,
    float fraction)
{
    LZH_B2_HITINFO info;

    const b2FixtureUserData &data = fixture->GetUserData();
    info.fixture = (LZH_B2_FIXUTRE *)data.pointer;
    info.point = lzh_vec2f_xy(point.x, point.y);
    info.normal = lzh_vec2f_xy(point.x, point.y);
    hitInfoList.push_back(info);

    float ret = 0.0f;

    switch (hitOption) {
    case RO_CLOSEST_HIT:
        ret = fraction;
        break;

    case RO_ALL_HIT:
        ret = 1.0f;
        break;

    case RO_CHECK:
    default:
        ret = 0.0f;
        break;
    }

    return ret;
}

/*===========================================================================*/
