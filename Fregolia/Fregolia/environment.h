#pragma once

#include "externalIncludes.h"
#include "loadModel.h"



class Environnement
{
    public:
        Environnement();
        virtual ~Environnement();
        virtual void setMatrices(glm::mat4 pView, glm::mat4 pProj) final;
        virtual void setSky(imageModel* pSky) final;
        virtual void setBackground(imageModel* pBg) final;
        virtual void setForeground(imageModel* pFg) final;
        virtual void drawSky(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawBackground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawForeground(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void drawGround(GLuint pShaderProgram, float pTimeElapsed) final;
        virtual void addObject(imageModel* pObj) final;
        virtual void setPlayerPos(glm::vec2 pPPos) final;
    private:

        glm::vec2 mPlayerPos;

        imageModel* mBackground;
        imageModel* mForeground;
        imageModel* mSky;
        std::vector<imageModel*> mGround;

        glm::mat4 mBgView, mBgProj;
        glm::mat4 mView, mProj;


};
