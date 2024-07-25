#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "tank.h"

/*===========================================================================*/
/* enemy */
/*===========================================================================*/

class Enemy : public Tank
{
public:
    Enemy(LZH_ENGINE *eg, Scene *scene);
    virtual ~Enemy();

protected:
    bool MoveToPos(glm::vec2 &pos, float delta);

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_TRANSFORM *chassisTransform;
    LZH_TRANSFORM *turretTransform;

    glm::vec2 visitList[4];
    int currentIndex;
    float intervalCount;
};

/*===========================================================================*/

#endif /* __ENEMY_H__ */
