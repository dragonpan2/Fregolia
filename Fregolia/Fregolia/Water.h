#ifndef WATER_H_INCLUDED
#define WATER_H_INCLUDED

#include "externalIncludes.h"

class Water
{
    public:
        Water();
        virtual ~Water();

<<<<<<< HEAD
        virtual void initWater(glm::vec2 pStart, glm::vec2 pEnd, int pResolution, float pViscosite, float pK) final; /// Vscosite ENTRE 0 ET 1
        virtual void actualiser(int pDeltaTemps) final;
        virtual void drawWater(GLuint pShaderProgram, glm::mat4 pView, glm::mat4 pProj) final;
        virtual void splashWater(float pRatio, float pIntensite) final; /// Intensite et ratio ENTRE 0 ET 1
    private:
        void genererGeometrie();

        float mViscosite, mK;
        float mHauteurInit;
        GLuint mVerticesVBO, mElementsBuffer;
        glm::mat4 mTranslateMat;
        std::vector<glm::vec3> mListePoints; /// X, Y, Vitesse;
        std::vector<int> mElements;
=======
        virtual void initWater(glm::vec2 pStart, glm::vec2 pEnd, int pResolution) final;
        virtual void drawWater(GLuint pShaderProgram, float pTimeElapsed, glm::mat4 pView, glm::mat4 pProj) final;
        virtual void splashWater(int pRatio, int pIntensite) final; /// Intensite et ratio ENTRE 0 ET 1
    private:
        void genererGeometrie();
        void calculerPosition(int pPoint);
        GLuint mVerticesVBO;
        std::vector<glm::vec4> mListePoints;
>>>>>>> origin/master
};

#endif // WATER_H_INCLUDED
