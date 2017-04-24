#ifndef HEALTHBAR_H_INCLUDED
#define HEALTHBAR_H_INCLUDED

#include "ExternalIncludes.h"
#include "LoadModel.h"

class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar() final;

        virtual void loadBar() final;
        virtual void updateHealth(float pPercent) final; /// ENTER 0 ET 1
        virtual void drawBar(GLuint pShaderProgram, int pTotalTime) final;

    private:
        imageModel mBackground;
        imageModel mHealth;


};

#endif // HEALTHBAR_H_INCLUDED
