#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "externalIncludes.h"

class Enemy
{

public:
    Enemy();
    virtual ~Enemy();
    virtual int damageEnnemi();
    virtual void ennemiTouche(int damageTaken);
    virtual bool isMortEnnemi();

protected:
private:
    int healthEnnemi = 15;






};

#endif // ENEMY_H_INCLUDED
