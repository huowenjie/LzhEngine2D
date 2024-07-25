#include "b2_contact.h"
#include "lzh_b2_contact_listener.h"

/*===========================================================================*/

LzhB2ContactListener::LzhB2ContactListener()
{
    beginContact = NULL;
    endContact = NULL;
    beginContactParam = NULL;
    endContactParam = NULL;
}

LzhB2ContactListener::~LzhB2ContactListener()
{
}

void LzhB2ContactListener::BeginContact(b2Contact *contact)
{
    if (beginContact) {
        const b2Fixture *fa = contact->GetFixtureA();
        const b2Fixture *fb = contact->GetFixtureB();

        if (fa && fb) {
            const b2FixtureUserData &da = fa->GetUserData();
            const b2FixtureUserData &db = fb->GetUserData();

            beginContact(
                (LZH_B2_FIXUTRE *)da.pointer,
                (LZH_B2_FIXUTRE *)db.pointer,
                beginContactParam);
        }
    }
}

void LzhB2ContactListener::EndContact(b2Contact *contact)
{
    if (endContact) {
        const b2Fixture *fa = contact->GetFixtureA();
        const b2Fixture *fb = contact->GetFixtureB();

        if (fa && fb) {
            const b2FixtureUserData &da = fa->GetUserData();
            const b2FixtureUserData &db = fb->GetUserData();

            endContact(
                (LZH_B2_FIXUTRE *)da.pointer,
                (LZH_B2_FIXUTRE *)db.pointer,
                endContactParam);
        }
    }
}

/*===========================================================================*/
