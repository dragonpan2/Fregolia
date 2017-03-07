#pragma once

#include "externalIncludes.h"
#include "Collisions.h"

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

    protected:
        glm::vec2 mPos;
        glm::mat4 mTranslateMat;

        bool mCanCollide = false;

        virtual void changeBB(glm::vec2 pDeplacement) final;

    private:
        GLuint mTextureVBO, mVerticesVBO;
        GLuint mTexture;

        int imageID;

        glm::vec2 mDimensions;
};
