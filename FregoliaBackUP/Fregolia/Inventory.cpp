#include "Inventory.h"
#include <algorithm>

Inventory::Inventory()
{

    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

bool Inventory::fullCheck()
{
    if (inventoryList.size() < 10)
    {
        return false;
    }
    return true;

}

void Inventory::pickup(Item itemToAdd)
{
    inventoryList.push_back(itemToAdd);
}

void Inventory::drop(Item itemToDrop)
{
    //inventoryList.erase(std::remove(inventoryList.begin(), inventoryList.end(), itemToDrop), inventoryList.end());
}

void Inventory::dropDirect(int indexToDrop)
{
    inventoryList.erase(inventoryList.begin() + indexToDrop-1);
}

void Inventory::dropAll()
{
    inventoryList.clear();
}

void Inventory::destroyItem(const Item itemToDestroy)
{
    //inventoryList.erase(std::remove(inventoryList.begin(), inventoryList.end(), itemToDestroy), inventoryList.end());
}

void Inventory::destroyItemDirect(int indexToDestroy)
{
    inventoryList.erase(inventoryList.begin() + indexToDestroy);
}

void Inventory::addItem(Item itemToAdd)
{
    //visuellement ajouter l'item a l'inventaire
    inventoryList.push_back(itemToAdd);

}

void Inventory::removeItem(Item itemToRemove)
{

    //visuellement enlever l'item de l'inventaire
    //inventoryList.erase(std::remove(inventoryList.begin(), inventoryList.end(), itemToRemove), inventoryList.end());
}
