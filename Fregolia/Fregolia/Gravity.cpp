#include "Gravity.h"

Gravity::Gravity()
{

}

Gravity::~Gravity()
{

}

/**La force de la gravité appliquer au PhysicActor **/
glm::vec2 Gravity::gravityApplication(float pMasse, int pTempsEcoule, float pAngle)
{
    float accelerationX;
    float accelerationY;
    accelerationX = GRAVITY * pMasse * cos(pAngle);

    if((int)pAngle % 90 != 0) accelerationY = GRAVITY * pMasse *  sin(pAngle);
    else accelerationY = GRAVITY * pMasse*pTempsEcoule/100;

    if(accelerationY < 0){
        accelerationY =- accelerationY;
    }

    return glm::vec2(accelerationX, accelerationY);
}


/**Calcul la résistance du sol**/
float Gravity::resistanceSol(float pMasse, float pMuc)
{
    return pMasse * GRAVITY * F_TERRE * pMuc;
}


/**Calcul la résistance de l'air sur les X**/
float Gravity::resistanceAirX(float pMasse, float pVitesseX, float pSurface)
{

    return coefficientRes * F_AIR * pSurface
                                  * pVitesseX
                                  * pVitesseX
                                  / pMasse;
}


/**Calcul la résistance de l'air sur les Y**/
float Gravity::resistanceAirY(float pMasse, float pVitesseY, float pSurface)
{

    return coefficientRes * F_AIR * pSurface * pVitesseY * pVitesseY / pMasse;
}


/**Rebondir les objets**/
glm::vec2 Gravity::rebondGravity(glm::vec2 pVitesse, float pCsteRessort)
{
  //  std:: cout<< pVitesse.x
       return glm::vec2(pVitesse.x, -pVitesse.y*pCsteRessort);
}


float Gravity::rentrerCollision(float pVitesse, float pMasseObjet, float pMuc, float pMassePerso)
{
    //if(choixCollision==0) collision elastique

    return pMassePerso / pMasseObjet * pVitesse/5;
    //if(choixCollision==1) collision parfaitement inélastique
    //return pVitesse*pMassePerso/( pMasseObjet+pMassePerso);

}

