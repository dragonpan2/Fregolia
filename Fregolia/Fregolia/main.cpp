#include "ExternalIncludes.h"
#include "InitOpenGL.h"
#include "ShaderUtilities.h"
#include "LoadModel.h"
#include "Personnage.h"
#include "Environment.h"
#include "Water.h"
#include "Gravity.h"
#include "PhysicActor.h"
#include "Weapon.h"
#include "SpiderWeb.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram, waterProgram;

imageModel testCollision1, testCollision2, testPorte, testCollision3;
imageModel testSouris;

imageModel testInv;
imageModel* currentSelection = nullptr;





PhysicActor testRoche1, testRoche2;
Environnement testEnv;
Personnage testPerso;
Water testWater;
Enemy testEnemy;
SpiderWeb spiderWeb;

Weapon testWeapon;

std::vector<groundObject*> listeMvt;


glm::mat4 projection, view;
glm::vec2 cameraPos;

glm::vec2 startPos;

int listeTouches[1000] = {0};

int timeLastFrame = 1;
float totalTime = 0.0f;

int timeWeapon = 0;
int timeWeaponUse = 0;
float angleAttaque = -45.0;
int compteurAngle = 1;
int compteurToile = 0;


/** DÉCLARATIONS DE FONCTIONS **/

int initResources();
int renderScreen(SDL_Window* pWindow);

void gererMouvement();
void deplacerSouris(int pX, int pY, int pRelX, int pRelY);

void actualiserCamera();

void gererWeapon();
void collisionToile(int compteurToile);


/** CODE **/


int initResources()
{
    shaderProgram = createProgram("./resources/vertShader.v", "./resources/fragShader.f");
    if(shaderProgram == 999999999) return -1;
    waveProgram = createProgram("./resources/vertShader.v", "./resources/fragWaveShader.f");
    if(waveProgram == 999999999) return -2;
    waterProgram = createProgram("./resources/vertWaterShader.v", "./resources/fragWaterShader.f");
    if(waterProgram == 999999999) return -3;

    testPerso.initPersonnage("./resources/testPersonnage.txt", glm::vec2(0.0f, 0.0f));
    testPerso.createActor(15, 5, 0.01f);

    testWeapon.loadWeapon("./resources/testWeapon.txt", glm::vec2(0.0f, 0.0f));

    spiderWeb.loadFile("./resources/testSpiderWeb.txt", glm::vec2(500.0f, 0.0f));

    testSouris.loadFile("./resources/mouse.txt", glm::vec2(0.0f, 0.0f));

    testInv.loadFile("./resources/invex.txt", glm::vec2(-0.0f, -0.85f));

    testEnemy.loadFile("./resources/testPersonnage2.txt", glm::vec2(500.0f, -200.0f));
    testEnemy.createActor(15, 5,0.05f);

    startPos = testEnv.loadLevel("./resources/level0.txt");

    testPerso.moveImage(startPos);

    cameraPos = glm::vec2(0, 384);

    projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));

    testEnv.setMatrices(view, projection);
    return 0;
}

void freeResources()
{
    for(unsigned int i = 0; i < listeMvt.size(); ++i)
        delete listeMvt[i];

    delete currentSelection;


}

int actualiserLogique()
{
    gererMouvement();
    gererWeapon();


    testEnemy.aiProcess(testPerso.getPos());
    testEnemy.gererDeplacement(timeLastFrame);

    testPerso.gererDeplacement(timeLastFrame);


    testEnv.resoudreCollisionsPerso(&testPerso);
    testEnv.resoudreCollisionsEnnemi(&testEnemy);
    testEnv.resoudreCollisionsObjets();

    testPerso.rebondPerso(timeLastFrame);
 /*   for(std::vector<groundObject*>::iterator v = testEnv.getGroundObject(); v != testEnv.lastGroundObj(); v++)
    {
              if((*v)->canDeplacer == 1)
                {
((PhysicActor*)(*v)->object)->gererDeplacement(timeLastFrame);

                                    }


    }
*/

    for(unsigned int i = 0; i < listeMvt.size(); ++i)
    {

        if(!(((PhysicActor*)listeMvt[i]->object)->enMouvement())) listeMvt.erase(listeMvt.begin() + i);
        else
        {
            ((PhysicActor*)listeMvt[i]->object)->vitesseReduite(timeLastFrame);
            ((PhysicActor*)listeMvt[i]->object)->moveImage(((PhysicActor*)listeMvt[i]->object)->getVitesse());
        }
    }

    for(std::vector<groundObject*>::iterator v = testEnv.getListeCollision(); v != testEnv.lastCollisionObj(); v++)
    {
        if((*v)->canDeplacer == 1)
        {
            if(listeMvt.size() == 0)
            {
                listeMvt.push_back(*v);
                testPerso.pousserObjet((PhysicActor*)(*v)->object);
                continue;
            }

            for(unsigned int i = 0; i < listeMvt.size(); i++)
            {
                if((listeMvt[i]) == (*v)) break;

                if(i == listeMvt.size() - 1)
                {
                    listeMvt.push_back(*v);
                    testPerso.pousserObjet((PhysicActor*)(*v)->object);
                }
            }

        }

        testPerso.setAngle((*v)->object->getAngle());
    }

    if(testPerso.verifierMort()) testPerso.reset(startPos);

    actualiserCamera();

    if (testWeapon.siBeingUsed() && testWeapon.isCollision(&testEnemy))
    {
        testWeapon.setBeingUsed(false);
        testEnemy.ennemiTouche(10);
        if (testEnemy.isMortEnnemi())
        {
            /// ENNEMI TUE
        }
    }

    /*collisionToile(compteurToile);

    if (testPerso.siImmobile())
    {
        compteurToile++;
    }*/

    testWeapon.moveImage(glm::vec2((testPerso.getPos() - testWeapon.getPos()).x + 40, (testPerso.getPos() - testWeapon.getPos()).y + 20));


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

    if(testWeapon.siEquipped()) testWeapon.drawImage(shaderProgram, totalTime, view, projection);

    testEnemy.drawImage(shaderProgram, totalTime, view, projection);
    //spiderWeb.drawImage(shaderProgram, totalTime, view, projection);

    testEnv.drawWater(waterProgram, timeLastFrame);
    testEnv.drawForeground(shaderProgram, totalTime);

    glDisable(GL_BLEND);

    testInv.drawImage(shaderProgram, totalTime, glm::mat4(1.0f), glm::mat4(1.0f));

    SDL_GL_SwapWindow(pWindow);

    std::cout << timeLastFrame << std::endl;

    return 0;
}



void gererWeapon()
{
    if(listeTouches[SDL_SCANCODE_F] && timeWeaponUse == 0)
    {
        angleAttaque = -45.0;
        compteurAngle = 0;
        timeWeaponUse++;
        testWeapon.setBeingUsed(true);
        testWeapon.setAngle(angleAttaque);
    }

    if(listeTouches[SDL_SCANCODE_TAB] && timeWeapon == 0)
    {
        timeWeapon++;
        if(testWeapon.siEquipped())
        {
            testWeapon.setEquipped(false);
        }
        else
        {
            testWeapon.setEquipped(true);
        }
    }

    if(timeWeaponUse >= 1)
    {
        timeWeaponUse++;
        testWeapon.setAngle(angleAttaque+compteurAngle);
        compteurAngle++;
    }
    if (timeWeaponUse > 45)
    {
        timeWeaponUse = 0;
        testWeapon.setBeingUsed(false);
    }

    if (timeWeapon > 50) timeWeapon = 0;
    else if(timeWeapon >= 1) timeWeapon++;
}



void collisionToile(int compteurToile)
{

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
    if(listeTouches[SDL_SCANCODE_E])
    {
        testEnv.splash();
        listeTouches[SDL_SCANCODE_E] = 0;
    }
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

    if(abs(distance) > 150)
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

    if(initOpenGL(&mainWindow, &mainContext) != 0)
    {
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

    freeResources();
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
