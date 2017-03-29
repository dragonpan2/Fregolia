#include "Gravity.h"

Gravity::Gravity()
{

}
Gravity::~Gravity()
{

}



void Gravity::gravityApplication(PhysicActor* pPersonne, int pTempsEcoule)
{
    int masseObject = pPersonne->getMasse();
    float anglePente = glm::radians(((imageModel*) pPersonne)->getAngle());
    float forceGravitationnelle = GRAVITY * masseObject;
    //forceGravitationnelle -= (pPersonne->getMuC() * forceGravitationnelle * cos(anglePente));
    //forceGravitationnelle = std::max(forceGravitationnelle, 0.0f);
    float accelerationX = ((int) anglePente % 90 == 0 ? 0 : forceGravitationnelle * cos(anglePente));
    float accelerationY = forceGravitationnelle /** sin(anglePente)**/;

    pPersonne->setAcceleration(glm::vec2(accelerationX, accelerationY));
}

void Gravity::gravityApplicationVitesse(PhysicActor* pPersonne,int pTempsEcoule)
{
    pPersonne->setAcceleration(glm::vec2(/*(pPersonne->getAcceleration().x - resistanceAirX(pPersonne)-resistanceSol(pPersonne))*/ 0,
                                    (pPersonne->getAcceleration().y- resistanceAirY(pPersonne))));
}

int Gravity::paraboliqueApplication(PhysicActor* pPersonne,int pTempsEcoule)
{

    gravityApplication(pPersonne,pTempsEcoule);
}

glm::vec2 Gravity::gravityObject(PhysicActor* pPersonne,int pTempsEcoule)
{

    gravityApplication(pPersonne,pTempsEcoule);

    glm::vec2 vecteurObject(pPersonne->getVitesse());
    return vecteurObject;
}

float Gravity::resistanceSol(PhysicActor* pPersonne)
{
    float accelerationX;
    accelerationX= pPersonne->getMasse()*-GRAVITY*F_TERRE;

    return accelerationX;
}
float Gravity::resistanceAirX(PhysicActor* pPersonne)
{
    float resistance;
    float coefficientRes= 0.01;
    float masseVolumique= F_AIR;
    float surface= ((imageModel*) pPersonne)->getDimensions().x;
    float accelerationAirX;

    resistance= coefficientRes*masseVolumique*surface*pPersonne->getVitesse().x*pPersonne->getVitesse().x;
    accelerationAirX=resistance/pPersonne->getMasse();



    return accelerationAirX;
}
float Gravity::resistanceAirY(PhysicActor* pPersonne)
{
    float resistance;
    float coefficientRes= 0.01;
    float masseVolumique= F_AIR;
    float surface= ((imageModel*) pPersonne)->getDimensions().y;
    float accelerationAirY;

    resistance= coefficientRes * masseVolumique * surface * pPersonne->getVitesse().y * pPersonne->getVitesse().y;
    accelerationAirY=resistance/pPersonne->getMasse();



    return accelerationAirY;

}
float Gravity::resistanceEauX(PhysicActor* pPersonne)
{
    float resistance;
    float coefficientRes = 1;
    float masseVolumique = F_EAU;
    float surface = ((imageModel*) pPersonne)->getDimensions().x;
    float accelerationEauX;

    resistance = coefficientRes * masseVolumique * surface * pPersonne->getVitesse().x*pPersonne->getVitesse().x;
    accelerationEauX = resistance / pPersonne->getMasse();
    return accelerationEauX;

}
float Gravity::resistanceEauY(PhysicActor* pPersonne)
{
    float resistance;
    float coefficientRes = 1;
    float masseVolumique = F_EAU;
    float surface = ((imageModel*) pPersonne)->getDimensions().y;
    float accelerationEauY;
    resistance = coefficientRes * masseVolumique * surface * pPersonne->getVitesse().y * pPersonne->getVitesse().y;
    accelerationEauY = resistance / pPersonne->getMasse();
    return accelerationEauY;
}
glm::vec2 Gravity::equationVitesse(PhysicActor* pPersonne,int pTempsEcoule)
{
    float vitesseX;
    float vitesseY;


    vitesseX = pPersonne->getVitesse().x + pPersonne->getAcceleration().x * pTempsEcoule / 1000;
    vitesseY = pPersonne->getVitesse().y + pPersonne->getAcceleration().y * pTempsEcoule / 1000;

    glm::vec2 vecteurVitesse(vitesseX, vitesseY);

    return vecteurVitesse;
}
