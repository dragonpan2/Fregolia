#pragma once

#include "ExternalIncludes.h"

#include "personnage.h"
#include "Water.h"
#include "LoadModel.h"
#include "Enemy.h"

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
        virtual void drawGround(GLuint pShaderProgram, float pTimeElapsed) final;

        virtual void drawWater(GLuint pShaderProgram, float pTimeLastFrame) final;
        virtual void splash() final {mWater->splashWater(0.5f, 1.0f);}

        virtual void resoudreCollisionsPerso(Personnage* pPerso);
        virtual void resoudreCollisionsEnnemi(Enemy* pPerso);
        virtual void resoudreCollisionsObjets();

        virtual std::vector<groundObject*>::iterator getListeCollision();
        virtual std::vector<groundObject*>::iterator lastCollisionObj() {return mListeCollisions.end();}

        virtual std::vector<groundObject*>::iterator getGroundObject(){return mGround.begin();}
        virtual std::vector<groundObject*>::iterator lastGroundObj() {return mGround.end();}

        virtual void appliquerGraviterEnvironnement(int pTempsEcoule);

        virtual void addMvtObject(groundObject* pObj) {mListeMvt.push_back(pObj);}
        virtual void removeMvtObject(int pIndex) {mListeMvt.erase(mListeMvt.begin() + pIndex);}
        virtual std::vector<groundObject*>::iterator getListeMvt(){return mListeMvt.begin();}
        virtual std::vector<groundObject*>::iterator lastMvtObj() {return mListeMvt.end();}


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
        std::vector<groundObject*> mListePhysic;
        std::vector<groundObject*> mListeCollisions;
        std::vector<groundObject*> mListeMvt;

        Water* mWater;

        glm::mat4 mBgView, mBgProj;
        glm::mat4 mView, mProj;

        int mId, mNextId;

};
