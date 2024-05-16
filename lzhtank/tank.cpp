#include <lzh_object.h>
#include <lzh_sprite.h>

#include "globalres.h"
#include "tank.h"

/*===========================================================================*/

Tank::Tank(LZH_ENGINE *engine)
{
    object = lzh_object_create(engine);
    chassis = lzh_object_create(engine);
    turret = lzh_object_create(engine);

    chassisSp = lzh_sprite_create(engine, get_tank_res_path());
    turretSp = lzh_sprite_create(engine, get_tank_turret_path());

    transform = lzh_object_get_transform(object);
    chassisTransform = lzh_object_get_transform(chassis);
    turretTransform = lzh_object_get_transform(turret);

    lzh_object_add_component(chassis, chassisSp);
    lzh_object_add_component(turret, turretSp);
}

Tank::~Tank()
{
    
}

/*===========================================================================*/

void Tank::Update()
{

}

void Tank::FixedUpdate()
{

}

/*===========================================================================*/

void Tank::UpdateTank(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{

}

void Tank::FixedUpdateTank(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{

}

/*===========================================================================*/
