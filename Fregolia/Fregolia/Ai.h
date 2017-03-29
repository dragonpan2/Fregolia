#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "externalIncludes.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();
        int previousState; //1 green, 2 yellow, 3 red,4 orange
        bool aiActive;
        void stateSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection , bool isPlayerSneak, int previousState);
        void greenState(glm::vec2 thisPos,glm::vec2 thisDirection);
        void yellowState();
        void redState();
        void orangeState();
        int AiMethode();

    protected:

    private:
};


#endif // AI_H_INCLUDED
