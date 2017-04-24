#include "Ai.h"


Ai::Ai()
{


}

Ai::~Ai()
{

}

int Ai::actionSetter(glm::vec2 thisPos, glm::vec2 playerPos,glm::vec2 thisDirection, bool isPlayerSneak, int previousState, int lastAction)
{

    if (thisDirection == glm::vec2 (0.0f,0.0f)) thisDirection = glm::vec2(-1.0f, 0.0f);

    float signeDistance = signe(playerPos.x - thisPos.x);
    float distance = glm::length(playerPos - thisPos);

    switch (previousState)
    {
    case 1: //if it was on green state
        //detection code here
        if(distance <= greenDetectionRange && signeDistance == signe(thisDirection.x)) return 2;
        else return 1;
        break;
    case 2:
        if(distance <= yellowOrangeDetectionRange && signeDistance == signe(thisDirection.x)) return 3;
        else return 1;
        break;
    case 3:
        if(distance <= redDetectionRange) return 3;
        else return 4;
        break;
    case 4:
        if(distance <= yellowOrangeDetectionRange && signeDistance == signe(thisDirection.x)) return 3;
        else return 1;
        break;
    }
    return 1;
}
int Ai::greenState(glm::vec2 thisPos,glm::vec2 thisDirection)
{
    switch (rand() % 7) //was 5
    {
        case 1:
            dirChangeCompter++;
            return 1;
            break;
        case 2:
            dirChangeCompter++;
            if(thisDirection.x < 0) return 2;
            else return 1;
        case 3:
            dirChangeCompter++;
            if (thisDirection.x > 0) return 3;
            else return 1;
        case 4:
            if(dirChangeCompter > 5)
            {
                dirChangeCompter = 0;
                if(lastAction != 4) return 4;
            }
        default :
            dirChangeCompter++;
            return 1;
    }
    //behavior on green here
    return 1;
}

int Ai::yellowState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{
    float signeDistance = signe(playerPos.x - thisPos.x);

    if(signeDistance == signe(thisDirection.x)) return std::ceil(2.5 + signe(thisDirection.x)); /// CHANGER CHIFFRE BASÉ SUR DIRECTION?
    else return 1;
}

int Ai::redState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{
    float signeDistance = signe(playerPos.x - thisPos.x);
    float distance = glm::length(playerPos - thisPos);
    //std::cout << "delta X" <<std::endl;
    //std::cout << abs(thisPos.x - playerPos.x) << std::endl;
    //std::cout << abs(playerPos.y-thisPos.y) << std::endl;

    if(distance < attackRange && signeDistance == signe(thisDirection.x)) return 5;

    ///ligne pour jump
    else if((abs(thisPos.x-playerPos.x) < 250) && (abs(playerPos.y-thisPos.y) > 10)) return 8;
    else if(signeDistance == signe(thisDirection.x)) return std::ceil(6.5 + signe(thisDirection.x));
    else return 4;
}

int Ai::orangeState(glm::vec2 thisPos, glm::vec2 playerPos, glm::vec2 thisDirection)
{
    return yellowState(thisPos,  playerPos, thisDirection);
    return 1;
}

int Ai::aiMethode(glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int previousState)
{
    int nextState = actionSetter(thisPos,playerPos,thisDirection,  isPlayerSneak, previousState,  lastAction);

    switch (nextState)
    {
        case 1:
            return greenState(thisPos,thisDirection);
        case 2:
            return yellowState(thisPos,  playerPos, thisDirection);
        case 3:
            return redState( thisPos,  playerPos,  thisDirection);
        case 4:
            return orangeState(thisPos,  playerPos,  thisDirection);
    }

    return 0;
}

