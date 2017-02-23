#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram;
GLuint verticesVBO;

GLuint textureVBO;

GLuint texture;

int timeLastFrame;

float couleur[] = {0.0, 1.0, 0.0};

/** DÉCLARATIONS DE FONCTIONS **/

int initResources();
int renderScreen(SDL_Window* pWindow);
int renderTriangle();


/** CODE **/

int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");

    vector<float> listePoints = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        -0.5f, 0.5f,

        0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f};

    glGenBuffers(1, &verticesVBO);

    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 listePoints.size() * sizeof(float),
                 listePoints.data(),
                 GL_DYNAMIC_DRAW);

    vector<float> listeTex = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,

        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f};

    glGenBuffers(1, &textureVBO);

    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);

    glBufferData(GL_ARRAY_BUFFER,
                 listeTex.size() * sizeof(float),
                 listeTex.data(),
                 GL_DYNAMIC_DRAW);

    texture = SOIL_load_OGL_texture("./resources/image.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(texture == 0 || NULL) {
        std::cout << "Erreur de chargement SOIL: '" << SOIL_last_result() << "'" << std::endl;
        return -1;
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    int curTime = SDL_GetTicks();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.3, 0.3, 0.35, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    renderTriangle();

    SDL_GL_SwapWindow(pWindow);

    timeLastFrame = SDL_GetTicks() - curTime;
    std::cout << timeLastFrame << std::endl;

    return 0;
}

int renderTriangle()
{
    GLint vertAttribute = glGetAttribLocation(shaderProgram, "Coord2D");
    GLint texAttribute = glGetAttribLocation(shaderProgram, "texCoords");

    if(vertAttribute < 0 || texAttribute < 0)
    {
        std::cout << "OpenGL: " << glGetError() << std::endl;
        return -1;
    }

    glEnableVertexAttribArray(vertAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);

    glVertexAttribPointer(vertAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

    glEnableVertexAttribArray(texAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);

    glVertexAttribPointer(texAttribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          0);

	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), GL_TEXTURE0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    return 0;
}

int main(int argc, char* argv[])
{
    SDL_Window* mainWindow;
    SDL_GLContext mainContext;
    bool loopEnd = false;
    SDL_Event events;

    if(initOpenGL(&mainWindow, &mainContext) != 0)
        return -3;

    if(initResources())
    {
        SDL_GL_DeleteContext(mainContext);
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -4;
    }

    while(!loopEnd)
    {
        while(SDL_PollEvent(&events))
        {
            if(events.window.event == SDL_WINDOWEVENT_CLOSE || events.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                loopEnd = true;
            }
            switch(events.type)
            {
                case SDL_KEYDOWN:
                    switch(events.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_Q:
                            couleur[0] += 0.1f;
                            break;
                        case SDL_SCANCODE_A:
                            couleur[0] -= 0.1f;
                            break;
                        case SDL_SCANCODE_W:
                            couleur[1] += 0.1f;
                            break;
                        case SDL_SCANCODE_S:
                            couleur[1] -= 0.1f;
                            break;
                        case SDL_SCANCODE_E:
                            couleur[2] += 0.1f;
                            break;
                        case SDL_SCANCODE_D:
                            couleur[2] -= 0.1f;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        if(renderScreen(mainWindow))
        {
            SDL_GL_DeleteContext(mainContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return -5;
        }
    }

    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
