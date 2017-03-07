#include "personnage.h"

Personnage::Personnage()
{

}

Personnage::~Personnage()
{

}

void Personnage::initPersonnage(std::string pFilePath, glm::vec2 pPos)
{
    this->loadFile(pFilePath, pPos);

    std::ifstream fichier;
    fichier.open(pFilePath.c_str());

    std::string line;
    while(std::getline(fichier, line))
    {
        if(line.substr(0, 4) == "vit ")
        {
            mVitesse = atoi(line.substr(3).c_str());
        }
    }

    fichier.close();
}

void Personnage::gererDeplacements(int pDeltaTemps, glm::vec2 pDirection)
{
    mPos += glm::vec2(pDirection.x * mVitesse * pDeltaTemps, pDirection.y * mVitesse * pDeltaTemps);
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
}

void Personnage::resoudreCollision(glm::vec2 pDeplacement)
{
    mPos += pDeplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
}
