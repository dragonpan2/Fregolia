#ifndef COLLISIONS_H_INCLUDED
#define COLLISIONS_H_INCLUDED

#include "externalIncludes.h"

/// Collisions utilisent le SAT (Separating Axis Theorem).

class Collidable
{
    public:
        Collidable();
        ~Collidable();

        virtual bool isCollision(Collidable* pOther);
        virtual bool checkOverlap(Collidable* pOther);
        virtual glm::vec2 getCoin(int index);
        virtual glm::vec2 getDeplacement(Collidable* pOther);
        virtual float getMinDistance() {return mMinDistance;}

    protected:
        glm::vec2 mCoins[4]; /// ORDONNES EN SENS HORAIRE, EN PARTANT DU COIN EN HAUT A GAUCHE
        glm::vec2 mAxes[2]; /// DEUX COTES PERPENDICULAIRES DU RECTANGLE
        float mAxesLongueur[2];

        float mMinDistance; /// Dist minimum pour resoudre la derniere collision verifiee
        glm::vec2 mMinAxe; /// Axe de la meme distance
};

#endif // COLLISIONS_H_INCLUDED
