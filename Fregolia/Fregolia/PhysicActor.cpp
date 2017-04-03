#include "PhysicActor.h"


PhysicActor::PhysicActor()
{

}

PhysicActor::~PhysicActor()
{

}

void PhysicActor::createActor(float pMuC, float pMasse,bool pEstCollision)
{
    mMuC = pMuC;
    mMasse = pMasse;
    mEstCollision=pEstCollision;

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
bool PhysicActor::getCollision(){

return mEstCollision;
}
bool PhysicActor:: setCollision(bool pEstCollision)
{
mEstCollision=pEstCollision;
}
float PhysicActor:: getCsteRessort()
{
    return mCsteRessort;
}

