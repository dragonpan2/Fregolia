#include "PhysicActor.h"


PhysicActor::PhysicActor()
{
    mAccel = glm::vec2(10, 10);
    mVitesse = glm::vec2(0, 0);
}

PhysicActor::~PhysicActor()
{

}

void PhysicActor::createActor(float pMuC, float pMasse,float pConstantRappel,float pMuS)
{
    mMuC = pMuC;
    mMasse = pMasse;
    mConstantRappel=pConstantRappel;
    mMuS=pMuS;

}

void PhysicActor::updateActor(float pDeltaTemps)
{

    mVitesse += mAccel;
    this->moveImage(mVitesse * (pDeltaTemps / 1000));

}

void PhysicActor::setAcceleration(glm::vec2 pAccel)
{
    mAccel = pAccel;
}

void PhysicActor::setVitesse(glm::vec2 pVitesse)
{
    mVitesse = pVitesse;
}

glm::vec2 PhysicActor::getAcceleration()
{
    return mAccel;
}

glm::vec2 PhysicActor::getVitesse()
{
    return mVitesse;
}

float PhysicActor::getMuC()
{
    return mMuC;
}

float PhysicActor::getMasse()
{
    return mMasse;
}


float PhysicActor:: getConstantRappel()
{
    return mConstantRappel;
}
void PhysicActor::vitesseReduite(int pDeltaTemps)
{
<<<<<<< HEAD
    //std::cout <<"---------------------------------------------------------------------------"<< mVitesse.x<<std::endl;
    if(mVitesse.x < 5 && mVitesse.x > -5) mVitesse.x = 0;
=======
    std::cout<< "---------------------------------------------VitesseCube1:"<<mVitesse.x<<std::endl;
    if(mVitesse.x < 0.8 && mVitesse.x > -0.8) mVitesse.x = 0;
>>>>>>> origin/master
    else if(mVitesse.x != 0) mVitesse.x -= ((testGravity.resistanceAirX(mMasse, mVitesse.x, mDimensions.y) + (mCollisionSol ? testGravity.resistanceSol(mMasse, mMuC) : 0))) * signe(mVitesse.x);
std::cout<< "---------------------------------------------VitesseCube2: "<<mVitesse.x<<std::endl;



    if(mVitesse.y<0.0005 && mVitesse.y >-0.0005)
    {

        mVitesse.y=0;
    }
    else if(mVitesse.y  > 0) mVitesse.y -= ((testGravity.resistanceAirY(this->getMasse(), this->getVitesse().x, this->getDimensions().x)) * signe(mVitesse.y) + testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y);
    else if(mVitesse.y<0)mVitesse.y -= ((testGravity.resistanceAirY(this->getMasse(), this->getVitesse().x, this->getDimensions().x)) * signe(mVitesse.y) + testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y);


}

bool PhysicActor:: enMouvement()
{
    if(this->getVitesse().x!=0 || this->getVitesse().y!=0 )
    {
        return true;
    }
    else
    {
        return false;
    }

}
void PhysicActor::gererDeplacement(int pDeltaTemps)
{

    vitesseReduite(pDeltaTemps);

    glm::vec2 deplacement = glm::vec2(mVitesse.x * pDeltaTemps / 100, pDeltaTemps * (mVitesse.y - testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y));

    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));

    changeBB(deplacement);

}
void PhysicActor:: rebondPerso()
{


    if(mCollisionSol)
    {
        mVitesse=  testGravity.rebondGravity(mVitesse, mConstantRappel);



    }

}
void PhysicActor:: mouvementRotation()
{

this->setAngle(0);


}


