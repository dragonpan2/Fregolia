#include "Ai.h"
#include "externalIncludes.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>

Ai::Ai()
{


}

Ai::~Ai()
{

}

int Ai::stateSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection, bool isPlayerSneak, int previousState, int lastAction)
{

    switch (previousState)
    {
    case 1: //if it was on green state
        //detection code here
        if ((thisDirection == glm::vec2(-1.0f,0.0f)) && (playerPos.x < thisPos.x))
        {

            if (glm::length(thisPos - playerPos) <= greenDetectionRange)
            {
                return 2;
            }
            else
            {
                return 1;
            }
        }
        else if (thisDirection == glm::vec2 (1.0f,0.0f) && playerPos.x > thisPos.x)
        {
            if (glm::length(playerPos - thisPos) <= greenDetectionRange)
            {
                return 2;
            }
            else
            {
                return 1;
            }
        }
        break;
    case 2:
        if (thisDirection == glm::vec2 (-1.0f,0.0f) && playerPos.x < thisPos.x )
        {
            if (glm::length(thisPos - playerPos) <= yellowOrangeDetectionRange)
            {   //
                return 3;
            }
            else
            {
                return 1;
            }
        }
        else if (thisDirection == glm::vec2 (1.0f,0.0f) && playerPos.x > thisPos.x)
        {
            if (glm::length(playerPos - thisPos) <= yellowOrangeDetectionRange)
            {
                return 3;
            }
            else
            {
                return 1;
            }
        }
        break;
    case 3:
        if (thisDirection == glm::vec2 (-1.0f,0.0f)  )
        {
            if (glm::length(thisPos - playerPos) <= redDetectionRange)
            {
                return 3;
            }
            else
            {
                return 4;
            }
        }
        else if (thisDirection == glm::vec2 (1.0f,0.0f) )
        {
            if (glm::length(playerPos - thisPos) <= redDetectionRange)
            {
                return 3;
            }
            else
            {
                return 4;
            }
        }
        break;
    case 4:
        if (thisDirection == glm::vec2 (-1.0f,0.0f) )
        {
            if (glm::length(thisPos - playerPos) <= yellowOrangeDetectionRange)
            {
                return 3;
            }
            else
            {
                return 1;
            }
        }
        else if (thisDirection == glm::vec2 (1.0f,0.0f))
        {
            if (glm::length(playerPos - thisPos) <= yellowOrangeDetectionRange)
            {
                return 3;
            }
            else
            {
                return 1;
            }
        }
        break;
    }
    return 1;
}
int Ai::greenState(glm::vec2 thisPos,glm::vec2 thisDirection)
{
    //
    switch (rand() % 5)
    //
    {
    case 1:
        return 1;
        break;
    case 2:
        if (thisDirection == glm::vec2 (-1.0f,0.0f))
        {
            return 2;
        }
        else return 1;
    case 3:
        if (thisDirection == glm::vec2 (1.0f,0.0f))
        {
            return 3;
        }
        else return 1;
    case 4:
        if (lastAction != 4) {
            return 4;
        }
    default : return 1;
    }
    //behavior on green here
    return 1;
}

int Ai::yellowState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{

    //error here
    if ((playerPos.x < thisPos.x) && (thisDirection == glm::vec2 (-1.0f,0.0f)) ) {
        return 2;
    }
    if ((thisPos.x < playerPos.x) && thisDirection == glm::vec2 (1.0f,0.0f) ) {
        return 3;
    }


return 1;
}

int Ai::redState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{
    if (playerPos.x <thisPos.x && thisDirection == glm::vec2 (-1.0f,0.0f) ) { //si le joueur est a droite du AI et le AI fais face au joueur
        if (glm::length(thisPos - playerPos) < attackRange) { //si le joueur est dans la distance dattack du ai
            return 5;
        }
        else {
            return 2;
        }
    }



    else if (thisPos.x < playerPos.x && thisDirection == glm::vec2 (1.0f,0.0f) ) { //si le joueur est a gauche du AI et le AI fais face au joueur
        if (glm::length(playerPos -thisPos) < attackRange) { //si le joueur est dans la distance dattack du ai
            return 5;
        }
        else {
            return 3;
        }
    }
    else {
        return 4;
    }

    return 1;
}

int Ai::orangeState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{

return yellowState(thisPos,  playerPos, thisDirection);

return 1;
}

int Ai::aiMethode(glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int previousState)
{
    //
    std::cout << "next state is " << std::endl;
    int nextState = stateSetter(thisPos,playerPos,thisDirection,  isPlayerSneak, previousState,  lastAction);
    std::cout << nextState  << std::endl;
    //
    switch (nextState)
    //
    {
    case 1:
        std::cout << "green state"<< std::endl;
        return greenState(thisPos,thisDirection);
    case 2:
        std::cout << "yellow state" <<std::endl;
        return yellowState(thisPos,  playerPos, thisDirection);
    case 3:
        std::cout << "red state" <<std::endl;
        return redState( thisPos,  playerPos,  thisDirection);
    case 4:
        return orangeState(thisPos,  playerPos,  thisDirection);
      break;

    }

    return 0;
}

