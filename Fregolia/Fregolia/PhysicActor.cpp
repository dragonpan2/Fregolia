#include "PhysicActor.h"

PhysicActor::PhysicActor()
{
    mAccel = glm::vec2(0, 0);
    mVitesse = glm::vec2(0, 0);
}

PhysicActor::~PhysicActor()
{

}

void PhysicActor::createActor(float pMuC, float pMasse)
{
    mMuC = pMuC;
    mMasse = pMasse;
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
