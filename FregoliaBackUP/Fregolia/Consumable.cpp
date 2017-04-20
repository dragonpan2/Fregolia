#include "Consumable.h"

void Consumable::pickupConsumable(){
    quantity++;
}

int Consumable::getQuantity(){
    return quantity;
}
