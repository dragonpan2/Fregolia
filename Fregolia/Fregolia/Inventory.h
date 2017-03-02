#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
#include "externalIncludes.h"

class Inventory
{
    public:
        Inventory();
        virtual ~Inventory();
      bool  fullCheck();
      void  pickup(Item itemToAdd);
       void drop(Item itemToDrop);
        void dropDirect(int indexToDrop);
        void dropAll();
       std:: vector<Item> inventoryList;

    protected:

    private:

};

#endif // INVENTORY_H
