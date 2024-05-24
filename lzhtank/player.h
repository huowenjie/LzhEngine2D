#ifndef __PALYER_H__
#define __PALYER_H__

#include "tank.h"

/*===========================================================================*/
/* player */
/*===========================================================================*/

class Player : public Tank
{
public:
    Player(LZH_ENGINE *eg, Scene *scene);
    virtual ~Player();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);
};


/*===========================================================================*/

#endif /* __PALYER_H__ */
