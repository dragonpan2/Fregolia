#ifndef GRAVITY_H_INCLUDED
#define GRAVITY_H_INCLUDED
#include "externalIncludes.h"
#include "PhysicActor.h"
#include "loadModel.h"


class Gravity
{

public:
    Gravity();
    ~Gravity();
    const float GRAVITY=-0.05;
    const float F_AIR=0.0002;
    const float F_EAU=998 ;
    const float F_TERRE=0.95;
    virtual void gravityApplication(PhysicActor* pPersonne,int pTempsEcoule);
    virtual void gravityApplicationVitesse(PhysicActor* pPersonne,int pTempsEcoule);
    virtual int paraboliqueApplication(PhysicActor* pPersonne,int pTempsEcoule);
    virtual float resistanceAirX(PhysicActor* pPersonne);
    virtual float resistanceAirY(PhysicActor* pPersonne);
    virtual float resistanceSol(PhysicActor* pPersonne);
    virtual glm::vec2  equationVitesse(PhysicActor* pPersonne,int pTempsEcoule);
    virtual float resistanceEauX(PhysicActor* pPersonne);
    virtual float resistanceEauY(PhysicActor* pPersonne);
    virtual glm::vec2 gravityObject(PhysicActor* pPersonne,int pTempsEcoule);




};




#endif // GRAVITY_H_INCLUDED
