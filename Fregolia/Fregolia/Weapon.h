#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"

class Weapon: public Item
{


    public:
        Weapon();
        virtual ~Weapon();
       virtual bool peutTirer();

    protected:
bool estPrpjectile;
virtual void damageWeapon();
        virtual void rangeWeapon();
    private:

};

#endif // WEAPON_H
