#ifndef __LZH_B2_RAYCAST_LISTENER_H__
#define __LZH_B2_RAYCAST_LISTENER_H__

#include <vector>
#include "lzh_b2_api.h"
#include "b2_world_callbacks.h"

/*===========================================================================*/
/* ÉäÏßÅö×²¼àÌý */
/*===========================================================================*/

class LzhB2RayCastListener : public b2RayCastCallback
{
public:
    LzhB2RayCastListener();
    virtual ~LzhB2RayCastListener();

public:
    virtual float ReportFixture(
        b2Fixture *fixture,
        const b2Vec2 &point,
        const b2Vec2 &normal,
        float fraction);

public:
    std::vector<LZH_B2_HITINFO> hitInfoList;
    LZH_B2_RAYHIT_OPT hitOption;
};

/*===========================================================================*/

#endif // __LZH_B2_RAYCAST_LISTENER_H__
