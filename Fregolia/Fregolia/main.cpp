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
#include "RangedWeapon.h"
#include "Arrow.h"
#include "HealthBar.h"


using namespace std;

/** VARIABLES GLOBALES **/

GLuint shaderProgram, waveProgram, waterProgram, textProgram;

imageModel testCollision1, testCollision2, testPorte, testCollision3;
imageModel testSouris;

imageModel testInv;
imageModel* currentSelection = nullptr;
imageModel arcOne;
imageModel swordOne;
imageModel selection;

Environnement* testEnv;
Personnage testPerso;

///
TextLine testLigne;
TextLine ligne1;
TextLine textMenuPTitre;
TextLine textMenuPPlay;
TextLine textMenuPCredit;
TextLine textMenuPHelp;
TextLine textMenuHHelp;
TextLine textMenuCCredit;
TextLine textMenuCnoms;
TextLine textMenuCretour;
TextLine textMenuHretour;


///text menue C for credit, h for help, p for princiaple


HealthBar HPPerso;

Weapon testWeapon;
RangedWeapon testBow;
Arrow testArrow;

glm::mat4 projection, view;
glm::vec2 cameraPos;

glm::vec2 startPos;

int listeTouches[1000] = {0};

int timeLastFrame = 1;
float totalTime = 0.0f;
float healthBarScale;

int timeWeapon = 0;
int timeWeaponUse = 0;
int timeBowUse = 0;
int compteurAngle = 1;
int slotSelected = 0;
float angleAttaque = -45.0;

bool weaponSelected = false;
bool slot3Selected = false;
bool slot4Selected = false;

/** DÉCLARATIONS DE FONCTIONS **/

int initResources();
int renderScreen(SDL_Window* pWindow);

void gererMouvement();
void deplacerSouris(int pX, int pY, int pRelX, int pRelY);

void actualiserCamera();

void gererWeapon();


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

    testBow.loadWeapon("./resources/testBow.txt", glm::vec2(0.0f, 0.0f));

    testArrow.loadFile("./resources/testArrow.txt", glm::vec2(0.0f, 0.0f));

    testSouris.loadFile("./resources/mouse.txt", glm::vec2(0.0f, 0.0f));

    testInv.loadFile("./resources/invex.txt", glm::vec2(-0.0f, -0.85f));

    HPPerso.loadBar();

    arcOne.loadFile("./resources/arcOne.txt", glm::vec2(-0.15f,-0.85f));
    swordOne.loadFile("./resources/swordOne.txt", glm::vec2(-0.45f,-0.85f));
    selection.loadFile("./resources/selection.txt", glm::vec2(-0.45f,-0.85f));

    testLigne.loadFont("./resources/Anke.ttf", 24);
    testLigne.setText("Je suis une patate.");
    testLigne.setLocation(glm::vec2(-0.9, 0.7));


    ligne1.loadFont("./resources/Anke.ttf", 34);
    ligne1.setText("Fregolia");
    ligne1.setLocation(glm::vec2(-0.9, 0.9));

    textMenuPTitre.manage(54, "Fregolia", glm::vec2(-0.9,0.7));
    textMenuPPlay.manage(34, "Jeu", glm::vec2(0.3,0.3));
    textMenuPCredit.manage(34, "Credit", glm::vec2(-0.9,0.2));
    textMenuPHelp.manage(34, "Aide", glm::vec2(-0.9,0.2));

    textMenuCCredit.manage(44, "Aide", glm::vec2(0.0,0.0));
    textMenuCnoms.manage(34, "Ahmad Faour   Bei Ning Pan    Hadrien Renault    Simon G-Roze ", glm::vec2(0.0,0.3));
    textMenuCretour.manage(34, "Retour", glm::vec2(0.0,0.9));

    textMenuHHelp.manage(34, "Aide", glm::vec2(0.0, 0.0));
    textMenuHretour.manage(44, "Retour", glm::vec2(0.0,0.0));


    testEnv = new Environnement;
    startPos = testEnv->loadLevel("./resources/level0.txt");
    //startPos = testEnv->loadLevel("./resources/level1.txt");

    testPerso.moveImage(startPos);

    cameraPos = glm::vec2(0, 384);

    projection = glm::ortho(0.0f, (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT, 0.0f, 1.0f, 1000.0f);
    view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));

    testEnv->setMatrices(view, projection);
    return 0;
}


void freeResources()
{
    if(currentSelection != nullptr) delete currentSelection;
}


int actualiserLogique()
{
    /// GESTION DE L'INPUT DU JOUEUR
    gererMouvement();
    gererWeapon();

    /// VERIFICATIONS DE FIN DE PARTIE OU DE CHANGEMENTS
    if(testPerso.verifierMort()) testPerso.reset(startPos);
    void* newPos = testEnv->resoudreCollisionPorte(&testPerso);
    if(newPos != nullptr)
    {
        std:;string id = testEnv->getId();
        delete testEnv;
        std::cout << "LOL " << ((std::string)"./resources/level" + id + (std::string)".txt") << std::endl;
        testEnv = new Environnement;
        std::cout << "LOL " << std::endl;
        startPos = testEnv->loadLevel((std::string)"./resources/level" + id + (std::string)".txt");
        std::cout << "LOL " << std::endl;
        testPerso.moveImage(startPos);
        return 0;
    }

    /// MAJ LISTES ET ACTIONS
    testEnv->updateListeMvt();
    testEnv->updateInteractifs(&testPerso, timeLastFrame);

    /// MAJ DES DEPLACEMENTS
    testEnv->appliquerGravite(timeLastFrame);
    testEnv->updateDeplacements(timeLastFrame);
    testPerso.gererDeplacement(timeLastFrame);
    //testPerso.rebondPerso();

    /// MAJ DES COLLISIONS
    testEnv->resoudreCollisionsInteractifs();
    testEnv->resoudreCollisionsObjets();
    testEnv->resoudreCollisionsPerso(&testPerso);
    if(testWeapon.siBeingUsed()) testEnv->resoudreCollisionsArme(&testWeapon);
    else if(testBow.siBeingUsed()) testEnv->resoudreCollisionsArme(&testArrow);

    /// MAJ ANIMATIONS
    testPerso.boucleAnimations();
    testEnv->updateAnimations();

    /// MAJ ARMES
    testWeapon.moveImage(glm::vec2((testPerso.getPos() - testWeapon.getPos()).x + 40, (testPerso.getPos() - testWeapon.getPos()).y + 20));
    testBow.moveImage(glm::vec2((testPerso.getPos() - testBow.getPos()).x + 40, (testPerso.getPos() - testBow.getPos()).y + 20));
    testArrow.moveImage(glm::vec2((testPerso.getPos() - testArrow.getPos()).x + 50, (testPerso.getPos() - testArrow.getPos()).y + 20));

    /// MAJ CAMERA
    actualiserCamera();

    /// MAJ INTERFACE
    HPPerso.updateHealth((float)testPerso.getHealth() / (float)testPerso.getMaxHealth());



    return 0;
}

int renderScreen(SDL_Window* pWindow)
{
    /// SETUP DE L'ECRAN
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /// AFFICHAGE DU CIEL
    testEnv->drawSky(waveProgram, totalTime);

    /// BLENDING
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /// AFFICHAGE DU BACKGROUND
    testEnv->drawBackground(shaderProgram, totalTime);
    testEnv->drawGround(shaderProgram, totalTime);

    /// AFFICHAGE DU PERSONNAGE
    testPerso.drawImage(shaderProgram, totalTime, view, projection);

    /// AFFICHAGE DES ARMES
    if(testWeapon.siEquipped()) testWeapon.drawImage(shaderProgram, totalTime, view, projection);
    else if(testBow.siEquipped()) {
        testBow.drawImage(shaderProgram, totalTime, view, projection);
        testArrow.drawImage(shaderProgram, totalTime, view, projection);
    }


    /// AFFICHAGE DU FOREGROUND
    testEnv->drawWater(waterProgram, timeLastFrame);
    testEnv->drawForeground(shaderProgram, totalTime);

    /// AFFICHAGE DE L'INTERFACE
    HPPerso.drawBar(shaderProgram, totalTime);

    testInv.drawImage(shaderProgram, totalTime, glm::mat4(1.0f), glm::mat4(1.0f));
    arcOne.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));
    swordOne.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));
    if (weaponSelected == true) selection.drawImage(shaderProgram,totalTime, glm::mat4(1.0f),glm::mat4(1.0f));

    /// AFFICHAGE DU TEXTE
    testLigne.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
    ligne1.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));

    ///
    //menuPrincipale();

    /// FIN DU SETUP
    glDisable(GL_BLEND);

    SDL_GL_SwapWindow(pWindow);

    return 0;
}


void gererWeapon()
{
    if(listeTouches[SDL_SCANCODE_F] && timeWeaponUse == 0)
    {
        cout << "Attacked" << endl;
        angleAttaque = -45.0;
        compteurAngle = 0;
        timeWeaponUse++;
        testWeapon.setBeingUsed(true);
        testWeapon.setAngle(angleAttaque);
    }

    if(listeTouches[SDL_SCANCODE_1] && timeWeapon == 0 /*&& testBow.siEquipped() == false && !slot3Selected && !slot4Selected*/)
    {
        if (slotSelected != 1) {
            slotSelected = 1;
            weaponSelected = true;

        }
        else {
            weaponSelected = false;
        }
       // weaponSelected = weaponSelected ^ 1;
      // weaponSelected = true;
         selection.setPos(glm::vec2(-0.45f,-0.85f));
        timeWeapon++;
        testBow.setEquipped(false);
        testWeapon.setEquipped(testWeapon.siEquipped() ^ 1);
        //listeTouches[SDL_SCANCODE_1] = 0;
    }

    if(listeTouches[SDL_SCANCODE_2] && timeWeapon == 0  /*&& testWeapon.siEquipped() == false && !slot3Selected && !slot4Selected*/)
    {
        if (slotSelected != 2) {
            slotSelected = 2;
            weaponSelected = true;

        }
        else {
            weaponSelected = false;
        }
       // weaponSelected = weaponSelected ^ 1;
     //  weaponSelected = true;
         selection.setPos(glm::vec2(-0.15f,-0.85f));
        timeWeapon++;
        testWeapon.setEquipped(false);
        testBow.setEquipped(testBow.siEquipped() ^ 1);
        //listeTouches[SDL_SCANCODE_1] = 0;
    }

    if(listeTouches[SDL_SCANCODE_3] && timeWeapon == 0 /*&& testWeapon.siEquipped() == false && testBow.siEquipped() == false && slot4Selected == false*/)
    {
        if (slotSelected != 3) {
            slotSelected = 3;
            weaponSelected = true;

        }
        else {
            weaponSelected = false;
        }
            testBow.setEquipped(false);
            testWeapon.setEquipped(false);
            selection.setPos(glm::vec2(0.15f,-0.85f));
            slot3Selected = slot3Selected ^ 1;
            timeWeapon++;
    }

    if(listeTouches[SDL_SCANCODE_4] && timeWeapon == 0/* && testWeapon.siEquipped() == false && testBow.siEquipped() == false && slot3Selected == false*/)
    {
        if (slotSelected != 4) {
            slotSelected = 4;
            weaponSelected = true;

        }
        else {
            weaponSelected = false;
        }
            testBow.setEquipped(false);
            testWeapon.setEquipped(false);
            selection.setPos(glm::vec2(0.45f,-0.85f));
            slot4Selected = slot4Selected ^ 1;
            timeWeapon++;
    }

    if(listeTouches[SDL_SCANCODE_G] && timeBowUse == 0)
    {
        timeBowUse++;
        testBow.setBeingUsed(true);
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

    if(timeBowUse >= 1)
    {
        timeWeaponUse++;
    }
    if (timeBowUse > 45)
    {
        timeBowUse = 0;
        testBow.setBeingUsed(false);
    }

    if (timeWeapon > 50) timeWeapon = 0;
    else if(timeWeapon >= 1) timeWeapon++;
}



void gererMouvement()
{
    if (testPerso.siImmobile() == false)
    {
        if(listeTouches[SDL_SCANCODE_SPACE])
        {
            if(!testPerso.mCollisionCoter)
            {
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
        }
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
        if((cameraPos.x > testEnv->getLength().x + 10 && signe(distance) == -1) || (cameraPos.x < testEnv->getLength().y - 10 && signe(distance) == 1))
        {
            cameraPos.x += 12 * signe(distance);
            if(currentSelection != nullptr) currentSelection->moveImage(glm::vec2(12 * signe(distance), 0));
            view = glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 0), glm::vec3(cameraPos.x, cameraPos.y, 1), glm::vec3(0, -1, 0));
            testEnv->setMatrices(view, projection);
        }
    }
}

void menuManage(int indicationMenu) {

    switch(indicationMenu) {
case 0:
    break;
case 1:
    menuPrincipale();
    break;
case 2:
    menuCredit();
    break;
case 3:
    menuAide();
    break;
    }

}

void menuPrincipale() {

        textMenuPTitre.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
        textMenuPPlay.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
        textMenuPCredit.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
        textMenuPHelp.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));


}

void menuCredit() {
    textMenuCCredit.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
    textMenuCnoms.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
    textMenuCretour.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));


}

void menuAide() {
    textMenuHHelp.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));
    textMenuHretour.drawText(textProgram, totalTime, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::mat4(1.0f), glm::mat4(1.0f));


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
        //SDL_Delay(100);
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
                if(events.button.button == SDL_BUTTON_LEFT) currentSelection = testEnv->getClickRef(&testSouris);
                else if(events.button.button == SDL_BUTTON_RIGHT && currentSelection != nullptr)
                {
                    std::cout << "Position: " << currentSelection->getPos().x << " " << currentSelection->getPos().y << "; Angle: " << currentSelection->getAngle() << std::endl;
                    currentSelection = nullptr;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_MOUSEWHEEL:
                //spiderWeb.changerAngle(&testPerso, signe(events.wheel.y));

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



