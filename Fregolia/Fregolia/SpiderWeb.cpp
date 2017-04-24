#include "SpiderWeb.h"

SpiderWeb::SpiderWeb()
{
    //ctor
}

SpiderWeb::~SpiderWeb()
{
    //dtor
}

void SpiderWeb::processusToile(Personnage* pPerso)
{
    if(mCollision) {
        if (finToile == false)
            pPerso->setImmobile(true);
        else
            pPerso->setImmobile(false);

        if (finToile) compteurToile++;
        else compteurLancee++;

        if(compteurLancee > 50)
        {
            mCollision = false;
            compteurLancee = 0;
            lancerPerso(pPerso);
        }

        if (compteurToile > 200){
            finToile = false;
            compteurToile = 0;
        }
    }
}

void SpiderWeb::changerAngle(Personnage* pPerso, int pDir)
{
    if(pPerso->siImmobile() && abs(pPerso->getAngle()) < 75)
        pPerso->setAngle(pPerso->getAngle() + 1 * pDir);
}

void SpiderWeb::collisionToile()
{
    mCollision = true;
}

void SpiderWeb::lancerPerso(Personnage* pPerso)
{
    if(pPerso->siImmobile()){
        finToile = true;
        pPerso->propulsionToile();
    }
}
