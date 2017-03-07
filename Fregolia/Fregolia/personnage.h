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

        virtual void resoudreCollision(glm::vec2 pDeplacement);

    private:
        int mVitesse;

};


#endif // PERSONNAGE_H_INCLUDED
