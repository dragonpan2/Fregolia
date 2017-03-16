#include "environment.h"

Environnement::Environnement()
{
    mPlayerPos = glm::vec2(0, 0);
    mBgView = glm::mat4(1.0f);
    mBgProj = glm::mat4(1.0f);
}

Environnement::~Environnement()
{
    delete mBackground;
    delete mForeground;
    delete mSky;
    for(int i = 0; i < mGround.size(); ++i) delete mGround[i];
}

void Environnement::setMatrices(glm::mat4 pView, glm::mat4 pProj)
{
    mView = pView;
    mProj = pProj;
}

void Environnement::setSky(imageModel* pSky)
{
    mSky = pSky;
}

void Environnement::setBackground(imageModel* pBg)
{
    mBackground = pBg;
}

void Environnement::setForeground(imageModel* pFg)
{
    mForeground = pFg;
}

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
        //if(mGround[i]->getPos().x > mPlayerPos.x - SCREEN_WIDTH / 2 && mGround[i]->getPos().x < mPlayerPos.x + SCREEN_WIDTH / 2)
            mGround[i]->drawImage(pShaderProgram, pTimeElapsed, mView, mProj);
}

void Environnement::addObject(imageModel* pObj)
{

}

void Environnement::setPlayerPos(glm::vec2 pPPos)
{
    mPlayerPos = pPPos;
    mBackground->setPos(mPlayerPos);
}


