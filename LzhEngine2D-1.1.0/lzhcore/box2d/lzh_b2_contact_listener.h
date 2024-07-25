#ifndef __LZH_B2_CONTACT_LISTENER_H__
#define __LZH_B2_CONTACT_LISTENER_H__

#include <map>
#include "lzh_b2_api.h"
#include "b2_world_callbacks.h"

/*===========================================================================*/
/* Åö×²¼àÌý */
/*===========================================================================*/

class LzhB2ContactListener : public b2ContactListener
{
public:
    LzhB2ContactListener();
    virtual ~LzhB2ContactListener();

public:
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);

public:
    LZH_B2_BEGIN_CONTACT beginContact;
    LZH_B2_END_CONTACT endContact;

    void *beginContactParam;
    void *endContactParam;
};

/*===========================================================================*/

#endif // __LZH_B2_CONTACT_LISTENER_H__
