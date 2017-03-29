#include "environment.h"


Environnement::Environnement()
{
    mBgView = glm::mat4(1.0f);
    mBgProj = glm::mat4(1.0f);

    mLevelLength = glm::vec2(0, 1024);
}
Environnement::~Environnement() {}
void Environnement::setMatrices(glm::mat4 pView, glm::mat4 pProj)
{
    mView = pView;
    mProj = pProj;
}
glm::vec2 Environnement::loadLevel(std::string pLevelFile)
{
    mWater = nullptr;

    glm::vec2 playerPos = glm::vec2(0, 0);

    std::ifstream fichier;
    fichier.open(pLevelFile.c_str());

    std::string line;
    while(std::getline(fichier, line))
    {
        if(line.substr(0, 4) == "sky ")
        {
            std::string modelFile;
            glm::vec2 coord;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;

            mSky = new imageModel();
            mSky->loadFile(modelFile, coord);
        }
        else if(line.substr(0, 4) == "bkg ")
        {
            std::string modelFile;
            glm::vec2 coord;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;

            mBackground = new imageModel();
            mBackground->loadFile(modelFile, coord);
        }
        else if(line.substr(0, 4) == "frg ")
        {
            std::string modelFile;
            glm::vec2 coord;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;

            mForeground = new imageModel();
            mForeground->loadFile(modelFile, coord);
        }
        else if(line.substr(0, 4) == "prt ")
        {
            std::string modelFile;
            glm::vec2 coord;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;

            mPorte = new imageModel();
            mPorte->loadFile(modelFile, coord);
        }
        else if(line.substr(0, 4) == "obj ")
        {
            std::string modelFile;
            glm::vec2 coord;
            float angle;
            int canCollide, canDraw, canInteract;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;
            streamLine >> angle;
            streamLine >> canCollide;
            streamLine >> canDraw;
            streamLine >> canInteract;

            imageModel* obj = new imageModel();
            obj->loadFile(modelFile, coord);
            obj->setAngle(angle);

            groundObject* go = new groundObject();
            go->object = obj;
            go->canCollide = canCollide;
            go->canDraw = canDraw;
            go->canInteract = canInteract;

            mGround.push_back(go);
        }
        else if(line.substr(0, 4) == "wtr ")
        {
            glm::vec2 coord;
            float height;

            std::istringstream streamLine(line.substr(4));
            streamLine >> coord.x;
            streamLine >> coord.y;
            streamLine >> height;

            mWater = new Water();
            mWater->initWater(glm::vec2(coord.x, height), glm::vec2(coord.y, height), 500, 0.01f, 0.02f);
        }
        else if(line.substr(0, 4) == "str ")
        {
            std::istringstream streamLine(line.substr(4));
            streamLine >> playerPos.x;
            streamLine >> playerPos.y;
        }
        else if(line.substr(0, 4) == "dim ")
        {
            std::istringstream streamLine(line.substr(4));
            streamLine >> mLevelLength.x;
            streamLine >> mLevelLength.y;
        }
        else if(line.substr(0, 4) == "rid ")
        {
            std::istringstream streamLine(line.substr(4));
            streamLine >> mId;
        }
        else if(line.substr(0, 4) == "cnn ")
        {
            std::istringstream streamLine(line.substr(4));
            streamLine >> mNextId;
        }
    }

    fichier.close();

    return playerPos;
}

void Environnement::setSky(imageModel* pSky) {}
void Environnement::setBackground(imageModel* pBg) {}
void Environnement::setForeground(imageModel* pFg) {}

void Environnement::drawSky(GLuint pShaderProgram, float pTimeElapsed)
{
    mSky->drawImage(pShaderProgram, pTimeElapsed, mBgView, mBgProj);
}

void Environnement::drawBackground(GLuint pShaderProgram, float pTimeElapsed)
{
    mBackground->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
}

void Environnement::drawForeground(GLuint pShaderProgram, float pTimeElapsed)
{
    mForeground->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
}

void Environnement::drawGround(GLuint pShaderProgram, float pTimeElapsed)
{
    for(int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canDraw)
            mGround[i]->object->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
}

void Environnement::drawWater(GLuint pShaderProgram, float pTimeLastFrame)
{
    if(mWater != nullptr){
        mWater->actualiser(pTimeLastFrame);
        mWater->drawWater(pShaderProgram, mView, mProj);
    }
}

void Environnement::resoudreCollisions(Personnage* pPerso)
{
    if(pPerso->isCollision(mPorte)) std::cout << "Changement de piece!" << std::endl;

    for(int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canCollide)
            if(pPerso->isCollision(mGround[i]->object)) pPerso->resoudreCollision(pPerso->getDeplacement(mGround[i]->object));
}

imageModel* Environnement::getClickRef(imageModel* pSouris)
{
    for(int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canInteract && mGround[i]->canDraw)
            if(pSouris->isCollision(mGround[i]->object))
                return mGround[i]->object;
                //std::cout << "Collision: " << mGround[i]->object->getId() << std::endl;

    return nullptr;
}


