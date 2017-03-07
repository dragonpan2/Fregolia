#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"
#include "loadModel.h"
#include "personnage.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram;

imageModel testBackground;
imageModel testCollision;
Personnage testPerso;

glm::mat4 projection, view;
glm::vec3 cameraPos, cameraTarget;

int listeTouches[1000] = {0};

int timeLastFrame;
float totalTime = 0.0f;

/** DÉCLARATIONS DE FONCTIONS **/

int initResources();
int renderScreen(SDL_Window* pWindow);
int renderTriangle();
void gererMouvement();


/** CODE **/

int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");
    waveProgram = createProgram("./resources/vertShader.v", "./resources/fragWaveShader.f");

    testBackground.loadFile("./resources/testBg.txt", glm::vec2(-512.0f, -384.0f));
    testPerso.initPersonnage("./resources/testPersonnage.txt", glm::vec2(-512.0f, -384.0f));
    testCollision.loadFile("./resources/tile.txt", glm::vec2(-512.0f, -550.0f));

    projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    int curTime = SDL_GetTicks();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.3, 0.3, 0.35, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    testPerso.gererDeplacement(timeLastFrame);

    if(testPerso.isCollision(&testCollision)) testPerso.resoudreCollision(testPerso.getDeplacement(&testCollision));
    testBackground.setPos(testPerso.getPos());

    testBackground.drawImage(waveProgram, totalTime, view, projection);
    testCollision.drawImage(shaderProgram, totalTime, view, projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    testPerso.drawImage(shaderProgram, totalTime, view, projection);
    glDisable(GL_BLEND);

    SDL_GL_SwapWindow(pWindow);

    timeLastFrame = SDL_GetTicks() - curTime;
    totalTime += timeLastFrame;
    std::cout << timeLastFrame << std::endl;

    return 0;
}

void gererMouvement()
{
    if(listeTouches[SDL_SCANCODE_W]) {
        testPerso.setState(2, glm::vec2(0, 1));
    }
    if(listeTouches[SDL_SCANCODE_S]) {
    }
    if(listeTouches[SDL_SCANCODE_A]) {
        testPerso.setState(1, glm::vec2(-1, 0));
    }
    if(listeTouches[SDL_SCANCODE_D]) {
        testPerso.setState(1, glm::vec2(1, 0));
    }
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
                case SDL_KEYUP:
                    listeTouches[events.key.keysym.scancode] = 0;
                    break;
                case SDL_KEYDOWN:
                    listeTouches[events.key.keysym.scancode] = 1;
                    break;
                default:
                    break;
            }
        }

        gererMouvement();
        view = glm::lookAt(glm::vec3(testPerso.getPos().x - 512, testPerso.getPos().y + 384, 0), glm::vec3(testPerso.getPos().x - 512, testPerso.getPos().y + 384, 1), glm::vec3(0, -1, 0));

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
