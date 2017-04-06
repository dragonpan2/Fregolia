#include "RangedWeapon.h"



RangedWeapon::RangedWeapon()
{

    //ctor
}

RangedWeapon::~RangedWeapon()
{
    //dtor
}
bool RangedWeapon ::  peutTirer()
{
Weapon::mEstProjectile=true;
return mEstProjectile;
}
