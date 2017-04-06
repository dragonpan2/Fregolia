#include "Weapon.h"
#include "Inventory.h"
#include "Enemy.h"

Weapon::Weapon()
{
    //ctor
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::damageWeapon() {
}

void Weapon::rangeWeapon() {
}

//void Weapon::equipWeapon(Item weaponToEquip, Inventory inventory)
//{
   // isEquipped = true;
    //visually update to show weapon on character
  //  inventory.removeItem(weaponToEquip); //remove weapon from inventory

//}
//void Weapon::unequipWeapon(Item weaponToUnequip, Inventory inventory)
//{
    //isEquipped = false;
    //visually update to not show weapon on character
    //inventory.addItem(weaponToUnequip); //add weapon to inventory
//}

//void Weapon::use(Enemy enemy)
//{
    //Appeler classe bool qui teste collision avec ennemi pour savoir si ce dernier prend du dommage
    //Si oui, appeler classe dans Enemy qui reduit les points de vie de ce dernier
    //enemy.ennemiTouche(5);
    //Visually update to show weapon attack animation
//}

bool Weapon::siEquipped()
{
    return mIsEquipped;
}

void Weapon::loadWeapon(std::string pFilePath, glm::vec2 pPos)
{
    this->loadFile(pFilePath, pPos);
}

void Weapon::setEquipped(bool pEquipped)
{
    mIsEquipped = pEquipped;
}

void Weapon::setBeingUsed(bool pUse)
{
    mBeingUsed = pUse;
}

bool Weapon::siBeingUsed()
{
    return mBeingUsed;
}



