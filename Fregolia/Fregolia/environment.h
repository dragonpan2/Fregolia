#pragma once

#include "ExternalIncludes.h"

#include "personnage.h"
#include "Water.h"
#include "LoadModel.h"
#include "Enemy.h"
#include "SpiderWeb.h"
#include "Weapon.h"

struct groundObject
{
    imageModel* object;

    int canCollide;
    int canDraw;
    int canInteract;
    int canDeplacer;
};

class Environnement
{
    public:
        Environnement();
        virtual ~Environnement();
        virtual void setMatrices(glm::mat4 pView, glm::mat4 pProj) final;

        virtual glm::vec2 loadLevel(std::string pLevelFile) final;

        virtual void setSky(imageModel* pSky) final;
        virtual void setBackground(imageModel* pBg) final;
        virtual void setForeground(imageModel* pFg) final;

        virtual void drawSky(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawBackground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawForeground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawGround(GLuint pShaderProgram, float pTimeElapsed) final; /// INCLUT INTERACTIFS

        //virtual void drawInteractifs(GLuint pShaderProgram, float pTimeElapsed) final;

        virtual void drawWater(GLuint pShaderProgram, float pTimeLastFrame) final;
        virtual void splash(float pLoc, float pMasse) final {mWater->splashWater(pLoc, 1.0f / pMasse);}

        virtual void resoudreCollisionsPerso(Personnage* pPerso);
        virtual void resoudreCollisionsInteractifs();
        virtual void resoudreCollisionsArme(Weapon* pWeapon);
        virtual void resoudreCollisionsObjets();

        virtual glm::vec2* resoudreCollisionPorte(Personnage* pPerso);

        virtual void appliquerGravite(int pTempsEcoule);

        virtual void updateListeMvt();
        virtual void updateDeplacements(int timeLastFrame);

        virtual void updateInteractifs(Personnage* pPerso, int timeLastFrame);

        virtual void updateAnimations();

        virtual imageModel* getClickRef(imageModel* pSouris);
        virtual glm::vec2 getLength() {return mLevelLength;}

    private:

        glm::vec2 mPlayerPos;
        glm::vec2 mLevelLength;

        //virtual void addObject(imageModel* pObj) final;
        //virtual void setPlayerPos(glm::vec2 pPPos) final;

        imageModel* mBackground;
        imageModel* mForeground;
        imageModel* mSky;
        imageModel* mPorte;

        std::vector<groundObject*> mGround;
        std::vector<groundObject*> mListePhysique;
        std::vector<groundObject*> mListeCollisions;
        std::vector<groundObject*> mListeMvt;
        std::vector<groundObject*> mListeInteractif;

        Water* mWater;

        glm::mat4 mBgView, mBgProj;
        glm::mat4 mView, mProj;

        int mId, mNextId;

};
