#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include "Inventory.h"
#include "Enemy.h"
#include "LoadModel.h"
#include "ExternalIncludes.h"

class Weapon: public Item
{


public:
    Weapon();
    virtual ~Weapon();
    virtual void loadWeapon(std::string pFilePath, glm::vec2 pPos) final;
    virtual bool siEquipped();
    virtual bool siBeingUsed();
	//virtual void equipWeapon(Item weaponToEquip, Inventory inventory);
	//virtual void unequipWeapon(Item weaponToUnequip, Inventory inventory);
	//virtual void use(Enemy enemy);
	virtual void setEquipped(bool pEquipped);
	virtual void setBeingUsed(bool pUse);

protected:
    virtual void damageWeapon();
    virtual void rangeWeapon();
    bool mEstProjectile;
private:
    bool mIsEquipped = false;
    bool mBeingUsed = false;

};

#endif // WEAPON_H
