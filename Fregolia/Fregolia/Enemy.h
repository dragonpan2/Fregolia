#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "externalIncludes.h"
#include "Ai.h"

class Enemy
{

public:
    Ai ai;
    glm::vec2 thisPos = glm::vec2(0.0f,0.0f);
    glm::vec2 thisD = glm::vec2(-1.0f,0.0f);
    int thisState = 1;
    Enemy();
    virtual ~Enemy();
    virtual int damageEnnemi();
    virtual void ennemiTouche(int damageTaken);
    virtual bool isMortEnnemi();
    glm::vec2 aiProcess(Ai ai, glm::vec2 thisPos,glm::vec2 playerPos, glm::vec2 thisDirection, bool isPlayerSneak, int thisState);
protected:
private:
    int healthEnnemi = 15;






};

#endif // ENEMY_H_INCLUDED
