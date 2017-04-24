#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "ExternalIncludes.h"
#include "Ai.h"
#include "PhysicActor.h"
#include "Gravity.h"
#include "Personnage.h"

class Enemy: public PhysicActor, public Gravity
{

public:
    Ai ai;

    Enemy();
    virtual ~Enemy();

    virtual int aiProcess(Personnage* pPlayer);
    virtual void gererDeplacement(int pDeltaTemps);
    virtual void vitesseReduite(int pDeltaTemps);

    virtual int damageEnnemi();
    virtual void ennemiTouche(int pDamageTaken);
    virtual bool isMortEnnemi();

    virtual void boucleAnimations();
protected:
    Gravity testGravity;
private:
    float mImpulsionSaut = 2.4;
    int healthEnnemi = 100;
    int maxHealtEnnemi = 100;
    glm::vec2 mDirection = glm::vec2(-1.0f,0.0f);
    int mAction = 1;
    float mAcceleration = 5.0f;
    int mState=0;

};

#endif // ENEMY_H_INCLUDED
