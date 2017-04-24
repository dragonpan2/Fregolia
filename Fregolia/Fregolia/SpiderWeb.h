#ifndef SPIDERWEB_H
#define SPIDERWEB_H
#include "PhysicActor.h"
#include "Personnage.h"

class SpiderWeb : public PhysicActor
{
    public:
        SpiderWeb();
        virtual ~SpiderWeb();
        virtual void processusToile(Personnage* pPerso);
        virtual void changerAngle(Personnage* pPerso, int pDir);
        virtual void collisionToile();
        virtual void lancerPerso(Personnage* pPerso);

    protected:

    private:
        int compteurToile = 0;
        int compteurLancee = 0;
        bool finToile = false;
        bool mCollision = false;
};

#endif // SPIDERWEB_H
