#include "Enemy.h"
#include "externalIncludes.h"

Enemy::Enemy() {
    Ai ai;
    glm::vec2 thisPos = glm::vec2(0.0f,0.0f); // default ai Position
    glm::vec2 thisD = glm::vec2(-1.0f,0.0f); //default direction
    thisState = 1; //defaut state Green

}

Enemy::~Enemy() {}

int Enemy::damageEnnemi()
{

return 0;
}

glm::vec2 aiProcess(Ai ai,glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int thisState) {

    ai.aiMethode(thisPos,playerPos, thisDirection,false, thisState);

return glm::vec2(0.0f,0.0f);
}



void Enemy::ennemiTouche(int damageTaken)
{
    healthEnnemi = healthEnnemi - 5;
}

bool Enemy::isMortEnnemi()
{
    if(healthEnnemi<=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
