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
#include "TextManager.h"

using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram, waterProgram, textProgram;

imageModel testCollision1, testCollision2, testPorte, testCollision3;
imageModel testSouris;

imageModel testInv;
imageModel* currentSelection = nullptr;
imageModel healthModel;
imageModel healthBarModel;
imageModel arcOne;
imageModel swordOne;


PhysicActor testRoche1, testRoche2;
Environnement testEnv;
Personnage testPerso;
Water testWater;
Enemy testEnemy;
SpiderWeb spiderWeb;
TextLine testLigne;

Weapon testWeapon;

glm::mat4 projection, view;
glm::vec2 cameraPos;

glm::vec2 startPos;

int listeTouches[1000] = {0};

int timeLastFrame = 1;
float totalTime = 0.0f;
float healthBarScale;

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
    textProgram = createProgram("./resources/vertTextShader.v", "./resources/fragTextShader.f");
    if(waterProgram == 999999999) return -4;

    testPerso.initPersonnage("./resources/persoPrincipal.txt", glm::vec2(0.0f, 0.0f));
    testPerso.createActor(15, 5, 0.01f, 0.02f);

    testWeapon.loadWeapon("./resources/testWeapon.txt", glm::vec2(0.0f, 0.0f));

    spiderWeb.loadFile("./resources/testSpiderWeb.txt", glm::vec2(500.0f, 0.0f));

    testSouris.loadFile("./resources/mouse.txt", glm::vec2(0.0f, 0.0f));

    testInv.loadFile("./resources/invex.txt", glm::vec2(-0.0f, -0.85f));

    testEnemy.loadFile("./resources/testPersonnage2.txt", glm::vec2(500.0f, -200.0f));
    testEnemy.createActor(15, 5,0.05f,0);
    healthModel.loadFile("./resources/health.txt", glm::vec2(0.0f,0.0f));
    healthBarModel.loadFile("./resources/healthBar.txt", glm::vec2(0.0f,0.0f));
    arcOne.loadFile("./resources/arcOne.txt", glm::vec2(-0.15f,-0.85f));
    swordOne.loadFile("./resources/swordOne.txt", glm::vec2(-0.45f,-0.85f));

    testLigne.loadFont("./resources/Anke.ttf", 24);
    testLigne.setText("Je suis une patate.");
    testLigne.setLocation(glm::vec2(-0.9, 0.7));

    startPos = testEnv.loadLevel("./resources/level0.txt");

    testPerso.moveImage(startPos);

    cameraPos = glm::vec2(0, 384);

    projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));

    testEnv.setMatrices(view, projection);
    return 0;
}
/*
void freeResources()
{
    delete currentSelection;
}
*/
int actualiserLogique()
{
    gererMouvement();
    gererWeapon();
    healthBarScale = (float)testPerso.getHealth()/(float)testPerso.getMaxHealth();

    healthModel.setTaille(glm::vec2(healthBarScale, 1.0f));


    if(testEnemy.aiProcess(testPerso.getPos()) == 5) {
        testPerso.setHealth(testPerso.getHealth()-1);
    }
    testEnemy.gererDeplacement(timeLastFrame);

    testPerso.gererDeplacement(timeLastFrame);

    testEnv.appliquerGraviterEnvironnement(timeLastFrame);

    testEnv.resoudreCollisionsPerso(&testPerso);
    testEnv.resoudreCollisionsEnnemi(&testEnemy);
    testEnv.resoudreCollisionsObjets();

    testPerso.rebondPerso();

    for(std::vector<groundObject*>::iterator v = testEnv.getListeMvt(); v != testEnv.lastMvtObj(); v++)
    {

        if(!(((PhysicActor*)(*v)->object)->enMouvement())) testEnv.removeMvtObject(v - testEnv.getListeMvt());
        else
        {
            ((PhysicActor*)(*v)->object)->vitesseReduite(timeLastFrame);
            ((PhysicActor*)(*v)->object)->moveImage(((PhysicActor*)(*v)->object)->getVitesse());
        }
    }

    for(std::vector<groundObject*>::iterator v = testEnv.getListeCollision(); v != testEnv.lastCollisionObj(); v++)
    {
        if((*v)->canDeplacer == 1)
        {
            if(testEnv.lastMvtObj() - testEnv.getListeMvt() == 0)
            {
                testEnv.addMvtObject(*v);
                testPerso.pousserObjet((PhysicActor*)(*v)->object);
                continue;
            }

            for(std::vector<groundObject*>::iterator w = testEnv.getListeMvt(); w != testEnv.lastMvtObj(); w++)
            {
                if((*w) == (*v)) break;
                if(w - testEnv.getListeMvt() == (testEnv.lastMvtObj() - testEnv.getListeMvt()) - 1)
                {
                    testEnv.addMvtObject(*v);
                    testPerso.pousserObjet((PhysicActor*)(*v)->object);
                }
            }

        }

        if(testPerso.mCollisionSol)
        {
            testPerso.setAngle((*v)->object->getAngle());
        }
    }

    for(std::vector<groundObject*>::iterator v = testEnv.getListeMvt(); v < testEnv.lastMvtObj(); v++)
    {
        if(!(((PhysicActor*)(*v)->object)->enMouvement()))
        {
            testEnv.removeMvtObject(v - testEnv.getListeMvt());
        }
        else
        {



            ((PhysicActor*)(*v)->object)->vitesseReduite(timeLastFrame);
            ((PhysicActor*)(*v)->object)->moveImage(((PhysicActor*)(*v)->object)->getVitesse());

           // ((PhysicActor*)(*v)->object)->rebondPerso();

        }

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

    testPerso.boucleAnimations();

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
    spiderWeb.drawImage(shaderProgram, totalTime, view, projection);


    testEnv.drawWater(waterProgram, timeLastFrame);
    testEnv.drawForeground(shaderProgram, totalTime);

    healthModel.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));
    healthBarModel.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));

    testInv.drawImage(shaderProgram, totalTime, glm::mat4(1.0f), glm::mat4(1.0f));
    arcOne.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));
    swordOne.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));

    testLigne.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));

    glDisable(GL_BLEND);

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
             if(!testPerso.mCollisionCoter){
   testPerso.setState(2, glm::vec2(0, 1));
             }
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

        if(testPerso.mCollisionCoter)testPerso.mCollisionCoter=false;
        else if(!testPerso.mCollisionCoter) testPerso.mCollisionCoter=true;

      /*  testEnv.splash();
        listeTouches[SDL_SCANCODE_E] = 0;*/
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

    //freeResources();
    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}
