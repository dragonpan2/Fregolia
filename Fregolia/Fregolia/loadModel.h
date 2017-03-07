#pragma once

#include "externalIncludes.h"

class imageModel
{
    public:
        imageModel();
        virtual ~imageModel();

        virtual void loadFile(std::string pFilePath, glm::vec2 pPos) final;
        virtual void moveImage(glm::vec2 pDeplacement) final;
        virtual void drawImage(GLuint pShaderProgram, glm::mat4 pView, glm::mat4 pProj) final;

        virtual glm::vec2 getPos();

    protected:
        glm::vec2 mPos;
        glm::mat4 mTranslateMat;

    private:
        GLuint mTextureVBO, mVerticesVBO;
        GLuint mTexture;

        int imageID;

        glm::vec2 mDimensions;
};
