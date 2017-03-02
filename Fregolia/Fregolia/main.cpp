#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"
#include "loadModel.h"
#include "personnage.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram;

imageModel /*testImage,*/ testBackground;
imageModel testCollision;
Personnage testPerso;

glm::mat4 projection, view;
glm::vec3 cameraPos, cameraTarget;

int listeTouches[sizeof(SDL_Scancode)] = {0};

int timeLastFrame;

/** DÉCLARATIONS DE FONCTIONS **/

int initResources();
int renderScreen(SDL_Window* pWindow);
int renderTriangle();
void gererMouvement();


/** CODE **/

int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");

    //testImage.loadFile("./resources/testImage.txt", glm::vec2(-400.0f, -300.0f));
    testBackground.loadFile("./resources/testBg.txt", glm::vec2(-400.0f, -300.0f));
    testPerso.initPersonnage("./resources/testPersonnage.txt", glm::vec2(-400.0f, -300.0f));
    testCollision.loadFile("./resources/tile.txt", glm::vec2(-400.0f, -300.0f));

    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0,-1,0));

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    int curTime = SDL_GetTicks();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.3, 0.3, 0.35, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    testBackground.drawImage(shaderProgram, view, projection);
    testCollision.drawImage(shaderProgram, view, projection);
    //testImage.drawImage(shaderProgram, view, projection);
    testPerso.drawImage(shaderProgram, view, projection);

    SDL_GL_SwapWindow(pWindow);

    timeLastFrame = SDL_GetTicks() - curTime;
    std::cout << timeLastFrame << std::endl;

    return 0;
}

void gererMouvement()
{
    if(listeTouches[SDL_SCANCODE_W]) {
        //testImage.moveImage(glm::vec2(0, 1));
        testPerso.gererDeplacements(timeLastFrame, glm::vec2(0, 1));
    }
    if(listeTouches[SDL_SCANCODE_S]) {
        //testImage.moveImage(glm::vec2(0, -1));
        testPerso.gererDeplacements(timeLastFrame, glm::vec2(0, -1));
    }
    if(listeTouches[SDL_SCANCODE_A]) {
        //testImage.moveImage(glm::vec2(1, 0));
        testPerso.gererDeplacements(timeLastFrame, glm::vec2(1, 0));
    }
    if(listeTouches[SDL_SCANCODE_D]) {
        //testImage.moveImage(glm::vec2(-1, 0));
        testPerso.gererDeplacements(timeLastFrame, glm::vec2(-1, 0));
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
            /*const Uint8 *keystate = SDL_GetKeyboardState(NULL);
            if(keystate[SDL_SCANCODE_W]) {
                testImage.moveImage(glm::vec2(0, 1));
            }
            if(keystate[SDL_SCANCODE_S]) {
                testImage.moveImage(glm::vec2(0, -1));
            }
            if(keystate[SDL_SCANCODE_A]) {
                testImage.moveImage(glm::vec2(1, 0));
            }
            if(keystate[SDL_SCANCODE_D]) {
                testImage.moveImage(glm::vec2(-1, 0));
            }*/
        }

        gererMouvement();

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
