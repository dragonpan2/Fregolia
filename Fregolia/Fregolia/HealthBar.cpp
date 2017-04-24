#include "HealthBar.h"

HealthBar::HealthBar()
{

}

HealthBar::~HealthBar()
{

}

void HealthBar::loadBar()
{
    mBackground.loadFile("./resources/healthBar.txt", glm::vec2(0.0f,-0.70f));
    mHealth.loadFile("./resources/health.txt", glm::vec2(0.0f,-0.70f));
}

void HealthBar::updateHealth(float pPercent)
{
    mHealth.setTaille(glm::vec2(pPercent, 1.0f));
}

void HealthBar::drawBar(GLuint pShaderProgram, int pTotalTime)
{
    mBackground.drawImage(pShaderProgram, pTotalTime, glm::mat4(1.0f), glm::mat4(1.0f));
    mHealth.drawImage(pShaderProgram, pTotalTime, glm::mat4(1.0f), glm::mat4(1.0f));
}
