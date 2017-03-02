#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H
#include "Weapon.h"
#include "externalIncludes.h"

class RangedWeapon: public Weapon
{
    public:
        RangedWeapon();
        virtual ~RangedWeapon();
virtual bool peutTirer();
    protected:

    private:
};

#endif // RANGEDWEAPON_H
