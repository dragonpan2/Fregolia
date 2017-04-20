#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "Weapon.h"
#include "ExternalIncludes.h"
class MeleeWeapon : public Weapon
{
public:
    MeleeWeapon();
    virtual ~MeleeWeapon();
    virtual bool peutTirer();

protected:

private:

};

#endif // MELEEWEAPON_H
