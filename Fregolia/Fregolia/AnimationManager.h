#ifndef ANIMATIONMANAGER_H_INCLUDED
#define ANIMATIONMANAGER_H_INCLUDED

#include "ExternalIncludes.h"

struct AnimationCycle
{
    std::vector<GLuint> mBuffers;
    unsigned int mNoActuel;
};

class AnimationManager
{
    public:
        AnimationManager();
        virtual ~AnimationManager();

        virtual void loadFile(int pIntervalle, glm::vec2 pDimensionsAnim, glm::vec2 pDimensionsTotales, std::string pImgFile);

        virtual GLuint getCurrentImageBuffer(); /// Renvoie un buffer des coordonnées de texture
        virtual void setCurrentAnimation(unsigned int pState);
        virtual int getCurrentAnimation() {return mCurrentAnimation;}

        virtual GLuint getTexture() {return mTexture;}

        virtual void updateAnimation(int pTimeElapsed);

    private:
        std::vector<AnimationCycle> mListeAnimations;
        unsigned int mCurrentAnimation;
        unsigned int mImageInterval; /// MS

        unsigned int mTimeLastChange;

        GLuint mTexture;
};

#endif
