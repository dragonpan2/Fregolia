#ifndef CONSUMABLE_H_INCLUDED
#define CONSUMABLE_H_INCLUDED

class Consumable
    {
    public:

        int health;
        void useConsumable();

        void pickupConsumable();
        int getQuantity();

    protected:

    private:
        int quantity = 0;
    };


#endif // CONSUMABLE_H_INCLUDED
