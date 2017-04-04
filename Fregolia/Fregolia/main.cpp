#include "externalIncludes.h"
#include "initOpenGL.h"
#include "shaderUtilities.h"
#include "loadModel.h"
#include "personnage.h"
#include "environment.h"
#include "Water.h"
#include "Gravity.h"
#include "PhysicActor.h"
#include "Weapon.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram, waterProgram;

imageModel testCollision1, testCollision2, testPorte, testCollision3;
imageModel testSouris;

imageModel testInv;
imageModel testEnemy;
imageModel* currentSelection = nullptr;





PhysicActor testRoche1, testRoche2;
Environnement testEnv;
Personnage testPerso;
Water testWater;
Enemy enemy;

//Weapon testWeapon;
//Inventory testInventory;
//Enemy testEnemy;

//Gravity testGrav;

glm::mat4 projection, view;
glm::vec2 cameraPos;

glm::vec2 startPos;

int listeTouches[1000] = {0};

int timeLastFrame = 1;
float totalTime = 0.0f;

/** DÉCLARATIONS DE FONCTIONS **/

void gererWeapon();
int initResources();
int renderScreen(SDL_Window* pWindow);
int renderTriangle();
void gererMouvement();
void deplacerSouris(int pX, int pY, int pRelX, int pRelY);
void actualiserCamera();


/** CODE **/

/*void gererWeapon()
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
}*/

int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");
    waveProgram = createProgram("./resources/vertShader.v", "./resources/fragWaveShader.f");
    waterProgram = createProgram("./resources/vertWaterShader.v", "./resources/fragWaterShader.f");

    testPerso.initPersonnage("./resources/testPersonnage.txt", glm::vec2(0.0f, 0.0f));
    testPerso.createActor(5, 5, false);

    testSouris.loadFile("./resources/mouse.txt", glm::vec2(0.0f, 0.0f));
    //
    testInv.loadFile("./resources/invex.txt", glm::vec2(500.0f, -325.0f));
    //
    testEnemy.loadFile("./resources/testPersonnage2.txt", glm::vec2(500.0f, -200.0f));

    startPos = testEnv.loadLevel("./resources/level0.txt");

    testPerso.moveImage(startPos);

    cameraPos = glm::vec2(0, 384);

    projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));

    testEnv.setMatrices(view, projection);

    return 0;
}

int actualiserLogique()
{
    gererMouvement();

    //
    testEnemy.moveImage(enemy.aiProcess(testPerso.getPos()));
    std::cout << "Player Position" << std::endl;
    std::cout << testPerso.getPos().x << std::endl;

    testPerso.modifierVitesse(0);
    testPerso.gererDeplacement(timeLastFrame);
    actualiserCamera();

    testEnv.resoudreCollisions(&testPerso);
    for(std::vector<groundObject*>::iterator v = testEnv.getListeCollision(); v != testEnv.lastCollisionObj(); v++)
    {
        std::cout << (*v)->object->getId() << std::endl;
    }

    if(testPerso.verifierMort()) testPerso.reset(startPos);

    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);



    testEnv.drawSky(waveProgram, totalTime);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    testEnv.drawBackground(shaderProgram, totalTime);
    testEnv.drawGround(shaderProgram, totalTime);

    testPerso.drawImage(shaderProgram, totalTime, view, projection);

    testEnv.drawWater(waterProgram, timeLastFrame);
    testEnv.drawForeground(shaderProgram, totalTime);

    glDisable(GL_BLEND);

    //
    testInv.drawImage(shaderProgram, totalTime, view, projection);
    //
    testEnemy.drawImage(shaderProgram,totalTime, view, projection);


    SDL_GL_SwapWindow(pWindow);

    //std::cout << timeLastFrame << std::endl;

    return 0;
}

void gererMouvement()
{
    if(listeTouches[SDL_SCANCODE_SPACE]) {
        testPerso.setState(2, glm::vec2(0, 1));
        //testPerso.modifierVitesse(2);
    }
    if(listeTouches[SDL_SCANCODE_S]) {
    }
    if(listeTouches[SDL_SCANCODE_A]) {
        testPerso.setState(1, glm::vec2(-1, 0));
        //testPerso.modifierVitesse(1);
    }
    if(listeTouches[SDL_SCANCODE_D]) {
        testPerso.setState(1, glm::vec2(1, 0));
        //testPerso.modifierVitesse(1);
    }
    if(listeTouches[SDL_SCANCODE_E]) {
        testEnv.splash();
        listeTouches[SDL_SCANCODE_E] = 0;
    }

    //testPerso.modifierVitesse(0);
}

void deplacerSouris(int pX, int pY, int pRelX, int pRelY)
{
    /// Corrections car SDL = 0 - 1024; OGL = -512 - 512.
    testSouris.setPos(glm::vec2(pX + cameraPos.x, 384 - pY));

    if(currentSelection != nullptr)
        currentSelection->moveImage(glm::vec2(pRelX, -pRelY));
}

void actualiserCamera()
{
    float distance = testPerso.getPos().x - (cameraPos.x + 512);

    if(abs(distance) > 350)
    {
        if((cameraPos.x > testEnv.getLength().x + 10 && signe(distance) == -1) || (cameraPos.x < testEnv.getLength().y - 10 && signe(distance) == 1))
        {
            cameraPos.x += 12 * signe(distance);
            if(currentSelection != nullptr) currentSelection->moveImage(glm::vec2(12 * signe(distance), 0));
            view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));
            testEnv.setMatrices(view, projection);
        }
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* mainWindow;
    SDL_GLContext mainContext;
    bool loopEnd = false;
    SDL_Event events;

    if(initOpenGL(&mainWindow, &mainContext) != 0) {
        std::cout << "Impossible d'initaliser OpenGL!" << std::endl;
        return -3;
    }

    if(initResources())
    {
        std::cout << "Problème d'initalisation des ressources!" << std::endl;
        SDL_GL_DeleteContext(mainContext);
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -4;
    }

    glDisable(GL_CULL_FACE);

    while(!loopEnd)
    {
        int curTime = SDL_GetTicks();

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
                case SDL_MOUSEMOTION:
                    deplacerSouris(events.motion.x, events.motion.y, events.motion.xrel, events.motion.yrel);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(events.button.button == SDL_BUTTON_LEFT)
                    {
                        currentSelection = testEnv.getClickRef(&testSouris);
                    }
                    else if(events.button.button == SDL_BUTTON_RIGHT && currentSelection != nullptr)
                    {
                        std::cout << "Position: " << currentSelection->getPos().x << " " << currentSelection->getPos().y << "; Angle: " << currentSelection->getAngle() << std::endl;
                        currentSelection = nullptr;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_MOUSEWHEEL:
                        if(currentSelection != nullptr)
                        {
                            currentSelection->setAngle(currentSelection->getAngle() + 1 * signe(events.wheel.y));
                        }
                    break;
                default:
                    break;
            }
        }

        actualiserLogique();

        if(renderScreen(mainWindow))
        {
            SDL_GL_DeleteContext(mainContext);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
            return -5;
        }

        if(timeLastFrame < 1000 / 60) SDL_Delay(1000 / 60 - timeLastFrame);
        timeLastFrame = SDL_GetTicks() - curTime;
        totalTime += timeLastFrame;
    }

    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
