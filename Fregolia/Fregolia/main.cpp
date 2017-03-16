#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"
#include "loadModel.h"
#include "personnage.h"
#include "environment.h"
#include "Weapon.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram;

imageModel testSky, testBackground, testForeground, testCollision1, testCollision2, testPorte;
Environnement testEnv;
Personnage testPerso;
Weapon testWeapon;
Inventory testInventory;
Enemy testEnemy;

glm::mat4 projection, view;
glm::vec3 cameraPos, cameraTarget;

int listeTouches[1000] = {0};

int timeLastFrame;
float totalTime = 0.0f;

/** DÉCLARATIONS DE FONCTIONS **/

void gererWeapon();
int initResources();
int renderScreen(SDL_Window* pWindow);
int renderTriangle();
void gererMouvement();


/** CODE **/

void gererWeapon()
{
    if(listeTouches[SDL_SCANCODE_TAB])
    {
        if(testWeapon.siEquipped())
        {
            testWeapon.unequipWeapon(testWeapon, testInventory);
        }
        else
        {
            testWeapon.equipWeapon(testWeapon, testInventory);
        }
    }

    if(listeTouches[SDL_SCANCODE_F])
    {
        testWeapon.use(testEnemy);
    }
}

int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");
    waveProgram = createProgram("./resources/vertShader.v", "./resources/fragWaveShader.f");

    testPorte.loadFile("./resources/Porte.txt", glm::vec2(450.0f, 0.0f));
    testSky.loadFile("./resources/Sky.txt", glm::vec2(0.0f, 0.0f));
    testBackground.loadFile("./resources/Background.txt", glm::vec2(0.0f, 0.0f));
    testForeground.loadFile("./resources/Foreground.txt", glm::vec2(0.0f, 0.0f));
    testPerso.initPersonnage("./resources/testPersonnage.txt", glm::vec2(-400.0f, 0.0f));
    testCollision1.loadFile("./resources/tile.txt", glm::vec2(-450.0f, -180.0f));
    testCollision2.loadFile("./resources/tile2.txt", glm::vec2(300.0f, -230.0f));

    testEnv.setSky(&testSky);
    testEnv.setBackground(&testBackground);
    testEnv.addObject(&testCollision1);
    testEnv.addObject(&testCollision2);
    testEnv.setForeground(&testForeground);


    projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
    testEnv.setMatrices(view, projection);

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    int curTime = SDL_GetTicks();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.3, 0.3, 0.35, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    testPerso.gererDeplacement(timeLastFrame);
    for(int i = 0; i < 50; ++i)
    {
        testPerso.isCollision(&testCollision1);
        testPerso.isCollision(&testCollision2);
        testPerso.getDeplacement(&testCollision1);
        testPerso.getDeplacement(&testCollision2);
        testPerso.resoudreCollision(glm::vec2(0, 0));
        testPerso.resoudreCollision(glm::vec2(0, 0));
    }
    if(testPerso.isCollision(&testCollision1)) testPerso.resoudreCollision(testPerso.getDeplacement(&testCollision1));
    if(testPerso.isCollision(&testCollision2)) testPerso.resoudreCollision(testPerso.getDeplacement(&testCollision2));
    if(testPerso.isCollision(&testPorte)) std::cout << "Changement de piece!" << std::endl;
    if(testPerso.verifierMort()) testPerso.reset(glm::vec2(-400.0f, 0.0f));

    testEnv.drawSky(waveProgram, totalTime);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    testEnv.drawBackground(shaderProgram, totalTime);
    testEnv.drawGround(shaderProgram, totalTime);

    testPerso.drawImage(shaderProgram, totalTime, view, projection);


    testEnv.drawForeground(shaderProgram, totalTime);
    glDisable(GL_BLEND);

    SDL_GL_SwapWindow(pWindow);

    timeLastFrame = SDL_GetTicks() - curTime;
    totalTime += timeLastFrame;
    //std::cout << timeLastFrame << std::endl;

    return 0;
}

void gererMouvement()
{
    if(listeTouches[SDL_SCANCODE_SPACE])
    {
        testPerso.setState(2, glm::vec2(0, 1));
    }
    if(listeTouches[SDL_SCANCODE_S])
    {
    }
    if(listeTouches[SDL_SCANCODE_A])
    {
        testPerso.setState(1, glm::vec2(-1, 0));
    }
    if(listeTouches[SDL_SCANCODE_D])
    {
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
        view = glm::lookAt(glm::vec3(-512, 300, 0), glm::vec3(-512, 300, 1), glm::vec3(0, -1, 0));
        testEnv.setMatrices(view, projection);


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
