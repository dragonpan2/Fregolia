#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED
#include "ExternalIncludes.h"

class Ai
{
    public:
        Ai();
        virtual ~Ai();

        //var
        int previousState; //1 green, 2 yellow, 3 red,4 orange
        int lastAction; //1 wait, 2 go left, 3 go right, 4 change direction,5 attack, 6 jump left, 7 jump right,
        int dirChangeCompter = 0;
        bool aiActive = true;
        int greenDetectionRange = 450;
        //int greenDetectionRange;
        float yellowOrangeDetectionRange = 375;
        float redDetectionRange = 335;
        float attackRange = 50;

      //  glm::vec2 thisDirection = glm::vec2(1.0f,0.0f);

        //m
        int actionSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection , bool isPlayerSneak, int previousState, int lastAction);
        int greenState(glm::vec2 thisPos,glm::vec2 thisDirection);
        int yellowState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection);
        int redState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection);
        int orangeState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection);
        int aiMethode(glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int previousState);
    protected:

    private:
};


#endif // AI_H_INCLUDED

