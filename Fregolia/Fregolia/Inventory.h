#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
#include "externalIncludes.h"

class Inventory
{
public:
    Inventory();
    virtual ~Inventory();
    int selectedIndex;
    bool  fullCheck();
    void  pickup(Item itemToAdd);
    void pickupMethod(Item itemToAdd);
    void drop(Item itemToDrop);
    void dropDirect(int indexToDrop);
    void dropAll();
    void destroyItem(Item itemToDestroy);
    void destroyItemDirect(int indexToDestroy);
    std:: vector<Item> inventoryList;

protected:

private:

};

#endif // INVENTORY_H
