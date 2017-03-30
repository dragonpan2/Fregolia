#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include "externalIncludes.h"
#include "loadModel.h"

class Personnage : public imageModel
{
    public:
        Personnage();
        virtual ~Personnage();

        virtual void initPersonnage(std::string pFilePath, glm::vec2 pPos) final;

        virtual void gererDeplacements(int pDeltaTemps, glm::vec2 pDirection);
        virtual void appliquerGravite(int pDeltaTemps);

        virtual void resoudreCollision(glm::vec2 pDeplacement);

        virtual void gererDeplacement(int pDeltaTemps);

        virtual void setState(int pState, glm::vec2 pDir);
        virtual int getState();

        virtual bool verifierMort();
        virtual void reset(glm::vec2 pPos);

    private:
        int mVitesse;
        int mImpulsionSaut = 40, mVitesseSaut = 0;

        /// 0 = Rien, 1 = Marche, 2 = Saut (incl. Chute)...
        int mState = 0;

        glm::vec2 mDirection = glm::vec2(0, 0);

        bool mMort;

};


#endif // PERSONNAGE_H_INCLUDED
