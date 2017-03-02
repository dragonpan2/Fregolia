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
