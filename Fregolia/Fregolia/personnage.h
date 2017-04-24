#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include "ExternalIncludes.h"

#include "PhysicActor.h"
#include "Gravity.h"

class Personnage : public PhysicActor, public Gravity
{
    public:
        Personnage();
        virtual ~Personnage();

        virtual void initPersonnage(std::string pFilePath, glm::vec2 pPos) final;

        virtual void gererDeplacements(int pDeltaTemps, glm::vec2 pDirection);
       /* virtual void appliquerGravite(int pDeltaTemps);*/

        virtual void resoudreCollision(glm::vec2 pDeplacement);

        virtual void gererDeplacement(int pDeltaTemps);

        virtual void setState(int pState, glm::vec2 pDir);
        virtual int getState();

        virtual bool siImmobile();
        virtual void setImmobile(int pEstImmobile);

        virtual bool verifierMort();
        virtual void reset(glm::vec2 pPos);

        virtual void  pousserObjet(PhysicActor* pImage);
        virtual void vitesseReduite(int pDeltaTemps);
        virtual int getHealth();
        virtual void setHealth(int pHealthSet);
        virtual int getMaxHealth();
        virtual void rebondPerso();

        virtual void boucleAnimations();

        virtual void propulsionToile();

    protected:
        Gravity testGravity;


    private:

        float mImpulsionSaut = 3, mAcceleration;

        /// 0 = Rien, 1 = Marche, 2 = Saut (incl. Chute)...
        int mState = 0;
        int mHealth = 100;
        int mMaxHealth = 100;
        int invSelection = 0;
        float mAngle;

        bool mEstImmobile;


        glm::vec2 mDirection = glm::vec2(0, 0);

        bool mMort;



};


#endif // PERSONNAGE_H_INCLUDED
