#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include "Inventory.h"
#include "Enemy.h"

class Weapon: public Item
{


public:
    Weapon();
    virtual ~Weapon();
    virtual bool siEquipped();
	virtual void equipWeapon(Item weaponToEquip, Inventory inventory);
	virtual void unequipWeapon(Item weaponToUnequip, Inventory inventory);
	virtual void use(Enemy enemy);

protected:
    bool estProjectile;
    virtual void damageWeapon();
    virtual void rangeWeapon();
private:
    bool isEquipped = false;

};

#endif // WEAPON_H
