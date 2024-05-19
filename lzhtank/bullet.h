#ifndef __BULLET_H__
#define __BULLET_H__

#include "object.h"

/*===========================================================================*/
/* bullet */
/*===========================================================================*/

class Bullet : public Object
{
public:
    Bullet(LZH_ENGINE *engine);
    virtual ~Bullet();

protected:
    virtual void Update(LZH_ENGINE *eg);
    virtual void FixedUpdate(LZH_ENGINE *eg);

protected:
    LZH_SPRITE *bulletSp;

    // 移动速度
    float moveSpeed;

    // 射程
    float fireDistance;
};

/*===========================================================================*/

#endif /* __BULLET_H__ */
