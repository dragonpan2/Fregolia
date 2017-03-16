#include "Enemy.h"

Enemy::Enemy() {}

Enemy::~Enemy() {}

int Enemy::damageEnnemi()
{

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
