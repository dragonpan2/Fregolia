#include "Ai.h"
#include "externalIncludes.h"
<<<<<<< HEAD

Ai::Ai() {

}

Ai::~Ai() {

}

void Ai::stateSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection , bool isPlayerSneak, int previousState) {

}
void Ai::greenState(glm::vec2 thisPos,glm::vec2 thisDirection) {

}

void Ai::yellowState() {

}

void Ai::redState() {

}

void Ai::orangeState() {

}

int Ai::AiMethode() {

return 0;
=======
#include <stdlib.h>     /* srand, rand */

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
        if (thisDirection ==glm::vec2  (-1.0f,0.0f) )
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
        else if (thisDirection == glm::vec2 (1.0f,0.0f))
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
    case 3:
        if (thisDirection == glm::vec2 (-1.0f,0.0f) )
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
        else if (thisDirection == glm::vec2 (1.0f,0.0f))
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
    switch (rand() % 7+1)
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
    if ((thisPos.x - playerPos.x > 0) && (thisDirection == glm::vec2 (-1.0f,0.0f)) ) {
        return 2;
    }
    if (playerPos.x - thisPos.x > 0 && thisDirection == glm::vec2 (1.0f,0.0f) ) {
        return 3;
    }


return 1;
}

int Ai::redState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{
    if (thisPos.x - playerPos.x > 0 && thisDirection == glm::vec2 (-1.0f,0.0f) ) { //si le joueur est a droite du AI et le AI fais face au joueur
        if (glm::length(thisPos - playerPos) < attackRange) { //si le joueur est dans la distance dattack du ai
            return 5;
        }
        else {
            return 2;
        }
    }
    else {
        return 4;
    }

    if (playerPos.x - thisPos.x > 0 && thisDirection == glm::vec2 (1.0f,0.0f) ) { //si le joueur est a gauche du AI et le AI fais face au joueur
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

int Ai::orangeState()
{



return 1;
}

int Ai::AiMethode(glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int previousState)
{

    switch (stateSetter(thisPos,playerPos,thisDirection,  isPlayerSneak, previousState,  lastAction))
    {
    case 1:
        return greenState(thisPos,thisDirection);
    case 2:
        return yellowState(thisPos,  playerPos, thisDirection);
    case 3:
        return redState( thisPos,  playerPos,  thisDirection);
    case 4:
        return orangeState();

    }

    return 0;
>>>>>>> origin/master
}

