#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
    mTexture = 0;
    mCurrentAnimation = 0;
    mImageInterval = 100;
    mTimeLastChange = 0;
}

AnimationManager::~AnimationManager()
{

}

void AnimationManager::loadFile(int pIntervalle, glm::vec2 pDimensionsAnim, glm::vec2 pDimensionsTotales, std::string pImgFile)
{
    mImageInterval = pIntervalle;

    for(int i = 0; i < pDimensionsTotales.y / pDimensionsAnim.y; ++i) /// Pour chaque rangée
    {
        AnimationCycle anim;
        anim.mNoActuel = 0;

        for(int j = 0; j < pDimensionsTotales.x / pDimensionsAnim.x; ++j) /// Pour chaque image
        {
            GLuint texBuffer;
            std::vector<glm::vec2> listePts;

            listePts.push_back(glm::vec2((j * pDimensionsAnim.x / pDimensionsTotales.x), 1 - ((i + 1) * pDimensionsAnim.y / pDimensionsTotales.y)));
            listePts.push_back(glm::vec2(((j + 1) * pDimensionsAnim.x / pDimensionsTotales.x), 1 - ((i + 1) * pDimensionsAnim.y / pDimensionsTotales.y)));
            listePts.push_back(glm::vec2((j * pDimensionsAnim.x / pDimensionsTotales.x), 1 - (i * pDimensionsAnim.y / pDimensionsTotales.y)));

            listePts.push_back(glm::vec2(((j + 1) * pDimensionsAnim.x / pDimensionsTotales.x), 1 - ((i + 1) * pDimensionsAnim.y / pDimensionsTotales.y)));
            listePts.push_back(glm::vec2((j * pDimensionsAnim.x / pDimensionsTotales.x), 1 - (i * pDimensionsAnim.y / pDimensionsTotales.y)));
            listePts.push_back(glm::vec2(((j + 1) * pDimensionsAnim.x / pDimensionsTotales.x), 1 - (i * pDimensionsAnim.y / pDimensionsTotales.y)));

            glGenBuffers(1, &texBuffer);

            glBindBuffer(GL_ARRAY_BUFFER, texBuffer);

            glBufferData(GL_ARRAY_BUFFER,
                        listePts.size() * sizeof(glm::vec2),
                        listePts.data(),
                        GL_DYNAMIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            anim.mBuffers.push_back(texBuffer);

            /*for(int k = 0; k < 6; ++k)
                std::cout << k << "\t" << listePts[k].x << "\t" << listePts[k].y << "\t" << texBuffer << std::endl;*/
        }
        mListeAnimations.push_back(anim);
    }

    mTexture = SOIL_load_OGL_texture(pImgFile.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(mTexture <= 0)
    {
        std::cout << "Erreur de chargement SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void AnimationManager::setCurrentAnimation(unsigned int pState)
{
    //mListeAnimations[mCurrentAnimation].mNoActuel = 0;
    mCurrentAnimation = pState;
}

void AnimationManager::updateAnimation(int pTimeElapsed)
{
    if(pTimeElapsed - mTimeLastChange >= mImageInterval)
    {
        mListeAnimations[mCurrentAnimation].mNoActuel += 1;
        mTimeLastChange = pTimeElapsed;

        if(mListeAnimations[mCurrentAnimation].mNoActuel >= mListeAnimations[mCurrentAnimation].mBuffers.size()) mListeAnimations[mCurrentAnimation].mNoActuel = 0;
    }
}

GLuint AnimationManager::getCurrentImageBuffer()
{
    return mListeAnimations[mCurrentAnimation].mBuffers[(mListeAnimations[mCurrentAnimation].mNoActuel)];
}
