#pragma once

#include "externalIncludes.h"
<<<<<<< HEAD
#include "personnage.h"
#include "Water.h"

struct groundObject
{
    imageModel* object;
    int canCollide;
    int canDraw;
    int canInteract;
};
=======
#include "loadModel.h"


>>>>>>> origin/master

class Environnement
{
    public:
        Environnement();
        virtual ~Environnement();
        virtual void setMatrices(glm::mat4 pView, glm::mat4 pProj) final;
<<<<<<< HEAD
        virtual glm::vec2 loadLevel(std::string pLevelFile) final;
=======
>>>>>>> origin/master
        virtual void setSky(imageModel* pSky) final;
        virtual void setBackground(imageModel* pBg) final;
        virtual void setForeground(imageModel* pFg) final;
        virtual void drawSky(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawBackground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawForeground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawGround(GLuint pShaderProgram, float pTimeElapsed) final;
<<<<<<< HEAD
        virtual void drawWater(GLuint pShaderProgram, float pTimeLastFrame) final;
        virtual void splash() final {mWater->splashWater(0.5f, 1.0f);}
        virtual void resoudreCollisions(Personnage* pPerso);
        virtual imageModel* getClickRef(imageModel* pSouris);
        virtual glm::vec2 getLength() {return mLevelLength;}
    private:

        glm::vec2 mPlayerPos;
        glm::vec2 mLevelLength;
=======
        virtual void addObject(imageModel* pObj) final;
        virtual void setPlayerPos(glm::vec2 pPPos) final;
    private:

        glm::vec2 mPlayerPos;
>>>>>>> origin/master

        imageModel* mBackground;
        imageModel* mForeground;
        imageModel* mSky;
<<<<<<< HEAD
        imageModel* mPorte;
        std::vector<groundObject*> mGround;

        Water* mWater;
=======
        std::vector<imageModel*> mGround;
>>>>>>> origin/master

        glm::mat4 mBgView, mBgProj;
        glm::mat4 mView, mProj;

<<<<<<< HEAD
        int mId, mNextId;
=======

>>>>>>> origin/master
};
