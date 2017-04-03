#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include "externalIncludes.h"

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

        virtual bool verifierMort();
        virtual void reset(glm::vec2 pPos);

        virtual void modifierVitesse(int pState);




    private:

        float mImpulsionSaut = 2.4, mAcceleration;

        /// 0 = Rien, 1 = Marche, 2 = Saut (incl. Chute)...
        int mState = 0;
        glm::vec2 mAccel, mVitesse;

        glm::vec2 mDirection = glm::vec2(0, 0);

        bool mMort;



};


#endif // PERSONNAGE_H_INCLUDED
