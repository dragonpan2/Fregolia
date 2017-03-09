#include "Inventory.h"

Inventory::Inventory()
{

    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

bool Inventory::fullCheck() { //check if the inv is full
    if (inventoryList.size() < 10) {
        return false;
    }
        return true;

}

void Inventory::pickup(Item itemToAdd) { //put a item in a inv
    inventoryList.push_back(itemToAdd);
}

void Inventory::pickupMethod(Item itemToAdd) { // combine fullCheck & pickup // this method should be used in game
   if (!fullCheck()) {
        pickup(itemToAdd);
   }
}

void Inventory::drop(Item itemToDrop ) { //

}

void Inventory::dropDirect(int indexToDrop) {

}

void Inventory::dropAll() {

}

void Inventory::destroyItem(const Item itemToDestroy) {
   // inventoryList.erase(std::remove(inventoryList.begin(), inventoryList.end(), itemToDestroy), inventoryList.end());
}

void Inventory::destroyItemDirect(int indexToDestroy) {
    inventoryList.erase(inventoryList.begin() + indexToDestroy);
}


