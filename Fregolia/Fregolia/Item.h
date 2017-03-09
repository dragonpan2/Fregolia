#ifndef ITEM_H
#define ITEM_H


class Item
{
    public:
        Item();
        virtual ~Item();
        virtual void use(Item itemToUse);

    protected:

    private:
};

#endif // ITEM_H
