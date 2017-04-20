#pragma once

#include "ExternalIncludes.h"
#include "Collisions.h"
#include "AnimationManager.h"

class imageModel : public Collidable
{
    public:
        imageModel();
        virtual ~imageModel();

        virtual void loadFile(std::string pFilePath, glm::vec2 pPos) final;
        virtual void moveImage(glm::vec2 pDeplacement) final;
        virtual void drawImage(GLuint pShaderProgram, float pTimeElapsed, glm::mat4 pView, glm::mat4 pProj) final;

        virtual glm::vec2 getPos();
        virtual void setPos(glm::vec2 pPos); /// UTILISE SEULEMENT POUR LE BACKGROUND

        virtual void setCanCollide(bool pValue) {mCanCollide = pValue;}
        virtual bool getCanCollide() {return mCanCollide;}

        virtual int getId() {return mImageID;}

        virtual void setAngle(float pAngle) final;
        virtual float getAngle() {return mAngle;}

        virtual glm::vec2 getDimensions() {return mDimensions;}

        virtual void setTaille(glm::vec2 pPourcentage);

    protected:
        glm::vec2 mPos;
        glm::mat4 mTranslateMat, mRotateMat, mOBBRotateMat, mTotalMat, mScaleMat;
        glm::vec2 mDimensions;

        float mAngle;

        bool mCanCollide = false;

        AnimationManager mAnimations;

        virtual void changeBB(glm::vec2 pDeplacement) final;

    private:
        GLuint mVerticesVBO;
        GLuint mTexture;

        int mImageID;
};
