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
    mMinDistance = 1000000;

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
        else
        {
            if(abs(maxAutre - glm::dot(mCoins[0], mAxes[i])) < abs(mMinDistance))
            {
                mMinDistance = abs(maxAutre - glm::dot(mCoins[0], mAxes[i]));
                mMinAxe = mAxes[i];
            }

            if(abs(glm::dot(mCoins[0], mAxes[i]) + mAxesLongueur[i] - minAutre) < abs(mMinDistance))
            {
                mMinDistance = abs(glm::dot(mCoins[0], mAxes[i]) + mAxesLongueur[i] - minAutre) * -1.000000001f;
                mMinAxe = mAxes[i];
            }
        }
    }

    /// Si tout a passe, il y a intersection (entendu qu'on arrive au meme resultat sur l'autre BB).
    return true;
}

glm::vec2 Collidable::getDeplacement(Collidable* pOther)
{
    if(abs(mMinDistance) <= abs(pOther->getMinDistance())) {
        return mMinDistance * mMinAxe;
    }
    else
    {
        return pOther->getDeplacement(this) * -1.0f;
    }

    /*if(abs(mMinDistance) <= abs(pOther->getMinDistance())) {
        std::cout << "PLAYER: " << mMinDistance << "; " << mMinAxe.x << " " << mMinAxe.y << std::endl;
        return mMinDistance * mMinAxe;
    }
    else
    {
        glm::vec2 d = pOther->getDeplacement(this) * -1.0f;
        std::cout << "OTHER: " << sqrt(pow(d.x, 2) + pow(d.y, 2)) << "; " << glm::normalize(d).x << " " << glm::normalize(d).y << std::endl;
        return pOther->getDeplacement(this) * -1.0f;
    }*/

    /*if(abs(mMinDistance) < abs(pOther->getMinDistance())) {
        std::cout << "PLAYER: " << mMinDistance << "; " << mMinAxe.x << " " << mMinAxe.y << std::endl;
        return mMinDistance * mMinAxe;
    }
    else
    {
        glm::vec2 d = pOther->getDeplacement(this, 1) * -1.0f;
        std::cout << "OTHER: " << glm::length(d) << "; " << glm::normalize(d).x << " " << glm::normalize(d).y << std::endl;
        return pOther->getDeplacement(this, 1) * -1.0f;
    }*/
}

glm::vec2 Collidable::getDeplacement(Collidable* pOther, int b)
{
    if(b) {
        return mMinDistance * mMinAxe;
    }
    else return pOther->getDeplacement(this, 1) * -1.0f;
}
