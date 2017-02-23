#include "loadModel.h"

imageModel::imageModel()
{

}

imageModel::~imageModel()
{

}

void imageModel::loadFile(std::string pFilePath)
{
    std::vector<glm::vec2> listePoints;
    std::vector<glm::vec2> listeTexture;

    std::ifstream fichier;
    fichier.open(pFilePath);

    std::string line;
    while(std::getline(fichier, line))
    {

    }
}

void imageModel::drawImage(GLuint shaderProgram)
{

}

