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


void Weapon::equipWeapon(Item weaponToEquip, Inventory inventory)
{
    isEquipped = true;
    //visually update to show weapon on character
    inventory.removeItem(weaponToEquip); //enlever l'arme de l'inventaire

}
void Weapon::unequipWeapon(Item weaponToUnequip, Inventory inventory)
{
    isEquipped = false;
    //visually update to not show weapon on character
    inventory.addItem(weaponToUnequip); //retourner l'arme a l'inventaire
}

void Weapon::use(Enemy enemy) {
    //appeler classe bool qui teste collision avec ennemi pour savoir si ce dernier prend du dommage
    //Si oui, appeler classe dans Enemy qui reduit les hitpoints de ce dernier
    enemy.ennemiTouche(5);
    //visually update to show weapon attack animation
}

bool Weapon::siEquipped(){
    return isEquipped;
}

