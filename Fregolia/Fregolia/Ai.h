#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include "glm.hpp"
#include "externalIncludes.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();

        //var
        int previousState; //1 green, 2 yellow, 3 red,4 orange
        int lastAction; //1 wait, 2 go left, 3 go right, 4 change direction,5 attack, 6 jump left, 7 jump right,
        bool aiActive;
        int greenDetectionRange;
        float yellowOrangeDetectionRange;
        float redDetectionRange;
        float attackRange;

        //m
        int stateSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection , bool isPlayerSneak, int previousState, int lastAction);
        int greenState(glm::vec2 thisPos,glm::vec2 thisDirection);
        int yellowState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection);
        int redState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection);
        int orangeState();
        int AiMethode(glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int previousState);


    protected:

    private:
};


#endif // AI_H_INCLUDED
