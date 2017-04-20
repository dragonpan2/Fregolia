#include "LoadModel.h"

imageModel::imageModel()
{
    mRotateMat = glm::mat4(1.0f);
    mScaleMat = glm::mat4(1.0f);
    mAngle = 0;
    mOBBRotateMat = glm::mat4(1.0f);
}

imageModel::~imageModel()
{
    glDeleteBuffers(1, &mVerticesVBO);
    glDeleteTextures(1, &mTexture);
}

void imageModel::loadFile(std::string pFilePath, glm::vec2 pPos)
{
    mPos = pPos;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(pPos.x, pPos.y, 0.0f));

    std::vector<glm::vec2> listePoints;
    std::vector<glm::vec2> listeTexture;

    glm::vec2 dimensionsImage;
    std::string imageFile;
    int intervalleAnim = 0;

    std::ifstream fichier;
    fichier.open(pFilePath.c_str());

    std::string line;
    while(std::getline(fichier, line))
    {
        if(line.substr(0, 3) == "di ")
        {
            std::istringstream streamLine(line.substr(3));
            glm::vec2 coord;
            streamLine >> mDimensions.x;
            streamLine >> mDimensions.y;
        }
        else if(line.substr(0, 3) == "dt ")
        {
            std::istringstream streamLine(line.substr(3));
            glm::vec2 coord;
            streamLine >> dimensionsImage.x;
            streamLine >> dimensionsImage.y;
        }
        else if(line.substr(0, 4) == "int ")
        {
            intervalleAnim = atoi(line.substr(3).c_str());
        }
        else if(line.substr(0, 3) == "id ")
        {
            mImageID = atoi(line.substr(2).c_str());
        }
        else if(line.substr(0, 2) == "i ")
        {
            imageFile = line.substr(2);

        }
    }

    fichier.close();


    /// Chargement des animations
    mAnimations.loadFile(intervalleAnim, mDimensions, dimensionsImage, imageFile);


    /// NOUVEAU: Génération des coorcdonnées dans l'espace à partir des dimensions
    listePoints.push_back(glm::vec2(-(mDimensions.x / 2), -(mDimensions.y / 2)));
    listePoints.push_back(glm::vec2((mDimensions.x / 2), -(mDimensions.y / 2)));
    listePoints.push_back(glm::vec2(-(mDimensions.x / 2), (mDimensions.y / 2)));

    listePoints.push_back(glm::vec2((mDimensions.x / 2), -(mDimensions.y / 2)));
    listePoints.push_back(glm::vec2(-(mDimensions.x / 2), (mDimensions.y / 2)));
    listePoints.push_back(glm::vec2((mDimensions.x / 2), (mDimensions.y / 2)));



    /// Génération des points du OBB
    mCoins[0] = glm::vec2((-mDimensions.x / 2) + mPos.x, (mDimensions.y / 2) + mPos.y);
    mCoins[1] = glm::vec2((mDimensions.x / 2) + mPos.x, (mDimensions.y / 2) + mPos.y);
    mCoins[2] = glm::vec2((mDimensions.x / 2) + mPos.x, (-mDimensions.y / 2) + mPos.y);
    mCoins[3] = glm::vec2((-mDimensions.x / 2) + mPos.x, (-mDimensions.y / 2) + mPos.y);



    /// Génération des bords du OBB
    mAxes[0] = mCoins[1] - mCoins[0];
    mAxes[1] = mCoins[3] - mCoins[0];

    mAxesLongueur[0] = glm::length(mAxes[0]);
    mAxesLongueur[1] = glm::length(mAxes[1]);

    mAxes[0] = glm::normalize(mAxes[0]);
    mAxes[1] = glm::normalize(mAxes[1]);

    glGenBuffers(1, &mVerticesVBO);



    /// Génération du buffer de points
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 listePoints.size() * sizeof(glm::vec2),
                 listePoints.data(),
                 GL_DYNAMIC_DRAW);
}

void imageModel::drawImage(GLuint shaderProgram, float pTimeElapsed, glm::mat4 pView, glm::mat4 pProj)
{
    mAnimations.updateAnimation(pTimeElapsed);

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
    glBindBuffer(GL_ARRAY_BUFFER, mAnimations.getCurrentImageBuffer());

    glVertexAttribPointer(texAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glBindTexture(GL_TEXTURE_2D, mAnimations.getTexture());
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), GL_TEXTURE0);

    mTotalMat = mTranslateMat * mRotateMat * mScaleMat;

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MMat"), 1, GL_FALSE, glm::value_ptr(mTotalMat));
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
    glm::vec2 deplacement = pPos - mPos;
    mPos = pPos;
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(mPos.x, mPos.y, 0.0f));
    changeBB(deplacement);
}

void imageModel::setAngle(float pAngle)
{

    mOBBRotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(pAngle - mAngle), glm::vec3(0, 0, 1));
    mAngle = pAngle;

    mRotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(mAngle), glm::vec3(0, 0, 1));

    for(int i = 0; i < 4; ++i) {
        glm::vec4 temp = mOBBRotateMat * glm::vec4(mCoins[i].x - mPos.x, mCoins[i].y - mPos.y, 0, 0);
        mCoins[i] = glm::vec2(temp.x + mPos.x, temp.y + mPos.y);
    }

    for(int i = 0; i < 4; ++i) {
        glm::vec4 temp = mOBBRotateMat * glm::vec4(mAxes[i].x, mAxes[i].y, 0, 0);
        mAxes[i] = glm::vec2(temp.x, temp.y);
    }
}

void imageModel::setTaille(glm::vec2 pPourcentage)
{
    mScaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(pPourcentage.x, pPourcentage.y, 1));
}

