#pragma once

#include "externalIncludes.h"

class imageModel
{
    public:
        imageModel();
        virtual ~imageModel();

        virtual void loadFile(std::string pFilePath) final;
        virtual void drawImage(GLuint pShaderProgram) final;

    private:
        GLuint mTextureVBO, mVerticesVBO;
        GLuint mTexture;

        int imageID;
};
