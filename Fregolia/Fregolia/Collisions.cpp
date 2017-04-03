#include "Collisions.h"

Collidable::Collidable()
{

}

Collidable::~Collidable()
{

}

bool Collidable::isCollision(Collidable* pOther)
{
    if(!checkOverlap(pOther)) return false;
    if(!pOther->checkOverlap(this)) return false;
    return true;
}

glm::vec2 Collidable::getCoin(int index)
{
    return mCoins[index];
}

bool Collidable::checkOverlap(Collidable* pOther)
{
    mMinDistance = 1000;

    /// Pour chaque axe
    for(int i = 0; i < 2; ++i)
    {
        float proj = glm::dot(pOther->getCoin(0), mAxes[i]);

        float minAutre = proj;
        float maxAutre = proj;

        /// Trouver le min et le max de l'autre BB pour cet axe (On commence a 1, car 0 est fait ci-dessus)
        for(int j = 1; j < 4; ++j)
        {
            proj = glm::dot(pOther->getCoin(j), mAxes[i]);

            if(proj < minAutre) minAutre = proj;
            else if(proj > maxAutre) maxAutre = proj;
        }

        /// Pour cet axe, on a le minimum et le maximum de l'autre BB.

        /// On veut maintenant voir s'il y a intersection entre les deux, i.e. si un des points de l'autre BB est entre les deux points de celui-ci.
        //std::cout << i << "LENGTH: " << glm::length(mAxes[i]) << std::endl;

        if(glm::dot(mCoins[0], mAxes[i]) > maxAutre || glm::dot(mCoins[0], mAxes[i]) + mAxesLongueur[i] < minAutre) return false;
        else if(maxAutre - glm::dot(mCoins[0], mAxes[i]) < mMinDistance)
        {
            mMinDistance = maxAutre - glm::dot(mCoins[0], mAxes[i]);
            mMinAxe = mAxes[i];
        }
    }

    /// Si tout a passe, il y a intersection (entendu qu'on arrive au meme resultat sur l'autre BB).
    return true;
}

glm::vec2 Collidable::getDeplacement(Collidable* pOther)
{
    if(mMinDistance <= pOther->getMinDistance()) {
        //std::cout << mMinDistance << "; " << mMinAxe.x << " " << mMinAxe.y << std::endl;
        return mMinDistance * mMinAxe;
    }
    else return pOther->getDeplacement(this) * -1.0f;
}

glm::vec2 Collidable::getDeplacement(Collidable* pOther, int b)
{
    if(b) {
        return mMinDistance * mMinAxe;
    }
    else return pOther->getDeplacement(this, 1) * -1.0f;
}
