#include "Inventory.h"

Inventory::Inventory()
{

    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

bool Inventory::fullCheck() {
    if (inventoryList.size() < 10) {
        return false;
    }
        return true;

}

void Inventory::pickup(Item itemToAdd) {
    inventoryList.push_back(itemToAdd);
}

void Inventory::drop(Item itemToDrop ) {

}

void Inventory::dropDirect(int indexToDrop) {

}

void Inventory::dropAll() {

}

void Inventory::destroyItem(Item itemToDestroy) {

}

void Inventory::destroyItemDirect(int indexToDestroy) {
}
