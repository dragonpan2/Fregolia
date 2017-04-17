#include "Environment.h"

Environnement::Environnement()
{
    mBgView = glm::mat4(1.0f);
    mBgProj = glm::mat4(1.0f);

    mLevelLength = glm::vec2(0, 1024);
}
Environnement::~Environnement()
{
    for(unsigned int i = 0; i < mListeMvt.size(); ++i)
        delete mListeMvt[i];

    for(unsigned int i = 0; i < mGround.size(); ++i)
        delete mGround[i];

    for(unsigned int i = 0; i < mListeCollisions.size(); ++i)
        delete mListeCollisions[i];

}

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
            float angle, uC,masse,constanteRappel;
            int canCollide, canDraw, canInteract, canDeplacer;

            std::istringstream streamLine(line.substr(4));
            streamLine >> modelFile;
            streamLine >> coord.x;
            streamLine >> coord.y;
            streamLine >> angle;
            streamLine >> canCollide;
            streamLine >> canDraw;
            streamLine >> canInteract;
            streamLine >> canDeplacer;
            streamLine >> uC;
            streamLine >> masse;
            streamLine >> constanteRappel;

            imageModel* obj = new imageModel();

            if(canDeplacer==1)
            {
                obj = new PhysicActor();
                ((PhysicActor*)obj)->createActor(uC, masse, constanteRappel);

            }
            else
            {

            }

            obj->loadFile(modelFile, coord);
            obj->setAngle(angle);


            groundObject* go = new groundObject();
            go->object = obj;
            go->canCollide = canCollide;
            go->canDraw = canDraw;
            go->canInteract = canInteract;
            go->canDeplacer=canDeplacer;
            mGround.push_back(go);
            if(canDeplacer==1)mListePhysic.push_back(go);
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
    for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canDraw)
            mGround[i]->object->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
}

void Environnement::drawWater(GLuint pShaderProgram, float pTimeLastFrame)
{
    if(mWater != nullptr)
    {
        mWater->actualiser(pTimeLastFrame);
        mWater->drawWater(pShaderProgram, mView, mProj);
    }
}

void Environnement::resoudreCollisionsPerso(Personnage* pPerso)
{
    if(pPerso->isCollision(mPorte)) std::cout << "Changement de piece!" << std::endl;



    mListeCollisions.clear();

    bool collisionSol = false;
    bool collisionCoter=false;


    for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canCollide)
            if(pPerso->isCollision(mGround[i]->object))
            {
                mListeCollisions.push_back(mGround[i]);
                glm::vec2 deplacement = pPerso->getDeplacement(mGround[i]->object);
                pPerso->resoudreCollision(deplacement);

                if(deplacement.y > 0) collisionSol = true;
                if( deplacement.x!=0 && deplacement.x<13 && deplacement.x>-13  ) collisionCoter=true; std::cout<<"------------------------------/" <<deplacement.x<<std::endl;
            }

    pPerso->mCollisionSol = collisionSol;
    pPerso->mCollisionCoter=collisionCoter;
}

void Environnement::resoudreCollisionsEnnemi(Enemy* pPerso)
{

    for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canCollide)
            if(pPerso->isCollision(mGround[i]->object)) pPerso->moveImage(pPerso->getDeplacement(mGround[i]->object));
}

imageModel* Environnement::getClickRef(imageModel* pSouris)
{
    for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canInteract && mGround[i]->canDraw)
            if(pSouris->isCollision(mGround[i]->object))
                return mGround[i]->object;

    return nullptr;
}

std::vector<groundObject*>::iterator Environnement::getListeCollision()
{
    return mListeCollisions.begin();
}

void Environnement::resoudreCollisionsObjets()
{
    bool collisionSol = false;

    for(unsigned int i = 0; i < mGround.size(); ++i)
        for(unsigned int j = 0; j < mGround.size(); ++j)
            if(mGround[i]->canCollide && mGround[j]->canCollide)
                if(i != j && ((Collidable*)mGround[i]->object)->isCollision(((Collidable*)mGround[j]->object)))
                    if(mGround[i]->canDeplacer)
                    {
                        mGround[i]->object->moveImage(((Collidable*)mGround[i]->object)->getDeplacement(((Collidable*)mGround[j]->object)));
                        /// L'OBJET mGround[i] A EU UNE COLLISION
                        glm::vec2 deplacement =((Collidable*)mGround[i]->object)->getDeplacement(((Collidable*)mGround[j]->object));
                        if(deplacement.y > 0) collisionSol = true;




                        ((PhysicActor*)mGround[i]->object)->mCollisionSol = collisionSol;

                    }
                    else if(mGround[j]->canDeplacer)
                    {
                        mGround[j]->object->moveImage(((Collidable*)mGround[j]->object)->getDeplacement(((Collidable*)mGround[i]->object)));
                        /// L'OBJET mGround[j] A EU UNE COLLISION

                        glm::vec2 deplacement =((Collidable*)mGround[j]->object)->getDeplacement(((Collidable*)mGround[i]->object));

                        if(deplacement.y > 0) collisionSol = true;
                        ((PhysicActor*)mGround[j]->object)->mCollisionSol = collisionSol;
                    }


}
void Environnement:: appliquerGraviterEnvironnement(int pTempsEcoule){

for(unsigned int i = 0; i < mListePhysic.size(); ++i)
    {

((PhysicActor*)mListePhysic[i]->object)->gererDeplacement(pTempsEcoule);
((PhysicActor*)mListePhysic[i]->object)->rebondPerso();

if(((PhysicActor*)mListePhysic[i]->object)->mCollisionSol){

((PhysicActor*)mListePhysic[i]->object)->mouvementRotation();

}
    }





}





