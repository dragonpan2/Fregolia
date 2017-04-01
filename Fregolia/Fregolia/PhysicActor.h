#ifndef PHYSICACTOR_H_INCLUDED
#define PHYSICACTOR_H_INCLUDED

#include "externalIncludes.h"
#include "loadModel.h"


class PhysicActor : public imageModel
{
    public:
        PhysicActor();
        virtual ~PhysicActor();

        virtual void createActor(float pMuC, float pMasse,bool pEstCollision);
        virtual void updateActor(float pDeltaTemps);

        virtual void setAcceleration(glm::vec2 pAccel);
        virtual void setVitesse(glm::vec2 pVitesse);

        virtual glm::vec2 getAcceleration();
        virtual glm::vec2 getVitesse();

        virtual float getMuC();
        virtual float getMasse();

        virtual bool getCollision();
        virtual bool setCollision(bool pEstCollision);

        virtual float getCsteRessort();

    private:
        glm::vec2 mAccel, mVitesse;
        float mMuC, mMasse;
        bool mEstCollision;
        float mCsteRessort;
};

#endif // PHYSICACTOR_H_INCLUDED
