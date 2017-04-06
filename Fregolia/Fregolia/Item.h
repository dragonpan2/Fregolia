#ifndef ITEM_H
#define ITEM_H
#include "LoadModel.h"


class Item : public imageModel
{
    public:
        Item();
        virtual ~Item();

        virtual void use(Item pItemToUse);
        virtual void use();

    protected:

    private:
};

#endif // ITEM_H
