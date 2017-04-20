#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED

#include "ExternalIncludes.h"

class TextManager
{
    public:
        TextManager();
        virtual ~TextManager();

        virtual void loadFont(std::string pFontFile, int pFontSize);

        virtual void setFont(std::string pFontFile);
        virtual void setFontSize(int pFontSize);
    protected:
        FT_Library mFTLib;
        FT_Face mFTFont;

        std::string mFontFile;
        unsigned int mFontSize;
};

struct textCharacter
{
    char mChar;
    FT_GlyphSlot mGlyph;

    GLuint mTexture;

    GLuint mVerticesVBO, mTextureVBO;
};

class TextLine : public TextManager
{
    public:
        TextLine();
        virtual ~TextLine();

        virtual void setText(std::string pText);
        virtual void setLocation(glm::vec2 pLocation);

        virtual void drawText(GLuint pShaderProgram, float pTimeElapsed, glm::vec4 pColor, glm::mat4 pView, glm::mat4 pProj);
    private:
        glm::mat4 mTranslateMat;
        std::vector<textCharacter> mListeTexte;
};

#endif
