#include "loadModel.h"

imageModel::imageModel()
{

}

imageModel::~imageModel()
{
    glDeleteBuffers(1, &mVerticesVBO);
    glDeleteBuffers(1, &mTextureVBO);
    glDeleteTextures(1, &mTexture);
}

void imageModel::loadFile(std::string pFilePath, glm::vec2 pPos)
{
    mPos = pPos;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(pPos.x, pPos.y, 0.0f));

    std::vector<glm::vec2> listePoints;
    std::vector<glm::vec2> listeTexture;

    std::ifstream fichier;
    fichier.open(pFilePath.c_str());

    std::string line;
    while(std::getline(fichier, line))
    {
        if(line.substr(0, 2) == "v ")
        {
            std::istringstream streamLine(line.substr(2));
            glm::vec2 coord;
            while(streamLine >> coord.x)
            {
                streamLine >> coord.y;
                listePoints.push_back(coord);
            }
        }
        if(line.substr(0, 2) == "t ")
        {
            std::istringstream streamLine(line.substr(2));
            glm::vec2 coord;
            while(streamLine >> coord.x)
            {
                streamLine >> coord.y;
                listeTexture.push_back(coord);
            }
        }
        else if(line.substr(0, 2) == "d ")
        {
            std::istringstream streamLine(line.substr(2));
            glm::vec2 coord;
            streamLine >> mDimensions.x;
            streamLine >> mDimensions.y;
        }
        else if(line.substr(0, 3) == "id ")
        {
            imageID = atoi(line.substr(2).c_str());
        }
        else if(line.substr(0, 2) == "i ")
        {
            mTexture = SOIL_load_OGL_texture(line.substr(2).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

            if(mTexture == 0)
            {
                std::cout << "Erreur de chargement SOIL: '" << SOIL_last_result() << "'" << std::endl;
            }

            glBindTexture(GL_TEXTURE_2D, mTexture);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    fichier.close();

    /// G�n�ration des points du AABB
    mCoins[0] = glm::vec2((-mDimensions.x / 2) + mPos.x, (mDimensions.y / 2) + mPos.y);
    mCoins[1] = glm::vec2((mDimensions.x / 2) + mPos.x, (mDimensions.y / 2) + mPos.y);
    mCoins[2] = glm::vec2((mDimensions.x / 2) + mPos.x, (-mDimensions.y / 2) + mPos.y);
    mCoins[3] = glm::vec2((-mDimensions.x / 2) + mPos.x, (-mDimensions.y / 2) + mPos.y);

    /// G�n�ration des bords du AABB
    mAxes[0] = mCoins[1] - mCoins[0];
    mAxes[1] = mCoins[3] - mCoins[0];

    mAxesLongueur[0] = glm::length(mAxes[0]);
    mAxesLongueur[1] = glm::length(mAxes[1]);

    mAxes[0] = glm::normalize(mAxes[0]);
    mAxes[1] = glm::normalize(mAxes[1]);

    glGenBuffers(1, &mVerticesVBO);
    glGenBuffers(1, &mTextureVBO);


    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 listePoints.size() * sizeof(glm::vec2),
                 listePoints.data(),
                 GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, mTextureVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 listeTexture.size() * sizeof(glm::vec2),
                 listeTexture.data(),
                 GL_DYNAMIC_DRAW);
}

void imageModel::drawImage(GLuint shaderProgram, float pTimeElapsed, glm::mat4 pView, glm::mat4 pProj)
{
    glUseProgram(shaderProgram);

    GLint vertAttribute = glGetAttribLocation(shaderProgram, "Coord2D");
    GLint texAttribute = glGetAttribLocation(shaderProgram, "texCoords");


    if(vertAttribute < 0 || texAttribute < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
    }

    GLint tex = glGetUniformLocation(shaderProgram, "Texture");
    if(tex < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
    }

    glEnableVertexAttribArray(vertAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);

    glVertexAttribPointer(vertAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glEnableVertexAttribArray(texAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, mTextureVBO);

    glVertexAttribPointer(texAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glBindTexture(GL_TEXTURE_2D, mTexture);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), GL_TEXTURE0);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MMat"), 1, GL_FALSE, glm::value_ptr(mTranslateMat));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "VMat"), 1, GL_FALSE, glm::value_ptr(pView));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "PMat"), 1, GL_FALSE, glm::value_ptr(pProj));

    glUniform1f(glGetUniformLocation(shaderProgram, "time"), pTimeElapsed);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    //std::cout << "ERREURFINAL: " << glGetError() << std::endl;
}

void imageModel::moveImage(glm::vec2 pDeplacement)
{
    mPos += pDeplacement;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(pDeplacement);
}

glm::vec2 imageModel::getPos()
{
    return mPos;
}

void imageModel::changeBB(glm::vec2 pDeplacement)
{
    mCoins[0] += pDeplacement;
    mCoins[1] += pDeplacement;
    mCoins[2] += pDeplacement;
    mCoins[3] += pDeplacement;
}

void imageModel::setPos(glm::vec2 pPos)
{
    mPos = pPos;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
}
