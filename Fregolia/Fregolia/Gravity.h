#ifndef GRAVITY_H_INCLUDED
#define GRAVITY_H_INCLUDED
#include "ExternalIncludes.h"
#include "LoadModel.h"


class Gravity
{
    public:
        Gravity();
        ~Gravity();

        virtual glm::vec2 gravityApplication(float pMasse,int pTempsEcoule,float pAngle);
        virtual glm::vec2 rebondGravity(glm::vec2 pVitesse,float pCsteRessort);

        virtual float resistanceAirX(float pMasse,float pVitesseX,float pSurface);
        virtual float resistanceAirY(float pMasse,float pVitesseY,float pSurface);
        virtual float resistanceSol(float pMasse,float pMuc);

        virtual float rentrerCollision(float pVitesse,float pMasseObjet, float pMuc, float pMassePerso);

    //  virtual float centreMasse(float pMasse, float pMuc);
    private:
        const float GRAVITY = 0.35;
        const float F_AIR = 0.00005;
        const float F_EAU = 998;
        const float F_TERRE = 0.15;
        const float coefficientRes=0.1;
};




#endif // GRAVITY_H_INCLUDED
