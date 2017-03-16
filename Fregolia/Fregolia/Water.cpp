#include "Water.h"

Water::Water()
{

}

Water::~Water()
{
    glDeleteBuffers(1, &mVerticesVBO);
}

void Water::initWater(glm::vec2 pStart, glm::vec2 pEnd, int pResolution)
{
    glm::vec2 delta = (pEnd - pStart) / (float) pResolution;
    glm::vec2 pointActuel = pStart;
    mListePoints.push_back(glm::vec4(pointActuel.x, pointActuel.y, 0.0f, 0.0f));

    for(int i = 0; i < pResolution; ++i)
    {
        pointActuel += delta;
        mListePoints.push_back(glm::vec4(pointActuel.x, pointActuel.y, 0.0f, 0.0f));
    }


}

void Water::drawWater(GLuint pShaderProgram, float pTimeElapsed, glm::mat4 pView, glm::mat4 pProj)
{

}

void Water::splashWater(int pRatio, int pIntensite)
{

}

void Water::genererGeometrie()
{

}

void Water::calculerPosition(int pPoint)
{

}

