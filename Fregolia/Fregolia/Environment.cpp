#include "Environment.h"

Environnement::Environnement()
{
    mBgView = glm::mat4(1.0f);
    mBgProj = glm::mat4(1.0f);

    mLevelLength = glm::vec2(0, 1024);
}
Environnement::~Environnement()
{
    for(unsigned int i = 0; i < mListeMvt.size(); ++i) {
        //delete mListeMvt[i]->object;
        delete mListeMvt[i];
    }

    for(unsigned int i = 0; i < mGround.size(); ++i) {
        delete mGround[i]->object;
        delete mGround[i];
    }

    for(unsigned int i = 0; i < mListeCollisions.size(); ++i) {
        //delete mListeCollisions[i]->object;
        delete mListeCollisions[i];
    }

    for(unsigned int i = 0; i < mListePhysique.size(); ++i) {
        //delete mListePhysique[i]->object;
        delete mListePhysique[i];
    }

    for(unsigned int i = 0; i < mListeInteractif.size(); ++i) {
        //delete mListeInteractif[i]->object;
        delete mListeInteractif[i];
    }

    mListeMvt.clear();
    mGround.clear();
    mListeCollisions.clear();
    mListePhysique.clear();
    mListeInteractif.clear();

    delete mSky;
    delete mBackground;
    delete mForeground;
    delete mPorte;
    delete mWater;

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
            float angle, uC,masse,constanteRappel,uS;
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
            streamLine >> uS;

            imageModel* obj = new imageModel();

            if(canDeplacer==1){
                    obj = new PhysicActor();
                    ((PhysicActor*)obj)->createActor(uC, masse, constanteRappel,uS);
            }else{

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
            if(canDeplacer==1) mListePhysique.push_back(go);
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
        else if(line.substr(0, 4) == "spw ")
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

            SpiderWeb* obj = new SpiderWeb();

            obj->loadFile(modelFile, coord);
            obj->setAngle(angle);

            groundObject* go = new groundObject();
            go->object = obj;
            go->canCollide = canCollide;
            go->canDraw = canDraw;
            go->canInteract = canInteract;
            go->canDeplacer = 0;
            //mGround.push_back(go);
            mListeInteractif.push_back(go);
        }
        else if(line.substr(0, 4) == "emi ")
        {
            std::string modelFile;
            glm::vec2 coord;
            float angle, uC,masse,constanteRappel,uS;
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
            streamLine >> uS;

            Enemy* obj = new Enemy();

            //obj = new PhysicActor();
            ((PhysicActor*)obj)->createActor(uC, masse, constanteRappel,uS);

            obj->loadFile(modelFile, coord);
            obj->setAngle(angle);

            groundObject* go = new groundObject();
            go->object = obj;
            go->canCollide = canCollide;
            go->canDraw = canDraw;
            go->canInteract = canInteract;
            go->canDeplacer=canDeplacer;

            //mGround.push_back(go);
            mListeInteractif.push_back(go);
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

    std::cout << mListeInteractif.size() << std::endl;

    for(unsigned int i = 0; i < mListeInteractif.size(); ++i)
        if(mListeInteractif[i]->canDraw) {
                std::cout << "Dessin de " << i << std::endl;
            mListeInteractif[i]->object->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
        }
}

void Environnement::drawWater(GLuint pShaderProgram, float pTimeLastFrame)
{
    if(mWater != nullptr){
        mWater->actualiser(pTimeLastFrame);
        mWater->drawWater(pShaderProgram, mView, mProj);
    }
}

void Environnement::resoudreCollisionsPerso(Personnage* pPerso)
{
    if(pPerso->isCollision(mPorte)) std::cout << "Changement de piece!" << std::endl;

    mListeCollisions.clear();

    bool collisionSol = false;

     for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canCollide)
            if(pPerso->isCollision(mGround[i]->object))
            {
                mListeCollisions.push_back(mGround[i]);
                glm::vec2 deplacement = pPerso->getDeplacement(mGround[i]->object);
                pPerso->resoudreCollision(deplacement);

                if(deplacement.y > 0) collisionSol = true;
            }

    pPerso->mCollisionSol = collisionSol;

    for(unsigned int i = 0; i < mListeInteractif.size(); ++i)
        if(pPerso->isCollision(mListeInteractif[i]->object) && mListeInteractif[i]->canInteract)
        {
            if(dynamic_cast<SpiderWeb*>(mListeInteractif[i]->object) != 0)
                ((SpiderWeb*)(mListeInteractif[i]->object))->collisionToile();
        }
}

void Environnement::updateInteractifs(Personnage* pPerso, int timeLastFrame)
{
    for(unsigned int i = 0; i < mListeInteractif.size(); ++i)
    {
        if(dynamic_cast<SpiderWeb*>(mListeInteractif[i]->object) != 0)
            ((SpiderWeb*)(mListeInteractif[i]->object))->processusToile(pPerso);
        else if(dynamic_cast<Enemy*>(mListeInteractif[i]->object) != 0) {
            ((Enemy*)(mListeInteractif[i]->object))->aiProcess(pPerso);
            ((Enemy*)(mListeInteractif[i]->object))->gererDeplacement(timeLastFrame);
        }
    }
}

void Environnement::resoudreCollisionsInteractifs()
{
    for(int j = 0; j < mListeInteractif.size(); ++j)
        if(dynamic_cast<Enemy*>(mListeInteractif[j]->object) != 0 && mListeInteractif[j]->canCollide)
            for(unsigned int i = 0; i < mGround.size(); ++i)
                if(mGround[i]->canCollide)
                    if(mListeInteractif[j]->object->isCollision(mGround[i]->object)) { std::cout << "COLLISION " << j << " " << i << "\t" << mGround[i]->object->getDimensions().x << " " << mGround[i]->object->getDimensions().y << std::endl;
                    std::cout << "DEPLACEMENT " << mListeInteractif[j]->object->getDeplacement(mGround[i]->object).x << " " << mListeInteractif[j]->object->getDeplacement(mGround[i]->object).y << std::endl;
                    mListeInteractif[j]->object->moveImage(mListeInteractif[j]->object->getDeplacement(mGround[i]->object));
                    ((PhysicActor*)mListeInteractif[j]->object)->mCollisionSol = (mListeInteractif[j]->object->getDeplacement(mGround[i]->object).y > 0 ? 1 : 0);
                    }
}

imageModel* Environnement::getClickRef(imageModel* pSouris)
{
    for(unsigned int i = 0; i < mGround.size(); ++i)
        if(mGround[i]->canInteract && mGround[i]->canDraw)
            if(pSouris->isCollision(mGround[i]->object))
                return mGround[i]->object;

    return nullptr;
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
                    else
                    {
                        mGround[i]->object->moveImage(((Collidable*)mGround[i]->object)->getDeplacement(((Collidable*)mGround[j]->object)));
                    }
}

void Environnement::appliquerGravite(int pTempsEcoule){
    for(unsigned int i = 0; i < mListePhysique.size(); ++i)
    {

        ((PhysicActor*)mListePhysique[i]->object)->gererDeplacement(pTempsEcoule);
        ((PhysicActor*)mListePhysique[i]->object)->rebondPerso();

        if(((PhysicActor*)mListePhysique[i]->object)->mCollisionSol)
            ((PhysicActor*)mListePhysique[i]->object)->mouvementRotation();
    }
}

void Environnement::updateListeMvt()
{
    for(int i = 0; i < mListeCollisions.size(); ++i)
    {
        if(mListeCollisions[i]->canDeplacer)
        {
            if(mListeMvt.size() == 0)
            {
                    mListeMvt.push_back(mListeCollisions[i]);
                    //testPerso.pousserObjet((PhysicActor*)(mListeCollisions[i])->object);
                    continue;
            }

            for(int j = 0; j < mListeMvt.size(); ++j)
            {
                if(mListeCollisions[i] == mListeMvt[j]) break;
                else if(j == mListeMvt.size() - 1)
                {
                    mListeMvt.push_back(mListeCollisions[i]);
                    //testPerso.pousserObjet((PhysicActor*)(mListeCollisions[i])->object);
                }
            }
        }
    }
}

void Environnement::updateDeplacements(int timeLastFrame)
{
    for(int i = 0; i < mListeMvt.size(); ++i)
    {
        if(!(((PhysicActor*)(mListeMvt[i])->object)->enMouvement())) mListeMvt.erase(mListeMvt.begin() + i);
        else
        {
            ((PhysicActor*)(mListeMvt[i])->object)->vitesseReduite(timeLastFrame);
            ((PhysicActor*)(mListeMvt[i])->object)->moveImage(((PhysicActor*)(mListeMvt[i])->object)->getVitesse());

            ((PhysicActor*)(mListeMvt[i])->object)->rebondPerso();
        }
    }
}

void Environnement::updateAnimations()
{
    /*for(int i = 0; i < mGround.size(); ++i)
    {
        mGround[i]->obje
    }*/

    for(unsigned int i = 0; i < mListeInteractif.size(); ++i)
        if(dynamic_cast<Enemy*>(mListeInteractif[i]->object) != 0)
            ((Enemy*)(mListeInteractif[i]->object))->boucleAnimations();
}

void Environnement::resoudreCollisionsArme(Weapon* pWeapon)
{
    for(unsigned int i = 0; i < mListeInteractif.size(); ++i)
        if(dynamic_cast<Enemy*>(mListeInteractif[i]->object) != 0)
            if(pWeapon->siBeingUsed() && pWeapon->isCollision(((Enemy*)(mListeInteractif[i]->object))))
            {
                pWeapon->setBeingUsed(false);
                ((Enemy*)(mListeInteractif[i]->object))->ennemiTouche(10);

                if (((Enemy*)(mListeInteractif[i]->object))->isMortEnnemi())
                {
                    delete mListeInteractif[i]->object;
                    delete mListeInteractif[i];
                    mListeInteractif.erase(mListeInteractif.begin() + i);
                }
            }
}

glm::vec2* Environnement::resoudreCollisionPorte(Personnage* pPerso)
{
    if(pPerso->isCollision(mPorte))
    {
        /// ON EFFACE TOUT!
        for(unsigned int i = 0; i < mListeMvt.size(); ++i) {
            delete mListeMvt[i];
        }

        for(unsigned int i = 0; i < mGround.size(); ++i) {
            delete mGround[i]->object;
            delete mGround[i];
        }

        for(unsigned int i = 0; i < mListeCollisions.size(); ++i) {
            delete mListeCollisions[i];
        }

        for(unsigned int i = 0; i < mListePhysique.size(); ++i) {
            delete mListePhysique[i];
        }

        for(unsigned int i = 0; i < mListeInteractif.size(); ++i) {
            delete mListeInteractif[i];
        }

        mListeMvt.clear();
        mGround.clear();
        mListeCollisions.clear();
        mListePhysique.clear();
        mListeInteractif.clear();

        delete mSky;
        delete mBackground;
        delete mForeground;
        delete mPorte;
        delete mWater;



        /// CHARGEMENT DU NOUVEAU NIVEAU
        std::stringstream ss;
        ss << mNextId;
        glm::vec2 newStartPos = this->loadLevel((std::string)"./resources/level" + ss.str() + (std::string)".txt");
        pPerso->moveImage(newStartPos);
        pPerso->reset(newStartPos);
        return &newStartPos;
    }

    return nullptr;
}


