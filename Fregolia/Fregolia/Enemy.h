#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "externalIncludes.h"
#include "Ai.h"

class Enemy
{

public:
    Ai ai;
    //doit etre synchroniser avec sa position dans le main
    glm::vec2 thisPos = glm::vec2(500.0f, -200.0f);
    glm::vec2 thisDirection = glm::vec2(-1.0f,0.0f);
    int thisState = 1;
    Enemy();
    virtual ~Enemy();
    virtual int damageEnnemi();
    virtual void ennemiTouche(int damageTaken);
    virtual bool isMortEnnemi();
    glm::vec2 aiProcess(glm::vec2 playerPos);
protected:
private:
    int healthEnnemi = 15;






};

#endif // ENEMY_H_INCLUDED
