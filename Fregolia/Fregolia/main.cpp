#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"
#include "loadModel.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram;

imageModel testImage;

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

    testImage.loadFile("./resources/testImage.txt");

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    int curTime = SDL_GetTicks();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.3, 0.3, 0.35, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    testImage.drawImage(shaderProgram);

    SDL_GL_SwapWindow(pWindow);

    timeLastFrame = SDL_GetTicks() - curTime;
    std::cout << timeLastFrame << std::endl;

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
