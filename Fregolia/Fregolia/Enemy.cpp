#include "Enemy.h"


Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::aiProcess(glm::vec2 pPlayerPos)
{
    mAction = ai.actionSetter(mPos, pPlayerPos, mDirection, false, mAction, 0);

    switch (ai.aiMethode(mPos, pPlayerPos, mDirection, false, mAction))
    {
        case 1:
            mAction = 0;
            break;
        case 2:
            mAction = 1;
            mDirection = glm::vec2(-1.0f, 0.0f);
            break;
        case 3:
            mAction = 1;
            mDirection = glm::vec2(1.0f, 0.0f);
            break;
        case 4:
            mDirection.x = mDirection.x * -1;
            mVitesse.x = 0;
            break;
        case 5:
            /// Attaque
            break;
    }
}

void Enemy::gererDeplacement(int pDeltaTemps)
{
    if(mVitesse.x > 30)
    {
        mVitesse.x = 30;
        mAccel.x = 0;
    }
    else if(mVitesse.x < -30)
    {
        mVitesse.x = -30;
        mAccel.x = 0;
    }
    else
    {
        mAccel.x = mAcceleration;
    }

    mVitesse.x += mAccel.x * mDirection.x;

    vitesseReduite(pDeltaTemps);

    glm::vec2 deplacement = glm::vec2(mVitesse.x * pDeltaTemps / 100, pDeltaTemps * (mVitesse.y - testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y));

    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);
}

void Enemy::vitesseReduite(int pDeltaTemps)
{
    if(mVitesse.x < 3 && mVitesse.x > -3) mVitesse.x = 0;
    else if(mVitesse.x != 0) mVitesse.x -= (testGravity.resistanceAirX(mMasse, mVitesse.x, mDimensions.y) + testGravity.resistanceSol(mMasse, mMuC)) * signe(mVitesse.x);

}

int Enemy::damageEnnemi()
{
    return 0;
}

void Enemy::ennemiTouche(int damageTaken)
{
    healthEnnemi = healthEnnemi - 5;
}

bool Enemy::isMortEnnemi()
{
    if(healthEnnemi <= 0) return true;
    else return false;
}

