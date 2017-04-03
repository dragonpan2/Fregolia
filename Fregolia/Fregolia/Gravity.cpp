#include "Gravity.h"

Gravity::Gravity()
{

}
Gravity::~Gravity()
{

}


/**La force de la gravité appliquer au PhysicActor **/
glm::vec2 Gravity::gravityApplication(PhysicActor* pPersonne, int pTempsEcoule/*,imageModel* pSol*/)
{

    // float anglePente = glm::radians(((imageModel*) pSol)->getAngle());
     float accelerationX;
float accelerationY;
    //forceGravitationnelle -= (pPersonne->getMuC() * forceGravitationnelle /** cos(anglePente)**/);
    //forceGravitationnelle = std::max(forceGravitationnelle, 0.0f);
//if((int) anglePente % 90!=0){
   accelerationX=  GRAVITY * pPersonne->getMasse() /* cos(anglePente)*/;
//}

//if(anglePente!=0){
      accelerationY = GRAVITY * pPersonne->getMasse() /* sin(anglePente)*/;
//}


    /** Assigne la nouvelle accélération sur les Y au PhysicActor **/
    /*Pas collision */
 /**if(!pPersonne->getCollision())
    {
        pPersonne->setAcceleration(glm::vec2(pPersonne->getAcceleration().x, accelerationY));
    }
    /*collision **/
  /**  else
    {
        pPersonne->setAcceleration(glm::vec2(pPersonne->getAcceleration().x, 0));
    }**/

if(accelerationY<0){
    accelerationY=-accelerationY;
}

return glm::vec2(accelerationX,accelerationY);

}
/** Change l'accélération du PhysicActor    **/
void Gravity::gravityApplicationVitesse(PhysicActor* pPersonne,int pTempsEcoule)
{
std::cout  << pPersonne->getAcceleration().x<<std::endl;

/**Si l'accélération est trop faible le met à zéro **/
    if(pPersonne->getAcceleration().x<1.0f && pPersonne->getAcceleration().x>-1.0f)
    {

        pPersonne->setAcceleration(glm::vec2 (0,pPersonne->getAcceleration().y));
        pPersonne->setVitesse(glm::vec2 (pPersonne->getVitesse().x-resistanceAirX(pPersonne)-resistanceSol(pPersonne),pPersonne->getVitesse().y));
    }
    /**Sinon applique les résistances  **/
    else
    {

        pPersonne->setAcceleration(glm::vec2((pPersonne->getAcceleration().x - resistanceAirX(pPersonne)-resistanceSol(pPersonne)) ,
                                             (pPersonne->getAcceleration().y- resistanceAirY(pPersonne))
                                            ));

    }

}
/*Pas utilisé*/
int Gravity::paraboliqueApplication(PhysicActor* pPersonne,int pTempsEcoule)
{

   // gravityApplication(pPersonne,pTempsEcoule);
}
/* Pas utilisé*/
glm::vec2 Gravity::gravityObject(PhysicActor* pPersonne,int pTempsEcoule)
{

  //  gravityApplication(pPersonne,pTempsEcoule);

    glm::vec2 vecteurObject(pPersonne->getVitesse());
    return vecteurObject;
}
/**Calcul la résistance du sol**/
float Gravity::resistanceSol(PhysicActor* pPersonne)
{
    float accelerationSolX=0;

    accelerationSolX=(pPersonne->getMasse()*GRAVITY*F_TERRE*pPersonne->getMuC());

    return accelerationSolX;
}
/**Calcul la résistance de l'air sur les X**/

float Gravity::resistanceAirX(PhysicActor* pPersonne)
{

    float coefficientRes= 0.01;

    float surface = ((imageModel*) pPersonne)->getDimensions().x;
    float accelerationAirX;

    accelerationAirX = coefficientRes * F_AIR * surface
                                      * pPersonne->getVitesse().x
                                      * pPersonne->getVitesse().x
                                      / pPersonne->getMasse();

    return accelerationAirX;
}
/**Calcul la résistance de l'air sur les Y**/
float Gravity::resistanceAirY(PhysicActor* pPersonne)
{

    float coefficientRes= 0.007777777799;

    float surface= ((imageModel*) pPersonne)->getDimensions().y;
    float accelerationAirY;



/*Si l'accélération vers la bas, frottement positive*/
     if(pPersonne->getAcceleration().x<0)
     {
    accelerationAirY= coefficientRes * F_AIR * surface * pPersonne->getVitesse().y * pPersonne->getVitesse().y/pPersonne->getMasse();
     }
     /*Si l'accélération vers la haut, frottement négative*/
     else if(pPersonne->getAcceleration().x>0)
     {
    accelerationAirY=-(coefficientRes * F_AIR * surface  * pPersonne->getVitesse().y * pPersonne->getVitesse().y/pPersonne->getMasse());
     }


    return accelerationAirY;

}
/*pas utilisé*/
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
/*pas utilisé*/
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
/*pas utilisé*/
glm::vec2 Gravity::equationVitesse(PhysicActor* pPersonne,int pTempsEcoule)
{
    float vitesseX;
    float vitesseY;


    vitesseX = pPersonne->getVitesse().x + pPersonne->getAcceleration().x * pTempsEcoule / 1000;
    vitesseY = pPersonne->getVitesse().y + pPersonne->getAcceleration().y * pTempsEcoule / 1000;

    glm::vec2 vecteurVitesse(vitesseX, vitesseY);

    return vecteurVitesse;
}
/**Rebondir les objets**/
void Gravity::rebondGravity(PhysicActor* pPersonne,int pTempsEcoule)
{
    /*si le PhysicActor est en collision*/
    if(pPersonne->getCollision())
    {
        pPersonne->setVitesse(glm::vec2(pPersonne->getVitesse().x,-pPersonne->getVitesse().y)*pPersonne->getCsteRessort());

    }


}
void Gravity:: appliquerForce(PhysicActor* pPersonne1, PhysicActor* pPersonne2)
{




}
