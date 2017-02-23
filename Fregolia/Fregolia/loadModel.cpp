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
        else if(line.substr(0, 2) == "t ")
        {
            std::istringstream streamLine(line.substr(2));
            glm::vec2 coord;
            while(streamLine >> coord.x)
            {
                streamLine >> coord.y;
                listeTexture.push_back(coord);
            }
        }
        else if(line.substr(0, 3) == "id ")
        {
            imageID = atoi(line.substr(2).c_str());
        }
        else if(line.substr(0, 2) == "i ")
        {
            mTexture = SOIL_load_OGL_texture(line.substr(2).c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

            if(mTexture == 0 || NULL)
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

void imageModel::drawImage(GLuint shaderProgram)
{
    glUseProgram(shaderProgram);

    GLint vertAttribute = glGetAttribLocation(shaderProgram, "Coord2D");
    GLint texAttribute = glGetAttribLocation(shaderProgram, "texCoords");

    if(vertAttribute < 0 || texAttribute < 0)
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
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "TMat"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1))));


    glDrawArrays(GL_TRIANGLES, 0, 6);
}

