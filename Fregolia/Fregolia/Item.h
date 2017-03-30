#ifndef ITEM_H
#define ITEM_H


class Item
{
    public:
        Item();
        virtual ~Item();

        virtual void use(Item itemToUse);
        virtual void use();


    protected:

    private:
};

#endif // ITEM_H
