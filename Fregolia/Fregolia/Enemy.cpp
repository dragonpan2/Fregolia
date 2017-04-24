#include "Enemy.h"


Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

int Enemy::aiProcess(Personnage* pPlayer)
{
    mAction = ai.actionSetter(mPos, pPlayer->getPos(), mDirection, false, mAction, 0);

    switch (ai.aiMethode(mPos, pPlayer->getPos(), mDirection, false, mAction))
    {
        case 1:

            mAction = 0;
             if(mState != 2) mState = 0;
            break;
        case 2:
            mAction = 1;
            mDirection = glm::vec2(-1.0f, 0.0f);
             if(mState != 2) mState = 1;
            break;
        case 3:
            mAction = 1;
            mDirection = glm::vec2(1.0f, 0.0f);
             if(mState != 2) mState = 1;
            break;
        case 4:
            mDirection.x = mDirection.x * -1;
            mVitesse.x = 0;
             if(mState != 2) mState = 1;
            break;
        case 5:
            //std::cout << "Attacked" << std::endl;
            /// Attaque
            pPlayer->setHealth(pPlayer->getHealth()-1);
            return 5;
            break;
        case 8:
            //std::cout << "Jumped" << std::endl;
            ///jump
            if(mState==0 || mState==1){
            mVitesse.y=3;
            mState=2;
            }
            return 6;
            break;
    }
    return 0;
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

    glm::vec2 deplacement = glm::vec2(mVitesse.x * pDeltaTemps / 100,  pDeltaTemps * (mVitesse.y - testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y));

    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);
}

void Enemy::vitesseReduite(int pDeltaTemps)
{
    if(mVitesse.x < 3 && mVitesse.x > -3) mVitesse.x = 0;
    else if(mVitesse.x != 0) mVitesse.x -= (testGravity.resistanceAirX(mMasse, mVitesse.x, mDimensions.y) + testGravity.resistanceSol(mMasse, mMuC)) * signe(mVitesse.x);

    if(mVitesse.y<0.0005 && mVitesse.y >-0.0005){

        mVitesse.y=0;
      }
      else if(mVitesse.y  > 0) mVitesse.y -= ((testGravity.resistanceAirY(this->getMasse(), this->getVitesse().x, this->getDimensions().x)) * signe(mVitesse.y) + testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y);
       else if(mVitesse.y<0)mVitesse.y -= ((testGravity.resistanceAirY(this->getMasse(), this->getVitesse().x, this->getDimensions().x)) * signe(mVitesse.y) + testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y);


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

void Enemy::boucleAnimations()
{
    if(mAction == 4) mAnimations.setCurrentAnimation(mAnimations.getCurrentAnimation() == 2 ? 3 : 2);
    else if(mAction == 5) mAnimations.setCurrentAnimation(1);

    std::cout << mPos.x << " " << mPos.y << std::endl;
}
