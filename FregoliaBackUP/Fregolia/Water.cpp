#include "Water.h"

Water::Water()
{
    mTranslateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

Water::~Water()
{
    glDeleteBuffers(1, &mVerticesVBO);
}

void Water::initWater(glm::vec2 pStart, glm::vec2 pEnd, int pResolution, float pViscosite, float pK)
{
    mViscosite = pViscosite;
    mK = pK;
    mHauteurInit = pStart.y;

    /// Creation des points
    glm::vec2 delta = (pEnd - pStart) / (float) pResolution;
    glm::vec2 pointActuel = pStart;
    mListePoints.push_back(glm::vec3(pointActuel.x, pointActuel.y, 0.0f));
    mListePoints.push_back(glm::vec3(pointActuel.x, -500.0f, 0.0f));

    for(int i = 0; i < pResolution; ++i)
    {
        pointActuel += delta;
        mListePoints.push_back(glm::vec3(pointActuel.x, pointActuel.y, 0.0f));
        mListePoints.push_back(glm::vec3(pointActuel.x, -500.0f, 0.0f));
    }

    /// Generation de l'array d'elements
    for(unsigned int i = 0; i < mListePoints.size() - 2; i += 2)
    {
        mElements.push_back(i);
        mElements.push_back(i + 2);
        mElements.push_back(i + 1);

        mElements.push_back(i + 2);
        mElements.push_back(i + 1);
        mElements.push_back(i + 3);
    }

    glGenBuffers(1, &mElementsBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementsBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mElements.size() * sizeof(int),
                 mElements.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &mVerticesVBO);

    genererGeometrie();
}

void Water::actualiser(int pDeltaTemps)
{

    /// Calcul de la loi de Hooke pour chaque "point" et actualisation de la vitesse / position
    for(unsigned int i = 0; i < mListePoints.size(); i += 2)
    {
        float mAccel = -(mK * (mListePoints[i].y - mHauteurInit)) - mListePoints[i].z * mK / 2;
        mListePoints[i].z += mAccel;
        mListePoints[i].y += mListePoints[i].z * pDeltaTemps / 25;
    }

    /// Influence de chaque point aux alentours
    for(int j = 0; j < 16; ++j) {
        for(unsigned int i = 0; i < mListePoints.size() - 2; i += 2)
        {
            float deltaI = (mListePoints[i + 2].y - mListePoints[i].y) * mViscosite * pDeltaTemps;
            float deltaI2 = (mListePoints[i].y - mListePoints[i + 2].y) * mViscosite * pDeltaTemps;

            mListePoints[i].y += deltaI;
            mListePoints[i + 2].y += deltaI2;

            mListePoints[i].z += deltaI;
            mListePoints[i + 2].z += deltaI2;
        }
    }

    genererGeometrie();
}

void Water::drawWater(GLuint pShaderProgram, glm::mat4 pView, glm::mat4 pProj)
{
    glUseProgram(pShaderProgram);

    GLint vertAttribute = glGetAttribLocation(pShaderProgram, "Coord2D");

    if(vertAttribute < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementsBuffer);

    glEnableVertexAttribArray(vertAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);

    glVertexAttribPointer(vertAttribute,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "MMat"), 1, GL_FALSE, glm::value_ptr(mTranslateMat));
    glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "VMat"), 1, GL_FALSE, glm::value_ptr(pView));
    glUniformMatrix4fv(glGetUniformLocation(pShaderProgram, "PMat"), 1, GL_FALSE, glm::value_ptr(pProj));

    glDrawElements(GL_TRIANGLES, mElements.size(), GL_UNSIGNED_INT, 0);
}

void Water::splashWater(float pRatio, float pIntensite)
{
    int startPoint = floor(pRatio * (mListePoints.size() / 2)) * 2;

    mListePoints[startPoint].z -= pIntensite * 500;
}

void Water::genererGeometrie()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 mListePoints.size() * sizeof(glm::vec3),
                 mListePoints.data(),
                 GL_STREAM_DRAW);
}


