#include "Personnage.h"

Personnage::Personnage()
{
    mState = 1;
    mMort = false;
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
            mAcceleration = atoi(line.substr(3).c_str());

        }
    }

    fichier.close();
}

void Personnage::gererDeplacements(int pDeltaTemps, glm::vec2 pDirection)
{
    glm::vec2 deplacement = glm::vec2(pDirection.x * mVitesse.x * pDeltaTemps / 100, 0.0f);
    if(pDirection.y == 1)
    {
        mState = 2;
        deplacement += glm::vec2(0.0f, mVitesse.x * pDeltaTemps / 100);
    }
    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));

    changeBB(deplacement);
}

void Personnage::resoudreCollision(glm::vec2 pDeplacement)
{
    mPos += pDeplacement;

    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(pDeplacement);

    if(pDeplacement.y > 0) /// On est tombés sur un obstacle
    {
        mState = 0;
    }

}

/*void Personnage::appliquerGravite(int pDeltaTemps)
{
    glm::vec2 deplacement = glm::vec2(0, -pDeltaTemps * 30.0f / 100);
    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);
}*/

void Personnage::setState(int pState, glm::vec2 pDir)
{

    switch(pState)
    {
    case 0: /// RIEN

        break;
    case 1: /// MARCHE
        mDirection.x += pDir.x;

        mVitesse.x += mAccel.x * signe(mDirection.x);

        if(mVitesse.x > 40)
        {
            mVitesse.x = 40;
            mAccel.x = 0;
        }
        else if(mVitesse.x < -40)
        {
            mVitesse.x = -40;
            mAccel.x = 0;
        }
        else
        {
            mAccel.x = mAcceleration;
        }

        if(mState != 2) mState = pState;

        break;
    case 2: /// SAUT
        if(mState == 0 || mState == 1)
        {
            mState = pState;
            mVitesse.y = mImpulsionSaut;
            mDirection += glm::vec2(0, 1);
        }
        break;
    }
}

int Personnage::getState()
{
    return mState;
}

void Personnage::gererDeplacement(int pDeltaTemps)
{
    if(mVitesse.y > 0) mVitesse.y -= ((testGravity.resistanceAirY(this->getMasse(), this->getVitesse().x, this->getDimensions().x)) * signe(mVitesse.y) + testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y);
    else mVitesse.y = 0;
    vitesseReduite(pDeltaTemps);

    glm::vec2 deplacement = glm::vec2(mVitesse.x * pDeltaTemps / 100, pDeltaTemps * (mVitesse.y - testGravity.gravityApplication(this->getMasse(), pDeltaTemps, this->getAngle()).y));

    mPos += deplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);

    mDirection = glm::vec2(0, 0);
}

bool Personnage::verifierMort()
{
    if(mPos.y < -SCREEN_HEIGHT)
        mMort = true;

    return mMort;
}

void Personnage::reset(glm::vec2 pPos)
{
    mState = 1;
    mMort = false;
    glm::vec2 deplacement = pPos - mPos;
    mPos = pPos;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);
    mDirection = glm::vec2(0, 0);
    mVitesse = glm::vec2(0, 0);
    mAccel = glm::vec2(0, 0);
}

void Personnage::pousserObjet(PhysicActor* pImage)
{
    mVitesse = glm::vec2(testGravity.rentrerCollision(mVitesse.x, pImage->getMasse(), pImage->getMuC(), mMasse), mVitesse.y);
    pImage->setVitesse(mVitesse);

    ((imageModel*)pImage)->moveImage(pImage->getVitesse());
}

void Personnage::vitesseReduite(int pDeltaTemps)
{
    if(mVitesse.x < 3 && mVitesse.x > -3) mVitesse.x = 0;
    else if(mVitesse.x != 0) mVitesse.x -= ((testGravity.resistanceAirX(mMasse, mVitesse.x, mDimensions.y) + testGravity.resistanceSol(mMasse, mMuC))) * signe(mVitesse.x);
}


