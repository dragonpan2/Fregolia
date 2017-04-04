#include "Enemy.h"
#include "externalIncludes.h"

Enemy::Enemy() {
  //  glm::vec2 thisPos = glm::vec2(0.0f,0.0f); // default ai Position
    //glm::vec2 thisD = glm::vec2(-1.0f,0.0f); //default direction
    //thisState = 1; //defaut state Green

}

Enemy::~Enemy() {}

int Enemy::damageEnnemi()
{

return 0;
}

glm::vec2 Enemy::aiProcess(glm::vec2 playerPos) {


 thisState = ai.stateSetter(thisPos,playerPos,thisDirection , false, thisState, 0);
    switch (ai.aiMethode(thisPos,playerPos, thisDirection,false, thisState)) {

case 1:
    std::cout << "action is wait"<< std::endl;
    return glm::vec2(0.0f,0.0f);
    break;
case 2:
    std::cout << "action is go left"<< std::endl;
    thisPos.x = thisPos.x -1;
    return glm::vec2(-1.0f,0.0f);
    break;
case 3:
    std::cout << "action is go right" <<std::endl;
    thisPos.x = thisPos.x +1;
    return glm::vec2(1.0f,0.0f);
    break;
    case 4:
    std::cout << "action is change direction" <<std::endl;
    thisDirection.x = thisDirection.x * -1;
    return glm::vec2(0.0f,0.0f);
    break;
    case 5:
    std::cout << "action is attack" <<std::endl;
    break;

    }
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
