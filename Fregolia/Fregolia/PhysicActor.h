#ifndef PHYSICACTOR_H_INCLUDED
#define PHYSICACTOR_H_INCLUDED

#include "ExternalIncludes.h"
#include "LoadModel.h"
#include "Gravity.h"


class PhysicActor : public imageModel
{
    public:
        PhysicActor();
        virtual ~PhysicActor();

        virtual void createActor(float pMuC, float pMasse,float pConstantRappel,float pMuS);
        virtual void updateActor(float pDeltaTemps);

        virtual void setAcceleration(glm::vec2 pAccel);
        virtual void setVitesse(glm::vec2 pVitesse);

        virtual glm::vec2 getAcceleration();
        virtual glm::vec2 getVitesse();

        virtual float getMuC();
        virtual float getMasse();

        virtual void gererDeplacement(int pDeltaTemps);


        virtual float getConstantRappel();

        virtual bool enMouvement( );
        virtual void vitesseReduite(int pDeltaTemps);


         virtual void rebondPerso();

        virtual void mouvementRotation();


         bool mCollisionSol = false;
         bool mCollisionCoter=false;
      //   bool mCollisionGauche=false;
        // bool mCollisionDroite=false;
    protected:
        Gravity testGravity;
        glm::vec2 mAccel, mVitesse;

        float mMuC, mMasse,mMuS;

        float mConstantRappel;

};

#endif // PHYSICACTOR_H_INCLUDED
